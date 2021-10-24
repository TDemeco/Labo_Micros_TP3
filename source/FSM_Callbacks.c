/***************************************************************************//**
  @file     FSM_Callbacks.c
  @brief    //
  @author   Matias Tripoli - Tobias Demeco
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/  

#include "FSM_Callbacks.h"
#include "FSMTable.h"
#include "led_module.h"
#include "led_rgb.h"
#include "validation.h"
#include "magnetic_app.h"
#include "sevenseg_app.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

typedef enum {ADD, DEL, MOD, ACCESS, UNBLOCK} ADMIN_STATE;

/*******************************************************************************
 * CONSTANTS
 ******************************************************************************/

/*******************************************************************************
 * CALLBACK VARIABLES
 ******************************************************************************/
static uint8_t brightness = 10;
static uint8_t current_digit = 0;

static uint8_t current_id[8] = {0,0,0,0,0,0,0,0};
static uint8_t current_pin[4] = {0,0,0,0};
static uint8_t index = 0;

static bool valid_id = false;
static bool valid_pin = false;
static uint8_t pin_attemps = 0;

static bool modifying = false;
static ADMIN_STATE admin_state = ACCESS;


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

//Does nothing
void nothing (State_Type** p_state)
{
    return;
}


//Cleaning variables
void clean (State_Type** p_state)
{
    current_digit = 0;
    for(int i = 0; i < 8; i++)
        current_id[i] = 0;
    for(int i = 0; i < 4; i++)
        current_pin[i] = 0;
    index = 0;
    valid_id = false;
    valid_pin = false;
    //modifying = false;
}


//Main menu callbacks
void to_access (State_Type** p_state)
{
    printLED("ACCESS");             //llamado a rutina de sevenseg
    clean(p_state);
    modifying = false;
    change_led_state(BLACK);
}
void to_modify (State_Type** p_state)
{
    printLED("MODIFY");             //llamado a rutina de sevenseg
    clean(p_state);
    modifying = true;
    change_led_state(BLACK);
}
void to_options (State_Type** p_state)
{
    printLED("OPTIONS");             //llamado a rutina de sevenseg
    clean(p_state);
    modifying = false;
    change_led_state(BLACK);
}


void to_led_dimming(State_Type** p_state)
{
    printLED("LED BRIGHTNESS");             //llamado a rutina de sevenseg
    clean(p_state);
}
void to_change_bright(State_Type** p_state)
{
    printLED("CHANGING LED BRIGHTNESS");     //llamado a rutina de sevenseg
    clean(p_state);
}
void brightness_up(State_Type** p_state)
{
    if(brightness == 20)
        return;
    brightness++;
    changeLEDIntensity(brightness);             //llamado a rutina de sevenseg
    printLED("NEW BRIGHTNESS");         //llamado a rutina de sevenseg

}
void brightness_down(State_Type** p_state)
{
    if(brightness == 1)
        return;
    brightness--;
    changeLEDIntensity(brightness);             //llamado a rutina de sevenseg
    printLED("NEW BRIGHTNESS");         //llamado a rutina de sevenseg

}

//Access menu callbacks
void to_card(State_Type** p_state)
{
    printLED("BY CARD");              //llamado a rutina de sevenseg
    clean(p_state);
}
void to_manual(State_Type** p_state)
{
    printLED("BY MANUAL INPUT");         //llamado a rutina de sevenseg
    clean(p_state);
}
void to_input_id(State_Type** p_state)
{
    printLED("PLEASE INPUT YOUR ID");                   //llamado a rutina de sevenseg
    clean(p_state);
}



/*** Admin menu callbacks ***/
void to_add (State_Type** p_state)
{
    printLED("ADD USER");             //llamado a rutina de sevenseg
    clean(p_state);
    admin_state = ADD;
}
void to_del (State_Type** p_state)
{
    printLED("DEL USER");             //llamado a rutina de sevenseg
    clean(p_state);
    admin_state = DEL;
}
void to_mod (State_Type** p_state)
{
    printLED("MODIFY PIN");             //llamado a rutina de sevenseg
    clean(p_state);
    admin_state = MOD;
}
void to_unblock (State_Type** p_state)
{
    printLED("UNBLOCK USER");
    clean(p_state);
    admin_state = UNBLOCK;
}
void logoff(State_Type** p_state)
{
    change_led_state(BLACK);
    admin_state = ACCESS;
    modifying = false;
    clean(p_state);
}



/*** Card reading functions ***/
void prep_card_read(State_Type** p_state)
{
    if(get_state_ma() != UNINITIALIZED_MA)
        enable_reading_ma();                //rutina de magnetic_app
    else{
        init_magnetic_ma();                 //rutina de magnetic_app
        enable_reading_ma();                //rutina de magnetic_app
    }
    
}
void read_card(State_Type** p_state)
{
    switch(get_state_ma()){
        case UNINITIALIZED_MA:
            init_magnetic_ma();                 //rutina de magnetic_app
            break;
        case DISABLED_MA:
            enable_reading_ma();                //rutina de magnetic_app
            break;
        case WAITING_MA:                        //estoy esperando pase de tarjeta
            printLED("SWIPE NOW");              //llamado a rutina de sevenseg
            break;
        case READING_MA:                        //estan pasando tarjeta
            printLED("READING...");             //llamado a rutina de sevenseg
            break;
        case INVALID_DATA_MA:                   
            printLED("SWIPE AGAIN");            //llamado a rutina de sevenseg
            break;
        case NEW_VALID_DATA_MA: ;
            uint8_t *data = get_data_ma();      //rutina de magnetic_app
            for(int i = 0; i<8; i++)
                current_id[i] = data[i];                  
            printLED("DATA AQUIRED");           //llamado a rutina de sevenseg
            validation(p_state);
            index = 0;
            break;
        case ERROR_MA:                   
            printLED("ERROR");                  //llamado a rutina de sevenseg
            break;
        default:
            printLED("DEF MA");                 //llamado a rutina de sevenseg
            break;
    }
}


/*** Manual Input Functions ***/
void plus_one(State_Type** p_state)
{
    if (current_digit == 9)
        current_digit = 0;
    else
        current_digit++;
    

    if(valid_id == false)
    {
        uint8_t current_id_and_digit[8];
        for(int i=0;i<8;i++)
        	current_id_and_digit[i]= current_id[i];
        current_id_and_digit[index] = current_digit;
    	display_data(current_id_and_digit,index);
    }
    else
    {
        uint8_t current_pin_and_digit[4];
        for(int i=0;i<4;i++)
        	current_pin_and_digit[i]= current_pin[i];
        current_pin_and_digit[index] = current_digit;
        display_secret_data(current_pin_and_digit,index);
    }
}
void minus_one(State_Type** p_state)
{
    if (current_digit == 0)
        current_digit = 9;
    else
        current_digit--;

    if(valid_id == false)
    {
        uint8_t current_id_and_digit[8];
        for(int i=0;i<8;i++)
        	current_id_and_digit[i]= current_id[i];
        current_id_and_digit[index] = current_digit;
    	display_data(current_id_and_digit,index);
    }
    else
    {
        uint8_t current_pin_and_digit[4];
        for(int i=0;i<4;i++)
        	current_pin_and_digit[i]= current_pin[i];
        current_pin_and_digit[index] = current_digit;
        display_secret_data(current_pin_and_digit,index);
    }
}
void input_confirm_id(State_Type** p_state)
{

    current_id[index] = current_digit;
    current_digit = 0;

    display_data(current_id,index);

    if(index == 7)
    {
        validation(p_state);
        index = 0;
    }
    else
    {
        index++;
    }
}
void input_confirm_pin(State_Type** p_state)
{

    current_pin[index] = current_digit;
    current_digit = 0;

    display_secret_data(current_pin,index);

    if(index == 3)
    {
        validation(p_state);
        index = 0;
    }
    else
    {
        index++;
    }
}
void backtrack(State_Type** p_state)
{
    index--;
}
void delete_input(State_Type** p_state)
{
    index = 0;
}

/*** Validation functions ***/
void to_validate(State_Type** p_state)
{
    printLED("STARTING VALIDATION");             //llamado a rutina de sevenseg
}
void validation(State_Type** p_state)
{
    if(admin_state == ACCESS)
    {
        int id_index = validateId(current_id);
        if(valid_id == false)
        {
            if(id_index == INVALID_ID)
            {
                valid_id = false;
                printLED("INVALID ID");             //llamado a rutina de sevenseg

                index = 0;
                for(int i = 0; i < 8; i++)
                    current_id[i] = 0;

                *p_state = card;
            }
            else
            {
                if(modifying == true && !validateAdmin(id_index)) //si estoy modificando pero el user no es admin
                {
                    printLED("USER IS NOT ADMIN. EXITING");
                    modifying = false;
                    clean(p_state);
                    *p_state = access;
                }
                else    //si no estoy modificando o el user si es admin
                {
                    if (isUserBlocked(id_index))
                    {
                        printLED("USER IS BLOCKED. CONTACT ADMIN");
                        modifying = false;
                        clean(p_state);
                        *p_state = access;
                    }
                    else
                    {
                        valid_id = true;
                        printLED("ID APPROVED. ENTER PIN");             //llamado a rutina de sevenseg
                        index = 0;
                        *p_state = first_pin;
                    }

                }
            }
        }
        else
        {
            valid_pin = validatePin(id_index, current_pin);
            if(valid_pin)
            {
                if(modifying == false)
                {
                    printLED("HAVE A GREAT DAY");                              //llamado a rutina de sevenseg
                    pin_attemps = 0;
                    change_led_state(GREEN);
                    uint32_t veces = 60000000UL;                                //llamado a rutina de led rgb
                    while(veces--);                     //Con el delay simulamos una entrada por la puerta
                    change_led_state(BLACK);                                   //llamado a rutina de led rgb
                    clean(p_state);
                    *p_state = access;
                }
                else
                {
                    printLED("ADMIN MENU");
                    change_led_state(CYAN);
                    *p_state = add_id;
                }
            }
            else
            {
                pin_attemps++;
                if(pin_attemps == 3)
                {
                    printLED("TOO MANY ATTEMPS. USER BLOCKED");
                    blockUser(id_index);
                    pin_attemps = 0;
                    clean(p_state);
                    modifying = false;
                    *p_state = access;
                }
                else
                {
                    printLED("INCORRET PIN. TRY AGAIN");          //llamado a rutina de sevenseg
                    index = 0;
                    for(int i = 0; i < 4; i++)
                        current_pin[i] = 0;
                    *p_state = first_pin;
                }
                change_led_state(RED);                        //llamado a rutina de led rgb
            }
        }
    }

    else if (admin_state == ADD)
    {
        if(index != 3) //si recien tengo el id (si recien puse el id va a estar en 7, si puse la tarjeta va a estar en 0)
        {
            printLED("INPUT PIN TO ADD");
            index = 0;
            for(int i = 0; i < 4; i++)
                current_pin[i] = 0;
            *p_state = first_pin;
        }
        else
        {
            User newUser;
            for(int i = 0; i < 8; i++)
                newUser.id[i] = current_id[i];
            for(int i = 0; i < 4; i++)
                newUser.pin[i] = current_pin[i];
            addNewId(newUser);
            printLED("NEW USER ADDED");
            admin_state = ACCESS;
            clean(p_state);
            *p_state = add_id;        
        }
    }

    else if (admin_state == DEL)
    {
        int id_index = validateId(current_id);
        if(id_index == INVALID_ID)
        {
            printLED("INVALID ID");             //llamado a rutina de sevenseg
            for(int i = 0; i < 8; i++)
                current_id[i] = 0;
        }
        else
        {
            printLED("CORRECT ID. DELETING");       //llamado a rutina de sevenseg
            deleteUser(id_index);           
        }
        index = 0;
        admin_state = ACCESS;
        clean(p_state);
        *p_state = add_id;
    }

    else if(admin_state == MOD)
    {
        int id_index = validateId(current_id);
        if(id_index == INVALID_ID)
        {
            printLED("INVALID ID");             //llamado a rutina de sevenseg
            for(int i = 0; i < 8; i++)
                current_id[i] = 0;
        }
        else
        {
            if(index != 3)  //si recien tengo el id (si recien puse el id va a estar en 7, si puse la tarjeta va a estar en 0)
            {
                printLED("INPUT NEW PIN");
                index = 0;
                for(int i = 0; i < 4; i++)
                    current_pin[i] = 0;
                *p_state = first_pin;
            }
            else
            {
                modifyPin(id_index, current_pin);
                printLED("PIN MODIFIED");
                admin_state = ACCESS;
                clean(p_state);
                *p_state = add_id;        
            }
        }
    }
    else if (admin_state == UNBLOCK)
    {
        int id_index = validateId(current_id);
        if(id_index == INVALID_ID)
        {
            printLED("USER DOESNT EXIST");
            for(int i = 0; i < 8; i++)
                current_id[i] = 0;
        }
        else
        {
            unblockUser(id_index);
            admin_state = ACCESS;
            clean(p_state);
            *p_state = add_id;
        }
    }
}

