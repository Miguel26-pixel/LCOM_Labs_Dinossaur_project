#pragma once
#include <lcom/lcf.h>
#include "i8042.h"

/**
 * @author Luísa Marques
 * @defgroup rtc RTC Properties
 * All function related to the internal clock feature to read data information, to save on files and to generate periodic alarms
 * @{
 */

/**
 * @brief Writes to a Address register
 *
 * @param reg value to write
 */
int rtc_write_cmd(uint8_t reg);

/**
 * @brief Read the command from the adress
 *
 * @param data Reads the data
 */
int rtc_read_cmd(uint8_t *data);

int rtc_reg_data(uint8_t reg, uint8_t *data);

/**
 * @brief Return the real year
 *
 * @return year
 */
int rtc_year();

/**
 * @brief Return the real month
 *
 * @return month
 */
int rtc_month();

/**
 * @brief Return the real day
 *
 * @return day
 */
int rtc_day();

/**
 * @brief Return the real hour
 *
 * @return hour
 */
int rtc_hour();

/**
 * @brief Return the real minute
 *
 * @return minutes
 */
int rtc_minute();

/**
 * @brief Return the real second
 *
 * @return second
 */
int rtc_second();

/**
 * @brief Reads and Prints the data
 */
void char_date(char *date);

/**
 * @}
 */

