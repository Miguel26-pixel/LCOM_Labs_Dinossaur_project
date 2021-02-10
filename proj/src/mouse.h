#pragma once
#include <lcom/lcf.h>

/**
 * @author Tiago Rodrigues
 * @defgroup mouse Mouse Properties
 * All functions realted to the mouse feature
 * @{
 */

/**
 * @brief Enable stream mode 
 */
int (mouse_enable_report)();

/**
 * @brief Subscribe mouse interruption
 */
int (mouse_subscribe_int)(uint8_t *mouse_bit_no);

/**
 * @brief Unsubscribe mouse interruption
 */
int (mouse_unsubscribe_int)();

/**
 * @brief Mouse Interrupt Handler
 */
void (mouse_ih)();

/**
 * @brief Read the data coming from Keyboard Controller
 *
 * @param mouse_scan data from Keyboard Controller
 */
void (mouse_read_byte)(uint8_t mouse_scan);

/**
 * @brief Disable Stream mode
 */
int (mouse_disable_report)();

/**
 * @brief Checks if left button is pressed
 */
bool (left_button)();

/**
 * @brief Checks if right button is pressed
 */
bool (right_button)();

/**
 * @brief Return delta x
 */
int16_t (delta_x)();

/**
 * @brief Return delta y
 */
int16_t (delta_y)();

/**
 * @brief Clear packet
 */
void (clearPP)();

/**
 * @}
 */
