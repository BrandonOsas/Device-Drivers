/** 
  ****************************************************************************** 
  * @file    GPIO/IOToggle/main.c 
  * @author  MCD Application Team 
  * @version V3.5.0 
  * @date    08-April-2011 
  * @brief   Main program body. 
  ****************************************************************************** 
  * @attention 
  * 
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS 
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE 
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY 
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING 
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE 
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS. 
  * 
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2> 
  ****************************************************************************** 
  */ 

/* Includes ------------------------------------------------------------------*/ 
#include <stm32f10x.h> 
#include <stm32f10x_rcc.h> 
#include <stm32f10x_gpio.h> 

/* Private variables ---------------------------------------------------------*/ 
GPIO_InitTypeDef GPIO_InitStructure; 

int main(void) 
{ 
	volatile uint32_t i; 
	volatile uint32_t j;
	static int GreenOn = 0;	 
	static int YellowOn = 0; 
	static int pressed = 0;
	static int pressed_confidence_level =0;
	static int released_confidence_level =0;
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup 
       file (startup_stm32f10x_xx.s) before to branch to application main. 
       To reconfigure the default setting of SystemInit() function, refer to 
       system_stm32f10x.c file 
     */     
        
  /* GPIOC Periph clock enable */ 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 

  /* Configure PC6 in output pushpull mode */ 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOC, &GPIO_InitStructure); 

  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
  GPIO_Init( GPIOA, &GPIO_InitStructure ); 

  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_13; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init( GPIOC, &GPIO_InitStructure ); 


  /* To achieve GPIO toggling maximum frequency, the following  sequence is mandatory. 
     You can monitor PD0 or PD2 on the scope to measure the output signal. 
     If you need to fine tune this frequency, you can add more GPIO set/reset 
     cycles to minimize more the infinite loop timing. 
     This code needs to be compiled with high speed optimization option.  */ 

  pressed = 0;
  while (1)
  {
	if ( GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) )
	{
		pressed_confidence_level++;
		released_confidence_level = 0;
		if (pressed_confidence_level > 200)
		{
			if ( pressed == 0 )
			{
				GPIO_WriteBit(GPIOC , GPIO_Pin_6 , GreenOn);
				GPIO_WriteBit(GPIOC , GPIO_Pin_7 , YellowOn);
				if ( GreenOn == 0 ){
					GreenOn = 1;
					YellowOn = 0;}
				else{
					GreenOn = 0;
					YellowOn = 1;}
				pressed = 1;
				pressed_confidence_level = 0;
			}
		}
	} else
		{
			released_confidence_level++;
			pressed_confidence_level = 0;
				if (released_confidence_level >200 )
				{
				pressed = 0;
				released_confidence_level = 0;
				}
			}
		}
  }

#ifdef  USE_FULL_ASSERT 

/** 
  * @brief  Reports the name of the source file and the source line number 
  *         where the assert_param error has occurred. 
  * @param  file: pointer to the source file name 
  * @param  line: assert_param error line source number 
  * @retval None 
  */ 
void assert_failed(uint8_t* file, uint32_t line) 
{ 
  /* User can add his own implementation to report the file name and line number, 
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */ 

  /* Infinite loop */ 
  while (1) 
  {
  } 
} 

#endif 
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/


