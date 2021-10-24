/***************************************************************************//**
  @file     sevenseg.c
  @brief    +Descripcion del archivo+
  @author   Gian
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "gpio.h"
#include "board.h"
#include "sevenseg.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

/******************
 * Seven Seg Mode *
 * ****************/
#define COMMON_CATHODE

#if defined(COMMON_CATHODE)
  #define SEG_ON	HIGH
  #define SEG_OFF	LOW

#elif defined(COMMON_ANODE)
  #define SEG_ON	LOW
  #define SEG_OFF	HIGH

#endif

/***********
 * Displays *
 * *********/
#define DIG0    0x00 //0b00000000
#define DIG1    0x01 //0b00000001
#define DIG2    0x02 //0b00000010
#define DIG3    0x03 //0b00000011

#define SEL0_VAL(n) (n & 1)
#define SEL1_VAL(n) (n & 2)

/********
 * Pins *
 * ******/
#define SEGA     DIO_0
#define SEGB     DIO_1
#define SEGC     DIO_2
#define SEGD     DIO_3
#define SEGE     DIO_4
#define SEGF     DIO_5
#define SEGG     DIO_6
#define SEGDP    DIO_7

#define SEL0     DIO_14
#define SEL1     DIO_15

/**********
 * Indexs *
 * ********/
#define BLANK_IDX       36 // Must match with 'digitCodeMap'
#define DASH_IDX        37
#define PERIOD_IDX      38
#define ASTERISK_IDX    39
#define UNDERSCORE_IDX  40


/********
 * Masks *
 * ******/
#define MASK_SEGA   0x01 //0b00000001
#define MASK_SEGB   0x02 //0b00000010
#define MASK_SEGC   0x04 //0b00000100
#define MASK_SEGD   0x08 //0b00001000
#define MASK_SEGE   0x10 //0b00010000
#define MASK_SEGF   0x20 //0b00100000
#define MASK_SEGG   0x40 //0b01000000
#define MASK_SEGDP  0x80 //0b10000000


#ifndef ON
#define ON 1
#define OFF 0
#endif

#define MAX_LENGTH 255
#define SCROLL_TIME 600
#define DISP_LENGTH 4
#define MAX_INTENSITY 20
#define BLINK_TIME 500
#define NSEGS 8

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

typedef uint8_t digit_t;

/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: unsigned int anio_actual;+


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

/**
 * @brief Saves the text to put on display
 * @param text pointer to the text you wish to display
 */
static void save_buffer(char* text, uint8_t n);

/**
 * @brief Cleans the buffer
 */
static void clean_buffer(void);

/**
 * @brief Trasnforms ascii to BCD
 * @param chara pointer to the character you wish to transalate
 */
static uint8_t ascii_to_bcd(char* chara);


/**
 * @brief Selects a digit of the display
 * @param digi the digit you wish to use or select
 */
static void digit_select(digit_t digi);


/**
 * @brief Cleans a digit of the display
 * @param digi the digit you wish to clean
 */
static void digit_off(digit_t digi);

/**
 * @brief Turns on a specific segment
 * @param seg the segment you wish to turn on
 */
static void segment_on(pin_t seg);

/**
 * @brief Turns off a specific segment
 * @param seg the segment you wish to turn off
 */
static void segment_off(pin_t seg);


/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

static const uint8_t charCodeMap[] = {
		//   GFEDCBA  ASCII			   Segments
  0x3F,	//0b00111111 // 48  "0"          AAA
  0x06, //0b00000110 // 49  "1"         F   B
  0x5B, //0b01011011 // 50  "2"         F   B
  0x4F, //0b01001111 // 51  "3"          GGG
  0x66, //0b01100110 // 52  "4"         E   C
  0x6D, //0b01101101 // 53  "5"         E   C
  0x7D, //0b01111101 // 54  "6"          DDD
  0x07, //0b00000111 // 55  "7"
  0x7F, //0b01111111 // 56  "8"
  0x6F, //0b01101111 // 57  "9"
  0x77, //0b01110111 // 65  'A'
  0x7C, //0b01111100 // 66  'b'
  0x39, //0b00111001 // 67  'C'
  0x5E, //0b01011110 // 68  'd'
  0x79, //0b01111001 // 69  'E'
  0x71, //0b01110001 // 70  'F'
  0x3D, //0b00111101 // 71  'G'
  0x74, //0b01110100 // 72  'H'
  0x30, //0b00110000 // 73  'I'
  0x1E, //0b00001110 // 74  'J'
  0x76, //0b01110110 // 75  'K'  Same as 'H'
  0x38, //0b00111000 // 76  'L'
  0x00, //0b00000000 // 77  'M'  NO DISPLAY
  0x54, //0b01010100 // 78  'n'
  0x5C, //0b00111111 // 79  'O'
  0x73, //0b01110011 // 80  'P'
  0x67, //0b01100111 // 81  'q'
  0x50, //0b01010000 // 82  'r'
  0x6D, //0b01101101 // 83  'S'
  0x78, //0b01111000 // 84  't'
  0x3E, //0b00111110 // 85  'U'
  0x3E, //0b00111110 // 86  'V'  Same as 'U'
  0x00, //0b00000000 // 87  'W'  NO DISPLAY
  0x76, //0b01110110 // 88  'X'  Same as 'H'
  0x6E, //0b01101110 // 89  'y'
  0x5B, //0b01011011 // 90  'Z'  Same as '2'
  0x00, //0b00000000 // 32  ' '  BLANK
  0x40, //0b01000000 // 45  '-'  DASH
  0x80, //0b10000000 // 46  '.'  PERIOD
  0x63, //0b01100011 // 42 '*'  DEGREE ..
  0x08, //0b00001000 // 95 '_'  UNDERSCORE
};

const uint8_t * const numberCodes = charCodeMap;
const uint8_t * const letterCodes = charCodeMap + 10;

static const pin_t pinMap[] = {SEGA, SEGB, SEGC, SEGD, SEGE, SEGF, SEGG, SEGDP, SEL0, SEL1};
static const digit_t digitMap[] = {DIG0, DIG1, DIG2, DIG3};
static const uint8_t maskSegMap[] = {MASK_SEGA, MASK_SEGB, MASK_SEGC, MASK_SEGD, MASK_SEGE, MASK_SEGF, MASK_SEGG, MASK_SEGDP};

/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

static uint8_t buffer[MAX_LENGTH];
static uint8_t brightness = DISP_LENGTH;
static uint8_t scroll_mode = OFF;
static uint8_t string_length = 0;
static uint8_t blink_mode = 0;

static uint8_t inx = 0;
static uint8_t pos = 0;
static uint32_t scroll = 0;
static uint32_t blink = 0;

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void display_init(void)
{
  for (uint8_t i=0; i < 10; i++)
  {
    gpioMode(pinMap[i], OUTPUT,DSE_DEFAULT,ODE_DEFAULT,SRE_DEFAULT,PFE_DEFAULT,DFE_DEFAULT,0);
  }

  display_clear();
}

void display_text(char* text, sevenseg_modes mode, uint8_t blinking_char)
{
	inx = 0;
	pos = 0;
	scroll = 0;
	blink = 0;
	blink_mode = blinking_char;

    switch (mode)
    {
    case DISPLAY_LEFT: //Show first 4
    save_buffer(text,DISP_LENGTH);
    scroll_mode = OFF;
    string_length = DISP_LENGTH;
      break;

    case DISPLAY_RIGHT: //Show last 4
    text = text + strlen(text) - DISP_LENGTH;
    save_buffer(text,DISP_LENGTH);
    scroll_mode = OFF;
    string_length = DISP_LENGTH;
      break;

    case DISPLAY_SCROLL: //Scroll
    string_length = strlen(text);
    save_buffer(text,string_length);
    scroll_mode = ON;
      break;

    default:
    save_buffer(text,MAX_LENGTH);
      break;
    }
}

void display_refresh(void)
{
  if(pos > brightness){pos = 0;}

  if((scroll_mode == ON) && (scroll > SCROLL_TIME))
  {
	  inx++;
	  scroll = 0;
  }

  if(inx > string_length){inx = 0;}

  if(pos < DISP_LENGTH)
  {
    if(blink_mode == digitMap[pos] && blink > BLINK_TIME )
    {
    	digit_off(digitMap[pos]);
    	if(blink >= (2*BLINK_TIME)){blink=0;}
    }

    else
    {
        digit_select(digitMap[pos]);
		for (uint8_t j = 0; j < NSEGS; j++)
		{
		  if((bool)(buffer[pos+inx] & maskSegMap[j])){segment_on(pinMap[j]);}
		  else{segment_off(pinMap[j]);}
		}
    }

  }

  else
  {
    digit_off(digitMap[0]);
  }

  blink++;
  scroll++;
  pos++;

}

void display_intensity(uint8_t intensity)
{
	if(intensity > MAX_INTENSITY){intensity = MAX_INTENSITY;}
	brightness = MAX_INTENSITY - intensity + DISP_LENGTH;
}

void display_clear(void)
{
  for (uint8_t i = 0; i < DISP_LENGTH; i++)
  {
	  digit_select(digitMap[i]);
	  for (uint8_t i = 0; i < NSEGS; i++)
	  {
	    segment_off(pinMap[i]);
	  }
  }
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

static void save_buffer(char* text, uint8_t n)
{
  uint8_t i;
  for(i = 0; *(text+i) != '\0' && i < n ; i++)
  {
    buffer[i] = ascii_to_bcd(text+i);
  }

  for(;i < (sizeof(buffer)/sizeof(buffer[0])) ; i++)
  {
	  buffer[i] = 0;
  }

}

static void clean_buffer(void)
{
  for(uint8_t i = 0; i < (sizeof(buffer)/sizeof(buffer[0])) ; i++)
  {
      buffer[i] = 0;
  }
}

static uint8_t ascii_to_bcd(char* chara)
{
  uint8_t new_char = 0;

  if((*chara >= '0') && (*chara <= '9'))
  {
    new_char = numberCodes[(*chara-'0')];
  }

  else if((*chara >= 'A') && (*chara <= 'Z'))
  {
    new_char = letterCodes[(*chara-'A')];
  }

  else if((*chara >= 'a') && (*chara <= 'z'))
  {
    new_char = letterCodes[(*chara-'a')];
  }

  else if(*chara == ' ')
  {
    new_char = charCodeMap[BLANK_IDX];
  }

  else if(*chara == '-')
  {
    new_char = charCodeMap[DASH_IDX];
  }

  else if(*chara == '.')
  {
    new_char = charCodeMap[PERIOD_IDX];
  }

  else if(*chara == '*')
  {
    new_char = charCodeMap[ASTERISK_IDX];
  }

  else if(*chara == '_')
  {
    new_char = charCodeMap[UNDERSCORE_IDX];
  }

  else
  {
    new_char = charCodeMap[BLANK_IDX];
  }

  return new_char;
}

static void digit_select(digit_t digi)
{
  gpioWrite(SEL0, (bool)SEL0_VAL(digi));
  gpioWrite(SEL1, (bool)SEL1_VAL(digi));

}

static void digit_off(digit_t digi)
{
  digit_select(digi);
  for (uint8_t i = 0; i < NSEGS; i++)
  {
	segment_off(pinMap[i]);
  }
}

static void segment_on(pin_t seg)
{
  gpioWrite(seg, SEG_ON);
}

static void segment_off(pin_t seg)
{
  gpioWrite(seg, SEG_OFF);
}


