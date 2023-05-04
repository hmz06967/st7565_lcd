#ifndef _LCD_H
#define _LCD_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define LCD_PAGE_1 1
#define LCD_PAGE_2 2
#define LCD_PAGE_3 3
#define LCD_PAGE_4 4
#define LCD_PAGE_5 5
#define LCD_PAGE_6 6
#define LCD_PAGE_7 7
#define LCD_PAGE_8 8

#define pprmin 1
#define pprmax 11

typedef struct {
	uint8_t screen;
	char constrat;
	char reverse;
	uint8_t wait; 
	uint8_t term;

} Screen;

void lcd_print(uint8_t page);
void lcd_print_page(uint8_t page);
void start_lcd(void);
void start_glcd(void);
void lcd_menu_control(void);
void lcd_print_task(void);

#ifdef __cplusplus
}
#endif
#endif
