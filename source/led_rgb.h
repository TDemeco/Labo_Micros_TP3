/***************************************************************************//**
  @file     gpio.h
  @brief    Simple GPIO Pin services, similar to Arduino
  @author   Nicolás Magliola
 ******************************************************************************/

#ifndef _LED_RGB_H_
#define _LED_RGB_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <stdbool.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

typedef enum {BLACK,RED,BLUE,GREEN,CYAN,YELLOW,MAGENTA,WHITE} led_color;

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/


/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

void init_led(void);
void change_led_state(led_color color);

/*******************************************************************************
 ******************************************************************************/

#endif