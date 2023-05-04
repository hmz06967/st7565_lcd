/**
  ******************************************************************************
  * @file           : main.cpp
  * @brief          : Main program body
  ******************************************************************************
  * @attention
	sd kart, esp ile haberlesme, log kayitlari bölümü ile kodlari tamamliyoruz.
  ******************************************************************************
  */
#include <Arduino.h>
#include "conf.h"

One_Page data = {
	0.0,//gspeed[0-99.9]
	0.0,//velocity[0-9.9]
	0,//rad dir_det
	0, //total_dist[0-999]
	0, //left_dist[0-999]
	22.3,//term[0-99]
	3,//batt[1-4]
	7,//progress
	4,//gsignal[1-5]
	0,//audio[0-1]
	945,//baro_alt
	1000//gps_alt
	
};

Button menu_cont;

Page page_stat = {
	1,//sayfa
	1,//[row] satir 
	1,//flag#aktif oldugunda ekran güncellemesi aktif olur.
	pprmin,//min row
	pprmax//max row
};

uint32_t k24h_timer, test_i;

Sound sound;
Times times;


void setup() {
	setup_pin();
	start_lcd(); 

	#ifdef DEBUG
		Serial.begin(115200);
	#endif
	//start_glcd();
	main();
}

/*
	her sayfanin, 
		sayfa seçimi
		menü satir seçimi 
		satir içi ayar seçimi bulunmakta.
		sayfa->satir->ayar, satir veri türüne göre degisiyor 
		veri degiskenleri menu kontrol bölümünde anlik olarak degismeli ve sayfa kapandiginda eeproma kaydedilmeli.
		
		UZUN basma, pil için optimize edilmis uyku durumunda cihazi baslaticak olan durum gösterimi 
			# cihaz belirli bir süre boyunca uyku halinde kalarak süre asimi durumunda buton durumu kontrol edilmeli 
			# uzun basma diger menu ayarlarini o sayfa içerisinde aktif kilar.
*/
void system_menu_task(){
	
	menu_cont.size = MENU_CONT_SIZE;
	/*menu_cont.now = GPIO_PIN_3;
	
	while(menu_cont.in_i < menu_cont.size){
		
		menu_cont.butons_state = HAL_GPIO_ReadPin(GPIOB, menu_cont.now);

		switch(menu_cont.now){
			case GPIO_PIN_3:menu_cont.right = menu_cont.butons_state; break;
			case GPIO_PIN_4:menu_cont.bottom = menu_cont.butons_state;break;
			case GPIO_PIN_5:menu_cont.top = menu_cont.butons_state;break;
			case GPIO_PIN_6:menu_cont.esc = menu_cont.butons_state;break;
			case GPIO_PIN_7:menu_cont.ok = menu_cont.butons_state;break;
			case GPIO_PIN_8:menu_cont.set = menu_cont.butons_state;break;
			case GPIO_PIN_9:menu_cont.left = menu_cont.butons_state;break;
			
		}
		
		menu_cont.in_i++;
		menu_cont.now <<=1;
		
	}
	
	lcd_menu_control();
	menu_cont.in_i = 0;*/
}

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
	float j = -10.0;

	
	while (1)
	{
		//bütün buton giris durumlarini sorgula ve buton menü kontrol fonskiyonuna aktar.
		system_menu_task();
		
		//test
		data.velocity = j;//m/s hiz 
		data.battery = (int)j%4; //battery doluluk[1-4]
		data.true_audio = 1;//ses kullan
		data.gps_signal = 5;//[1-5]
		//lcd_print(1);

		if(j>=10.0)
			j = 5.0;

		j +=0.1;
		//lcd_print_task();
		yield();//soft wdt den kurtuluyoruz olley!
	}

}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  while (1)
  {
	//lcd_print_err("404");
  }
}


void _debug(char * text){
  #ifdef DEBUG
    Serial.println(text);
  #endif
}

void DelaymS(int32_t nTime){
	 delay(nTime);
};

void loop() {}
