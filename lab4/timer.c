#include <lcom/lcf.h>
#include "timer.h"
#include "i8042.h"

int past_time = 0;

int timer_hook_id=0;

void (timer_int_handler)(){
  past_time++;
}

int (timer_subscribe_int)(uint8_t *timer_bit_no) {

  *timer_bit_no = BIT(timer_hook_id);

  sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &timer_hook_id);

  return 0;
}

int (timer_unsubscribe_int)() {

  sys_irqrmpolicy(&timer_hook_id);

  return 0;
}
