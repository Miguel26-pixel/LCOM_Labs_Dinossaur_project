#pragma once
#include <lcom/lcf.h>

int (mouse_enable_report)();

int (mouse_subscribe_int)(uint8_t *mouse_bit_no);

int (mouse_unsubscribe_int)();

void (mouse_ih)();

void (mouse_read_byte)(uint8_t mouse_scan);

int (mouse_disable_report)();

bool (left_button)();

bool (right_button)();

bool (deltaX)(uint8_t tolerance);

bool (deltaY)(uint8_t tolerance);

bool (left_state_func)(uint8_t x_len,uint8_t tolerance);

bool (middle_state_func)(uint8_t x_len,uint8_t tolerance);

bool (right_state_func)(uint8_t x_len,uint8_t tolerance);

void state_ih(uint8_t x_len,uint8_t tolerance);

bool (slope)();

