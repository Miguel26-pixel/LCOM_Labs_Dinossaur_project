#include "graphic.h"
#include "utils.h"
#include "i8042.h"

static void *video_mem = 0;
static vbe_mode_info_t mode_info;

uint16_t xres;
uint16_t yres;

extern uint8_t scancode;

static uint16_t bitspp;
static uint16_t bytespp;
static uint8_t RedMaskSize, RedFieldPosition, GreenMaskSize, GreenFieldPosition, BlueMaskSize, BlueFieldPosition;

static struct minix_mem_range mem;

void mem_mapping(uint16_t mode){
  int r = 0;
	
	memset(&mem, 0, sizeof(mem));

	if(vbe_get_mode_info(mode, &mode_info)!=0)
  {
    printf("Failed to get vbe info\n");
  }


  bitspp = mode_info.BitsPerPixel;
	bytespp = (bitspp+7)/8;

	RedMaskSize = mode_info.RedMaskSize;
	GreenMaskSize = mode_info.GreenMaskSize;
	BlueMaskSize = mode_info.BlueMaskSize;

	RedFieldPosition = mode_info.RedFieldPosition;
	GreenFieldPosition = mode_info.GreenFieldPosition;
	BlueFieldPosition = mode_info.BlueFieldPosition;

	xres = mode_info.XResolution;
	yres = mode_info.YResolution;
	bitspp = mode_info.BitsPerPixel;
	bytespp = ceil(bitspp / 8);
	
  unsigned int vram_base = mode_info.PhysBasePtr;
	unsigned int vram_size= mode_info.XResolution * mode_info.YResolution * bitspp;

	mem.mr_base = (phys_bytes) vram_base;

	mem.mr_limit = mem.mr_base + vram_size;

  if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mem)))
  panic("sys_privctl (ADD_MEM) failed: %d\n", r);


	video_mem = vm_map_phys(SELF, (void *)mem.mr_base,vram_size);
	

	if(video_mem == MAP_FAILED)
		panic("couldn't map video memory");

}

void *(vg_init)(uint16_t mode){
	/* Specify the appropriate register values */
  struct reg86 r86;

	memset(&r86, 0, sizeof(r86));	/* zero the structure */
		
	r86.intno = 0x10; /* BIOS video services */
	r86.ah = 0x4F;
	r86.al = 0x02; // VBE call, function 02 -- set VBE mode
	r86.bx = mode | BIT(14);
  

	/* Make the BIOS call */
	

	if( sys_int86(&r86) != OK ) {
		printf("\tvg_exit(): sys_int86() failed \n");
	}
  return video_mem;
	return video_mem;
}


int (vg_draw_pixel)(uint16_t x , uint16_t y , uint32_t color){
	/*
	memcpy(video_mem + ((y * xres + x) * bytespp), &color, bytespp);
	return 0;
	*/
	
  uint8_t cl = (uint8_t) color;
  //uint32_t pos = (y * mode_info.XResolution + x)*(mode_info.BytesPerScanLine/mode_info.XResolution);
  uint8_t* m = (uint8_t*) video_mem + (mode_info.BytesPerScanLine/mode_info.XResolution) * (x + y * mode_info.XResolution);

  *m = cl;
  return 0;
}

int (vg_draw_hline)(uint16_t x,uint16_t y,uint16_t len,uint32_t color){
	/*
	for (int i = 0; i < len; i++) {
		if(x + i >= xres) break;
        memcpy(video_mem + ((y * xres + (x + i)) * bytespp), &color, bytespp);
    }
	return 0;
	*/
	
  uint16_t x_max = min(mode_info.XResolution,x+len);
  for (uint16_t i=x;i<x_max;i++){
    vg_draw_pixel(i,y,color);
  }
  return 0;
}

uint8_t decompose_color(uint32_t color, unsigned mask_size, unsigned field_position) {
	uint32_t temp = color >> field_position;

	uint32_t mask = pow(2, mask_size) - 1;

	return (uint8_t)(temp & mask);
}

void color_setup(uint32_t* color, unsigned row, unsigned column, uint8_t no_rectangles, uint32_t first, uint8_t step)
{
	if (bitspp== 8) { // Indexed mode
		*color = (first + (row * no_rectangles + column) * step) % (1 << bitspp);
	}
	else // Direct mode
	{
		uint8_t red_bits = decompose_color(first, RedMaskSize, RedFieldPosition);
		uint8_t green_bits = decompose_color(first, GreenMaskSize, GreenFieldPosition);
		uint8_t blue_bits = decompose_color(first, BlueMaskSize, BlueFieldPosition);

		uint32_t red = (red_bits + column * step) % (1 << RedMaskSize);
		uint32_t green = (green_bits + column * step) % (1 << GreenMaskSize);
		uint32_t blue = (blue_bits + column * step) % (1 << BlueMaskSize);

		*color = (red << RedFieldPosition) | (green << GreenFieldPosition) | (blue << BlueFieldPosition);
	}
}


int esc_exit(){
  int ipc_status;
  message msg;
  uint8_t kbc_bit_no = 1;
  kbc_subscribe_int(&kbc_bit_no);
  do {                                                            //the input to stop is the esc key
        int r;
        if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
            printf("driver_receive failed with: %d", r);
            continue;
        }

        if (is_ipc_notify(ipc_status)) {                            /* received notification */
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE:                                      /* hardware interrupt notification */				
                    if (msg.m_notify.interrupts & kbc_bit_no) {    /* subscribed interrupt */
                      uint8_t status = 0;

                      util_sys_inb(STATUS_PORT, &status);

                      if (status & 0x01) {
                        util_sys_inb(KBD_OUT_BUF, &scancode);
                        printf("%d",scancode);
                        if((status & 0xC0) != 0)
                          break;
                                            
                      }  
                    }
                    break;
                default:
                    break;                                          /* no other notifications expected: do nothing */	
            }
        } 
    }    
    while(scancode != 0x81); 
    kbc_unsubscribe_int();
    return 0;

}


uint32_t (index_color)(uint8_t row,uint8_t col,uint32_t first,uint8_t no_recs,uint8_t step) {
    return (first + (row * no_recs + col) * step) % (1 << bitspp);
}

void print_pixmap(uint16_t x, uint16_t y,xpm_image_t* img,uint8_t *pixel_pointer){
  uint16_t y_max = min(getHR(),y+img->height);
  uint16_t x_max = min(getVR(),x+img->width);
  unsigned int counter=0;
  for (uint16_t px_y = y ; px_y < y_max;px_y++){
    for(uint16_t px_x = x; px_x < x_max;px_x++){
      vg_draw_pixel(px_x,px_y,pixel_pointer[counter]);
      counter++;
    }
  }
}

void clean_minix(){
  uint8_t i;
    // Clear the screen by drawing 'black' in every pixel
    uint8_t *ptr = (uint8_t*)video_mem ;
    uint8_t trans = xpm_transparency_color(XPM_INDEXED);
    for (i=0 ; i<xres*yres ; i++,ptr++){
        *ptr = trans;
    }
}

uint16_t getHR(){
  return xres;
}

uint16_t getVR(){
  return yres;
}

uint8_t getBYTES(){
  return bytespp;
}

void* getVIDEO(){
  return video_mem;
}

