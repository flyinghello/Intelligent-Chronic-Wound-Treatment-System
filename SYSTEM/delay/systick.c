/**
  ********************************  STM32F10x  *********************************
  * @文件名     ： systick.c
  * @库版本     ： V3.5.0
  * @文件版本   ： V1.0.0
  * @摘要       ： systick源文件
  ******************************************************************************/

/* 包含的头文件 --------------------------------------------------------------*/
#include "stm32f10x.h"
//systick = HCLK/8
static __IO uint32_t TimingDelay;

void RCC_HSE_Config(void)
{
//配置内置振荡器 36MHz
	RCC_DeInit(); /*将外设RCC寄存器重设为缺省值 */ 
//	RCC_HSICmd(ENABLE); //使能内部时钟  HSI
    RCC_HSEConfig(RCC_HSE_ON);  //外部高速时钟HSE 
//  while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY)== RESET);//等待HSI就绪 
	while(RCC_GetFlagStatus(RCC_FLAG_HSERDY)== RESET);//等待HSE就绪 
	 
	RCC_HCLKConfig(RCC_SYSCLK_Div1);  /*设置AHB时钟（HCLK） RCC_SYSCLK_Div1——AHB时钟 = 系统时*/  
	RCC_PCLK2Config(RCC_HCLK_Div1);   /* 设置高速AHB时钟（PCLK2)RCC_HCLK_Div1——APB2时钟 = HCLK*/     
	RCC_PCLK1Config(RCC_HCLK_Div2);   /*设置低速AHB时钟（PCLK1）RCC_HCLK_Div2——APB1时钟 = HCLK / 2*/   
 
	 //下面这语句设置时钟频率  记住参考
//	RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_16);/*设置PLL时钟HSI源及倍频系数，频率为8/2*16=64Mhz*/
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9 );/*设置PLL时钟源HSE及倍频系数，频率为8*9=72Mhz*/
	RCC_PLLCmd(ENABLE); 	 /*使能PLL *///这里使用的内部时钟所以不能被 失能 
	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET) ; /*检查指定的RCC标志位(PLL准备好标志)设置与否   等待是否配置成功*/    
	
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);  /*设置系统时钟（SYSCLK） */  
	//选择哪一个做为时钟   
//  RCC_SYSCLKSource_HSI;   	 //  0x00：HSI 作为系统时钟   
//  RCC_SYSCLKSource_HSE       //  0x04：HSE作为系统时钟 
//  RCC_SYSCLKSource_PLLCLK    //  0x08：PLL作为系统时钟 
	 
	while(RCC_GetSYSCLKSource() != 0x08);//需与被选择的系统时钟对应起来，RCC_SYSCLKSource_PLL

}

void SYSTICK_CONFIG(void)
{
    /* SystemFrequency / 1000    1000us/1ms
       SystemFrequency / 10000	 100us
       SystemFrequency / 100000 10us
    */
    if (SysTick_Config(SystemCoreClock/100000))//设置为 10us
    {
        /* Capture error */
        while (1);
    }
}

//使用SysTick的普通计数模式对延迟进行管理
//修正了中断中调用出现死循环的错误
//防止延时不准确,采用do while结构!
static u8  fac_us = 0; //us延时倍乘数
static u16 fac_ms = 0; //ms延时倍乘数

/**********************************************************
** 函数名: delay_init
** 功能描述: 初始化延迟函数,SYSTICK的时钟固定为HCLK时钟的1/8
** 输入参数: SYSCLK（单位MHz)
** 输出参数: 无
** 调用方法：如果系统时钟被设为72MHz,则调用delay_init(72)
***********************************************************/
void delay_init(u8 SYSCLK)
{
    SysTick->CTRL &= 0xfffffffb; //bit2清空,选择外部时钟  HCLK/8
    fac_us = SYSCLK / 8;
    fac_ms = (u16)fac_us * 1000;
}
/**********************************************************
** 函数名: delay_us
** 功能描述: 延时nus，nus为要延时的us数.
** 输入参数: nus
** 输出参数: 无
***********************************************************/
void delay_us(u32 nus)
{
    u32 temp;
    SysTick->LOAD = nus * fac_us; //时间加载
    SysTick->VAL = 0x00;      //清空计数器
    SysTick->CTRL = 0x01;    //开始倒数

    do
    {
        temp = SysTick->CTRL;
    }
    while(temp & 0x01 && !(temp & (1 << 16))); //等待时间到达

    SysTick->CTRL = 0x00;     //关闭计数器
    SysTick->VAL = 0X00;      //清空计数器
}
/**********************************************************
** 函数名: delay_ms
** 功能描述: 延时nms
** 输入参数: nms
** 输出参数: 无
** 说明：SysTick->LOAD为24位寄存器,所以,最大延时为:
		nms<=0xffffff*8*1000/SYSCLK
		SYSCLK单位为Hz,nms单位为ms
		对72M条件下,nms<=1864
***********************************************************/
void delay_ms(u16 nms)
{
    u32 temp;
    SysTick->LOAD = (u32)nms * fac_ms; //时间加载(SysTick->LOAD为24bit)
    SysTick->VAL = 0x00;          //清空计数器
    SysTick->CTRL = 0x01 ;        //开始倒数

    do
    {
        temp = SysTick->CTRL;
    }
    while(temp & 0x01 && !(temp & (1 << 16))); //等待时间到达

    SysTick->CTRL = 0x00;     //关闭计数器
    SysTick->VAL = 0X00;      //清空计数器
}
