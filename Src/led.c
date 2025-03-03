#include "led.h"

void led_all_on(void);
void led_all_off(void);
void led2_toggle(void);
void led_on_up(void);
void led_on_down(void);
void led_keppon_up(void);
void led_keepon_down(void);
void flower_on(void);
void flower_off(void);

extern t1ms_counter;

void led_all_on(void){
	HAL_GPIO_WritePin(GPIOB, 0xff, 1);
	// 요렇게 하는 것과 같음
/*	HAL_GPIO_WritePin(GPIOB,
			GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
			,1);*/
}
void led_all_off(void){
	HAL_GPIO_WritePin(GPIOB, 0xff, 0);
	// 요렇게 하는 것과 같음
/*	HAL_GPIO_WritePin(GPIOB,
			GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
			,0);*/
}


void led2_toggle(void){
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}

// 0 -> 1..... ->7
void led_on_up(){
	for(int i=0; i<8;i++){
		led_all_off();
		HAL_GPIO_WritePin(GPIOB, 0x01 << i, 1);
		HAL_Delay(200);
	}
}

// 7->6->5...->0
void led_on_down(){
	for(int i=0; i<8;i++){
		led_all_off();
		HAL_GPIO_WritePin(GPIOB, 0x80 >> i, 1);
		HAL_Delay(200);
	}
}

// 0->1->....->7 기존 on된 것 끄지말고 유지하기
void led_keppon_up(){
	uint16_t pattern = 0x01;
	led_all_off();
	HAL_Delay(100);
	for(int i=0; i<8;i++){
		HAL_GPIO_WritePin(GPIOB, pattern, 1);
		HAL_Delay(200);
		pattern = pattern << 1 | 0x01;
	}
}
// 7->6->5->....->0 기존 off된 것 끄지말고 유지하기
void led_keepon_down(){
	uint16_t pattern = 0x80;
	led_all_on();
	HAL_Delay(100);
	for(int i=0; i<8;i++){
		// GPIO_PIN_SET : if it's set to 0, the pin is not affected.
		// 	HAL_GPIO_WritePin(GPIOB, pattern, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, pattern>>i, GPIO_PIN_RESET);
		HAL_Delay(200);
	}
}

void flower_on(){
	led_all_off();
	HAL_Delay(100);
	for(int i=0;i<4;i++){
		HAL_GPIO_WritePin(GPIOB,(0b00001000 >> i) | (0b00010000 << i), GPIO_PIN_SET);
		HAL_Delay(200);
	}
}

void flower_off(){
	led_all_on();
	HAL_Delay(100);
	for(int i=0;i<4;i++){
		HAL_GPIO_WritePin(GPIOB,(0b10000000 >> i) | (0b00000001 << i), GPIO_PIN_RESET);
		HAL_Delay(200);
	}
}
