/***************************************************************************//**
  @file     sevenseg.c
  @brief    +Descripcion del archivo+
  @author   Gian
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "sevenseg_app.h"
#include "sevenseg.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

void display_data(uint8_t* data,int index){
	static char arr[200];
	arr[index+1] = '\0';
	for(int i= 0; i<=index;i++){
		arr[i] = (data[i]&0x0F)|0x30;
	}
	if(index<=3){
		display_text(arr, DISPLAY_LEFT, index);
	}else{
		display_text(arr, DISPLAY_RIGHT, 3);
	}

}

void display_secret_data(uint8_t* data,int index){
	static char arr[200];
	arr[index+1] = '\0';
	for(int i= 0; i<=index-1;i++){
		arr[i] ='-';
	}
	arr[index] = (data[index]&0x0F)|0x30;

	if(index<=3){
		display_text(arr, DISPLAY_LEFT, index);
	}else{
		display_text(arr, DISPLAY_RIGHT, 3);
	}
}
