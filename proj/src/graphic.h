#pragma once
#include <lcom/lcf.h>
#include "keyboard.h"
#include <math.h>

/**
 * @author Miguel Amorim
 * @defgroup graphics Graphics Properties
 * All functions related to the video card feature, all prints, VBE functions
 * @{
 */

/**
 * @brief Map the memory
 */
void *(mem_mapping)(uint16_t mode);

/** 
 * @brief Initializes with vbe call
 */
void *(vg_init)(uint16_t mode);

/**
 * @brief Initialize the VBE
 */
void *(vg_rec_init)(uint16_t mode);

/**
 * @brief Draw an horizontal line
 *
 * @param x x position
 * @param y y position
 * @param len length
 * @param color color
 */
int (vg_draw_hline)(uint16_t x,uint16_t y,uint16_t len,uint32_t color);

/**
 * @brief Draw an rectangle
 *
 * @param x x position
 * @param y y position
 * @param width width 
 * @param height height
 * @param color color
 */
int (vg_draw_rectangle)(uint16_t 	x,uint16_t 	y,uint16_t 	width,uint16_t 	height,uint32_t color);	

/**
 * @brief Color an pixel
 *
 * @param x x position
 * @param y y position
 * @param color color
 */
int (vg_draw_pixel)(uint16_t x , uint16_t y , uint32_t color);

/**
 * @brief Esc to quit graphics mode
 */
int esc_exit();

/**
 * @brief Return horizontal resolution
 */ 
uint16_t getHR();

/**
 * @brief Return vertical resolution
 */ 
uint16_t getVR();

/**
 * @brief Return Bytes per pixel
 */
uint16_t getBYTES();

/**
 * @brief Return temp video memory
 */
void* getTEMP_VIDEO();

/**
 * @brief Draw a pixmap
 *
 * @param x x position
 * @param y y position
 * @param img pixmap
 * @param pixel_pointer color
 */
void print_pixmap(uint16_t x, uint16_t y,xpm_image_t* img, uint8_t *pixel_pointer);

/**
 * @brief Video memory
 */
void* getVIDEO();


/**
 * @brief Set the background with color
 *
 * @param color color
 */
void background_color(uint32_t color);

/**
 * @brief Draw a pixmap without the the background
 *
 * @param x x position
 * @param y y position
 * @param img image to draw
 * @param pixel_pointer color
 */
void print_whitout_back(uint16_t x, uint16_t y,xpm_image_t* img, uint8_t *pixel_pointer);

/**
 * @brief Check the collision between dinossaur and and pixmap
 *
 * @param x_dino x position of dinossaur
 * @param y_dino y position of dinossaur
 * @param img_dino pixmap of dino
 * @param pixel_pointer color
 */
bool collision(uint16_t x_dino, uint16_t y_dino, xpm_image_t* img_dino, uint8_t *pixel_pointer);

/**
 * @brief Bios Call function that changes buffer to double buffer
 */
void PageFlipping();

/**
 * @brief Set the background to White color
 */
void(setBackground)();

/**
 * @brief Clean the memory of temporary video memory
 */
void clear_temp_video_mem();

/**
 * @brief Set the temporary video memory
 */
void draw_temp_video_mem();


/**
 * @}
 */

