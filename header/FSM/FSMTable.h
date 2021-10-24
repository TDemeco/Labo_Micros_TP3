/***************************************************************************//**
  @file     FSM.h
  @brief    //
  @author  Matias Tripoli - Tobias Demeco
 ******************************************************************************/

#ifndef _FSMTABLE_H_
#define _FSMTABLE_H_

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

//TODO: Agregar parametro en tablas para reutilizar funciones

/*FowardDeclarations*/

/* Main Menu */
extern State_Type access[];
extern State_Type modify[];
extern State_Type options[];


/* Options Menu */
extern State_Type led_dimming[];
extern State_Type change_led_brigthness[];


/* Admin Menu */
extern State_Type add_id[];
extern State_Type del_id[];
extern State_Type mod_id[];
extern State_Type unblock_id[];

/* Input Menu */
extern State_Type card[];
extern State_Type manual[];

/* Validation State */
extern State_Type validate[];

/* Card reading */
extern State_Type reading_card[];

/* ID input */
extern State_Type first_id[];
extern State_Type second_id[];
extern State_Type third_id[];
extern State_Type fourth_id[];
extern State_Type fifth_id[];
extern State_Type sixth_id[];
extern State_Type seventh_id[];
extern State_Type final_id[];

/* PIN Input */
extern State_Type first_pin[];
extern State_Type second_pin[];
extern State_Type third_pin[];
extern State_Type fourth_pin[];


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/*******************************************************************************
 ******************************************************************************/

#endif // _FSMTABLE_H_
