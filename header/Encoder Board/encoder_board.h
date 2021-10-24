/***************************************************************************//**
  @file     encoder_board.h
  @brief    Encoder board driver. Advance implementation
  @author   Nicolás Magliola
 ******************************************************************************/

#ifndef _ENCODER_BOARD_H_
#define _ENCODER_BOARD_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

typedef enum{
	NO_ENCODER_BOARD_EVENT,
	INVALID_ENCODER_BOARD_EVENT,
	ENCODER_BOARD_LEFT,
	ENCODER_BOARD_RIGHT,
	ENCODER_BOARD_PRESS,
	ENCODER_BOARD_RELEASE,
	ENCODER_BOARD_SKP,
	ENCODER_BOARD_LKP,
	ENCODER_BOARD_TYPEMATIC,
	END_OF_ENCODER_BOARD_QUEUE
}encoderBoardEvents;

typedef enum{LED_D1, LED_D2, LED_D3}boardLED;

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
/**
 * @brief Initializes the encoder  board driver
 */
void encoderBoardInit(void);
 /**
  * @brief Read the oldest event in the encoder board, then deletes it
  * @return oldest event in the event queue
  */
const encoderBoardEvents getEncoderBoardEvent(void);

//Button Service
uint32_t getEncoderButtonTimePressed(void);

//LED Services
void boardLEDTurnOn(boardLED led);
void boardLEDTurnOff(void);
/*******************************************************************************
 ******************************************************************************/

#endif // _ENCODER_BOARD_H_

