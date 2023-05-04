/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "lcd.h"

typedef struct{
	uint8_t number;
	uint8_t row;
	uint8_t flag;
	uint8_t min;
	uint8_t max;
} Page;

typedef struct{
	float gspeed;
	float velocity;
	float direct_determine;
	unsigned short int total_dist;
	unsigned short int left_dist; 
	float term;
	unsigned short int battery;
	unsigned short int progress;
	unsigned short int gps_signal;
	unsigned short int true_audio;
	uint16_t baro_alt;
	uint16_t gps_alt;
	
	
} One_Page;

typedef struct{
	uint8_t right;
	uint8_t left;
	uint8_t top;
	uint8_t bottom;
	uint8_t ok;
	uint8_t esc;
	uint8_t set;
	uint8_t butons_state;
	uint8_t in_i;
	uint8_t size; 
	uint16_t now;
	uint16_t flag;
} Button;

typedef struct TRACK_ {
   int   year;
   int   month;
   int   day;
   int   hour;
   int   minute;
   float startLatdeg;
   float startLondeg;
   int32_t startAltm;
   int32_t maxAltm;
   float maxClimbrateCps;
   float maxSinkrateCps;
   int32_t startTowmS;
   int32_t distanceFromStartm;
   int32_t elapsedHours;
   int32_t elapsedMinutes;
   int     nextWptInx;
} Track;

typedef struct{
	uint8_t on;
	uint8_t tone;
	uint8_t level;
	uint8_t warning;
	uint8_t charge;
	int8_t term;
	uint8_t speed;
} Sound;

typedef struct{
	uint8_t on;
	uint8_t hours;
	uint8_t minute;
	uint8_t day;
	uint8_t month;
	int8_t year;
} Times;

void Error_Handler(void);
	
void DelaymS(int32_t nTime);


#define GPIO_INPUT_PINS GPIO_PIN_1|GPIO_PIN_2|LD4_Pin|LD3_Pin|GPIO_PIN_6|GPIO_PIN_7
#define MENU_CONT_SIZE 7
#define BUTTON_FLAG_NORMAL 0

#define _BFC(button)   (button==BUTTON_FLAG_NORMAL)

void _debug(char * text);

int main(void);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
