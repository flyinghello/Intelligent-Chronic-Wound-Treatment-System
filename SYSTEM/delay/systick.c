/**
  ********************************  STM32F10x  *********************************
  * @�ļ���     �� systick.c
  * @��汾     �� V3.5.0
  * @�ļ��汾   �� V1.0.0
  * @ժҪ       �� systickԴ�ļ�
  ******************************************************************************/

/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "stm32f10x.h"
//systick = HCLK/8
static __IO uint32_t TimingDelay;

void RCC_HSE_Config(void)
{
//������������ 36MHz
	RCC_DeInit(); /*������RCC�Ĵ�������Ϊȱʡֵ */ 
//	RCC_HSICmd(ENABLE); //ʹ���ڲ�ʱ��  HSI
    RCC_HSEConfig(RCC_HSE_ON);  //�ⲿ����ʱ��HSE 
//  while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY)== RESET);//�ȴ�HSI���� 
	while(RCC_GetFlagStatus(RCC_FLAG_HSERDY)== RESET);//�ȴ�HSE���� 
	 
	RCC_HCLKConfig(RCC_SYSCLK_Div1);  /*����AHBʱ�ӣ�HCLK�� RCC_SYSCLK_Div1����AHBʱ�� = ϵͳʱ*/  
	RCC_PCLK2Config(RCC_HCLK_Div1);   /* ���ø���AHBʱ�ӣ�PCLK2)RCC_HCLK_Div1����APB2ʱ�� = HCLK*/     
	RCC_PCLK1Config(RCC_HCLK_Div2);   /*���õ���AHBʱ�ӣ�PCLK1��RCC_HCLK_Div2����APB1ʱ�� = HCLK / 2*/   
 
	 //�������������ʱ��Ƶ��  ��ס�ο�
//	RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_16);/*����PLLʱ��HSIԴ����Ƶϵ����Ƶ��Ϊ8/2*16=64Mhz*/
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9 );/*����PLLʱ��ԴHSE����Ƶϵ����Ƶ��Ϊ8*9=72Mhz*/
	RCC_PLLCmd(ENABLE); 	 /*ʹ��PLL *///����ʹ�õ��ڲ�ʱ�����Բ��ܱ� ʧ�� 
	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET) ; /*���ָ����RCC��־λ(PLL׼���ñ�־)�������   �ȴ��Ƿ����óɹ�*/    
	
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);  /*����ϵͳʱ�ӣ�SYSCLK�� */  
	//ѡ����һ����Ϊʱ��   
//  RCC_SYSCLKSource_HSI;   	 //  0x00��HSI ��Ϊϵͳʱ��   
//  RCC_SYSCLKSource_HSE       //  0x04��HSE��Ϊϵͳʱ�� 
//  RCC_SYSCLKSource_PLLCLK    //  0x08��PLL��Ϊϵͳʱ�� 
	 
	while(RCC_GetSYSCLKSource() != 0x08);//���뱻ѡ���ϵͳʱ�Ӷ�Ӧ������RCC_SYSCLKSource_PLL

}

void SYSTICK_CONFIG(void)
{
    /* SystemFrequency / 1000    1000us/1ms
       SystemFrequency / 10000	 100us
       SystemFrequency / 100000 10us
    */
    if (SysTick_Config(SystemCoreClock/100000))//����Ϊ 10us
    {
        /* Capture error */
        while (1);
    }
}

//ʹ��SysTick����ͨ����ģʽ���ӳٽ��й���
//�������ж��е��ó�����ѭ���Ĵ���
//��ֹ��ʱ��׼ȷ,����do while�ṹ!
static u8  fac_us = 0; //us��ʱ������
static u16 fac_ms = 0; //ms��ʱ������

/**********************************************************
** ������: delay_init
** ��������: ��ʼ���ӳٺ���,SYSTICK��ʱ�ӹ̶�ΪHCLKʱ�ӵ�1/8
** �������: SYSCLK����λMHz)
** �������: ��
** ���÷��������ϵͳʱ�ӱ���Ϊ72MHz,�����delay_init(72)
***********************************************************/
void delay_init(u8 SYSCLK)
{
    SysTick->CTRL &= 0xfffffffb; //bit2���,ѡ���ⲿʱ��  HCLK/8
    fac_us = SYSCLK / 8;
    fac_ms = (u16)fac_us * 1000;
}
/**********************************************************
** ������: delay_us
** ��������: ��ʱnus��nusΪҪ��ʱ��us��.
** �������: nus
** �������: ��
***********************************************************/
void delay_us(u32 nus)
{
    u32 temp;
    SysTick->LOAD = nus * fac_us; //ʱ�����
    SysTick->VAL = 0x00;      //��ռ�����
    SysTick->CTRL = 0x01;    //��ʼ����

    do
    {
        temp = SysTick->CTRL;
    }
    while(temp & 0x01 && !(temp & (1 << 16))); //�ȴ�ʱ�䵽��

    SysTick->CTRL = 0x00;     //�رռ�����
    SysTick->VAL = 0X00;      //��ռ�����
}
/**********************************************************
** ������: delay_ms
** ��������: ��ʱnms
** �������: nms
** �������: ��
** ˵����SysTick->LOADΪ24λ�Ĵ���,����,�����ʱΪ:
		nms<=0xffffff*8*1000/SYSCLK
		SYSCLK��λΪHz,nms��λΪms
		��72M������,nms<=1864
***********************************************************/
void delay_ms(u16 nms)
{
    u32 temp;
    SysTick->LOAD = (u32)nms * fac_ms; //ʱ�����(SysTick->LOADΪ24bit)
    SysTick->VAL = 0x00;          //��ռ�����
    SysTick->CTRL = 0x01 ;        //��ʼ����

    do
    {
        temp = SysTick->CTRL;
    }
    while(temp & 0x01 && !(temp & (1 << 16))); //�ȴ�ʱ�䵽��

    SysTick->CTRL = 0x00;     //�رռ�����
    SysTick->VAL = 0X00;      //��ռ�����
}
