#pragma once
#include <lcom/lcf.h>

/**
 * @author Miguel Amorim
 * @defgroup keyboard Keyboard Properties
 * All functions related to the keyboard feature
 * @{
 */

/**
 * @brief Keyboard interrupt handler
 */
void (kbc_ih)();

/**
 * @brief Read the keyboard data
 *
 * @param data 
 */
void (kbc_read_data)(uint8_t data);

/**
 * @brief Subscribe the keyboard interruption
 *
 * @param bit_no 
 */
int (kbc_subscribe_int)(uint8_t *bit_no);

/**
 * @brief Unsubscribe the keyboard interruption
 */
int (kbc_unsubscribe_int)();

