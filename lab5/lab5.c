// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>
#include <lcom/lab5.h>
#include "graphic.h"
#include "utils.h"
#include <stdint.h>
#include <stdio.h>
#include "keyboard.h"
#include "lcom/pixmap.h"


// Any header files included below this line should have been created by you
extern int kbc_hook_id;

extern int past_time;

extern int timer_hook_id;

uint8_t scancode = 0x00;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/g05/lab5/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/g05/lab5/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(video_test_init)(uint16_t mode, uint8_t delay) {
	mem_mapping(mode);
	vg_init(mode);
	sleep(delay);
	vg_exit();
	return 0;
}



int(video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y,
                          uint16_t width, uint16_t height, uint32_t color) {
	mem_mapping(mode);
	vg_init(mode);
	vg_draw_rectangle(x,y,width,height,color);
	if(esc_exit()==0)	
		vg_exit();	
	return 0;
}

int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {
  mem_mapping(mode);
	vg_init(mode);

  uint32_t color; // Color at any given time
	uint16_t horirec = (uint16_t)(getHR()/no_rectangles);
	uint16_t vertrec = (uint16_t)(getVR()/no_rectangles);
	
	for(uint8_t row = 0; row < no_rectangles; row++){
		for(uint8_t col = 0; col < no_rectangles; col++){
			color_setup(&color, row, col, no_rectangles, first, step);

      vg_draw_rectangle(row * horirec, col * vertrec, horirec, vertrec, color);
    }
  }
	if(esc_exit()==0)	
		vg_exit();	
	return 0;

}

int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {
  mem_mapping(0x105);
  vg_init(0x105);
  enum xpm_image_type type = XPM_INDEXED;
  xpm_image_t img;
  uint8_t *pixel_pointer= xpm_load(xpm,type,&img);
  print_pixmap(x,y,&img,pixel_pointer);
  if(esc_exit()==0)	
		vg_exit();
  return 0;
}

int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf,
                     int16_t speed, uint8_t fr_rate) {
  mem_mapping(0x105);
  vg_init(0x105);
  int r;
  message msg;
	int ipc_status;
  enum xpm_image_type type = XPM_INDEXED;
  xpm_image_t img;
  bool h_v = xi==xf;
  uint8_t *pixel_pointer= xpm_load(xpm,type,&img);
  uint16_t temp_x = xi, temp_y= yi;
  uint16_t  delta= speed/fr_rate;
  uint8_t timer_bit_no = 0;

  timer_subscribe_int(&timer_bit_no);
  print_pixmap(temp_x,temp_y,&img,pixel_pointer);
  //clean_();
  while (temp_x!=xf || temp_y!=yf){
        
        if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
            printf("driver_receive failed with: %d", r);
            continue;
        }

        if (is_ipc_notify(ipc_status)) {                            /* received notification */
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE:                                      /* hardware interrupt notification */	
                    if (msg.m_notify.interrupts & timer_bit_no)	{
                        timer_int_handler();
                        if(past_time/60==1/fr_rate){
                          past_time=0;
                          //clean_minix();
                          if(!h_v){
                            temp_x += delta;
                            print_pixmap(temp_x,temp_y,&img,pixel_pointer);
                          }
                          else{
                            temp_y += delta;
                            print_pixmap(temp_x,temp_y,&img,pixel_pointer);
                          }
                        }
                    }		
                    break;
                default:
                    break;                                          /* no other notifications expected: do nothing */	
            }
            //tickdelay(micros_to_ticks(DELAY_US));
        }   
  }
  timer_unsubscribe_int();
  if(esc_exit()==0)	
		vg_exit();
  return 0;

}

int(video_test_controller)() {
  /* To be completed */
  printf("%s(): under construction\n", __func__);

  return 1;

}

