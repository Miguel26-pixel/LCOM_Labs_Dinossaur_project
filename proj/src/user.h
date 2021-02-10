#pragma once
#include <lcom/lcf.h>

/**
 * @author Luísa Marques
 * @defgroup user User Properties
 * Struct User to save information, like the score, name and date
 * @{
 */

/**
 * @brief User that contains the high score
 *
 * @param date day / month / year
 * @param name name
 * @param sc score
 */
typedef struct {
  char date[10];
  char name[5];
  long int sc ;
} User;

/**
 * @brief Create an User to set the new highscore
 *
 * @param name Name
 * @param data day / month / year
 * @param sc score
 */
User *create_user(char name[5],char d[10], long int sc);

/**
 * @brief Destroy an user
 *
 * @param u User to destroy
 */ 
void destroy_user(User *u);

/**
 * @}
 */
