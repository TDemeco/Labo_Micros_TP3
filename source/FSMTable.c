#include "FSMTable.h"
#include "FSM_Callbacks.h"



/*** Access ***/
State_Type access[]=
{//Event        State           Action
{NO_ENCODER_BOARD_APP_EVENT,       access,         nothing},      
{ENCODER_BOARD_APP_RIGHT,         modify,         to_modify},         //cambia a modify entonces debe poner modify en pantalla
{ENCODER_BOARD_APP_LEFT,          options,        to_options},        //cambia a options entonces debe poner options en pantalla
{ENCODER_BOARD_APP_ENTER,         card,           to_card},           //elige access entonces aparece card en pantalla
{ENCODER_BOARD_APP_BACKSPACE,     access,         nothing},
{ENCODER_BOARD_APP_DELETE,        access,         nothing},
{ENCODER_BOARD_APP_ESCAPE,        access,         nothing},
{EOT,           access,         nothing},
};

/*** Modify ***/
State_Type modify[]=
{//Event        State           Action
{NO_ENCODER_BOARD_APP_EVENT,      modify,         nothing},
{ENCODER_BOARD_APP_RIGHT,         options,        to_options},
{ENCODER_BOARD_APP_LEFT,          access,         to_access},
{ENCODER_BOARD_APP_ENTER,         card,           to_card_mod},           //Aca capaz habria que ver como diferenciar cuando se entra a card por access o por modify
{ENCODER_BOARD_APP_BACKSPACE,     modify,         nothing},
{ENCODER_BOARD_APP_DELETE,        modify,         nothing},
{ENCODER_BOARD_APP_ESCAPE,        modify,         nothing},
{EOT,           modify,         nothing},
};

/*** Options ***/
State_Type options[]=
{//Event        State           Action
{NO_ENCODER_BOARD_APP_EVENT,       options,        nothing},
{ENCODER_BOARD_APP_RIGHT,         access,         to_access},
{ENCODER_BOARD_APP_LEFT,          modify,         to_modify},
{ENCODER_BOARD_APP_ENTER,         led_dimming,    to_led_dimming},              //El menu options no tiene un estado extra para entrar??
{ENCODER_BOARD_APP_BACKSPACE,     options,        nothing},
{ENCODER_BOARD_APP_DELETE,        options,        nothing},
{ENCODER_BOARD_APP_ESCAPE,        options,        nothing},
{EOT,           options,        nothing},
};


/*** ADMIN MENU ***/
State_Type add_id[]=
{//Event        State           Action
{NO_ENCODER_BOARD_APP_EVENT,       add_id,         nothing},
{ENCODER_BOARD_APP_RIGHT,         del_id,        to_options},
{ENCODER_BOARD_APP_LEFT,          mod_id,         to_access},
{ENCODER_BOARD_APP_ENTER,         card,           to_card_admin},           //Aca capaz habria que ver como diferenciar cuando se entra a card por access o por modify
{ENCODER_BOARD_APP_BACKSPACE,     add_id,         nothing},
{ENCODER_BOARD_APP_DELETE,        add_id,         nothing},
{ENCODER_BOARD_APP_ESCAPE,        access,         logoff},
{EOT,           add_id,         nothing},
};

State_Type del_id[]=
{//Event        State           Action
{NO_ENCODER_BOARD_APP_EVENT,       del_id,         nothing},
{ENCODER_BOARD_APP_RIGHT,         mod_id,        to_options},
{ENCODER_BOARD_APP_LEFT,          add_id,         to_access},
{ENCODER_BOARD_APP_ENTER,         card,           to_card_admin},           //Aca capaz habria que ver como diferenciar cuando se entra a card por access o por modify
{ENCODER_BOARD_APP_BACKSPACE,     del_id,         nothing},
{ENCODER_BOARD_APP_DELETE,        del_id,         nothing},
{ENCODER_BOARD_APP_ESCAPE,        access,         logoff},
{EOT,           del_id,         nothing},
};

State_Type mod_id[]=
{//Event        State           Action
{NO_ENCODER_BOARD_APP_EVENT,       mod_id,         nothing},
{ENCODER_BOARD_APP_RIGHT,         add_id,        to_options},
{ENCODER_BOARD_APP_LEFT,          del_id,         to_access},
{ENCODER_BOARD_APP_ENTER,         card,           to_card_admin},           //Aca capaz habria que ver como diferenciar cuando se entra a card por access o por modify
{ENCODER_BOARD_APP_BACKSPACE,     mod_id,         nothing},
{ENCODER_BOARD_APP_DELETE,        mod_id,         nothing},
{ENCODER_BOARD_APP_ESCAPE,        access,         logoff},
{EOT,           mod_id,         nothing},
};




/*** Led dimming ***/
State_Type led_dimming[]=
{//Event        State                   Action
{NO_ENCODER_BOARD_APP_EVENT,       led_dimming,            nothing},
{ENCODER_BOARD_APP_RIGHT,         led_dimming,            nothing},
{ENCODER_BOARD_APP_LEFT,          led_dimming,            nothing},
{ENCODER_BOARD_APP_ENTER,         change_led_brigthness,  to_change_bright},              
{ENCODER_BOARD_APP_BACKSPACE,     options,                to_options},
{ENCODER_BOARD_APP_DELETE,        options,                to_options},
{ENCODER_BOARD_APP_ESCAPE,        options,                to_options},
{EOT,           led_dimming,            nothing},
};

State_Type change_led_brigthness[]=
{//Event        State                   Action
{NO_ENCODER_BOARD_APP_EVENT,       change_led_brigthness,  nothing},
{ENCODER_BOARD_APP_RIGHT,         change_led_brigthness,  brightness_up},
{ENCODER_BOARD_APP_LEFT,          change_led_brigthness,  brightness_down},
{ENCODER_BOARD_APP_ENTER,         change_led_brigthness,  nothing},              
{ENCODER_BOARD_APP_BACKSPACE,     change_led_brigthness,  nothing},
{ENCODER_BOARD_APP_DELETE,        change_led_brigthness,  nothing},
{ENCODER_BOARD_APP_ESCAPE,        led_dimming,            to_led_dimming},
{EOT,           change_led_brigthness,  nothing},
};

/**********************
*   ACCESS STATES     *
**********************/

/*** Card ***/
State_Type card[]=
{//Event        State           Action
{NO_ENCODER_BOARD_APP_EVENT,       card,           nothing},
{ENCODER_BOARD_APP_RIGHT,         manual,         to_manual},
{ENCODER_BOARD_APP_LEFT,          manual,         to_manual},
{ENCODER_BOARD_APP_ENTER,         reading_card,   prep_card_read},
{ENCODER_BOARD_APP_BACKSPACE,     card,           nothing},
{ENCODER_BOARD_APP_DELETE,        card,           nothing},
{ENCODER_BOARD_APP_ESCAPE,        access,         to_access},
{EOT,           card,           nothing},
};

/*** Manual input ***/
State_Type manual[]=
{//Event        State           Action
{NO_ENCODER_BOARD_APP_EVENT,       manual,         nothing},
{ENCODER_BOARD_APP_RIGHT,         card,           to_card},
{ENCODER_BOARD_APP_LEFT,          card,           to_card},
{ENCODER_BOARD_APP_ENTER,         first_id,       to_input_id},
{ENCODER_BOARD_APP_BACKSPACE,     manual,         nothing},
{ENCODER_BOARD_APP_DELETE,        manual,         nothing},
{ENCODER_BOARD_APP_ESCAPE,        access,         to_access},
{EOT,           manual,         nothing},
};

/**********************
*   ID CARD READING   *
**********************/

State_Type reading_card[]=
{//Event        State           Action
{NO_ENCODER_BOARD_APP_EVENT,       reading_card,   read_card},
{ENCODER_BOARD_APP_RIGHT,         reading_card,   read_card},
{ENCODER_BOARD_APP_LEFT,          reading_card,   read_card}, //pase lo que pase leemos la tarjeta, el callback se encarga de cambiar el estado cuando tenemos la id
{ENCODER_BOARD_APP_ENTER,         reading_card,   read_card},
{ENCODER_BOARD_APP_BACKSPACE,     reading_card,   read_card},
{ENCODER_BOARD_APP_DELETE,        reading_card,   read_card},
{ENCODER_BOARD_APP_ESCAPE,        card,           to_card},
{EOT,           reading_card,   read_card},
};


/**********************
*   MANUAL ID INPUT STATES   *
**********************/

/*** First digit ID input ***/
State_Type first_id[]=
{//Event        State           Action
{NO_ENCODER_BOARD_APP_EVENT,       first_id,       nothing},
{ENCODER_BOARD_APP_RIGHT,         first_id,       plus_one},
{ENCODER_BOARD_APP_LEFT,          first_id,       minus_one},
{ENCODER_BOARD_APP_ENTER,         second_id,      input_confirm_id},
{ENCODER_BOARD_APP_BACKSPACE,     first_id,       nothing},
{ENCODER_BOARD_APP_DELETE,        first_id,       nothing},
{ENCODER_BOARD_APP_ESCAPE,        manual,         to_manual},
};

/*** Second digit ID input ***/
State_Type second_id[]=
{//Event        State           Action
{NO_ENCODER_BOARD_APP_EVENT,       second_id,      nothing},
{ENCODER_BOARD_APP_RIGHT,         second_id,      plus_one},
{ENCODER_BOARD_APP_LEFT,          second_id,      minus_one},
{ENCODER_BOARD_APP_ENTER,         third_id,       input_confirm_id},
{ENCODER_BOARD_APP_BACKSPACE,     first_id,       backtrack},
{ENCODER_BOARD_APP_DELETE,        first_id,       delete_input},
{ENCODER_BOARD_APP_ESCAPE,        manual,         to_manual},
};

/*** Third digit ID input ***/
State_Type third_id[]=
{//Event        State           Action
{NO_ENCODER_BOARD_APP_EVENT,       third_id,       nothing},
{ENCODER_BOARD_APP_RIGHT,         third_id,       plus_one},
{ENCODER_BOARD_APP_LEFT,          third_id,       minus_one},
{ENCODER_BOARD_APP_ENTER,         fourth_id,      input_confirm_id},
{ENCODER_BOARD_APP_BACKSPACE,     second_id,      backtrack},
{ENCODER_BOARD_APP_DELETE,        first_id,       delete_input},
{ENCODER_BOARD_APP_ESCAPE,        manual,         to_manual},
};

/*** Fourth digit ID input ***/
State_Type fourth_id[]=
{//Event        State           Action
{NO_ENCODER_BOARD_APP_EVENT,       fourth_id,      nothing},
{ENCODER_BOARD_APP_RIGHT,         fourth_id,      plus_one},
{ENCODER_BOARD_APP_LEFT,          fourth_id,      minus_one},
{ENCODER_BOARD_APP_ENTER,         fifth_id,       input_confirm_id},
{ENCODER_BOARD_APP_BACKSPACE,     third_id,       backtrack},
{ENCODER_BOARD_APP_DELETE,        first_id,       delete_input},
{ENCODER_BOARD_APP_ESCAPE,        manual,         to_manual},
};


/*** Fifth digit ID input ***/
State_Type fifth_id[]=
{//Event        State           Action
{NO_ENCODER_BOARD_APP_EVENT,       fifth_id,       nothing},
{ENCODER_BOARD_APP_RIGHT,         fifth_id,       plus_one},
{ENCODER_BOARD_APP_LEFT,          fifth_id,       minus_one},
{ENCODER_BOARD_APP_ENTER,         sixth_id,       input_confirm_id},
{ENCODER_BOARD_APP_BACKSPACE,     fourth_id,      backtrack},
{ENCODER_BOARD_APP_DELETE,        first_id,       delete_input},
{ENCODER_BOARD_APP_ESCAPE,        manual,         to_manual},
};

/*** Sixth digit ID input ***/
State_Type sixth_id[]=
{//Event        State           Action
{NO_ENCODER_BOARD_APP_EVENT,       sixth_id,       nothing},
{ENCODER_BOARD_APP_RIGHT,         sixth_id,       plus_one},
{ENCODER_BOARD_APP_LEFT,          sixth_id,       minus_one},
{ENCODER_BOARD_APP_ENTER,         seventh_id,     input_confirm_id},
{ENCODER_BOARD_APP_BACKSPACE,     fifth_id,       backtrack},
{ENCODER_BOARD_APP_DELETE,        first_id,       delete_input},
{ENCODER_BOARD_APP_ESCAPE,        manual,         to_manual},
};

/*** Seventh digit ID input ***/
State_Type seventh_id[]=
{//Event        State           Action
{NO_ENCODER_BOARD_APP_EVENT,       seventh_id,     nothing},
{ENCODER_BOARD_APP_RIGHT,         seventh_id,     plus_one},
{ENCODER_BOARD_APP_LEFT,          seventh_id,     minus_one},
{ENCODER_BOARD_APP_ENTER,         final_id,       input_confirm_id},
{ENCODER_BOARD_APP_BACKSPACE,     sixth_id,       backtrack},
{ENCODER_BOARD_APP_DELETE,        first_id,       delete_input},
{ENCODER_BOARD_APP_ESCAPE,        manual,         to_manual},
};

/*** Final digit ID input ***/
State_Type final_id[]=
{//Event        State           Action
{NO_ENCODER_BOARD_APP_EVENT,       final_id,       nothing},
{ENCODER_BOARD_APP_RIGHT,         final_id,       plus_one},
{ENCODER_BOARD_APP_LEFT,          final_id,       minus_one},
{ENCODER_BOARD_APP_ENTER,         final_id,       input_confirm_id},      //se queda en final_id porque se cambia el estado en el callback
{ENCODER_BOARD_APP_BACKSPACE,     seventh_id,     backtrack},
{ENCODER_BOARD_APP_DELETE,        first_id,       delete_input},
{ENCODER_BOARD_APP_ESCAPE,        manual,         to_manual},
};



/**********************
*   MANUAL PIN INPUT STATES   *
**********************/

/*** First digit PIN input ***/
State_Type first_pin[]=
{//Event        State           Action
{NO_ENCODER_BOARD_APP_EVENT,       first_pin,       nothing},
{ENCODER_BOARD_APP_RIGHT,         first_pin,       plus_one},
{ENCODER_BOARD_APP_LEFT,          first_pin,       minus_one},
{ENCODER_BOARD_APP_ENTER,         second_pin,      input_confirm_pin},
{ENCODER_BOARD_APP_BACKSPACE,     first_pin,       nothing},
{ENCODER_BOARD_APP_DELETE,        first_pin,       nothing},
{ENCODER_BOARD_APP_ESCAPE,        manual,          to_manual},
};

/*** Second digit PIN input ***/
State_Type second_pin[]=
{//Event        State           Action
{NO_ENCODER_BOARD_APP_EVENT,       second_pin,     nothing},
{ENCODER_BOARD_APP_RIGHT,         second_pin,     plus_one},
{ENCODER_BOARD_APP_LEFT,          second_pin,     minus_one},
{ENCODER_BOARD_APP_ENTER,         third_pin,      input_confirm_pin},
{ENCODER_BOARD_APP_BACKSPACE,     first_pin,      backtrack},
{ENCODER_BOARD_APP_DELETE,        first_pin,      delete_input},
{ENCODER_BOARD_APP_ESCAPE,        manual,         to_manual},
};

/*** Third digit PIN input ***/
State_Type third_pin[]=
{//Event        State           Action
{NO_ENCODER_BOARD_APP_EVENT,       third_pin,      nothing},
{ENCODER_BOARD_APP_RIGHT,         third_pin,      plus_one},
{ENCODER_BOARD_APP_LEFT,          third_pin,      minus_one},
{ENCODER_BOARD_APP_ENTER,         fourth_pin,     input_confirm_pin},
{ENCODER_BOARD_APP_BACKSPACE,     second_pin,     backtrack},
{ENCODER_BOARD_APP_DELETE,        first_pin,      delete_input},
{ENCODER_BOARD_APP_ESCAPE,        manual,         to_manual},
};

/*** Fourth digit PIN input ***/
State_Type fourth_pin[]=
{//Event        State           Action
{NO_ENCODER_BOARD_APP_EVENT,       fourth_pin,     nothing},
{ENCODER_BOARD_APP_RIGHT,         fourth_pin,     plus_one},
{ENCODER_BOARD_APP_LEFT,          fourth_pin,     minus_one},
{ENCODER_BOARD_APP_ENTER,         fourth_pin,     input_confirm_pin}, //el estado se queda en fourth_pin porque se cambia en el callback 
{ENCODER_BOARD_APP_BACKSPACE,     third_pin,      backtrack},
{ENCODER_BOARD_APP_DELETE,        first_pin,      delete_input},
{ENCODER_BOARD_APP_ESCAPE,        manual,         to_manual},
};



////////////////////////////////////////////////////////////////////