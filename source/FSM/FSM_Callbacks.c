/***************************************************************************//**
  @file     FSM_Callbacks.c
  @brief    Callback functions for each event
  @author   Tobias Demeco
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/  

#include "header/FSM/FSMTable.h"
#include "header/FSM/FSM_Callbacks.h"

#include "header/Event Handler/event_handler.h"
#include "header/Node-RED/ESP8266_UART.h"
#include "header/Potenciometer/potenciometer.h"
#include "header/Accelerometer/Acelerometro.h"
#include "header/LED Matrix/LED_matrix_app.h"



/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
typedef struct{
	float velX;
	float velY;
} velocity_t;

typedef struct{
    uint8_t row;
    uint8_t col;
} led_pos_t;
/*******************************************************************************
 * CONSTANTS
 ******************************************************************************/

/*******************************************************************************
 * CALLBACK VARIABLES
 ******************************************************************************/
static ESP_data ledData = {255, 0, 0, false, false, 50, 50, 0, 0, 0};	   //led data (color, brightness, acceleration)
static led_pos_t ledPosition = {3, 3};				    //led position
static velocity_t ledVelocity = {0, 0};				    //led velocity
static accel_t ledAccelerations = {0, 0, 0};			//variable for quick access to acceleration values


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

//Does nothing
void nothing(State_Type** p_state)
{
    return;
}

void update_node_ui(State_Type** p_state)
{
    ledAccelerations = get_accelerations();         //updates accelerations
    ledData.accel_x = ledAccelerations.accel_x;
    ledData.accel_y = ledAccelerations.accel_y;
    ledData.accel_z = ledAccelerations.accel_z;

    ledData.pot = pote_read();                      //updates potenciometer reading

    ESP8266_send_data(&ledData);

    return;
}

void move_up(State_Type** p_state)
{
    if(ledPosition.row > 0)
        ledPosition.row--;
    else
        ledPosition.row = 0;
    return;
}

void move_down(State_Type** p_state)
{
    if(ledPosition.row < 7)
        ledPosition.row++;
    else
        ledPosition.row = 7;
    return;
}


void move_left(State_Type** p_state)
{
    if(ledPosition.col > 0)
        ledPosition.col--;
    else
        ledPosition.row = 0;
    return;
}

void move_right(State_Type** p_state)
{
    if(ledPosition.col < 7)
        ledPosition.col++;
    else
        ledPosition.col = 7;
    return;
}


void update_data(State_Type** p_state)
{
    ESP_data dummy;
    ESP8266_parse_msg(&dummy);

    ledData.led_color = dummy.led_color;
    ledData.brightness = dummy.brightness;
    return;
}

void update_led(void){				//WILL PROBABLY HAVE TO UPDATE THIS FUNCTION (TO ADD A MULTIPLICATIVE FACTOR TO ACCELERATION)

	ledPosition.row += ledVelocity.velX;		//update led row position in matrix
	if(ledPosition.row <= 0)					//left wall
	{
		ledVelocity.velX = 0;
		ledPosition.row = 0;
	}
	if(ledPosition.row >= 7)					//right wall
	{
		ledVelocity.velX = 0;
		ledPosition.row = 7;
	}

	ledPosition.col += ledVelocity.velY;		//update led column position in matrix
	if(ledPosition.col <= 0)					//floor
	{
		ledVelocity.velY = 0;
		ledPosition.col = 0;
	}
	if(ledPosition.col >= 7)					//ceiling
	{
		ledVelocity.velY = 0;
		ledPosition.col = 7;
	}

	ledAccelerations = get_accelerations();			//update accelerations
	ledVelocity.velX += ledAccelerations.accel_x;	//update led velocities acording to accelerations
	ledVelocity.velY += ledAccelerations.accel_y;

    LED_matrix_app_dot(ledPosition.row, ledPosition.col, ledData.led_color);	//show current led
	LED_matrix_app_brightness(ledData.brightness);								//set current brightness
}