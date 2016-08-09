//-------------------------------------------STM32F4_PWM-------------------------------------------------------

/* Beschreibung:
 * Erzeugt zwei PWM-Signale per Timer
 */
/*

Hinweis zum Clock fuer 8MHz Quarz, damit er auf 168MHz läuft (betrifft das stm32F4Discovery):

in der system_stm32f4xx.c muss eingetragen sein:
PLL_M = 8

in der stm32f4xx.h muss eingetragen sein:
HSE_VALUE = 8000000
*/

#include <stdio.h>
#include <stdlib.h>

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"

void GPIO_OUT_INIT_EXAMPLE(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  /* GPIOD Periph clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

  /* Configure PD14 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
}


void GPIO_IN_INIT_EXAMPLE(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  /* GPIOD Periph clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  /* Configure PD14 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}
void TIMER_PWM_INIT_EXAMPLE(uint16_t timPrescaler)
{
      GPIO_InitTypeDef  GPIO_InitStructure;
      TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
      TIM_OCInitTypeDef  TIM_OCInitStructure;

      // TIM4 clock enable
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

      // GPIOD Clock enable
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

      // GPIO Config
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13;
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
      GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
      GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
      GPIO_Init(GPIOD, &GPIO_InitStructure);
      GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4); // Verbindet den Pin12 über die Multiplexerfunktion mit AF2/TIM4
      GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4); // Verbindet den Pin13 über die Multiplexerfunktion mit AF2/TIM4

      // Timer Config
      TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
      TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
      TIM_TimeBaseInitStructure.TIM_Period = 0x3FF-1; // 10bit Auflösung der PWM
      TIM_TimeBaseInitStructure.TIM_Prescaler = timPrescaler; // 84MHz / 100 = 0,84 MHz nach dem Prescaler
      TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
      TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);

      TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
      TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
      TIM_OCInitStructure.TIM_Pulse = 0;
      TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
      TIM_OC1Init(TIM4, &TIM_OCInitStructure);
      TIM_OC2Init(TIM4, &TIM_OCInitStructure);

      TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
      TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

      TIM_ARRPreloadConfig(TIM4, ENABLE);
      TIM_Cmd(TIM4, ENABLE);

      TIM4->CCR1 = 0;
      TIM4->CCR2 = 0;
}

void updatePwmCycleTime(void)
{
    static uint16_t timPrescaler = 50;

    if ( timPrescaler > 200)
        timPrescaler = 40-1;
    else
        timPrescaler = timPrescaler+10;

    TIMER_PWM_INIT_EXAMPLE(timPrescaler);

    TIM4->CCR1 = 500; // LED heller
    TIM4->CCR2 = 10;  // LED dunkler
}

int main(void)
{
    uint16_t timPrescaler = 40;
    uint16_t highLevelCtr = 0;

    //PLL auf 168MHz konfigurieren
    SystemInit();

    GPIO_OUT_INIT_EXAMPLE();

    GPIO_IN_INIT_EXAMPLE();

    // PWM INIT
    TIMER_PWM_INIT_EXAMPLE(timPrescaler);

    // Zwei PWM-Outputs setzen
     TIM4->CCR1 = 500;
     TIM4->CCR2 = 10;

    while(1)
    {
        if (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0))
        {
            highLevelCtr += 1;
        }
        else
        {
      // debounce button (action on button release)
            if (highLevelCtr > 1000)
            {
                updatePwmCycleTime();
                highLevelCtr=0;
            }
        }
    }
}
