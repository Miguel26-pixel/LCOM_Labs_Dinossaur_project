#ifndef _FILE_H_
#define _FILE_H_

#include <lcom/lcf.h>
#include "user.h"

/**
 * @author Tiago Rodrigues
 * @defgroup file File Properties
 * All functions related txt files
 *
 * @{
 */

/**
 * @brief Reads the high score from a file
 */
void read_file();

/**
 * @brief Writes the high score to file
 */
void write_file();

/**
 * @}
 */

#endif //_FILE_H_
