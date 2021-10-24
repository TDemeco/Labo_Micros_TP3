/***************************************************************************//**
  @file     encoder_board.c
  @brief    Application functions
  @author   Ale
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "encoder_board_app.h"
#include "encoder_board.h"
#include "timer.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define MAX_EVENT_NUMBER 50

void updateEncoderBoardApp(void);

static encoderBoardAppEvents release_button_event = ENCODER_BOARD_APP_ENTER;
static encoderBoardAppEvents eventQueue[MAX_EVENT_NUMBER];
static int beginEvent = 0;
static int endEvent = 0;

/*******************************************************************************
 * CONSTANTS
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

void addEventToQueue(encoderBoardAppEvents newEvent);

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void encoderBoardAppInit(void){
	beginEvent = 0;
	endEvent = 0;

	encoderBoardInit();
	timerInit();
	tim_id_t timer_id = timerGetId();
	timerStart(timer_id,5,TIM_MODE_PERIODIC,updateEncoderBoardApp);
}
const encoderBoardAppEvents getEncoderBoardAppEvent(void){
	if (beginEvent == endEvent)
		return NO_ENCODER_BOARD_APP_EVENT;
	else{
		encoderBoardAppEvents event = eventQueue[beginEvent++];
		if(beginEvent >= MAX_EVENT_NUMBER)
			beginEvent = 0;
		return event;
	}
}

/*******************************************************************************
 *******************************************************************************
                        PRIVATE FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void updateEncoderBoardApp(void){
	static uint32_t pressTimer,previousPressTimer;
	pressTimer = getEncoderButtonTimePressed();
	encoderBoardEvents nextEvent = getEncoderBoardEvent();

	if(pressTimer == 0 && previousPressTimer != 0){
		boardLEDTurnOff();
		addEventToQueue(release_button_event);
		release_button_event = ENCODER_BOARD_APP_ENTER;
	}
	else if(pressTimer < 500){
		boardLEDTurnOff();
		release_button_event = ENCODER_BOARD_APP_ENTER;
	}
	else if(pressTimer >= 500 && pressTimer <= 1000){
		boardLEDTurnOn(LED_D1);
		release_button_event = ENCODER_BOARD_APP_BACKSPACE;
	}
	else if(pressTimer >= 1000 && pressTimer <= 1500){
		boardLEDTurnOn(LED_D2);
		release_button_event = ENCODER_BOARD_APP_DELETE;
	}
	else if(pressTimer >= 1500){
		boardLEDTurnOn(LED_D3);
		release_button_event = ENCODER_BOARD_APP_ESCAPE;
	}

	if(nextEvent == ENCODER_BOARD_RIGHT){
		addEventToQueue(ENCODER_BOARD_APP_RIGHT);
	}
	if(nextEvent == ENCODER_BOARD_LEFT){
		addEventToQueue(ENCODER_BOARD_APP_LEFT);
	}

	previousPressTimer = pressTimer;
}

void addEventToQueue(encoderBoardAppEvents newEvent){
	eventQueue[endEvent++] = newEvent;
	if(endEvent >= MAX_EVENT_NUMBER)
		endEvent = 0;
	if (beginEvent == endEvent){
		beginEvent++;
		if(beginEvent >= MAX_EVENT_NUMBER)
			beginEvent = 0;
	}
}

/*******************************************************************************
                        INTERRUPTS ZONE
 ******************************************************************************/
