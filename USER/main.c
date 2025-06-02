#include "led.h"
#include "systick.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "key.h"
#include "24cxx.h"
#include "myiic.h"
#include "misc.h"
#include "mlx90614.h"
// ALIENTEK Mini STM32�����巶������19
// IICʵ��
// ����֧�֣�www.openedv.com
// ������������ӿƼ����޹�˾


int main(void)
{
	SMBus_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 //���ڳ�ʼ��Ϊ115200
 	//LED_Init();			     //LED�˿ڳ�ʼ��
	//KEY_Init();          //��ʼ���밴�����ӵ�Ӳ���ӿ�
	
	printf("test");
 	while(1)
	{
		printf("temperature:\r\n");
		//delay_ms(1000);
		printf("%.2f\r\n",(float)SMBus_ReadTemp());
		// temp=SMBus_ReadTemp();
		
		// printf("%d\r\n",(int)temp);
	}	 
}
