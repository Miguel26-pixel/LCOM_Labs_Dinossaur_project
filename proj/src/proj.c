// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>

#include <stdbool.h>
#include <stdint.h>

#include "sprite.h"
#include "while_game.h"


// Any header files included below this line should have been created by you

uint8_t kbc_bit_no=1;
uint8_t mouse_bit_no = 12;
uint8_t timer_bit_no = 0;
uint8_t rtc_bit_no=8;
extern User* high[3];
extern int high_sc[3];

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/proj/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/proj/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(proj_main_loop)(int argc, char *argv[]) {
  mem_mapping(0x11A);
  vg_init(0x11A);
  if(timer_subscribe_int(&timer_bit_no)) return !OK;
  if(mouse_enable_report()) return !OK;
  if(mouse_subscribe_int(&mouse_bit_no))return !OK;
  if(kbc_subscribe_int(&kbc_bit_no))return !OK;

  setBackground();

  while_game();

  
  vg_exit();
  if(kbc_unsubscribe_int())return !OK;
  if(mouse_unsubscribe_int())return !OK; 
  if(mouse_disable_report()) return !OK;
  if(timer_unsubscribe_int())return !OK;
  return OK;
}
