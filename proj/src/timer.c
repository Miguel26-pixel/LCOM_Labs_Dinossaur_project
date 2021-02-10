#include <lcom/lcf.h>
#include "timer.h"
#include "i8042.h"

int past_time = 0;

int score_counter = 0;

int past_counter = 0;

int timer_hook_id=0;

void (timer_int_handler)(){
  past_time++;
  past_counter++;
  score_counter++;
}

int (timer_subscribe_int)(uint8_t *timer_bit_no) {

  *timer_bit_no = BIT(timer_hook_id);

  return sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &timer_hook_id);
}

int (timer_unsubscribe_int)() {

  return sys_irqrmpolicy(&timer_hook_id);
}

