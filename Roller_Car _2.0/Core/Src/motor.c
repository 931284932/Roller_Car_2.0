#include "main.h"
#include "OLED.h"
#include "usart.h"
void Send_To_Servo(uint8_t *Data,uint8_t lenth);
void send_to_servo(uint8_t *arr,uint8_t lenth);
void servo_en(uint8_t state)
{
	static uint8_t data[6] = {0x01,0x06,0x31,0x00,0x00,0x00};
	data[5] = state;
	send_to_servo(data,6);
}
void servo_dir(uint8_t state)
{
		HAL_GPIO_WritePin(DIR_GPIO_Port,DIR_Pin,(GPIO_PinState)state);
}

/*发送数据给伺服电机*/
void send_to_servo(uint8_t *arr,uint8_t lenth)
{
	static uint8_t crc[2];
	crc[0] = CRC16_MudBus(arr,lenth)%256;
	crc[1] = CRC16_MudBus(arr,lenth)/256;
	HAL_UART_Transmit(&huart3,arr,lenth,1000);
	HAL_UART_Transmit(&huart3,crc,2,1000);
}
/*获取伺服电机编码值*/
uint64_t get_servo_encoder(void)
{
	static uint8_t servo_rx_data[12];
	static uint8_t arr[6] = {0x01,0x03,0x10,0x18,0x00,0x04};
	send_to_servo(arr,6);
	/*在任务中使用*/
	if(servo_rx_data[0] == 0x01 && servo_rx_data[1] == 0x03 && servo_rx_data[2] == 0x08)
		return servo_rx_data[3]*256+servo_rx_data[4]+servo_rx_data[5]*256*256*256+servo_rx_data[6]*256*256
							+servo_rx_data[7]*256*256*256*256*256+servo_rx_data[8]*256*256*256*256+servo_rx_data[9]*256*256*256*256*256*256*256
							+servo_rx_data[10]*256*256*256*256*256*256;
	 else	
		 return 0;
}
void out(uint8_t addr,uint8_t state)
{
	switch(addr)
	{
		case 1:HAL_GPIO_WritePin(OUT1_GPIO_Port,OUT1_Pin,(GPIO_PinState)state);break;
		case 2:HAL_GPIO_WritePin(OUT2_GPIO_Port,OUT2_Pin,(GPIO_PinState)state);break;
		case 3:HAL_GPIO_WritePin(OUT3_GPIO_Port,OUT3_Pin,(GPIO_PinState)state);break;
		case 4:HAL_GPIO_WritePin(OUT4_GPIO_Port,OUT4_Pin,(GPIO_PinState)state);break;
		case 5:HAL_GPIO_WritePin(OUT5_GPIO_Port,OUT5_Pin,(GPIO_PinState)state);break;
		case 6:HAL_GPIO_WritePin(OUT6_GPIO_Port,OUT6_Pin,(GPIO_PinState)state);break;
		case 7:HAL_GPIO_WritePin(OUT7_GPIO_Port,OUT7_Pin,(GPIO_PinState)state);break;
		case 8:HAL_GPIO_WritePin(OUT8_GPIO_Port,OUT8_Pin,(GPIO_PinState)state);break;
		case 9:HAL_GPIO_WritePin(OUT9_GPIO_Port,OUT9_Pin,(GPIO_PinState)state);break;
		case 10:HAL_GPIO_WritePin(OUT10_GPIO_Port,OUT10_Pin,(GPIO_PinState)state);break;
		default :break;
	}
}
uint8_t in(uint8_t addr)
{
	switch(addr)
	{
		case 1:return HAL_GPIO_ReadPin(IN1_GPIO_Port,IN1_Pin); break;
		case 2:return HAL_GPIO_ReadPin(IN2_GPIO_Port,IN2_Pin); break;
		case 3:return HAL_GPIO_ReadPin(IN3_GPIO_Port,IN3_Pin); break;
		case 4:return HAL_GPIO_ReadPin(IN4_GPIO_Port,IN4_Pin); break;
		case 5:return HAL_GPIO_ReadPin(IN5_GPIO_Port,IN5_Pin); break;
		case 6:return HAL_GPIO_ReadPin(IN6_GPIO_Port,IN6_Pin); break;
		case 7:return HAL_GPIO_ReadPin(IN7_GPIO_Port,IN7_Pin); break;
		case 8:return HAL_GPIO_ReadPin(IN8_GPIO_Port,IN8_Pin); break;
		case 9:return HAL_GPIO_ReadPin(IN9_GPIO_Port,IN9_Pin); break;
		case 10:return HAL_GPIO_ReadPin(IN10_GPIO_Port,IN10_Pin); break;
		case 11:return HAL_GPIO_ReadPin(IN11_GPIO_Port,IN11_Pin); break;
		case 12:return HAL_GPIO_ReadPin(IN12_GPIO_Port,IN12_Pin); break;
		case 13:return HAL_GPIO_ReadPin(IN13_GPIO_Port,IN13_Pin); break;
		case 14:return HAL_GPIO_ReadPin(IN14_GPIO_Port,IN14_Pin); break;
		case 15:return HAL_GPIO_ReadPin(IN15_GPIO_Port,IN15_Pin); break;
		case 16:return HAL_GPIO_ReadPin(IN16_GPIO_Port,IN16_Pin); break;
		case 17:return HAL_GPIO_ReadPin(IN17_GPIO_Port,IN17_Pin); break;
		case 18:return HAL_GPIO_ReadPin(IN18_GPIO_Port,IN18_Pin); break;
		case 19:return HAL_GPIO_ReadPin(IN19_GPIO_Port,IN19_Pin); break;
		case 20:return HAL_GPIO_ReadPin(IN20_GPIO_Port,IN20_Pin); break;
		default: return 10;break;
	}
}
//CRC校验
uint16_t CRC16_MudBus(uint8_t *Data, uint8_t usDataLen)
{
	
	uint16_t uCRC = 0xffff;//CRC寄存器
	for(uint8_t num=0;num<usDataLen;num++){
		uCRC = (*Data++)^uCRC;//把数据与16位的CRC寄存器的低8位相异或，结果存放于CRC寄存器。
		for(uint8_t x=0;x<8;x++){	//循环8次
			if(uCRC&0x0001){	//判断最低位为：“1”
				uCRC = uCRC>>1;	//先右移
				uCRC = uCRC^0xA001;	//再与0xA001异或
			}else{	//判断最低位为：“0”
				uCRC = uCRC>>1;	//右移
			}
		}
	}
	return uCRC;//返回CRC校验值
}
void Send_To_Servo(uint8_t *Data,uint8_t lenth)
{	
	static uint8_t send_servo_byte[1];
	for(uint8_t i=0;i<lenth;i++)
	{
		send_servo_byte[0] = Data[i];
		HAL_UART_Transmit(&huart3,send_servo_byte,1,1000);
	}
	send_servo_byte[0] = Data[lenth] = CRC16_MudBus(Data,lenth)%256;
	HAL_UART_Transmit(&huart3,send_servo_byte,1,1000);
	send_servo_byte[0] = Data[lenth] = CRC16_MudBus(Data,lenth)/256;
	HAL_UART_Transmit(&huart3,send_servo_byte,1,1000);
}
void Servo_Init(void)
{
	//启用VDI
	static uint8_t send_servo_1[6] = {0x01,0x06,0x0C,0x09,0x00,0x01};
	send_to_servo(send_servo_1,6);
	HAL_Delay(10);
	//禁用DI
	static uint8_t send_servo_3[6] = {0x01,0x06,0x03,0x0A,0x00,0x00};
	send_to_servo(send_servo_3,6);
	HAL_Delay(10);
	//设置VDI
	static uint8_t send_servo_2[6] = {0x01,0x06,0x17,0x00,0x00,0x01};
	send_to_servo(send_servo_2,6);
	HAL_Delay(10);
	//脉冲实时输出
	static uint8_t send_servo_4[6] = {0x01,0x06,0x05,0x26,0x00,0x01};//01
	send_to_servo(send_servo_4,6);
	HAL_Delay(10);
	//失能
	static uint8_t send_servo[6] = {0x01,0x06,0x31,0x00,0x00,0x01};
	Send_To_Servo(send_servo,6);
	HAL_Delay(10);
}
void motor_en(uint8_t num,uint8_t state)
{
	switch(num)
	{
		case 1:HAL_GPIO_WritePin(EN1_GPIO_Port,EN1_Pin,(GPIO_PinState)!state);break;
		case 2:HAL_GPIO_WritePin(EN2_GPIO_Port,EN2_Pin,(GPIO_PinState)!state);break;
		case 3:HAL_GPIO_WritePin(EN3_GPIO_Port,EN3_Pin,(GPIO_PinState)!state);break;
		case 4:HAL_GPIO_WritePin(EN4_GPIO_Port,EN4_Pin,(GPIO_PinState)!state);break;
		case 5:HAL_GPIO_WritePin(EN5_GPIO_Port,EN5_Pin,(GPIO_PinState)!state);break;
		default:break;
	}
}
