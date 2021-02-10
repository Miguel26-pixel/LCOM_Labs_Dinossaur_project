#pragma once
#include <lcom/lcf.h>

/**
 * @author Tiago Rodrigues
 * @defgroup utils Utils Functions
 * Some funtions related to help feature on other functions
 * @{
 */

/**
 * @brief Return minimum between 2 values
 *
 * @param all values
 *
 * @return minimum value
 */
int min(int x, int y);


/**
 * @brief Return maximum between 2 values
 *
 * @param all values
 *
 * @return maximum value
 */
int max(int x, int y);

/**
 * @brief Gives us the Least Signicant Bytes
 *
 * @param val Value to analize
 * @param lsb Least Significant bytes
 */
int(util_get_LSB)(uint16_t val, uint8_t *lsb);

/**
 * @brief Gives us the Most Signicant Bytes
 *
 * @param val Value to analize
 * @param msb Most Significant bytes
 */
int(util_get_MSB)(uint16_t val, uint8_t *msb);

/**
 * @brief Help with the command sys_inb
 */
int(util_sys_inb)(int port, uint8_t *value);

/**
 * @}
 */
