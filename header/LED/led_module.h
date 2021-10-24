/***************************************************************************//**
  @file     led_module.h
  @brief    Header of LED module for app interaction//
  @author   Matias Tripoli - Tobias Demeco
 ******************************************************************************/

#ifndef _LEDMOD_H_
#define _LEDMOD_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief Prints message in LED display
 * @param msg pointer to the message you want to print
 * @param msg_length length of message
 */
void printLED(const char* msg);

/**
 * @brief Changes LED brigthness
 * @param intensity level of brightness (0 (min) - 255 (max))
 */
void changeLEDIntensity(uint8_t newIntensity);


/*******************************************************************************
 ******************************************************************************/

#endif // _LEDMOD_H_