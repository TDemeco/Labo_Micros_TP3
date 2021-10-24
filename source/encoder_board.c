/***************************************************************************//**
  @file     encoder_board.c
  @brief    Application functions
  @author   Ale
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <encoder_board.h>
#include "board.h"
#include "encoder_board.h"
#include "encoder.h"
#include "button.h"
#include "timer.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
//HARDWARE
#define ENC_A		DIO_9
#define ENC_B		DIO_10
#define ENC_SW		DIO_11

#define STATUS_0	DIO_12
#define STATUS_1	DIO_13
//SOFTWARE
#define ENCODER_BOARD_TIMER_MS		100
#define MAX_BOARD_EVENTS			50

#define LEN(array) (sizeof(array) / sizeof(array[0]))

/*******************************************************************************
 * CONSTANTS
 ******************************************************************************/


 /*******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 ******************************************************************************/
static buttonID boardButton;
static encoderID boardEncoder;
static tim_id_t boardTimer;
static encoderBoardEvents boardEventQueue[MAX_BOARD_EVENTS];
static uint8_t eventBeginIndex = 0;
static uint8_t eventEndIndex = 0;
static bool boardEventFlag = false;
/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
void encoderBoardUpdate(void);
void appendBoardEvent(encoderBoardEvents event);
/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
/**
 * @brief Initializes the encoder  board driver
 */
void encoderBoardInit(void){
	timerInit();
	buttonInit();
	encoderInit();
	boardButton = getButtonID(ENC_SW, INPUT_PULLUP, LOW);				//Register button
	boardEncoder = getEncoderID(ENC_A, ENC_B);							//Register rotary encoder
	boardTimer = timerGetId();											//Start onboard timer
	timerStart(boardTimer, TIMER_MS2TICKS(ENCODER_BOARD_TIMER_MS), TIM_MODE_PERIODIC, encoderBoardUpdate);	//Periodically scan for new events

	gpioMode(STATUS_0,OUTPUT,DSE_DEFAULT,ODE_DEFAULT,SRE_DEFAULT,PFE_DEFAULT,DFE_DEFAULT,0);
	gpioWrite(STATUS_0, 0);
	gpioMode(STATUS_1,OUTPUT,DSE_DEFAULT,ODE_DEFAULT,SRE_DEFAULT,PFE_DEFAULT,DFE_DEFAULT,0);
	gpioWrite(STATUS_1, 0);

}
 /**
  * @brief Read the oldest event in the encoder board, then deletes it
  * @return oldest event in the event queue
  */
const encoderBoardEvents getEncoderBoardEvent(void){
	encoderEvents ret = INVALID_ENCODER_BOARD_EVENT;

	if (eventBeginIndex != eventEndIndex){									//If event queue is not empty
		ret = boardEventQueue[eventBeginIndex];								//Load next event
		eventBeginIndex = (++eventBeginIndex) % (LEN(boardEventQueue));		//Point to next event in queue
		if (eventBeginIndex == eventEndIndex)								//If the index are the same, there are no new events
			boardEventFlag = false;
	}
	else
		ret = END_OF_ENCODER_BOARD_QUEUE;
	return ret;
}
//Button Service
uint32_t getEncoderButtonTimePressed(void){
	uint32_t time = getTimePressed(boardButton);
	return time;
}

//LED Services
void boardLEDTurnOn(boardLED led){
	//See board schematic and 74HC139 datasheet
	switch(led){
	case LED_D1:	gpioWrite(STATUS_0, HIGH);	gpioWrite(STATUS_1,  LOW);	break;
	case LED_D2:	gpioWrite(STATUS_0, LOW);	gpioWrite(STATUS_1, HIGH);	break;
	case LED_D3:	gpioWrite(STATUS_0, HIGH);	gpioWrite(STATUS_1, HIGH);	break;
	}
}
void boardLEDTurnOff(void){
	//See board schematic and 74HC139 datasheet
	gpioWrite(STATUS_0, LOW);
	gpioWrite(STATUS_1, LOW);
}
/*******************************************************************************
 *******************************************************************************
                        PRIVATE FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
void appendBoardEvent(encoderBoardEvents event){
	if (eventEndIndex != (eventBeginIndex + LEN(boardEventQueue))){
		boardEventQueue[eventEndIndex] = event;
		eventEndIndex = (++eventEndIndex) % (LEN(boardEventQueue));
		boardEventFlag = false;
	}
}
/*******************************************************************************
                        INTERRUPTS ZONE
 ******************************************************************************/
void encoderBoardUpdate(void){
	encoderEvents encoderEvent = getEncoderEvent(boardEncoder);
	const buttonEvents *buttonEvent = buttonGetEvent(boardButton);
	uint8_t i =0;

	while(buttonEvent[i] != END_OF_BUTTON_QUEUE){
		if(buttonEvent[i] == BUTTON_PRESS)
			appendBoardEvent(ENCODER_BOARD_PRESS);
		else if(buttonEvent[i] == BUTTON_RELEASE)
			appendBoardEvent(ENCODER_BOARD_RELEASE);
		else if(buttonEvent[i] == BUTTON_SKP)
			appendBoardEvent(ENCODER_BOARD_SKP);
		else if(buttonEvent[i] == BUTTON_LKP)
			appendBoardEvent(ENCODER_BOARD_LKP);
		else if(buttonEvent[i] == BUTTON_TYPEMATIC)
			appendBoardEvent(ENCODER_BOARD_TYPEMATIC);
		i++;
	}

	if(encoderEvent == ENCODER_LEFT)
		appendBoardEvent(ENCODER_BOARD_LEFT);
	else if(encoderEvent == ENCODER_RIGHT)
		appendBoardEvent(ENCODER_BOARD_RIGHT);
}
