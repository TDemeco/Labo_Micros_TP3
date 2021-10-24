/***************************************************************************//**
  @file     gpio.h
  @brief    Simple GPIO Pin services, similar to Arduino
  @author   Nicolás Magliola
 ******************************************************************************/

#ifndef _SEVENSEG_H_
#define _SEVENSEG_H_
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

typedef enum {DISPLAY_LEFT, DISPLAY_RIGHT, DISPLAY_SCROLL, MODES_SEVENSEG_CANT} sevenseg_modes;

/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

void display_init(void);
void display_text(char* text, sevenseg_modes mode, uint8_t blinking_char);
void display_refresh(void);
void display_intensity(uint8_t intensity);
void display_clear(void);

/*******************************************************************************
 ******************************************************************************/

#endif // _SEVENSEG_H_

