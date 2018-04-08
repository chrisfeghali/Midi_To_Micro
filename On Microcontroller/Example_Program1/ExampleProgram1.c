#include "main.h"
uint32_t PB_RIGHT_pressed(void);
void switch_LED_on(int xvar);
void switch_LED_off(int xvar);
void SysTick_Handler(void);
void SystemClock_Config(void);
void delay_micro_s(uint32_t t);
void PlayTune( const unsigned short notes[], const unsigned short notenum[], const unsigned short timedelay[], int x);
static volatile uint32_t count;
#define notecount 566  // paste notecount here

const unsigned short notes[notecount] = { 1136, 1275, 1136, 758, 851, 955, 1136, 1136, 1275, 1136, 758, 851, 955, 1136, 955, 1012, 1275, 955, 1012,\
 1275, 955, 1012, 1275, 851, 955, 1275, 1136, 1275, 1136, 758, 851, 955, 1136, 1136, 1275, 1136, 758, 851,\
 955, 1136, 955, 955, 955, 851, 851, 758, 758, 758, 851, 851, 1136, 1275, 1136, 758, 851, 955, 1136,\
 1136, 1275, 1136, 758, 851, 955, 1136, 955, 1012, 1275, 955, 1012, 1275, 955, 1012, 1275, 851, 955, 1275,\
 1136, 1275, 1136, 758, 851, 955, 1136, 1136, 1275, 1136, 758, 851, 955, 1136, 758, 803, 851, 901, 955,\
 901, 851, 803, 568, 568, 506, 477, 568, 568, 506, 477, 506, 568, 637, 715, 637, 715, 758, 568,\
 568, 506, 477, 568, 568, 506, 477, 506, 568, 637, 715, 637, 715, 758, 955, 955, 1012, 955, 955,\
 851, 758, 851, 955, 851, 955, 1136, 1136, 1275, 1136, 1136, 1136, 851, 955, 851, 955, 851, 758, 955,\
 955, 1012, 955, 955, 851, 758, 851, 955, 851, 955, 1136, 1136, 1275, 1136, 1136, 1136, 1012, 955, 851,\
 758, 758, 851, 851, 851, 955, 1136, 955, 851, 851, 955, 851, 637, 758, 637, 715, 758, 758, 851,\
 851, 851, 955, 851, 955, 851, 955, 851, 955, 758, 318, 357, 379, 379, 425, 425, 425, 477, 568,\
 477, 425, 425, 477, 425, 318, 379, 318, 357, 379, 379, 425, 425, 425, 477, 425, 477, 425, 477,\
 425, 379, 425, 379, 425, 379, 568, 637, 568, 379, 425, 477, 568, 568, 637, 568, 379, 425, 477,\
 568, 477, 506, 637, 477, 506, 637, 477, 506, 637, 425, 477, 637, 568, 637, 568, 379, 425, 477,\
 568, 568, 637, 568, 379, 425, 477, 568, 477, 477, 477, 425, 425, 379, 379, 379, 425, 425, 568,\
 637, 568, 379, 425, 477, 568, 568, 637, 568, 379, 425, 477, 568, 477, 506, 637, 477, 506, 637,\
 477, 506, 637, 425, 477, 637, 568, 637, 568, 379, 425, 477, 568, 568, 637, 568, 379, 425, 477,\
 568, 379, 401, 425, 450, 477, 450, 425, 401, 568, 568, 506, 477, 568, 568, 506, 477, 506, 568,\
 637, 715, 637, 715, 758, 568, 568, 506, 477, 568, 568, 506, 477, 506, 568, 637, 715, 637, 715,\
 758, 955, 955, 1012, 955, 955, 851, 758, 851, 955, 851, 955, 1136, 1136, 1275, 1136, 1136, 1136, 1275,\
 1516, 1275, 1516, 1275, 1136, 1136, 1136, 1275, 1136, 1136, 1012, 955, 1012, 1136, 1012, 1136, 1136, 1136, 1275,\
 1136, 1136, 1136, 1012, 955, 851, 758, 1136, 1275, 1136, 758, 851, 955, 1136, 1136, 1275, 1136, 758, 851,\
 955, 1136, 955, 1012, 1275, 955, 1012, 1275, 955, 1012, 1275, 851, 955, 1275, 1136, 1275, 1136, 758, 851,\
 955, 1136, 1136, 1275, 1136, 758, 851, 955, 1136, 955, 955, 955, 851, 851, 758, 758, 758, 851, 851,\
 1136, 1275, 1136, 758, 851, 955, 1136, 1136, 1275, 1136, 758, 851, 955, 1136, 955, 1012, 1275, 955, 1012,\
 1275, 955, 1012, 1275, 851, 955, 1275, 1136, 1275, 1136, 758, 851, 955, 1136, 1136, 1275, 1136, 758, 851,\
 955, 1136, 1012, 1072, 1136, 1203, 1136, 1072, 1012, 955, 955, 1012, 1012, 1012, 1136, 1136, 955, 851, 851,\
 637, 851, 637, 758, 637, 715, 758, 758, 851, 851, 851, 955, 851, 955, 851, 955, 851, 955, 758,\
 637, 715, 758, 758, 851, 851, 851, 955, 1136, 955, 851, 851, 955, 851, 637, 758, 637, 715, 758,\
 758, 851, 851, 851, 955, 851, 955, 851, 955, 851, 758, 851, 758, 851, 758};

 const unsigned short notenum[notecount] = { 16, 14, 16, 24, 21, 19, 51, 16, 14, 16, 24, 21, 19, 51, 19, 18, 14, 61, 18,\
 45, 19, 18, 14, 68, 19, 45, 16, 14, 16, 24, 21, 19, 51, 16, 14, 16, 24, 21,\
 19, 51, 19, 19, 19, 21, 21, 24, 24, 24, 21, 21, 16, 14, 16, 24, 21, 19, 51,\
 16, 14, 16, 24, 21, 19, 51, 19, 18, 14, 61, 18, 45, 19, 18, 14, 68, 19, 45,\
 16, 14, 16, 24, 21, 19, 51, 16, 14, 16, 24, 21, 19, 51, 105, 99, 94, 88, 83,\
 88, 94, 99, 70, 70, 79, 587, 70, 70, 79, 251, 237, 211, 565, 167, 188, 55, 263, 70,\
 70, 79, 419, 70, 70, 79, 251, 237, 211, 565, 167, 188, 55, 263, 125, 125, 39, 41, 125,\
 47, 52, 47, 41, 47, 209, 105, 105, 31, 35, 105, 35, 47, 41, 141, 41, 47, 52, 125,\
 125, 39, 41, 125, 47, 52, 47, 41, 47, 209, 105, 105, 31, 35, 105, 105, 118, 125, 141,\
 158, 158, 141, 47, 141, 209, 35, 41, 141, 47, 41, 141, 54, 263, 188, 167, 158, 158, 141,\
 47, 141, 209, 141, 41, 47, 41, 141, 41, 263, 377, 336, 316, 316, 282, 94, 282, 419, 70,\
 83, 282, 94, 83, 282, 125, 527, 377, 336, 316, 316, 282, 94, 282, 419, 282, 83, 94, 83,\
 282, 316, 94, 105, 94, 738, 32, 28, 32, 48, 43, 38, 102, 32, 28, 32, 48, 43, 38,\
 102, 38, 36, 28, 122, 36, 91, 38, 36, 28, 137, 38, 91, 32, 28, 32, 48, 43, 38,\
 102, 32, 28, 32, 48, 43, 38, 102, 38, 38, 38, 43, 43, 48, 48, 48, 43, 43, 32,\
 28, 32, 48, 43, 38, 102, 32, 28, 32, 48, 43, 38, 102, 38, 36, 28, 122, 36, 91,\
 38, 36, 28, 137, 38, 91, 32, 28, 32, 48, 43, 38, 102, 32, 28, 32, 48, 43, 38,\
 102, 211, 193, 184, 177, 167, 177, 188, 199, 70, 70, 79, 587, 70, 70, 79, 251, 237, 211,\
 565, 167, 188, 55, 263, 70, 70, 79, 419, 70, 70, 79, 251, 237, 211, 565, 167, 188, 55,\
 263, 125, 125, 39, 41, 125, 47, 52, 47, 41, 47, 209, 105, 105, 31, 35, 105, 35, 31,\
 26, 94, 26, 31, 35, 105, 105, 31, 35, 105, 39, 41, 39, 35, 39, 176, 105, 105, 31,\
 35, 105, 105, 118, 125, 141, 10, 16, 14, 16, 24, 21, 19, 51, 16, 14, 16, 24, 21,\
 19, 51, 19, 18, 14, 61, 18, 45, 19, 18, 14, 68, 19, 45, 16, 14, 16, 24, 21,\
 19, 51, 16, 14, 16, 24, 21, 19, 51, 19, 19, 19, 21, 21, 24, 24, 24, 21, 21,\
 16, 14, 16, 24, 21, 19, 51, 16, 14, 16, 24, 21, 19, 51, 19, 18, 14, 61, 18,\
 45, 19, 18, 14, 68, 19, 45, 16, 14, 16, 24, 21, 19, 51, 16, 14, 16, 24, 21,\
 19, 51, 79, 74, 70, 66, 70, 74, 79, 116, 125, 118, 39, 118, 176, 35, 41, 141, 47,\
 62, 131, 62, 263, 188, 167, 158, 158, 141, 47, 141, 209, 141, 41, 47, 41, 141, 41, 261,\
 188, 167, 158, 158, 141, 47, 141, 209, 35, 41, 141, 47, 41, 141, 62, 263, 188, 167, 158,\
 158, 141, 47, 141, 209, 141, 41, 47, 41, 141, 158, 47, 52, 47, 428};



 const unsigned short timedelay[notecount] = { 0, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433,\
 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433,\
 433, 433, 433, 433, 1233, 433, 1233, 1233, 433, 1233, 433, 1233, 1233, 433, 433, 433, 433, 433, 433,\
 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433,\
 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 0, 0, 0, 0,\
 0, 0, 0, 3033, 800, 800, 800, 2400, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 4000,\
 800, 800, 800, 4000, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800,\
 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800,\
 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800,\
 800, 800, 800, 800, 800, 800, 4000, 800, 800, 800, 800, 800, 833, 866, 4000, 800, 800, 800, 800,\
 800, 800, 800, 5600, 800, 800, 800, 800, 800, 800, 4000, 800, 800, 800, 800, 800, 800, 800, 4000,\
 800, 800, 800, 800, 800, 800, 800, 4000, 800, 800, 800, 800, 800, 800, 800, 5600, 800, 800, 800,\
 800, 2400, 800, 800, 800, 800, 966, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433,\
 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433,\
 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 1233, 433, 1233, 1233, 433, 1233, 433, 1233, 1233,\
 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433,\
 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433,\
 433, 433, 16, 33, 33, 0, 0, 0, 0, 3033, 800, 800, 800, 2400, 800, 800, 800, 800, 800,\
 800, 800, 800, 800, 800, 4000, 800, 800, 800, 4000, 800, 800, 800, 800, 800, 800, 800, 800, 800,\
 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800,\
 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800,\
 800, 800, 800, 800, 800, 800, 800, 16, 416, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433,\
 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433,\
 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 1233, 433, 1233, 1233, 433, 1233, 433, 1233,\
 1233, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433,\
 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433, 433,\
 433, 433, 2033, 0, 0, 0, 0, 0, 0, 0, 800, 800, 800, 800, 800, 4000, 800, 800, 800,\
 800, 966, 800, 800, 4000, 800, 800, 800, 800, 800, 800, 800, 5600, 800, 800, 800, 800, 800, 700,\
 4133, 800, 800, 800, 800, 800, 800, 800, 4000, 800, 800, 800, 800, 800, 800, 800, 4000, 800, 800,\
 800, 800, 800, 800, 800, 5600, 800, 800, 800, 800, 2400, 800, 800, 800, 800};





 
int main(void){
	
  int xvar = 0;
	SystemClock_Config(); 																										// Configure the system clock to 84 MHz
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA); 											// Enable clock for port A - BLUE LED
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB); 											// Enable clock for port B - RED LED and Speaker
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);											// Enable clock for port C - GREEN LED, PB_LEFT, PB_RIGHT

	LL_GPIO_SetPinMode (GPIOA, LL_GPIO_PIN_9, LL_GPIO_MODE_OUTPUT); 					//set PA9 as output(BLUE LED)
	LL_GPIO_SetPinOutputType (GPIOA, LL_GPIO_PIN_9, LL_GPIO_OUTPUT_PUSHPULL); //output type is push-pull
	LL_GPIO_SetPinPull (GPIOA, LL_GPIO_PIN_9, LL_GPIO_PULL_NO); 							//set PA9 as NO pull
	LL_GPIO_SetPinSpeed (GPIOA, LL_GPIO_PIN_9, LL_GPIO_SPEED_FREQ_HIGH); 			// high speed
	LL_GPIO_SetPinMode (GPIOC, LL_GPIO_PIN_7, LL_GPIO_MODE_OUTPUT); 					//set PC7 as output(GREEN LED)
	LL_GPIO_SetPinOutputType (GPIOC, LL_GPIO_PIN_7, LL_GPIO_OUTPUT_PUSHPULL); //output type is push-pull
	LL_GPIO_SetPinPull (GPIOC, LL_GPIO_PIN_7, LL_GPIO_PULL_NO); 							//set PC7 as NO pull
	LL_GPIO_SetPinSpeed (GPIOC, LL_GPIO_PIN_7, LL_GPIO_SPEED_FREQ_HIGH); 			// high speed
 	LL_GPIO_SetPinMode (GPIOB, LL_GPIO_PIN_4, LL_GPIO_MODE_OUTPUT); 					//set PB4 as output(RED LED)
	LL_GPIO_SetPinOutputType (GPIOB, LL_GPIO_PIN_4, LL_GPIO_OUTPUT_PUSHPULL); //output type is push-pull
	LL_GPIO_SetPinPull (GPIOB, LL_GPIO_PIN_4, LL_GPIO_PULL_NO); 							//set PB4 as NO pull
	LL_GPIO_SetPinSpeed (GPIOB, LL_GPIO_PIN_4, LL_GPIO_SPEED_FREQ_HIGH); 			// high speed	
	LL_GPIO_SetPinMode (GPIOB, LL_GPIO_PIN_10, LL_GPIO_MODE_OUTPUT); 					//set PB10 as output(SPEAKER)
	LL_GPIO_SetPinOutputType (GPIOB, LL_GPIO_PIN_10, LL_GPIO_OUTPUT_PUSHPULL);//output type is push-pull
	LL_GPIO_SetPinPull (GPIOB, LL_GPIO_PIN_10, LL_GPIO_PULL_NO); 							//set PB10 as NO pull
	LL_GPIO_SetPinSpeed (GPIOB, LL_GPIO_PIN_10, LL_GPIO_SPEED_FREQ_HIGH); 		// high speed
	LL_GPIO_SetPinMode (GPIOC, LL_GPIO_PIN_0, LL_GPIO_MODE_INPUT); 						//set PA4 as Input(JOYSTICK RIGHT)
	LL_GPIO_SetPinPull (GPIOC, LL_GPIO_PIN_0, LL_GPIO_PULL_NO); 							//set PA4 as NO pull
	LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_9);																//start with leds off
	LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_7);
	LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_4);
	while (1){
		if(PB_RIGHT_pressed()){
			for(;xvar < notecount;xvar++){
				PlayTune( notes, notenum, timedelay, xvar);
			}
			xvar = 0;
		}
		else{
			switch_LED_off(xvar);
		}
	}
}


uint32_t PB_RIGHT_pressed(void) {																									// check if down button pressed
	return (LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_0));
}

void switch_LED_on(int xvar) {																									// switch LED on
	switch(xvar % 3){																													// Case statement for rgb led looping
		case 0:
			LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_9);
			break;
		case 1:
			LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_7);
			break;
		case 2:
			LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_4);
			break;
		default:
			break;
	}
	LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_10);														// switch speaker on
}
			
void switch_LED_off(int xvar) {																									// switch LED off
	switch(xvar % 3){
		case 0:
			LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_9);
			break;
		case 1:
			LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_7);
			break;
		case 2:
			LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_4);
			break;
		default:
			break;
	}
	LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_10);												// switch speaker off
}
void PlayTune( const unsigned short notes[], const unsigned short notenum[], const unsigned short timedelay[], int x){
	if ((timedelay[x]) == 0){
		delay_micro_s(25);
	}
	if((timedelay[x]) != 0){
	delay_micro_s(timedelay[x]*100);
	}
	for(int i = 0; i < notenum[x]; i++){
		switch_LED_on(x);
		delay_micro_s(notes[x]);																		
		switch_LED_off(x);
		delay_micro_s(notes[x]);
	}
}


/**
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 84000000
  *            HCLK(Hz)                       = 84000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 8
  *            PLL_N                          = 336
  *            PLL_P                          = 4
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale2 mode
  *            Flash Latency(WS)              = 2
  */
void SystemClock_Config(void)
{
  /* Enable HSE oscillator */
  LL_RCC_HSE_EnableBypass();
  LL_RCC_HSE_Enable();
  while(LL_RCC_HSE_IsReady() != 1)
  {
  };

  /* Set FLASH latency */
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);

  /* Main PLL configuration and activation */
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_8, 336, LL_RCC_PLLP_DIV_4);
  LL_RCC_PLL_Enable();
  while(LL_RCC_PLL_IsReady() != 1)
  {
  };

  /* Sysclk activation on the main PLL */
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {
  };

  /* Set APB1 & APB2 prescaler */
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_2);

  /* Set systick to 1micro second */
  SysTick_Config(84000000 / 1000000);

  /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  SystemCoreClock = 84000000;
}

 
// return the system clock as milliseconds
 void SysTick_Handler(void) {
  count++;
}

uint32_t millis(void) {
  return count;
}
 
void delay_micro_s(uint32_t t) {
  uint32_t start, end;
  start = millis();
  end = start + t;
  if (start < end) { 
    while ((millis() >= start) && (millis() < end)) { 
      // do nothing 
    } 
  } else { 
    while ((millis() >= start) || (millis() < end)) {
      // do nothing
    };
  }
}
