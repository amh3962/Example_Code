// https://github.com/frisnit/STM32L476-radar/blob/8cdf8e68006f85f321a1309565379e80d5fb5a26/software/STM32-radar/Utilities/STM32L476G-Discovery/stm32l476g_discovery.c

#include "stm32l476g_discovery.h"

 GPIO_TypeDef* JOY_PORT[JOYn] =  {SEL_JOY_GPIO_PORT,
                                  DOWN_JOY_GPIO_PORT,
                                  LEFT_JOY_GPIO_PORT,
                                  RIGHT_JOY_GPIO_PORT,
                                  UP_JOY_GPIO_PORT};

const uint16_t JOY_PIN[JOYn] =   {SEL_JOY_PIN,
                                  LEFT_JOY_PIN,
                                  RIGHT_JOY_PIN,
                                  DOWN_JOY_PIN,
                                  UP_JOY_PIN};

const uint8_t JOY_IRQn[JOYn] =   {SEL_JOY_EXTI_IRQn,
                                  LEFT_JOY_EXTI_IRQn,
                                  RIGHT_JOY_EXTI_IRQn,
                                  DOWN_JOY_EXTI_IRQn,
                                  UP_JOY_EXTI_IRQn};


void joystick_init() {
    JOYState_TypeDef joykey;
    GPIO_InitTypeDef GPIO_InitStruct;
    
    /* Initialized the Joystick. */
    for(joykey = JOY_LEFT /*JOY_SEL MLT - using this for ADC input */; joykey < (JOY_SEL + JOYn) ; joykey++) {
        /* Enable the JOY clock */
        JOYx_GPIO_CLK_ENABLE(joykey);
    
        GPIO_InitStruct.Pin = JOY_PIN[joykey];
        GPIO_InitStruct.Pull = GPIO_PULLDOWN;
        GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
        
        /* Configure Joy pin as input */
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        HAL_GPIO_Init(JOY_PORT[joykey], &GPIO_InitStruct);
    }
}


int get_joystick_state(void) {
    JOYState_TypeDef joykey;
    
    if (HAL_GPIO_ReadPin(JOY_PORT[JOY_SEL], JOY_PIN[JOY_SEL]) == GPIO_PIN_SET) {
        return 1;
    }
    
    return 0;
}
