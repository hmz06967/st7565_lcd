#ifndef _CONF_H
#define _CONF_H

#ifdef __cplusplus
extern "C" {
#endif

#include <Arduino.h>
#include "lcd.h"
#include "main.h"

//IO CONF

//DEBUG ON 
#define DEBUG 1

//#define HIGH 1
//#define LOW 0

//OUTPUT
#define LCD_RST_PIN D4
#define LCD_DC_PIN D3

//SPI1 (use lcd)
#define SPI_SCK_PIN1 SCK
#define SPI_CS_PIN1 SS
#define SPI_MOSI_PIN1 MOSI
#define SPI_MISO_PIN1 MISO

void setup_pin(void);

#ifdef __cplusplus
}
#endif
#endif
