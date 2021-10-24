/***************************************************************************//**
  @file     encoder.h
  @brief    Rotary Encoder driver. Advance implementation
  @author   Ale
 ******************************************************************************/

#ifndef _ENCODER_H_
#define _ENCODER_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define MAX_ENCODER_QUEUE		50
#define ENCODER_REFRESH_PERIOD	100
/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
//Possible events for an encoder
typedef int encoderID;
typedef enum{
	NO_ENCODER_EVENT,
	INVALID_ENCODER_EVENT,
	ENCODER_LEFT,
	ENCODER_RIGHT,
	END_OF_ENCODER_QUEUE
}encoderEvents;


/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
/**
 * @brief Initializes the encoder driver
 */
void encoderInit(void);
/**
 * @brief create a new encoder structure
 * @param pinA: the pin A of the new encoder
 * @param pinB: the pin B of the new encoder
 * @return ID for a new encoder, will return -1 if it couldn't create new encoder;
 */
encoderID getEncoderID(pin_t pinA, pin_t pinB);
/**
 * @brief Read the oldest event for a given encoder, the user must go through the queue if he needs it, until END_OF_QUEUE reached
 * @param id: the id of the given encoder
 * @return oldest event in the event queue, will return INVALID if the id corresponds to a disabled or invalid encoder
 */
const encoderEvents getEncoderEvent(encoderID id);

/**
 * @brief Disables a given encoder
 * @param id: the id of the given encoder
 */
void disableEncoder(encoderID id);
/**
 * @brief Enables a given encoder
 * @param id: the id of the given encoder
 */
void enableEncoder(encoderID id);
/**
 * @brief Informs on wheater or not a given encoder is enabled
 * @param id: the id of the given encoder
 * @return TRUE if a encoder is enabled, FALSE if the encoder deesn't exist or is disabled
 */
bool isEncoderEnabled(encoderID id);

/*******************************************************************************
 ******************************************************************************/

#endif // _ENCODER_H_

