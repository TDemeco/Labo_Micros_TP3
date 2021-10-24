/***************************************************************************//**
  @file     ESP8266_UART.h
  @brief    ESP8266_UART communication service
  @author   Ale
 ******************************************************************************/

#ifndef _ESP8266_UART_H_
#define _ESP8266_UART_H_

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

typedef struct {
	color_t color;
	bool new_pixel;
	bool destroy_pixel;
	uint8_t brightness;
	uint16_t pot;
	float accel_x;
	float accel_y;
	float accel_z;
} ESP_data;				//There can be up to 5 UART communications



/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief initializes ESP8266 UART communication, assumes UART_0, 9600 baud rate
 * @return
 */
void ESP8266_UART_init(void);

/**
 * @brief resolves communications from the ESP8266 and copies useful data
 * @param data structure where the data will be copied
 * @return
 */
void ESP8266_parse_msg(ESP_data* data);

/**
 * @brief sends relevant data to the ESP8266
 * @param data structure where the data will be read
 * @return
 */
void ESP8266_send_data(ESP_data* data);
/*******************************************************************************
 ******************************************************************************/

#endif // _ESP8266_UART_H_
