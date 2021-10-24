/***************************************************************************//**
  @file     validation.h
  @brief    description of validation functions
  @author   Matias Tripoli - Tobias Demeco
 ******************************************************************************/

#ifndef _VALID_H_
#define _VALID_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define MAX_USERS 65535 //limit given by the use of uint16_t for IDs
#define INVALID_ID -1
/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
typedef struct
{
  uint8_t id[8];
  uint8_t pin[4];
  bool admin;
} User ;

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief Validate user ID
 * @param enteredId Id to validate
 * @return int: database index of valid ID, returns INVALID_ID if user hasnt been found
 */
int validateId(uint8_t enteredId[8]);

/**
 * @brief Validate user PIN
 * @param enteredPin PIN to validate
 * @return bool: true if Pin valid, false otherwise
 */
bool validatePin(int userIndex, uint8_t enteredPin[4]);


/**
 * @brief Add a new valid ID with its corresponding PIN
 * @param newUser user credentials to add to system
 * @return bool: true if ID adding was succesful, false otherwise
 */
bool addNewId(User newUser);

/**
 * @brief Deletes a user
 * @param userIndex database index of user to delete
 */
void deleteUser(int userIndex);

/**
 * @brief Modifies a user pin
 * @param userIndex database index of user to modify
 * @param newPin new pin for user
 */
void modifyPin(int userIndex, uint8_t newPin[4]);

/**
 * @brief Check if current user is admin
 * @param user_index user index in database
 * @return bool: true if user is admin, false otherwise
 */
bool checkIfAdmin(int user_index);

/*******************************************************************************
 ******************************************************************************/

#endif //_VALID_H_