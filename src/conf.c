#include "conf.h"

void setup_pin(){
    pinMode(SPI_SCK_PIN1, OUTPUT);   
    pinMode(SPI_MOSI_PIN1, OUTPUT);   
    pinMode(SPI_CS_PIN1, OUTPUT);   
    pinMode(LCD_RST_PIN, OUTPUT);   
    pinMode(LCD_DC_PIN, OUTPUT);   
}
