#include <lcom/lcf.h>
#include "keyboard.h"
#include "i8042.h"

extern uint8_t scancode; //scancode initialized

extern uint8_t scan_array[2]; //array of scans, used when the scancode has more than 8 bits

extern bool complete;

extern uint8_t size;

int kbc_hook_id=1;

int timer_hook_id=0;

int past_time=0;

/*
void (kbc_read_data)(uint8_t data){
  if(data == FIRST_PART_OF_2_BYTES) scan_array[0] = data;                             //first byte its the 0xE0 part

  else if (scan_array[0] == FIRST_PART_OF_2_BYTES){  //second byte after 0xE0
    scan_array[1] = data;
    complete = true;
  }

  else {
    scan_array[0] = 0;
    scan_array[1] = data;
    complete = true;
  }
}*/
/*
void (kbc_ih)(){
  uint8_t status = 0;

  util_sys_inb(STATUS_PORT, &status);

  if (status & 0x01) {
    util_sys_inb(KBD_OUT_BUF, &scancode);

    if((status & 0xC0) != 0)
      return;
    
    kbc_read_data(scancode);
  }
}*/

int (kbc_subscribe_int)(uint8_t *kbc_bit_no) {
  
  //kbc_hook_id = *kbc_bit_no;
  *kbc_bit_no = BIT(kbc_hook_id);

  sys_irqsetpolicy(KBC_IRQ1, IRQ_REENABLE|IRQ_EXCLUSIVE, &kbc_hook_id);

  return 0;
}

int (kbc_unsubscribe_int)() {
  sys_irqrmpolicy(&kbc_hook_id);
  return 1;
}

int (timer_subscribe_int)(uint8_t *timer_bit_no) {

  //timer_hook_id = *timer_bit_no;
  *timer_bit_no = BIT(timer_hook_id);

  sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &timer_hook_id);

  return 0;
}

void (timer_int_handler)() {
  
  past_time++;  
}

int (timer_unsubscribe_int)() {
  sys_irqrmpolicy(&timer_hook_id);
  return 1;
}
