#pragma once
#include <lcom/lcf.h>
#include "keyboard.h"
#include "graphic.h"
#include "timer.h"
#include "user.h"
#include "file.h"
#include "xpm.h"
#include "utils.h"
#include "mouse.h"
#include "rtc.h"
#include "i8042.h"


/**
 * @author Miguel Amorim
 * @author Tiago Rodrigues
 * @defgroup sprite Sprites
 * All funtions related with moving sprites , spawn the obstacles, write on screen
 * @{
 */

/**
 * @brief Sprite to draw
 *
 * @param x x position
 * @param y y position
 * @param width width 
 * @param height height
 * @param xspeed speed on x axis
 * @param yspeed speed on y axis
 * @param pixel_pointer Colors
 * @param image pixmap that contains the image to draw
 */
typedef struct {
  int x, y;                   
  int width, height;          // dimensions
  int xspeed, yspeed;         // current speed
  uint8_t *pixel_pointer;     // colors
  xpm_image_t image;          // image
} Sprite;


/**
 * @brief Creates a new sprite
 *
 * @param x             x position
 * @param y             y position
 * @param xspeed        x speed
 * @param yspeed        y speed
 * @param width         width
 * @param height        heigth
 * @param pixel_pointer colors
 * @param image         image 
 *
 * @return Return the new sprite
 */
Sprite *create_sprite(int x, int y,int xspeed, int yspeed, int width, int height, uint8_t *pixel_pointer,xpm_image_t image);

/**
 * @brief Destroy a sprite
 *
 * @param sp sprite to remove
 */
void destroy_sprite(Sprite *sp);

/**
 * @brief Destroy all sprites
 *
 * @param all sprites to destroy
 */
void destroy_all(Sprite *cactus,Sprite *meteor,Sprite *cursor,Sprite *game_over,Sprite *dino_normal,Sprite *right_down,Sprite *left_down,Sprite *right,Sprite *left,Sprite *zero,Sprite *one,Sprite *two,Sprite *three,Sprite *four,Sprite *five,Sprite *six,Sprite *seven,Sprite *eight,Sprite *nine);


/**
 * @brief Draw the menu
 *
 * @param all sprites to draw
 */
void menu_handler(Sprite *spacebar,Sprite *no_spacebar, Sprite *a, Sprite *b, Sprite *c, Sprite *d, Sprite *e, Sprite *f, Sprite *g, Sprite *h, Sprite *i, Sprite *j, Sprite *k, Sprite *l, Sprite *m, Sprite *n, Sprite *o, Sprite *p, Sprite *q, Sprite *r, Sprite *s, Sprite *t, Sprite *u, Sprite *v, Sprite *w, Sprite *x, Sprite *y, Sprite *z, Sprite *zero, Sprite *one,Sprite *two,Sprite *three,Sprite *four,Sprite *five,Sprite *six,Sprite *seven,Sprite *eight,Sprite *nine);

/**
 * @brief Draw the dinossaur when is jumping
 *
 * @param all sprites to draw
 */
void jumpup(Sprite *dino_normal, Sprite *game_over);

/**
 * @brief Draw the dinossaur when is falling
 *
 * @param all sprites to draw
 */
void jumpdown(Sprite *dino_normal, Sprite *game_over);

/**
 * @brief Draw the dinossaur when is crouching
 *
 * @param all sprites to draw
 */
void down(Sprite *dino_normal, Sprite *game_over, Sprite *right_down, Sprite *left_down);

/**
 * @brief Draw the dinossaur with leg changes
 *
 * @param all sprites to draw
 */
void switch_leg(Sprite *dino_normal, Sprite *game_over, Sprite *right, Sprite *left);

/**
 * @brief Creates a new obstacle
 *
 * @param all obstacle to create
 */
void obstacles_spawn(Sprite *cactus,Sprite *meteor, Sprite *up_bird , Sprite *down_bird);

/**
 * @brief Draw the score
 *
 * @param all Numbers to draw the score
 */
void score(Sprite *zero, Sprite *one,Sprite *two,Sprite *three,Sprite *four,Sprite *five,Sprite *six,Sprite *seven,Sprite *eight,Sprite *nine);

/**
 * @brief Draw the nickname of highscore
 *
 * @param all Numbers and letter to draw the highscore
 */
void nickname(Sprite *a, Sprite *b, Sprite *c, Sprite *d, Sprite *e, Sprite *f, Sprite *g, Sprite *h, Sprite *i, Sprite *j, Sprite *k, Sprite *l, Sprite *m, Sprite *n, Sprite *o, Sprite *p, Sprite *q, Sprite *r, Sprite *s, Sprite *t, Sprite *u, Sprite *v, Sprite *w, Sprite *x, Sprite *y, Sprite *z, Sprite *zero, Sprite *one,Sprite *two,Sprite *three,Sprite *four,Sprite *five,Sprite *six,Sprite *seven,Sprite *eight,Sprite *nine);

/**
 * @brief Check if is the new high score
 *
 * @param sc Score to check if high score
 *
 * @return True if is the new high score
 */
bool new_record(int sc);

/**
 * @brief Insert new high score
 */
void insert_new_record(User *u);

/**
 * @brief Write text on screen
 * 
 * @param text text  to draw
 * @param xr x position
 * @param yr y position
 * @param all Letters to draw text
 */
int write_text_on_screen(char text[], int xr, int yr, Sprite *a, Sprite *b, Sprite *c, Sprite *d, Sprite *e, Sprite *f, Sprite *g, Sprite *h, Sprite *i, Sprite *j, Sprite *k, Sprite *l, Sprite *m, Sprite *n, Sprite *o, Sprite *p, Sprite *q, Sprite *r, Sprite *s, Sprite *t, Sprite *u, Sprite *v, Sprite *w, Sprite *x, Sprite *y, Sprite *z, Sprite *zero, Sprite *one,Sprite *two,Sprite *three,Sprite *four,Sprite *five,Sprite *six,Sprite *seven,Sprite *eight,Sprite *nine);

/**
 * @brief Write text on screen
 * 
 * @param number number to draw
 * @param xr x position
 * @param yr y position
 * @param all Numbers to draw text
 */
int write_int_on_screen(long int number, int xr, int yr, Sprite *zero, Sprite *one,Sprite *two,Sprite *three,Sprite *four,Sprite *five,Sprite *six,Sprite *seven,Sprite *eight,Sprite *nine);

/**
 * @brief Draw the high score
 *
 * @param all Numbers to draw the score
 */
void show_high_score(Sprite *zero, Sprite *one,Sprite *two,Sprite *three,Sprite *four,Sprite *five,Sprite *six,Sprite *seven,Sprite *eight,Sprite *nine);

/**
 * @brief Check and update new mouse position
 * 
 * @param cursor Draw a cursor on mouse
 */
void new_mouse_pos(Sprite *cursor, Sprite *meteor);

/**
 * @brief Change the state of games
 * 
 * @param all Sprites to draw
 */
bool state_h(Sprite *cactus,Sprite *meteor,Sprite *cursor,Sprite *game_over,Sprite *dino_normal,Sprite *right_down,Sprite *left_down,Sprite *right,Sprite *left,Sprite *a, Sprite *b, Sprite *c, Sprite *d, Sprite *e, Sprite *f, Sprite *g, Sprite *h, Sprite *i, Sprite *j, Sprite *k, Sprite *l, Sprite *m, Sprite *n, Sprite *o, Sprite *p, Sprite *q, Sprite *r, Sprite *s, Sprite *t, Sprite *u, Sprite *v, Sprite *w, Sprite *x, Sprite *y, Sprite *z, Sprite *zero, Sprite *one,Sprite *two,Sprite *three,Sprite *four,Sprite *five,Sprite *six,Sprite *seven,Sprite *eight,Sprite *nine);

/**
 * @}
 */ 

