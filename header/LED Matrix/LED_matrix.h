/***************************************************************************//**
  @file     gpio.h
  @brief    Simple GPIO Pin services, similar to Arduino
  @author   Nicolás Magliola
 ******************************************************************************/

#ifndef _LED_MATRIX_H_
#define _LED_MATRIX_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/



/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
typedef struct{
  uint8_t row;
  uint8_t col;
} led_pos_t;


typedef struct{
	uint8_t r;
	uint8_t g;
	uint8_t b;
} color_t;

/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

void LED_matrix_init(void);
void LED_matrix_set_rgb(uint8_t row, uint8_t col, uint8_t r,uint8_t g,uint8_t b);
void LED_matrix_set_color(uint8_t row, uint8_t col, color_t color);


/*******************************************************************************
 ******************************************************************************/

#endif // _LED_MATRIX_H_

