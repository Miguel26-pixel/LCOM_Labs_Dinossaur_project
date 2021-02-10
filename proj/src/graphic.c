#include "graphic.h"
#include "utils.h"
#include "i8042.h"


extern enum xpm_image_type type;

extern int ipc_status;
extern message msg;
extern int r;
extern uint8_t kbc_bit_no;

static char *video_mem = 0;
char* temp_video_mem;
static vbe_mode_info_t mode_info;

uint16_t xres;
uint16_t yres;

extern uint8_t scancode;

static uint16_t bitspp;
static uint16_t bytespp;
static uint8_t RedMaskSize, RedFieldPosition, GreenMaskSize, GreenFieldPosition, BlueMaskSize, BlueFieldPosition;
unsigned int vram_size;

static struct minix_mem_range mem;

bool current_video = false;

bool usepf = true;

void* mem_mapping(uint16_t mode){
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
	
  unsigned int vram_base = mode_info.PhysBasePtr;
	vram_size= mode_info.XResolution * mode_info.YResolution * bytespp*2;

	mem.mr_base = (phys_bytes) vram_base;

	mem.mr_limit = mem.mr_base + vram_size;

  if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mem)))
  panic("sys_privctl (ADD_MEM) failed: %d\n", r);


	video_mem = vm_map_phys(SELF, (void *)mem.mr_base,vram_size);
  temp_video_mem = malloc(vram_size);


	if(video_mem == MAP_FAILED)
		panic("couldn't map video memory");

  
  return temp_video_mem;

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
}


int (vg_draw_pixel)(uint16_t x , uint16_t y , uint32_t color){
	
  uint8_t *adr = (uint8_t *)temp_video_mem;

	adr += (xres * y * bytespp);
	adr += (x * bytespp);

  memcpy(adr,&color,bytespp);

	return 0;

}

int (vg_draw_hline)(uint16_t x,uint16_t y,uint16_t len,uint32_t color){
  uint16_t x_max = min(mode_info.XResolution,x+len);
  for (uint16_t i=x;i<x_max;i++){
    vg_draw_pixel(i,y,color);
  }
  return 0;
}


void print_pixmap(uint16_t x, uint16_t y,xpm_image_t* img, uint8_t *pixel_pointer){
  uint16_t y_max = min(getVR(),y+img->height);
  uint16_t x_max = min(getHR(),x+img->width);

  for (uint16_t px_y = y; px_y < y_max; px_y++){
    for(uint16_t px_x = x; px_x < x_max; px_x++){
      uint8_t *addr = (uint8_t *) temp_video_mem + px_x*bytespp + px_y*xres*bytespp;
      memcpy(addr,pixel_pointer+(px_x-x)*bytespp + (px_y-y)*img->width*bytespp,bytespp);
    }
  }
}

void print_whitout_back(uint16_t x, uint16_t y,xpm_image_t* img, uint8_t *pixel_pointer){ 
  uint16_t y_max = min(getVR(),y+img->height);
  uint16_t x_max = min(getHR(),x+img->width);

  for (uint16_t px_y = y; px_y < y_max; px_y++){
    for(uint16_t px_x = x; px_x < x_max; px_x++){
      if(*(pixel_pointer+(px_x-x)*bytespp + (px_y-y)*img->width*bytespp)==0x00){
      uint8_t *addr = (uint8_t *) temp_video_mem + px_x*bytespp + px_y*xres*bytespp;
      memcpy(addr,pixel_pointer+(px_x-x)*bytespp + (px_y-y)*img->width*bytespp,bytespp);}
    }
  }
}

bool collision(uint16_t x_dino, uint16_t y_dino, xpm_image_t* img_dino, uint8_t *pixel_pointer){
  uint16_t y_max = min(458,y_dino+img_dino->height);
  uint16_t x_max = min(getHR(),x_dino+img_dino->width);

  for (uint16_t px_y = y_dino; px_y < y_max-1; px_y++){
    for(uint16_t px_x = x_dino; px_x < x_max; px_x++){
      if(*(pixel_pointer+(px_x-x_dino)*bytespp + (px_y-y_dino)*img_dino->width*bytespp)==0x00){
        uint8_t *addr = (uint8_t *) temp_video_mem + px_x*bytespp + px_y*xres*bytespp;
        if(*addr==0x00)
          return true;
      }
    }
  }

  return false;
}

uint16_t getHR(){
  return xres;
}

uint16_t getVR(){
  return yres;
}

uint16_t getBYTES(){
  return bytespp;
}

void* getVIDEO(){
  return video_mem;
}

void* getTEMP_VIDEO(){
  return temp_video_mem;
}

void PageFlipping() {
  if (!usepf) {
    memcpy(video_mem, temp_video_mem, getVR() * getHR() * getBYTES());
  }
  else {

    struct reg86 reg;
    memset(&reg, 0, sizeof(reg));
    reg.intno = 0x10; // 10
    reg.ax = 0x4F07; // 4F07
    reg.dx = current_video * getVR();

    if (sys_int86(&reg) != OK) {
      printf("Error page Flipping\n");
      return;
    }

    current_video ^= 1;
    temp_video_mem = video_mem + getVR() * getHR() * getBYTES() * current_video;
  }
  clear_temp_video_mem();
}

void background_color(uint32_t color){
  memset(temp_video_mem, color, bytespp * xres * yres);
}

void(setBackground)(){  
  background_color(WHITE);
  vg_draw_hline(0, 500, getHR(),BLACK);
}

void clear_temp_video_mem() {
	memset(temp_video_mem, 0, bytespp * getHR() * getVR());
}

void draw_temp_video_mem() {
	memcpy(video_mem, temp_video_mem, vram_size);
}

