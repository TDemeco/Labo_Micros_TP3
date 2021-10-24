/***************************************************************************//**
  @file     encoder_board.h
  @brief    Encoder board driver. Advance implementation
  @author   Nicolás Magliola
 ******************************************************************************/

#ifndef _ENCODER_BOARD_APP_H_
#define _ENCODER_BOARD_APP_H_

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
	NO_ENCODER_BOARD_APP_EVENT,
	ENCODER_BOARD_APP_LEFT,
	ENCODER_BOARD_APP_RIGHT,
	ENCODER_BOARD_APP_ENTER,
	ENCODER_BOARD_APP_BACKSPACE,
	ENCODER_BOARD_APP_DELETE,
	ENCODER_BOARD_APP_ESCAPE
}encoderBoardAppEvents;

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
void encoderBoardAppInit(void);
 /**
  * @brief Read the oldest event in the encoder board, then deletes it
  * @return oldest event in the event queue
  */
const encoderBoardAppEvents getEncoderBoardAppEvent(void);


/*******************************************************************************
 ******************************************************************************/

#endif // _ENCODER_BOARD_APP_H_

