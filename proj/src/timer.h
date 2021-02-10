#pragma once
#include <lcom/lcf.h>

/**
 * @author Tiago Rodrigues
 * @defgroup timer Timer Properties
 * All functions related to the timer
 * @{
 */

/**
 * @brief Timer interrupt handler
 */
void (timer_int_handler)();

/**
 * @brief Subscribe the timer interruption
 */
int (timer_subscribe_int)(uint8_t *timer_bit_no);

/**
 * @brief Unsubscribe the timer interruption
 */
int (timer_unsubscribe_int)();

/**
 * @}
 */
