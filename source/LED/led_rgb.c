/***************************************************************************//**
  @file
  @brief
  @author
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "gpio.h"
#include "led_rgb.h"
#include "board.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

const bool ON = LOW;
const bool OFF = HIGH;

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

static bool initialized = false;

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void init_led(void){
	gpioMode(PIN_LED_RED, OUTPUT,DSE_DEFAULT,ODE_DEFAULT,SRE_DEFAULT,PFE_DEFAULT,DFE_DEFAULT,0);
	gpioMode(PIN_LED_GREEN, OUTPUT,DSE_DEFAULT,ODE_DEFAULT,SRE_DEFAULT,PFE_DEFAULT,DFE_DEFAULT,0);
	gpioMode(PIN_LED_BLUE, OUTPUT,DSE_DEFAULT,ODE_DEFAULT,SRE_DEFAULT,PFE_DEFAULT,DFE_DEFAULT,0);
	gpioWrite(PIN_LED_RED, OFF);
	gpioWrite(PIN_LED_GREEN, OFF);
	gpioWrite(PIN_LED_BLUE, OFF);
	initialized = true;
}


void change_led_state(led_color color){
	if(initialized){
		switch (color){
		case BLACK:
		default:
			gpioWrite(PIN_LED_RED, OFF);
			gpioWrite(PIN_LED_GREEN, OFF);
			gpioWrite(PIN_LED_BLUE, OFF);
			break;
		case RED:
			gpioWrite(PIN_LED_RED, ON);
			gpioWrite(PIN_LED_GREEN, OFF);
			gpioWrite(PIN_LED_BLUE, OFF);
			break;
		case GREEN:
			gpioWrite(PIN_LED_RED, OFF);
			gpioWrite(PIN_LED_GREEN, ON);
			gpioWrite(PIN_LED_BLUE, OFF);
			break;
		case BLUE:
			gpioWrite(PIN_LED_RED, OFF);
			gpioWrite(PIN_LED_GREEN, OFF);
			gpioWrite(PIN_LED_BLUE, ON);
			break;
		case MAGENTA:
			gpioWrite(PIN_LED_RED, ON);
			gpioWrite(PIN_LED_GREEN, OFF);
			gpioWrite(PIN_LED_BLUE, ON);
			break;
		case CYAN:
			gpioWrite(PIN_LED_RED, OFF);
			gpioWrite(PIN_LED_GREEN, ON);
			gpioWrite(PIN_LED_BLUE, ON);
			break;
		case YELLOW:
			gpioWrite(PIN_LED_RED, ON);
			gpioWrite(PIN_LED_GREEN, ON);
			gpioWrite(PIN_LED_BLUE, OFF);
			break;
		case WHITE:
			gpioWrite(PIN_LED_RED, ON);
			gpioWrite(PIN_LED_GREEN, ON);
			gpioWrite(PIN_LED_BLUE, ON);
			break;
		}
	}
}



/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/


/*******************************************************************************
 ******************************************************************************/
