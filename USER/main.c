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
// ALIENTEK Mini STM32开发板范例代码19
// IIC实验
// 技术支持：www.openedv.com
// 广州市星翼电子科技有限公司


int main(void)
{
	SMBus_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	 //串口初始化为115200
 	//LED_Init();			     //LED端口初始化
	//KEY_Init();          //初始化与按键连接的硬件接口
	
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
