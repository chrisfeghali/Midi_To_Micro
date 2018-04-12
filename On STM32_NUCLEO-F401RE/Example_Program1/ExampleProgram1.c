#include "main.h"
uint32_t PB_RIGHT_pressed(void);
void switch_LED_on(int xvar);
void switch_LED_off(int xvar);
void SysTick_Handler(void);
void SystemClock_Config(void);
void delay_micro_s(uint32_t t);
void PlayTune( const unsigned short notes[], const unsigned short notenum[], const unsigned short timedelay[], int x);
static volatile uint32_t count;
#define notecount 311  // paste notecount here

const unsigned short notes[notecount] = { 1803, 1431, 1203, 1431, 1203, 1431, 1203, 1431, 1203, 1072, 1431, 1607, 1431, 1803, 1607, 2145, 2407, 2145, 1803,\
 1607, 1431, 1203, 1072, 1431, 1607, 1431, 1203, 1431, 1203, 1072, 1072, 1203, 803, 1431, 1607, 1431, 1803, 1607,\
 2145, 2407, 2145, 1803, 1607, 1431, 1203, 1072, 536, 601, 715, 803, 536, 601, 715, 803, 536, 601, 715,\
 803, 536, 601, 715, 803, 1203, 1072, 1203, 1072, 901, 1203, 1072, 1203, 1072, 901, 803, 901, 715, 803,\
 901, 1072, 1203, 1072, 1203, 1072, 1203, 1072, 901, 1203, 1072, 1203, 1072, 901, 803, 901, 715, 601, 536,\
 803, 901, 1203, 1072, 1203, 1072, 901, 1203, 1072, 1203, 1072, 901, 803, 901, 715, 803, 901, 1072, 1203,\
 1072, 1203, 1072, 1203, 1072, 901, 1203, 1072, 1203, 1072, 901, 803, 901, 715, 601, 536, 803, 901, 1431,\
 1607, 1431, 1203, 1431, 1203, 1072, 1072, 1203, 803, 1607, 1431, 1607, 1431, 1803, 1607, 2145, 2407, 2145, 1803,\
 1607, 1431, 1203, 1072, 1431, 1607, 1431, 1203, 1431, 1203, 1072, 1203, 901, 803, 1431, 1607, 1431, 1803, 1607,\
 2145, 2407, 2145, 1803, 1607, 1431, 1203, 1072, 536, 601, 715, 803, 536, 601, 715, 803, 536, 601, 715,\
 803, 536, 601, 715, 803, 1203, 1072, 1203, 1072, 901, 1203, 1072, 1203, 1072, 901, 803, 901, 715, 803,\
 901, 1072, 1203, 1072, 1203, 1072, 1203, 1072, 901, 1203, 1072, 1203, 1072, 901, 803, 901, 715, 601, 536,\
 803, 901, 1203, 1072, 1203, 1072, 901, 1203, 1072, 1203, 1072, 901, 803, 901, 715, 803, 901, 1072, 1203,\
 1072, 1203, 1072, 1203, 1072, 901, 1203, 1072, 1203, 1072, 901, 803, 901, 715, 601, 536, 803, 901, 1803,\
 1431, 1431, 1431, 1203, 1431, 1203, 1431, 1203, 1072, 1431, 1607, 1431, 1803, 1607, 2145, 2407, 2145, 1803, 1607,\
 1431, 1203, 1072, 1803, 1431, 1431, 1431, 1203, 1431, 1203, 1431, 1203, 1072, 1431, 1607, 1431, 1803, 1607, 2145,\
 2407, 2145, 1803, 1607, 1431, 1203, 1072};

 const unsigned short notenum[notecount] = { 266, 419, 20, 16, 19, 17, 98, 41, 349, 111, 125, 112, 209, 166, 37, 27, 24, 83, 33,\
 37, 125, 99, 139, 251, 37, 335, 49, 41, 249, 111, 111, 149, 149, 125, 112, 209, 166, 37,\
 27, 24, 83, 33, 37, 125, 99, 139, 895, 798, 671, 298, 671, 599, 671, 298, 895, 798, 671,\
 298, 671, 599, 671, 298, 24, 27, 49, 55, 332, 24, 27, 49, 55, 233, 149, 133, 167, 149,\
 133, 111, 99, 83, 24, 27, 24, 55, 332, 24, 27, 49, 55, 233, 149, 133, 251, 199, 223,\
 149, 166, 24, 27, 49, 55, 332, 24, 27, 49, 55, 233, 149, 133, 167, 149, 133, 111, 99,\
 83, 24, 27, 24, 55, 332, 24, 27, 49, 55, 233, 149, 133, 251, 199, 223, 149, 166, 251,\
 37, 335, 49, 41, 249, 111, 83, 124, 0, 0, 125, 112, 209, 166, 37, 27, 24, 83, 33,\
 37, 125, 99, 139, 251, 37, 335, 49, 41, 249, 110, 95, 199, 149, 125, 112, 209, 166, 32,\
 27, 24, 83, 33, 37, 125, 99, 139, 893, 798, 671, 298, 671, 599, 671, 298, 893, 796, 671,\
 298, 671, 599, 671, 298, 24, 27, 49, 55, 332, 24, 27, 49, 55, 233, 149, 133, 167, 149,\
 133, 111, 99, 83, 24, 27, 24, 55, 332, 24, 27, 49, 55, 233, 149, 133, 251, 199, 223,\
 149, 166, 24, 27, 49, 55, 332, 24, 27, 49, 55, 233, 149, 133, 167, 149, 133, 111, 99,\
 83, 24, 27, 24, 55, 332, 24, 27, 49, 55, 233, 149, 133, 251, 199, 223, 149, 166, 266,\
 419, 0, 20, 24, 20, 99, 41, 349, 111, 125, 112, 209, 166, 37, 27, 24, 83, 33, 37,\
 125, 99, 139, 266, 419, 0, 20, 24, 20, 99, 41, 349, 111, 125, 112, 209, 166, 37, 27,\
 24, 83, 33, 37, 125, 99, 139};



 const unsigned short timedelay[notecount] = { 0, 0, 0, 125, 100, 150, 75, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,\
 0, 0, 0, 0, 600, 0, 0, 1200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,\
 0, 0, 0, 0, 0, 0, 0, 0, 600, 0, 0, 2400, 2400, 2400, 2400, 2400, 2400, 0, 0,\
 2400, 2525, 2400, 2400, 2400, 3475, 0, 0, 0, 0, 0, 0, 0, 0, 0, 600, 0, 0, 0,\
 0, 0, 0, 0, 2400, 0, 0, 0, 0, 0, 0, 0, 0, 0, 600, 0, 0, 0, 0,\
 0, 0, 1800, 0, 0, 0, 0, 0, 0, 0, 0, 0, 600, 0, 0, 0, 0, 0, 0,\
 0, 2400, 0, 0, 0, 0, 0, 0, 0, 0, 0, 600, 0, 0, 0, 0, 0, 0, 163800,\
 0, 0, 1200, 0, 0, 0, 600, 600, 0, 2400, 0, 0, 0, 0, 0, 0, 0, 0, 0,\
 0, 0, 0, 0, 600, 0, 0, 1200, 0, 0, 0, 25, 100, 0, 0, 0, 0, 0, 25,\
 125, 0, 0, 0, 0, 0, 0, 0, 725, 25, 0, 2400, 2400, 2400, 2400, 2400, 2400, 25, 25,\
 2400, 2525, 2400, 2400, 2400, 3675, 0, 0, 0, 0, 0, 0, 0, 0, 0, 600, 0, 0, 0,\
 0, 0, 0, 0, 2400, 0, 0, 0, 0, 0, 0, 0, 0, 0, 600, 0, 0, 0, 0,\
 0, 0, 1825, 0, 0, 0, 0, 0, 0, 0, 0, 0, 600, 0, 0, 0, 0, 0, 0,\
 0, 2400, 0, 0, 0, 0, 0, 0, 0, 0, 0, 600, 0, 0, 0, 0, 0, 0, 163450,\
 0, 600, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,\
 0, 0, 0, 600, 0, 600, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,\
 0, 0, 0, 0, 0, 0, 0};





 
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
