/***************************************************************************//**
  @file     encoder.c
  @brief    Application functions
  @author   Ale
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "board.h"
#include "gpio.h"
#include "encoder.h"
#include "timer.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define MAX_ENCODERS		10
#define LEN(array) (sizeof(array) / sizeof(array[0]))
/*******************************************************************************
 * CONSTANTS
 ******************************************************************************/


/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
//Structure for any encoder
typedef struct {
	encoderID id;
	pin_t pinA;				//Where it is connected
	pin_t pinB;				//Where it is connected
	bool enable;			//It can be declared and left momentarily disabled
	bool flag;				//Flag to detect changes
	tim_id_t timer;
	encoderEvents eventQueue[MAX_ENCODER_QUEUE];
	uint8_t eventBeginIndex;
	uint8_t eventEndIndex;
} encoder_t;
/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL LEVEL SCOPE
 ******************************************************************************/

static encoder_t encoderArray[MAX_ENCODERS];				//Stores info on all possible encoder
/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

bool isValidEncoderID(encoderID id);
void encodersUpdate(void);
void appendEncoderEvent(encoderID id, encoderEvents event);
/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
/**
 * @brief Initializes the encoder driver
 */
void encoderInit(void){
	uint8_t i;
	timerInit();			//Just in case our user hasn't already initialized the timer driver
	for(i=0; i<MAX_ENCODERS; i++)
		encoderArray[i].id = -1;
}
/**
 * @brief Read the oldest event for a given encoder, the user must go through the queue if he needs it, until END_OF_QUEUE reached
 * @param id: the id of the given encoder
 * @return oldest event in the event queue, will return INVALID if the id corresponds to a disabled or invalid encoder
 */
const encoderEvents getEncoderEvent(encoderID id){
//	encoderEvents ret;
//	if(isValidEncoderID(id)){
//		ret = encoderArray[id].eventQueue[encoderArray[id].eventBeginIndex];//return the oldest event in the queue
//		encoderArray[id].eventQueue[encoderArray[id].eventBeginIndex] = END_OF_ENCODER_QUEUE;//And erase the event
//
//		if((encoderArray[id].eventBeginIndex + 1) < MAX_ENCODER_QUEUE){		//If the index hasn't reached the end of the circular buffer
//			if(encoderArray[id].eventQueue[encoderArray[id].eventBeginIndex+1] != END_OF_ENCODER_QUEUE)	//If next element is important
//				encoderArray[id].eventBeginIndex++;														//Point to the next event in the queue, if not we stay in place
//		}
//		else																//If next element is at the beginning
//			if(encoderArray[id].eventQueue[0] != END_OF_ENCODER_QUEUE)			//And if next element is important
//				encoderArray[id].eventBeginIndex = 0;						//Go back to the beginning of the queue
//		if(encoderArray[id].eventQueue[encoderArray[id].eventBeginIndex] == END_OF_ENCODER_QUEUE)
//			encoderArray[id].flag = false;									//If there are no more events in queue, lower flag
//	}
//	else
//		ret = INVALID_ENCODER_EVENT;
//	return ret;
	//Is the buffer non-empty?
	encoderEvents ret;
	if(isValidEncoderID(id)){
		if (encoderArray[id].eventBeginIndex != encoderArray[id].eventEndIndex){
			ret = encoderArray[id].eventQueue[encoderArray[id].eventBeginIndex];
			encoderArray[id].eventBeginIndex = (++encoderArray[id].eventBeginIndex) % (LEN(encoderArray[id].eventQueue));
			if (encoderArray[id].eventBeginIndex == encoderArray[id].eventEndIndex)
				encoderArray[id].flag = false;
		}
		else
			ret = END_OF_ENCODER_QUEUE;
	}
	return ret;
}

/**
 * @brief create a new encoder structure
 * @param pinA: the pin A of the new encoder
 * @param pinB: the pin B of the new encoder
 * @return ID for a new encoder, will return -1 if it couldn't create new encoder;
 */
encoderID getEncoderID(pin_t pinA, pin_t pinB){
	encoderID id = -1;
	uint8_t i;
	tim_id_t timer;
	for(i=0; i<MAX_ENCODERS; i++)
		if(encoderArray[i].id == -1){					//If there is an available free encoder, then register it
			id = i;
			encoderArray[i].id = i;
			encoderArray[i].pinA = pinA;
			encoderArray[i].pinB = pinB;
			encoderArray[i].enable = true;
			encoderArray[i].flag = false;
			timer = timerGetId();
			encoderArray[i].timer = timer;
			timerStart(encoderArray[i].timer, (uint32_t)TIMER_MS2TICKS(ENCODER_REFRESH_PERIOD), TIM_MODE_SINGLESHOT, NULL); //start individual timer
			encoderArray[i].eventBeginIndex = 0;
			encoderArray[i].eventEndIndex = 0;
			gpioMode(pinA, INPUT_PULLUP, DSE_DEFAULT, ODE_DEFAULT, SRE_DEFAULT, PFE_DEFAULT, DFE_DEFAULT, 0);
			gpioMode(pinB, INPUT_PULLUP, DSE_DEFAULT, ODE_DEFAULT, SRE_DEFAULT, PFE_DEFAULT, DFE_DEFAULT, 0);
			gpioIRQ(pinB, GPIO_IRQ_MODE_FALLING_EDGE, encodersUpdate);
			uint8_t j;
			for(j=0; j< MAX_ENCODER_QUEUE; j++)
				encoderArray[i].eventQueue[j] = END_OF_ENCODER_QUEUE;
			break;
		}
	return id;
}

/**
 * @brief Disables a given encoder
 * @param id: the id of the given encoder
 */
void disableEncoder(encoderID id){
	if(isValidEncoderID(id))
		encoderArray[id].enable = false;
}
/**
 * @brief Enables a given encoder
 * @param id: the id of the given encoder
 */
void enableEncoder(encoderID id){
	if(isValidEncoderID(id))
		encoderArray[id].enable = true;
}
/**
 * @brief Informs on whether or not a given encoder is enabled
 * @param id: the id of the given encoder
 * @return TRUE if a encoder is enabled, FALSE if the encoder deesn't exist or is disabled
 */
bool isEncoderEnabled(encoderID id){
	bool ret = false;
	if(isValidEncoderID(id))
		ret = encoderArray[id].enable;
	return ret;
}

/*******************************************************************************
 *******************************************************************************
                        PRIVATE FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
/**
 * @brief Queue a new event on the given encoder
 * @param id: the id of the given encoder
 * @param event: the event that needs to be queued
 */
void appendEncoderEvent(encoderID id, encoderEvents event){
//	if(isValidEncoderID(id)){
//		encoderArray[id].flag = true;
//		encoderArray[id].eventQueue[encoderArray[id].eventEndIndex] = event;	//Load event
//		if(encoderArray[id].eventEndIndex != encoderArray[id].eventBeginIndex){	//If Begin and End are equal at the interrupt point, there weren't any new events before
//			if((encoderArray[id].eventEndIndex + 1) < MAX_ENCODER_QUEUE)	//If the index hasn't reached the end of the circular buffer
//				encoderArray[id].eventEndIndex++;							//Point to the next event in the queue
//			else
//				encoderArray[id].eventEndIndex = 0;							//Else, go back to the beginning of the queue
//
//			if(encoderArray[id].eventEndIndex == encoderArray[id].eventBeginIndex){	//If the END index will overwrite useful data
//				if((encoderArray[id].eventBeginIndex + 1) < MAX_ENCODER_QUEUE)		//BEGIN will point to next oldest event
//					encoderArray[id].eventBeginIndex++;								//One event (the oldest) will be lost, but it's not likely
//				else																//If the user pulls events often enough
//					encoderArray[id].eventBeginIndex = 0;
//			}
//		}
//	}
	if(isValidEncoderID(id)){
		if (encoderArray[id].eventEndIndex != (encoderArray[id].eventBeginIndex + LEN(encoderArray[id].eventQueue)))
			{
				encoderArray[id].eventQueue[encoderArray[id].eventEndIndex] = event;
				encoderArray[id].eventEndIndex = (++encoderArray[id].eventEndIndex) % (LEN(encoderArray[id].eventQueue));
				encoderArray[id].flag = false;
			}
	}
}

/**
 * @brief validates encoder ID
 * @param id: the id of the given encoder
 * @return either TRUE or FALSE
 */
bool isValidEncoderID(encoderID id){
	bool valid = false;
	uint8_t i;
	for(i=0; i<MAX_ENCODERS; i++){
		if(encoderArray[i].id == id)
			valid = true;
	}
	return valid;
}

/*******************************************************************************
                        TIMER ZONE
 ******************************************************************************/
/**
 * @brief Updates buttons events with timers
 */
void encodersUpdate(void){
	uint8_t i;
	bool pinA;
	for(i=0; i < MAX_ENCODERS; i++){				//Go through every encoder
		if((encoderArray[i].enable == true) && (timerExpired(encoderArray[i].timer))){		//If it's enabled and it's timer expired
			//We know that pinB went from HIGH to LOW, since its interrupt is FALLING_EDGE
			pinA = gpioRead(encoderArray[i].pinA);											//Read input at pinA
			if(pinA == HIGH)																//If B went LOW before A
				appendEncoderEvent(i, ENCODER_LEFT);												//It's COUNTERCLOCKWISE
			else
				appendEncoderEvent(i, ENCODER_RIGHT);												//If not, it's CLOCKWISE
			timerStart(encoderArray[i].timer, TIMER_MS2TICKS(ENCODER_REFRESH_PERIOD), TIM_MODE_SINGLESHOT, NULL);	//Reset the timer
		}
	}
	return;
}
