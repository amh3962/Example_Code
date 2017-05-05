// https://github.com/frisnit/STM32L476-radar/blob/8cdf8e68006f85f321a1309565379e80d5fb5a26/software/STM32-radar/Utilities/STM32L476G-Discovery/stm32l476g_discovery.c

/**
 * @brief JOYSTICK Types Definition
 */
typedef enum 
{ 
  JOY_SEL   = 0,
  JOY_LEFT  = 1,
  JOY_RIGHT = 2,
  JOY_DOWN  = 3,
  JOY_UP    = 4,
  JOY_NONE  = 5
}JOYState_TypeDef;

typedef enum 
{  
  JOY_MODE_GPIO = 0,
  JOY_MODE_EXTI = 1
}JOYMode_TypeDef;

typedef enum 
{  
  SUPPLY_MODE_ERROR = 0,
  SUPPLY_MODE_EXTERNAL = 1,
  SUPPLY_MODE_BATTERY = 2
}SupplyMode_TypeDef;


#define SEL_JOY_PIN                       GPIO_PIN_0   /* PA.00 */
#define SEL_JOY_GPIO_PORT                 GPIOA
#define SEL_JOY_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOA_CLK_ENABLE()
#define SEL_JOY_GPIO_CLK_DISABLE()        __HAL_RCC_GPIOA_CLK_DISABLE()
#define SEL_JOY_EXTI_IRQn                 EXTI0_IRQn 


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
