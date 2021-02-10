#pragma once
#include <lcom/lcf.h>

void (kbc_ih)();
void (kbc_read_data)(uint8_t data);
void (timer_int_handler)();


int (kbc_subscribe_int)(uint8_t *bit_no);
int (timer_subscribe_int)(uint8_t *bit_no);
int (kbc_unsubscribe_int)();

