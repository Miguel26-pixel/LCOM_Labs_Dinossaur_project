#pragma once
#include <lcom/lcf.h>
#include "keyboard.h"
#include <math.h>


void mem_mapping(uint16_t mode);

void *(vg_init)(uint16_t mode);

void *(vg_rec_init)(uint16_t mode);

int (vg_draw_hline)(uint16_t x,uint16_t y,uint16_t len,uint32_t color);

int (vg_draw_rectangle)(uint16_t 	x,uint16_t 	y,uint16_t 	width,uint16_t 	height,uint32_t color);	

int vg_draw_pixel(uint16_t x , uint16_t y , uint32_t color);

void *(vbe_get_video_mem)();

int esc_exit();

void color_setup(uint32_t* color, unsigned row, unsigned column, uint8_t no_rectangles, uint32_t first, uint8_t step);

uint8_t decompose_color(uint32_t color, unsigned mask_size, unsigned field_position);

uint16_t getHR();

uint16_t getVR();

uint8_t getBYTES();

void print_pixmap(uint16_t x, uint16_t y,xpm_image_t* img,uint8_t *pixel_pointer);

void* getVIDEO();

void clean_minix();

uint32_t (index_color)(uint8_t row,uint8_t col,uint32_t first,uint8_t no_recs,uint8_t step);

