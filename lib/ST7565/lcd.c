#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "main.h"
#include "lcd.h"
#include "ST7565.h"
#include "glc_st7565.h"
#include "graphics.h"
#include "font.h"
#include "font_verdana.h"

//#include "font_tahoma.h"
//#include "font_arialblack.h" 
//#include "font_webdings.h"
//#include "font_wingdings.h"
//#include "font_lucidaconsole.h"

/*MAIN*/

extern const uint8_t p_logo[] ;
extern const uint8_t p_one[] ;
bounding_box_t ret;
extern One_Page data;
extern Page page_stat;
extern Button menu_cont;
extern Sound sound;
extern Times times; 
extern uint8_t font_color;
char buffer[128];

//uint32_t time,end_time;

int8_t drawn_box = 0, vlctround = 0, center = 0;


char disp_title_menu2[][9]  = {
	" MENU",
	"Ucus",
	"Task",
	"SD Kart",
	"Kalibre",
	"Ekran",
	"Ses",
	"Saat",
	"Log",
	"WiFi",
	"Bilgi"
};

char disp_title_menu4[][9]  = {
	"KALiBRE",
		"AUTO",
	"ivme X:",
	"ivme Y:",
	"ivme Z:",
	"gyro X:",
	"gyro Y:",
	"gyro Z:",
	"mag X:",
	"mag Y:",
	"mag Z:"
};

char disp_title_menu5[][9]  = {
	"EKRAN",
	"konstr:",
	"ters ek:",
	"ana-ek:",
	"term:"
};

char disp_title_menu6[][9]  = {
	"SES",
	"acik:",
	"ton:",
	"seviye:",
	"",
	"UYARI",
	"sarj:",
	"term:",
	"hiz:"
};

char disp_title_menu7[][9]  = {
	"ZAMAN",
	"acik:",
	"saat:",
	"dakk:",
	"gun",
	"ay:",
	"yil:",
	"AUTO"
};

unsigned char wok_ico;
char v1,v2;

Screen screen = {1,0x01,0x00,0,1};


uint8_t cal_center( char *string, uint8_t space){
	return (64-text_width(string,Verdana8,space))/2;
	//return (int)(64-sizeof(string))/4;
}

void lcd_print_page(uint8_t page){
	if(page==0){
		ST7565_drawbitmap(0,9,p_logo,128,48,1);
	}else if(page==LCD_PAGE_1){
		ST7565_drawbitmap(0,0,p_one,128,64,1);
	}
	glcd_refresh();
}

void lcd_print_err(unsigned int code){
	snprintf(buffer, sizeof(buffer),"e%d",code);
	draw_text(buffer,4,41, Verdana8,1);
}

void lcd_audio_mute(){
	uint8_t adm_logo[] = {0x18,0x2A,0xC4,0x88,0x90,0xA8,0x48,0x98};
	uint8_t ad_logo[] = {0x18,0x2A,0xCB,0x8B,0x8B,0xCB,0x2A,0x18};
		
	if(!data.true_audio){
		ST7565_drawbitmap(2,15,adm_logo,8,8,1);
	}else{
		ST7565_drawbitmap(2,15,ad_logo,8,8,1);
	}

}

void lcd_vario_progress(){
	//data.progress = (int)map(data.velocity, -9.90, 9.90, 0, 15);

	uint8_t pmap[8] = {0,2,3,5,6,8,10},
	i = 0,
	c = 1,
	k = 63;

	//int8_t vlct = 0;
	
	vlctround = round(data.velocity);

	
	while(i < sizeof(pmap)){
		c = i>abs(vlctround) ? 0 : 1;
		if(vlctround>0){
			draw_bar(k-(i*3), 0, pmap[i], 2, c); 
			draw_bar(k+6-(-i*3), 0, pmap[i], 2, 0); 
		}
		else if(vlctround<0){
			draw_bar(k-(i*3), 0, pmap[i], 2, 0); 
			draw_bar(k+6-(-i*3), 0, pmap[i], 2, c); 
		}	
		i++;
	}
	
} 

void lcd_gps_volume(){
	uint8_t pmap[8] = {0,2,3,4,5,7},
	  i = 0,
	  c = 0;
	while(i < 6){
		c = i<=data.gps_signal;
		draw_bar((8-pmap[i]),52+2*i,1,pmap[i], c);
		i++;
	}
}


void lcd_menu_select_row(uint8_t page){
	
	if(_BFC(menu_cont.top)){
		page_stat.row -= page_stat.row > page_stat.min ? 1 : 0;
		menu_cont.flag = 0;
		draw_bar(ret.x1, ret.y1, wok_ico,Verdana8[4],0);//bir �nceki ok tusunu sil
	}
	else if(_BFC(menu_cont.bottom)){
		page_stat.row += page_stat.row < page_stat.max ? 1 : 0;
		menu_cont.flag = 0;
		draw_bar(ret.x1, ret.y1, wok_ico,Verdana8[4],0);//bir �nceki ok tusunu sil
	}
	else if(_BFC(menu_cont.esc)){
		menu_cont.flag = 0;
		glcd_blank();
		if(page_stat.number ==2){//ayarlar sayfasindan one_page sayfasina gel
			page_stat.row = 1;
			lcd_print_page(1);
		}
		lcd_print(page);//1. sayfada ok tusu ayarlari a�ar.
	}
	else if(_BFC(menu_cont.ok)){
		menu_cont.flag = 0;
		if(page==screen.screen){//start vario
			
		}
		if(page==LCD_PAGE_4){//kalibre
			//auto set
		}
		if(page==LCD_PAGE_7){//saat
			//auto set 
		}
	}

	else if(_BFC(menu_cont.left)||_BFC(menu_cont.right)){
		
		if(page==LCD_PAGE_4){//sd kart
			//each folder/file from sd kart
			
		}
		else if(page==LCD_PAGE_5){//ekran
			switch(page_stat.row){
				case 1://konstrat
					if(_BFC(menu_cont.left))
						screen.constrat -= screen.constrat<0x03 ? 0 : 1;
					glcd_contrast(0,screen.constrat);
				break;
				case 2: //ters
					if(_BFC(menu_cont.left))
						screen.reverse = screen.reverse==0 ? 1 : 0;
					glcd_inverse_screen(screen.reverse);
				break;
				case 3://ana ekran
					screen.screen = 0;
				break;
				case 4:
				break;
				case 5://term ekranda g�sterilsin mi ?
					screen.term = screen.term==0 ? 1 : 0;
				break;
			}
		}
		else if(page==LCD_PAGE_6){//ses 
			switch(page_stat.row){
				case 1: 
					sound.on = sound.on > 0 ? 0 : 1; 
				break;
				case 2: 
					if(_BFC(menu_cont.left))
						sound.tone -= sound.tone < 1 ? 0 : 1; 
				break;
				case 3: 
					if(_BFC(menu_cont.left))
						sound.level -= sound.level < 1 ? 0 : 1;
				break;
				case 5: 
					if(_BFC(menu_cont.left))
						sound.warning -= sound.warning < 1 ? 0 : 1;
				break;
				case 6:
					if(_BFC(menu_cont.left))
						sound.charge -= sound.charge < 1 ? 0 : 1;
				break;
				case 7: 
					if(_BFC(menu_cont.left))
						sound.term -= sound.term < -19 ? -20 : 1;
				break;
				case 8:
					if(_BFC(menu_cont.left))
						sound.speed -= sound.speed < 1 ? 0 : 1;
				break;
			}
		}
		else if(page==LCD_PAGE_7){//zaman
			switch(page_stat.row){
				case 1:
					times.on = times.on > 0 ? 0 : 1; 
				//update time
				break;
				case 2: 
					if(_BFC(menu_cont.left))
						times.hours -= times.hours < 1 ? 0 : 1; 
				break;
				case 3: 
					if(_BFC(menu_cont.left))
						times.minute -= times.minute < 1 ? 0 : 1;
				break;
				case 5: 
					if(_BFC(menu_cont.left))
						times.day -= times.day < 1 ? 0 : 1;
				break;
				case 6:
					if(_BFC(menu_cont.left))
						times.month -= times.month < 1 ? 0 : 1;
				break;
				case 7: 
					if(_BFC(menu_cont.left))
						times.year -= times.year < 1 ? 0 : 1;
				break;
			}
		}			
	}
}


/*men� ok simgesi, y�n tuslari ile asagi yukari hareketi saglanacak
	[page] degiskeni ile sayfa numarasina g�re �zel g�sterimler yapacak.
		kural: her sayfanin kendine ait kontrol �zellikleri lcd de g�r�nt�lenir.
	y�n tuslari lcd ekrandaki konum bilgisini g�nceller, set veya y�n tuslari ile veri degistirilir.

	menu_cont.flag: butonlardan herhangi biri yakalandiginda flag a�ik olur. 
									a�ik flag buton numarasini belirtir.
									kapatilma islemi yakalanan fonksiyon ile yapilir.
*/
void lcd_menu_control(){
	
	switch(page_stat.number){
		case LCD_PAGE_1:
			if(_BFC(menu_cont.ok)){
				page_stat.flag = 0;
				glcd_clear();
				lcd_print(2);//1. sayfada ok tusu ayarlari a�ar.
			}
		break;
		case LCD_PAGE_2:
		
			if(_BFC(menu_cont.ok) && page_stat.row>2 && page_stat.row<8){
				glcd_clear();
				lcd_print(page_stat.row);//1. sayfada ok tusu ayarlari a�ar.
				page_stat.row = 1;
			}
			lcd_menu_select_row(1);
		break;
		case LCD_PAGE_3:
			lcd_menu_select_row(2);
		break;
		case LCD_PAGE_4://kalibre
			lcd_menu_select_row(2);
		break;
		case LCD_PAGE_5://ekran
			lcd_menu_select_row(2);
		break;
		case LCD_PAGE_6://ses
			lcd_menu_select_row(2);
		break;
		case LCD_PAGE_7://saat 
			lcd_menu_select_row(2);
		break;
	}

	if(page_stat.number >1 && menu_cont.flag==0){
		//print select
		ret = draw_text("<",page_stat.row*Verdana8[4],64-wok_ico, Verdana8, 1);
		glcd_refresh();

		menu_cont.flag = 1;	
	}
	
	page_stat.min = pprmin;
	page_stat.max = pprmax;
}

void lcd_draw_menu_title(char *string, uint8_t i, uint8_t space){
	space = i==0 ? 2 : 1;
	center = i==0 ? cal_center(string,space): 2; 
	snprintf(buffer, 9, "%s", string);
	draw_text(buffer,i*Verdana8[4],center, Verdana8, space);
	draw_line(Verdana8[4]-1,64,Verdana8[4]-1,1,1);
}

void lcd_battery_volume(){
	uint8_t i = 0,
		k = 4;
	
	while(i < 4){
		draw_bar(k,3+2*i+1,1,2, i<data.battery);
		i++; 
	}
}

void lcd_print(uint8_t page){
	
	//time = HAL_GetTick();
	uint8_t i = 0,
			space = 0;
	
	switch(page){
		case LCD_PAGE_1://ANA SAYFA
			page_stat.number = 1;
			page_stat.flag = 1;
			lcd_vario_progress();
			lcd_battery_volume();
			lcd_gps_volume();
			lcd_audio_mute();

		//print baro alt
			snprintf(buffer, sizeof(buffer), "%d",data.gps_alt);
			draw_text(buffer,15,39, Verdana8,1);
			
		//print gps alt
			snprintf(buffer, sizeof(buffer), "%d",data.baro_alt);
			draw_text(buffer, 15,3, Verdana8,1);
		
		//print velocity m/s
			//v0 = ((data.velocity)>0.0 ? ' ' : '-');
			snprintf(buffer, sizeof(buffer), "%s",((data.velocity)>0.0 ? "   " : "-"));
			v1 = abs((int)(data.velocity*10/10)) + '0';
			v2 = abs((int)(data.velocity*10) % 10 ) + '0'; 
		
		  	draw_text(buffer,57,4, ArialBlack14,0);  
			draw_char(v1, 57,13, ArialBlack14); 
			draw_char(v2,57,29, ArialBlack14);
			
		//print ground speed
			snprintf(buffer, sizeof(buffer), "%0.1f",data.gspeed);
			draw_text(buffer,40,25, Verdana8, 1);
		
		//print left_dist km
			snprintf(buffer, sizeof(buffer), "%d",data.left_dist);
			draw_text(buffer,76,30, Verdana8,1);
			
		//print total_dist km 
			snprintf(buffer, sizeof(buffer), "%d",data.left_dist);
			draw_text(buffer,87,30, Verdana8,1);
		
			//print term
			snprintf(buffer, sizeof(buffer), "%0.0f",data.term);
			draw_text(buffer,101,38, Verdana8,1);
			
		break;
		
		case LCD_PAGE_2://AYARLAR
			page_stat.number = 2;
			for(i=0;i<11;i++){	
				space = i==0 ? 2 : 1;
				center = i==0 ? cal_center(disp_title_menu2[i],space) : 2;  
				snprintf(buffer, 9, "%s", disp_title_menu2[i]); 
				draw_text(buffer,i*Verdana8[4],center, Verdana8,space);
			}
			draw_line(Verdana8[4]-1,64,Verdana8[4]-1,1,1);
		break;
			
		case LCD_PAGE_3://SD-KART
			page_stat.number = 3;
			i=0;
			lcd_draw_menu_title("SD-KART",i,2);
			lcd_menu_control();
			i++;
			
		break;
		
		case LCD_PAGE_4://KALIBRE
			page_stat.number = 4;
			page_stat.min = 10;
			page_stat.row = page_stat.min;
			lcd_draw_menu_title(disp_title_menu4[0],0,2);
			for(i=1;i<11;i++){
				snprintf(buffer,(i==1 ? 6 : 14),"%s %0.2f",disp_title_menu4[i], 0.0);
				draw_text(buffer,i*Verdana8[4],2, Verdana8,1);
			}
		break;
		
		case LCD_PAGE_5://EKRAN
			page_stat.number = 5;
			lcd_draw_menu_title(disp_title_menu5[0],0,2);
			for(i=1;i<5;i++){
				snprintf(buffer,14,"%s %d",disp_title_menu5[i], 1);
				draw_text(buffer,i*Verdana8[4],2, Verdana8,1);
			}
		break;
		
		case LCD_PAGE_6://SES
			page_stat.number = 6;
			lcd_draw_menu_title((char*)disp_title_menu6[0],0,2);
			for(i=1;i<9;i++){
				if(i==4)
					continue;
				if(i==5){
					draw_text((char*)disp_title_menu6[i],i*Verdana8[4],2, Verdana8,1);
					continue;
				}
				snprintf(buffer,14,"%s %d",disp_title_menu6[i], 1);
				draw_text(buffer,i*Verdana8[4],2, Verdana8,1);
			}
		break;
		
		case LCD_PAGE_7://SAAT
			page_stat.number = 7;
			lcd_draw_menu_title(disp_title_menu7[0],0,2);
			for(i=1;i<8;i++){
				if(i==7){
					draw_text((char*)disp_title_menu7[i],i*Verdana8[4],2, Verdana8,1);
					continue;
				}
				snprintf(buffer,14,"%s %d",disp_title_menu7[i], 1);
				draw_text(buffer,i*Verdana8[4],2, Verdana8,1);
			}
		break;
		
		default:
			lcd_print_page(0);//LOGO
		break;
			
	}
	
	glcd_refresh();
	
	//end_time = HAL_GetTick() - time;
}

void lcd_print_task(){
	if(page_stat.flag==1){//güncelleme aktif
		lcd_print(page_stat.number); 
	}
}

void start_lcd(){
	ST7565_begin(screen.constrat);
	//HAL_SPI_TransmitReceive(&hspi2,buffer_tx_spi, buffer_rx_spi, sizeof(buffer_tx_spi), 1);
	//while(HAL_SPI_GetState(&hspi2) != HAL_SPI_STATE_READY){};
	//	ST7565_clear_display();
	//	ST7565_drawstring(0,0,"FLYOZKAN");
	//	ST7565_display();
	//	ST7565_drawchar(0,0,'A');
	//	ST7565_display();

	/**************************************/
	menu_cont.flag = 0;
	wok_ico = text_width("<",Verdana8,1);//ok belirteci i�in lcd genislik hesabi
	
	//ST7565_clear();
	glcd_blank();
	lcd_print(0);//LOGO PAGE
	glcd_refresh();
	//ST7565_display();
	ST7565_clear();
	glcd_clear(); 
	lcd_print_page(page_stat.number);


	//HAL_Delay(2000);
	//ST7565_drawchar_vert(10,6,'A');
	//glcd_test_card();
	//HAL_Delay(2000);
	//page_stat.number = 7;
	//lcd_print(7);//MEN� PAGE

	//lcd test
  /*
	float j = -10.0;
	lcd_print_page(1);
	while(1){
		data.velocity = j;//m/s hiz 
		data.battery = (int)j%4; //battery doluluk[1-4]
		data.true_audio = 1;//ses kullan
		data.gps_signal = 5;
		lcd_print(1);

	if(j>=10.0)
		j = 5.0;

	j +=0.1;
	}*/
	

}

void start_glcd(){
	//ST7565_begin(0x08, hspi2);
	ST7565_begin(screen.constrat);
	while(1) glcd_test_card();
}
