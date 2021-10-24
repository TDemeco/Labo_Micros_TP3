/***************************************************************************//**
  @file     App.c
  @brief    Application
  @author   Tobias Demeco
 ******************************************************************************/

#define MYDEBUG false

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "header/FSM/FSM.h"
#include "header/FSM/FSMTable.h"

#include "header/Validation/validation.h"

#include "header/Board Drivers/timer.h"



/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

State_Type *p2state;


static void timer_callback(void);

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/* Función que se llama 1 vez, al comienzo del programa */
void App_Init (void)
{

	display_init();
	display_intensity(20);
	init_led();

	init_magnetic_ma();
	encoderBoardAppInit();

	timerInit();
	tim_id_t timer_id = timerGetId();
	timerStart(timer_id,1,TIM_MODE_PERIODIC,timer_callback);



	User newUser = {{1,1,1,1,1,1,1,1}, {1,2,3,4}, true};
	addNewId(newUser);
	newUser = (User){{1,2,3,4,5,6,7,8}, {1,1,1,1}, false};
	addNewId(newUser);
	newUser = (User){{3,0,8,6,2,5,6,0}, {0,0,0,0}, true};
	addNewId(newUser);
	newUser = (User){{6,0,6,1,2,6,8,3}, {0,0,0,0}, false};
	addNewId(newUser);

	p2state = access;         /*Used to store FSM state*/
	encoderBoardAppInit();

}

/* Función que se llama constantemente en un ciclo infinito */
void App_Run (void)
{
	  encoderBoardAppEvents event = getEncoderBoardAppEvent();
	  p2state = fsm(p2state, event);
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

static void timer_callback(void){
	display_refresh();
}

/*******************************************************************************
 ******************************************************************************/
