#pragma once
#include <lcom/lcf.h>

void (timer_int_handler)();

int (timer_subscribe_int)(uint8_t *timer_bit_no);

int (timer_unsubscribe_int)();

