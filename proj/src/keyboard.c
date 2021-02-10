#include <lcom/lcf.h>
#include "keyboard.h"
#include "i8042.h"

uint8_t scancode; //scancode initialized

uint8_t scan_array[2]; //array of scans, used when the scancode has more than 8 bits

bool complete;

uint8_t size;

int kbc_hook_id=1;


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
}

void (kbc_ih)(){
  uint8_t status = 0;

  util_sys_inb(STATUS_PORT, &status);

  if (status & 0x01) {
    util_sys_inb(KBD_OUT_BUF, &scancode);

    if((status & 0xC0) != 0)
      return;
    
    kbc_read_data(scancode);
  }
}

int (kbc_subscribe_int)(uint8_t *kbc_bit_no) {
  
  *kbc_bit_no = BIT(kbc_hook_id);

  return sys_irqsetpolicy(KBC_IRQ1, IRQ_REENABLE|IRQ_EXCLUSIVE, &kbc_hook_id);
}

int (kbc_unsubscribe_int)() {
  return sys_irqrmpolicy(&kbc_hook_id);
}


