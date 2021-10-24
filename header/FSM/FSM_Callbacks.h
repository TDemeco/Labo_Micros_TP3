/***************************************************************************//**
  @file     FSM.h
  @brief    //
  @author  Matias Tripoli
 ******************************************************************************/

#ifndef _FSMCALL_H_
#define _FSMCALL_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "FSM.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

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
 * @brief Does nothing
 */
void nothing(State_Type** p_state);


/*** Main menu functions ***/
/**
 * @brief Prints access to LED
 */
void to_access(State_Type** p_state);

/**
 * @brief Prints modify to LED
 */
void to_modify (State_Type** p_state);

/**
 * @brief Prints options to LED
 */
void to_options(State_Type** p_state);



/*** Admin Menu ***/
/**
 * @brief Prints ADD USER to LED
 */
void to_add (State_Type** p_state);
/**
 * @brief Prints DEL USER to LED
 */
void to_del (State_Type** p_state);
/**
 * @brief Prints MODIFY PIN to LED
 */
void to_mod (State_Type** p_state);
/**
 * @brief Prints UNBLOCK USER to LED
 */
void to_unblock (State_Type** p_state);
/**
 * @brief Logs off from admin menu
 */
void logoff(State_Type** p_state);



/*** Options menu (LED Dimming) ***/

/**
 * @brief Prints LED DIM to LED
 */
void to_led_dimming(State_Type** p_state);

/**
 * @brief Prints LED brightness number to LED
 */
void to_change_bright(State_Type** p_state);

/**
 * @brief Increases LED Brightness
 */
void brightness_up(State_Type** p_state);

/**
 * @brief Decreases LED Brightness
 */
void brightness_down(State_Type** p_state);


/*** Access menu funcionts ***/
/**
 * @brief Prints card access to LED
 */
void to_card(State_Type** p_state);

/**
 * @brief Prints manual access to LED
 */
void to_manual(State_Type** p_state);

/**
 * @brief Clears LED and prepares to receive input id
 */
void to_input_id(State_Type** p_state);


/*** Card reading ***/
/**
 * @brief Prepares ID reading
 */
void prep_card_read(State_Type** p_state);

/**
 * @brief Reads ID from card
 */
void read_card(State_Type** p_state);



/*** Manual input functions ***/
/**
 * @brief Adds one to current number shown on LED
 */
void plus_one(State_Type** p_state);

/**
 * @brief Substracts one from current number shown on LED
 */
void minus_one(State_Type** p_state);

/**
 * @brief Confirms input ID to show on LED
 */
void input_confirm_id(State_Type** p_state);

/**
 * @brief Confirms input PIN to show on LED
 */
void input_confirm_pin(State_Type** p_state);

/**
 * @brief Deletes last input
 */
void backtrack(State_Type** p_state);

/**
 * @brief Deletes all inputs
 */
void delete_input(State_Type** p_state);

/*** Validation functions ***/
/**
 * @brief prints Validation on LED
 */
void to_validate(State_Type** p_state);

/**
 * @brief validates input
 */
void validation(State_Type** p_state);


/*******************************************************************************
 ******************************************************************************/

#endif // _FSMCALL_H_
