#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "usart.h"
#include "queue.h"
#include "mytask.h"
#include "motor.h"
#include "W25Q64.h"
#include <stdio.h>
#include "tmc5160.h"

TaskHandle_t step_motor1_Handle,step_motor2_Handle,step_motor3_Handle,step_motor4_Handle,step_motor5_Handle,
						 step_motor_in_Handle,servo_motor_Handle,task_run_1_Handle,task_run_2_Handle,task_run_3_Handle;
uint8_t uart1_rx_byte[1];
/*��������������*/
QueueHandle_t screen_rx_queue;
/*�ŷ��������*/
QueueHandle_t servo_rx_queue;
/*W25Q64������*/
QueueHandle_t W25Q64_queue;
/*�̵�����������*/
static uint16_t output;
static uint32_t input;
/*�����������*/
struct motor_debug_pra motor_pra;
/*������Բ���*/
struct motor_debug_pra motor_debug;
static uint8_t page;
void screen_data_pro(void *Pra)
{
	static uint8_t screen_rx_data[200];
	while(1)
	{ 
		if(xQueueReceive(screen_rx_queue,screen_rx_data,portMAX_DELAY) == pdPASS)
		{
			if(screen_rx_data[0]>=0x31&&screen_rx_data[0]<=0x36&&screen_rx_data[1]==0xff)   
			{
				switch(screen_rx_data[0])
				{
					case 0x31:page = 0;break;  	//����
					case 0x32:page = 1;break;		//���Բ���
					case 0x33:page = 2;break;		//���Ե��
					case 0x34:page = 3;break;		//�Լ����
					case 0x35:page = 4;break;		//�Լ���
					case 0x36:page = 5;break;		//�Լ�����
					default:break;
				}
				printf("page_val=%d\xff\xff\xff",page);
			}

			/*���Բ���*/
//			if(page == 1)
//			{
				/*ȫ����ʼ*/	
				if(screen_rx_data[0] == 0x21)     
				{
					/*���Ͳ���*/
//					TaskStatus_t task_run;
					xQueueSend(W25Q64_queue,screen_rx_data,0);
				}
			/*����ֹͣ*/
			if(screen_rx_data[0] == 0x22) 
			{
				vTaskSuspend(task_run_1_Handle);
			}
//		}
			/*���Ե��*/
//			else if(page == 2)
//			{
			/*���1��ʼ*/
				static uint8_t motor1_speed[2],motor2_speed[2],motor3_speed[2],motor4_speed[2],motor5_speed[2],servo_speed[2];
				if(screen_rx_data[0] == 0x11)     
				{
					vTaskResume(step_motor1_Handle);
					motor_debug.motor1[0] = screen_rx_data[1];//����
					motor_debug.motor1[1] = screen_rx_data[2] + (screen_rx_data[3]<<8) 
																	+ (screen_rx_data[4]<<16)+(screen_rx_data[5]<<24);//����
					motor_debug.motor1[2] = screen_rx_data[6] + (screen_rx_data[7]<<8);//�ٶ�
					W25Q64_SectorErase(0x002000);								//�洢���ٶ�
					motor1_speed[0] = motor_debug.motor1[2]%256;
					motor1_speed[1] = motor_debug.motor1[2]/256;
					W25Q64_PageProgram(0x002000,motor1_speed,2);
					vTaskResume(step_motor1_Handle);
				}
				/*���2��ʼ*/
				else if(screen_rx_data[0] == 0x12)     
				{
					vTaskResume(step_motor2_Handle);
					motor_debug.motor2[0] = screen_rx_data[1];//����
					motor_debug.motor2[1] = screen_rx_data[2] + (screen_rx_data[3]<<8) 
																	+ (screen_rx_data[4]<<16)+(screen_rx_data[5]<<24);//����
					motor_debug.motor2[2] = screen_rx_data[6] + (screen_rx_data[7]<<8);//�ٶ�
					W25Q64_SectorErase(0x003000);								//�洢���ٶ�
					motor2_speed[0] = motor_debug.motor2[2]%256;
					motor2_speed[1] = motor_debug.motor2[2]/256;
					W25Q64_PageProgram(0x003000,motor2_speed,2);
					vTaskResume(step_motor2_Handle);
				}
				/*���3��ʼ*/
				else if(screen_rx_data[0] == 0x13)     
				{
					vTaskResume(step_motor3_Handle);
					motor_debug.motor3[0] = screen_rx_data[1];//����
					motor_debug.motor3[1] = screen_rx_data[2] + (screen_rx_data[3]<<8) 
																	+ (screen_rx_data[4]<<16)+(screen_rx_data[5]<<24);//����
					motor_debug.motor3[2] = screen_rx_data[6] + (screen_rx_data[7]<<8);//�ٶ�
					W25Q64_SectorErase(0x004000);								//�洢���ٶ�
					motor3_speed[0] = motor_debug.motor3[2]%256;
					motor3_speed[1] = motor_debug.motor3[2]/256;
					W25Q64_PageProgram(0x004000,motor3_speed,2);
					vTaskResume(step_motor3_Handle);
				}
				/*���4��ʼ*/
				else if(screen_rx_data[0] == 0x14)     
				{
					vTaskResume(step_motor4_Handle);
					motor_debug.motor4[0] = screen_rx_data[1];//����
					motor_debug.motor4[1] = screen_rx_data[2] + (screen_rx_data[3]<<8) 
																	+ (screen_rx_data[4]<<16)+(screen_rx_data[5]<<24);//����
					motor_debug.motor4[2] = screen_rx_data[6] + (screen_rx_data[7]<<8);//�ٶ�
					W25Q64_SectorErase(0x005000);								//�洢���ٶ�
					motor4_speed[0] = motor_debug.motor4[2]%256;
					motor4_speed[1] = motor_debug.motor4[2]/256;
					W25Q64_PageProgram(0x005000,motor4_speed,2);
					vTaskResume(step_motor4_Handle);
				}
				/*���5��ʼ*/
				else if(screen_rx_data[0] == 0x15)     
				{
					vTaskResume(step_motor5_Handle);
					motor_debug.motor5[0] = screen_rx_data[1];//����
					motor_debug.motor5[1] = screen_rx_data[2] + (screen_rx_data[3]<<8) 
																	+ (screen_rx_data[4]<<16)+(screen_rx_data[5]<<24);//����
					motor_debug.motor5[2] = screen_rx_data[6] + (screen_rx_data[7]<<8);//�ٶ�
					W25Q64_SectorErase(0x006000);								//�洢���ٶ�
					motor5_speed[0] = motor_debug.motor5[2]%256;
					motor5_speed[1] = motor_debug.motor5[2]/256;
					W25Q64_PageProgram(0x006000,motor5_speed,2);
					vTaskResume(step_motor5_Handle);
				}
				/*���6��ʼ*/
				else if(screen_rx_data[0] == 0x16)     
				{
					static uint8_t enable[6] = {0x01,0x06,0x31,0x00,0x00,0x01}; 	//ʹ��
					Send_To_Servo(enable,6);
					vTaskDelay(4);
					motor_debug.motor6[0] = screen_rx_data[1];//����
					motor_debug.motor6[1] = screen_rx_data[2] + (screen_rx_data[3]<<8) 
																	+ (screen_rx_data[4]<<16)+(screen_rx_data[5]<<24);//����
					motor_debug.motor6[2] = screen_rx_data[6] + (screen_rx_data[7]<<8);//�ٶ�
					W25Q64_SectorErase(0x007000);								//�洢���ٶ�
					servo_speed[0] = motor_debug.motor6[2]%256;
					servo_speed[1] = motor_debug.motor6[2]/256;
					W25Q64_PageProgram(0x007000,servo_speed,2);
					vTaskResume(servo_motor_Handle);
				}
				/*֧�ۼ�ͷ����*/
				else if(screen_rx_data[0] == 0x17)
				{
					out(1,screen_rx_data[1]);
				}
				/*ץ������*/
				else if(screen_rx_data[0] == 0x18)
				{
					out(5,screen_rx_data[1]);
				}
				/*βɴ����*/
				else if(screen_rx_data[0] == 0x19)
				{
					out(3,screen_rx_data[1]);
				}
				/*���۰�����*/
				else if(screen_rx_data[0] == 0x1A)
				{
					out(4,screen_rx_data[1]);
				}
				/*���1ֹͣ*/
				if(screen_rx_data[0] == 0x01)
				{
					motor_en(1,0);
				}
				/*���2ֹͣ*/
				if(screen_rx_data[0] == 0x02)
				{
					motor_en(2,0);
				}
				/*���3ֹͣ*/
				if(screen_rx_data[0] == 0x03)
				{
					motor_en(3,0);
				}
				/*���4ֹͣ*/
				if(screen_rx_data[0] == 0x04)
				{
					motor_en(4,0);
				}
				/*���5ֹͣ*/
				if(screen_rx_data[0] == 0x05)
				{
					motor_en(5,0);
				}
				/*���6ֹͣ*/
				if(screen_rx_data[0] == 0x06)
				{
					motor_debug.motor6[1] = 1;
					vTaskSuspend(servo_motor_Handle);
				}
//			}
		}
	}
}
/*�洢����*/
void save_pra(void *Pra)
{
	static uint8_t pra_data[100];//����
//	static uint8_t location_addr[2];//�洢�ŷ����λ�õĵ�ַ(1~2046)*4096
//	static uint8_t location_pra[1];//�ŷ������ǰλ���뱣�����
//	static uint8_t loc_cnt[1]; //�ŷ����λ����
//	static uint8_t erase_cnt[2];//�������������0~65000
	while(1)
	{
		if(xQueueReceive(W25Q64_queue,pra_data,portMAX_DELAY) == pdPASS)
		{
			W25Q64_SectorErase(0x000000);//��������
			W25Q64_PageProgram(0x000000,pra_data,200);//�������
				/*βɴ�����ת*/
				motor_pra.motor1[0] = pra_data[1] + (pra_data[2]<<8) + 
															(pra_data[3]<<16) + (pra_data[4]<<24);
				vTaskDelay(1);
				/*��׵����һ����ת*/
				motor_pra.motor2[0] = pra_data[9] + (pra_data[10]<<8) + 
															(pra_data[11]<<16) + (pra_data[12]<<24);
				vTaskDelay(1);
				/*��׵���ڶ�����ת*/
				motor_pra.motor2[2] = pra_data[81] + (pra_data[82]<<8) + 
															(pra_data[83]<<16) + (pra_data[84]<<24);
				vTaskDelay(1);
				/*��׵����ת*/
				motor_pra.motor2[1] = pra_data[13] + (pra_data[14]<<8) + 
															(pra_data[15]<<16) + (pra_data[16]<<24);
				/*֧�۵����һ����ת*/
				motor_pra.motor3[0] = pra_data[17] + (pra_data[18]<<8) + 
															(pra_data[19]<<16) + (pra_data[20]<<24);
				vTaskDelay(1);
				vTaskDelay(1);
				/*֧�۵����һ�η�ת*/
				motor_pra.motor3[1] = pra_data[21] + (pra_data[22]<<8) + 
															(pra_data[23]<<16) + (pra_data[24]<<24);
				vTaskDelay(1);
				/*֧�۵���ڶ�����ת*/
				motor_pra.motor3[2] = pra_data[65] + (pra_data[66]<<8) + 
															(pra_data[67]<<16) + (pra_data[68]<<24);
				vTaskDelay(1);
				/*֧�۵���ڶ��η�ת*/
				motor_pra.motor3[3] = pra_data[69] + (pra_data[70]<<8) + 	
															(pra_data[71]<<16) + (pra_data[72]<<24);
				vTaskDelay(1);
				/*��ɴ�����һ����ת*/
				motor_pra.motor4[0] = pra_data[25] + (pra_data[26]<<8) + 
															(pra_data[27]<<16) + (pra_data[28]<<24);
				vTaskDelay(1);
				/*��ɴ����ڶ�����ת*/
				motor_pra.motor4[1] = pra_data[29] + (pra_data[30]<<8) + 
															(pra_data[31]<<16) + (pra_data[32]<<24);
				vTaskDelay(1);
				/*��ɴ�����������ת*/
				motor_pra.motor4[2] = pra_data[85] + (pra_data[86]<<8) + 
															(pra_data[87]<<16) + (pra_data[88]<<24);
				vTaskDelay(1);
				/*��ɴ������Ĵ���ת*/
				motor_pra.motor4[3] = pra_data[89] + (pra_data[90]<<8) + 
															(pra_data[91]<<16) + (pra_data[92]<<24);
				vTaskDelay(1);
				/*��ɴ����������ת*/
				motor_pra.motor4[4] = pra_data[5] + (pra_data[6]<<8) + 
															(pra_data[7]<<16) + (pra_data[8]<<24);
				vTaskDelay(1);
				/*ץ�ֵ����һ����ת*/
				motor_pra.motor5[0] = pra_data[33] + (pra_data[34]<<8) + 			
															(pra_data[35]<<16) + (pra_data[36]<<24);
				vTaskDelay(1);
				/*ץ�ֵ���ڶ�����ת*/
				motor_pra.motor5[1] = pra_data[37] + (pra_data[38]<<8) + 			
															(pra_data[39]<<16) + (pra_data[40]<<24);
				vTaskDelay(1);
				/*ץ�ֵ����һ�η�ת*/
				motor_pra.motor5[2] = pra_data[73] + (pra_data[74]<<8) + 			
															(pra_data[75]<<16) + (pra_data[76]<<24);
				vTaskDelay(1);
				/*ץ�ֵ���ڶ��η�ת*/
				motor_pra.motor5[3] = pra_data[93] + (pra_data[94]<<8) + 			
															(pra_data[95]<<16) + (pra_data[96]<<24);
				vTaskDelay(1);
				/*����λ�ò���*/
				motor_pra.motor6[0] = pra_data[41] + (pra_data[42]<<8) + 
															(pra_data[43]<<16) + (pra_data[44]<<24);
				/*��ǰλ��*/
				motor_pra.motor6[1] = pra_data[45] + (pra_data[46]<<8) + 
															(pra_data[47]<<16) + (pra_data[48]<<24);
				/*��ʱʱ��*/
				motor_pra.t[0]      = pra_data[49] + (pra_data[50]<<8)
															+ (pra_data[51]<<16) + (pra_data[52]<<24);
				motor_pra.t[1]      = pra_data[53] + (pra_data[54]<<8)
															+ (pra_data[55]<<16) + (pra_data[56]<<24);
				/*�洢�ŷ����λ����*/
				//loc_cnt[0] = pra_data[77];
				//W25Q64_SectorErase(0x008000);  //�����õ�ַ
				//W25Q64_PageProgram(0x008000,loc_cnt,1);//д���µ�ַ
				/*�����ŷ����λ��*/
				//W25Q64_ReadData(0x7FF000,location_addr,2);//��ȡ����λ�õĵ�ַ
				//location_pra[0] = pra_data[45];
				//W25Q64_SectorErase((location_addr[0]+(location_addr[1]<<8))<<12);//�����õ�ַ
				//W25Q64_PageProgram((location_addr[0]+(location_addr[1]<<8))<<12,location_pra,1);//д���µ�ַ
				/*��ʼ����*/
				vTaskResume(task_run_1_Handle);
				vTaskDelay(100);
		}
	}
}
void task_run_1(void *Pra)
{
	static uint8_t motor1_speed[2],motor2_speed[2],motor3_speed[2],motor4_speed[2],motor5_speed[2];
	static uint32_t t1,t2,t3,t4,t5;
	while(1)
	{
			printf("b14.bco=1024\xff\xff\xff");
		/*��ȡ�ٶ�*/
		W25Q64_ReadData(0x002000,motor1_speed,2);//δ��
		W25Q64_ReadData(0x003000,motor2_speed,2);
		W25Q64_ReadData(0x004000,motor3_speed,2);
		W25Q64_ReadData(0x005000,motor4_speed,2);
		W25Q64_ReadData(0x006000,motor5_speed,2);
		motor_en(1,1);
		HAL_Delay(1);
		motor_en(2,1);
		HAL_Delay(1);
		motor_en(3,1);
		HAL_Delay(1);
		motor_en(4,1);
		HAL_Delay(1);
		motor_en(5,1);
		HAL_Delay(1);
		TMC5160_CS1_Init(motor1_speed[0]+(motor1_speed[1]<<8));
		HAL_Delay(1);
		TMC5160_CS2_Init(motor2_speed[0]+(motor2_speed[1]<<8));
		HAL_Delay(1);
		TMC5160_CS3_Init(motor3_speed[0]+(motor3_speed[1]<<8));
		HAL_Delay(1);
		TMC5160_CS4_Init(motor4_speed[0]+(motor4_speed[1]<<8));
		HAL_Delay(1);
		TMC5160_CS5_Init(motor5_speed[0]+(motor5_speed[1]<<8));
		HAL_Delay(1);
//		/*ץ�ֵ����λ*/
		out(4,0);//δ��
//		motor_en(5,0);
//		motor_dir(5,0);
			TMC5160_CS5_Move(-10000);
			while(1)
			{
				if(in(4)||SPI1_CS5_ReadData(0x21)==-10000)
				{
					TMC5160_CS5_Move(0);
					break;
				}
				vTaskDelay(50);
			}
//		for(uint16_t i = 0;i<12000;i++)
//		{
//			HAL_GPIO_TogglePin(PUL5_GPIO_Port,PUL5_Pin);
//			t5 = 500000/(motor5_speed[0]+(motor5_speed[1]<<8));
//			while(t5--);
//			HAL_GPIO_TogglePin(PUL5_GPIO_Port,PUL5_Pin);
//			t5 = 500000/(motor5_speed[0]+(motor5_speed[1]<<8));
//			while(t5--);
//			if(in(4))
//				break;
//		}
//		/*֧�۵����һ�η�ת*/
				TMC5160_CS3_Move((-1)*motor_pra.motor3[1]);
				while(1)
				{
					if(SPI1_CS3_ReadData(0x21)==(-1)*motor_pra.motor3[1])
					{
						TMC5160_CS3_Move(0);
						break;
					}
					vTaskDelay(50);
				}
//			motor_en(3,0);
//			motor_dir(3,0);
//			for(;motor_pra.motor3[1];motor_pra.motor3[1]--)
//			{
//				HAL_GPIO_TogglePin(PUL3_GPIO_Port,PUL3_Pin);
//				t1 = 500000/(motor3_speed[0]+(motor3_speed[1]<<8));
//				while(t1--);
//				HAL_GPIO_TogglePin(PUL3_GPIO_Port,PUL3_Pin);
//				t1 = 500000/(motor3_speed[0]+(motor3_speed[1]<<8));
//				while(t1--);
//			}
//			/*֧�۵����һ����ת*/
				TMC5160_CS3_Move(motor_pra.motor3[0]);
				while(1)
				{
					if(SPI1_CS3_ReadData(0x21)==motor_pra.motor3[0])
					{
						TMC5160_CS3_Move(0);
						break;
					}
					vTaskDelay(50);
				}
//			motor_dir(3,1);	
//			for(;motor_pra.motor3[0];motor_pra.motor3[0]--)
//			{
//				HAL_GPIO_TogglePin(PUL3_GPIO_Port,PUL3_Pin);
//				t3 = 500000/(motor3_speed[0]+(motor3_speed[1]<<8));
//				while(t3--);
//				HAL_GPIO_TogglePin(PUL3_GPIO_Port,PUL3_Pin);
//				t3 = 500000/(motor3_speed[0]+(motor3_speed[1]<<8));
//				while(t3--);
//			}
//			motor_en(3,1);
//			/*��׵����һ����ת*/
				TMC5160_CS2_Move(motor_pra.motor2[0]);
				while(1)
				{
					if(SPI1_CS2_ReadData(0x21)==motor_pra.motor2[0])
					{
						TMC5160_CS2_Move(0);
						break;
					}
					vTaskDelay(50);
				}
//			motor_en(2,0);
//			motor_dir(2,1);
//			for(;motor_pra.motor2[0];motor_pra.motor2[0]--)
//			{
//				HAL_GPIO_TogglePin(PUL2_GPIO_Port,PUL2_Pin);
//				t2 = 500000/(motor2_speed[0]+(motor2_speed[1]<<8));
//				while(t2--);
//				HAL_GPIO_TogglePin(PUL2_GPIO_Port,PUL2_Pin);
//				t2 = 500000/(motor2_speed[0]+(motor2_speed[1]<<8));
//				while(t2--);
//			}
//			/*֧�ۼ�ͷ���״�*/
				out(1,1);//δ��
				vTaskDelay(motor_pra.t[0]);
//			/*��׵���ڶ�����ת*/
				TMC5160_CS2_Move(motor_pra.motor2[2]);
				while(1)
				{
					if(SPI1_CS2_ReadData(0x21)==motor_pra.motor2[2]||in(7))
					{
						TMC5160_CS2_Move(0);
						break;
					}
					vTaskDelay(50);
				}
//			for(;motor_pra.motor2[2];motor_pra.motor2[2]--)
//			{
//				HAL_GPIO_TogglePin(PUL2_GPIO_Port,PUL2_Pin);
//				t2 = 500000/(motor2_speed[0]+(motor2_speed[1]<<8));
//				while(t2--);
//				HAL_GPIO_TogglePin(PUL2_GPIO_Port,PUL2_Pin);
//				t2 = 500000/(motor2_speed[0]+(motor2_speed[1]<<8));
//				while(t2--);
//				/*�����յ�ֹͣ*/
//				if(in(7))
//				{
//					motor_pra.motor2[2] = 0;
//					break;
//				}
//			}
//			motor_en(2,1);			
//			/*ѭ����ɴ��һ�ε����ת*/
				TMC5160_CS4_Move(motor_pra.motor4[0]);
				while(1)
				{
					if(SPI1_CS4_ReadData(0x21)==motor_pra.motor4[0])
						break;
					vTaskDelay(50);
				}
//			motor_en(4,0);
//			motor_dir(4,1);
//			for(;motor_pra.motor4[0];motor_pra.motor4[0]--)
//			{
//				HAL_GPIO_TogglePin(PUL4_GPIO_Port,PUL4_Pin);
//				t4 = 500000/(motor4_speed[0]+(motor4_speed[1]<<8));
//				while(t4--);
//				HAL_GPIO_TogglePin(PUL4_GPIO_Port,PUL4_Pin);
//				t4 = 500000/(motor4_speed[0]+(motor4_speed[1]<<8));
//				while(t4--);
//			}
//			/*ץ�ֵ����һ����ת����׵����ת*/
				TMC5160_CS5_Move(motor_pra.motor5[0]);
				HAL_Delay(1);
				TMC5160_CS2_Move((-1)*motor_pra.motor2[0]);
				while(1)
				{
					if((SPI1_CS2_ReadData(0x21)==(-1)*motor_pra.motor2[0] || in(1)) && (in(5)||SPI1_CS5_ReadData(0x21)==motor_pra.motor5[0]))
						break;
					if(SPI1_CS2_ReadData(0x21)==(-1)*motor_pra.motor2[0] || in(1))
							TMC5160_CS2_Move(0);
					if(in(5)||SPI1_CS5_ReadData(0x21)==motor_pra.motor5[0])
						TMC5160_CS5_Move(0);
					vTaskDelay(50);
				}
				out(5,1);//δ��
//			motor_en(5,0);
//			motor_dir(5,1);
//			motor_en(2,0);
//			motor_dir(2,0);
//			for(;motor_pra.motor5[0]||motor_pra.motor2[1];motor_pra.motor5[0] = motor_pra.motor5[0]==0?0:--motor_pra.motor5[0],motor_pra.motor2[1] = motor_pra.motor2[1]==0?0:--motor_pra.motor2[1])
//			{
//				if(motor_pra.motor5[0])
//				{
//					HAL_GPIO_TogglePin(PUL5_GPIO_Port,PUL5_Pin);
//					t5 = 250000/(motor5_speed[0]+(motor5_speed[1]<<8));
//					while(t5--);
//					HAL_GPIO_TogglePin(PUL5_GPIO_Port,PUL5_Pin);
//					t5 = 250000/(motor5_speed[0]+(motor5_speed[1]<<8));
//					while(t5--);
//					if(in(5))
//						motor_pra.motor5[0] = 0;
//				}
//				if(motor_pra.motor2[1])
//				{
//					HAL_GPIO_TogglePin(PUL2_GPIO_Port,PUL2_Pin);
//					t2 = 250000/(motor2_speed[0]+(motor2_speed[1]<<8));
//					while(t2--);
//					HAL_GPIO_TogglePin(PUL2_GPIO_Port,PUL2_Pin);
//					t2 = 250000/(motor2_speed[0]+(motor2_speed[1]<<8));
//					while(t2--);
//					if(in(1))
//						motor_pra.motor2[1] = 0;
//				}
//			}
//			/*�ر�ץ������*/
				out(5,0);//δ��
//		/*ѭ����ɴ����ڶ�����ת*/
				TMC5160_CS4_Move(motor_pra.motor4[1]);
				while(1)
				{
					if(SPI1_CS4_ReadData(0x21)==motor_pra.motor4[1])
						break;
				}
//			for(;motor_pra.motor4[1];motor_pra.motor4[1]--)
//			{
//				HAL_GPIO_TogglePin(PUL4_GPIO_Port,PUL4_Pin);
//				t4 = 250000/(motor4_speed[0]+(motor4_speed[1]<<8));
//				while(t4--);
//				HAL_GPIO_TogglePin(PUL4_GPIO_Port,PUL4_Pin);
//				t4 = 250000/(motor4_speed[0]+(motor4_speed[1]<<8));
//				while(t4--);
//			}
//		/*ץ�ֵ���ڶ�����ת*/
				TMC5160_CS5_Move(motor_pra.motor5[1]);
				while(1)
				{
					if(SPI1_CS5_ReadData(0x21)==motor_pra.motor5[1])
						break;
				}
//			for(;motor_pra.motor5[1];motor_pra.motor5[1]--)
//			{
//				HAL_GPIO_TogglePin(PUL5_GPIO_Port,PUL5_Pin);
//				t5 = 250000/(motor5_speed[0]+(motor5_speed[1]<<8));
//				while(t5--);
//				HAL_GPIO_TogglePin(PUL5_GPIO_Port,PUL5_Pin);
//				t5 = 250000/(motor5_speed[0]+(motor5_speed[1]<<8));
//				while(t5--);
//			}
//			motor_en(5,1);
				/*�ر�֧�ۼ�ͷ����*/
				out(1,0);      //δ��       
//			vTaskDelay(motor_pra.t[1]);
				/*��ץ������*/
				out(5,1);	//δ��
//			/*ѭ����ɴ�����������ת*/
				TMC5160_CS4_Move(motor_pra.motor4[1]);
				while(1)
				{
					if(SPI1_CS4_ReadData(0x21)==motor_pra.motor4[1])
						break;
				}
//			motor_en(4,0);
//			motor_dir(4,1);
//			for(;motor_pra.motor4[2];motor_pra.motor4[2] = motor_pra.motor4[2] == 0?0:--motor_pra.motor4[2])
//			{
//					HAL_GPIO_TogglePin(PUL4_GPIO_Port,PUL4_Pin);
//					t4 = 250000/(motor4_speed[0]+(motor4_speed[1]<<8));
//					while(t4--);
//					HAL_GPIO_TogglePin(PUL4_GPIO_Port,PUL4_Pin);
//					t4 = 250000/(motor4_speed[0]+(motor4_speed[1]<<8));
//					while(t4--);
//			}
//			/*βɴ���׿�*/
				out(3,1);//δ��
//			/*ץ�ֵ����ת��֧�۵���ڶ��η�ת��βɴ�����ת��ѭ����ɴ������Ĵ���ת*/
				TMC5160_CS5_Move(motor_pra.motor5[2]);
				HAL_Delay(1);
				TMC5160_CS3_Move(motor_pra.motor3[3]);
				HAL_Delay(1);
				TMC5160_CS4_Move(motor_pra.motor4[3]);
				HAL_Delay(1);
				TMC5160_CS1_Move(motor_pra.motor1[0]);
				while(1)
				{
					if(in(4))
						TMC5160_CS5_Move(0);
					
					vTaskDelay(50);
				}
//			motor_en(3,0);
//			motor_dir(3,0);
//			motor_en(1,0);
//			motor_dir(1,1);
//			motor_en(4,0);
//			motor_dir(4,1);
//			motor_en(5,0);
//			motor_dir(5,0);
//			for(;motor_pra.motor5[2]||motor_pra.motor3[3]||motor_pra.motor1[0]||motor_pra.motor4[3];)
//			{
//				if(motor_pra.motor5[2])
//				{
//				HAL_GPIO_TogglePin(PUL5_GPIO_Port,PUL5_Pin);
//				t5 = 100000/(motor5_speed[0]+(motor5_speed[1]<<8));
//				while(t5--);
//				HAL_GPIO_TogglePin(PUL5_GPIO_Port,PUL5_Pin);
//				t5 = 100000/(motor5_speed[0]+(motor5_speed[1]<<8));
//				while(t5--);
//				motor_pra.motor5[2]--;
//				/*������λֹͣ*/
//				if(in(4))
//					motor_pra.motor5[2] = 0;
//				}
//				if(motor_pra.motor5[2]<=50000)
//				{
//					if((motor_pra.motor3[3]>=10) && (motor_pra.motor3[3] < 100000))
//					{
//						HAL_GPIO_TogglePin(PUL3_GPIO_Port,PUL3_Pin);
//						t3 = 250000/(motor3_speed[0]+(motor3_speed[1]<<8));
//						while(t3--);
//						HAL_GPIO_TogglePin(PUL3_GPIO_Port,PUL3_Pin);
//						t3 = 250000/(motor3_speed[0]+(motor3_speed[1]<<8));
//						while(t3--);
//						HAL_GPIO_TogglePin(PUL3_GPIO_Port,PUL3_Pin);
//						t3 = 250000/(motor3_speed[0]+(motor3_speed[1]<<8));
//						while(t3--);
//						HAL_GPIO_TogglePin(PUL3_GPIO_Port,PUL3_Pin);
//						t3 = 250000/(motor3_speed[0]+(motor3_speed[1]<<8));
//						while(t3--);
//						HAL_GPIO_TogglePin(PUL3_GPIO_Port,PUL3_Pin);
//						t3 = 250000/(motor3_speed[0]+(motor3_speed[1]<<8));
//						while(t3--);
//						HAL_GPIO_TogglePin(PUL3_GPIO_Port,PUL3_Pin);
//						t3 = 250000/(motor3_speed[0]+(motor3_speed[1]<<8));
//						while(t3--);
//						HAL_GPIO_TogglePin(PUL3_GPIO_Port,PUL3_Pin);
//						t3 = 250000/(motor3_speed[0]+(motor3_speed[1]<<8));
//						while(t3--);
//						HAL_GPIO_TogglePin(PUL3_GPIO_Port,PUL3_Pin);
//						t3 = 250000/(motor3_speed[0]+(motor3_speed[1]<<8));
//						while(t3--);
//						HAL_GPIO_TogglePin(PUL3_GPIO_Port,PUL3_Pin);
//						t3 = 250000/(motor3_speed[0]+(motor3_speed[1]<<8));
//						while(t3--);
//						HAL_GPIO_TogglePin(PUL3_GPIO_Port,PUL3_Pin);
//						t3 = 250000/(motor3_speed[0]+(motor3_speed[1]<<8));
//						while(t3--);
//						HAL_GPIO_TogglePin(PUL3_GPIO_Port,PUL3_Pin);
//						t3 = 250000/(motor3_speed[0]+(motor3_speed[1]<<8));
//						while(t3--);
//						HAL_GPIO_TogglePin(PUL3_GPIO_Port,PUL3_Pin);
//						t3 = 250000/(motor3_speed[0]+(motor3_speed[1]<<8));
//						while(t3--);
//						HAL_GPIO_TogglePin(PUL3_GPIO_Port,PUL3_Pin);
//						t3 = 250000/(motor3_speed[0]+(motor3_speed[1]<<8));
//						while(t3--);
//						HAL_GPIO_TogglePin(PUL3_GPIO_Port,PUL3_Pin);
//						t3 = 250000/(motor3_speed[0]+(motor3_speed[1]<<8));
//						while(t3--);
//						motor_pra.motor3[3]-=7;
//					}
//					else 
//						motor_pra.motor3[3] = 0;
//					if(motor_pra.motor1[0])
//					{
//						HAL_GPIO_TogglePin(PUL1_GPIO_Port,PUL1_Pin);
//						t1 = 250000/(motor1_speed[0]+(motor1_speed[1]<<8));
//						while(t1--);
//						HAL_GPIO_TogglePin(PUL1_GPIO_Port,PUL1_Pin);
//						t1 = 250000/(motor1_speed[0]+(motor1_speed[1]<<8));
//						while(t1--);
//						motor_pra.motor1[0]--;
//						if(motor_pra.motor1[0]<=10)
//						{
//							out(3,0);
//							motor_pra.motor1[0] = 0;
//						}
//					}
//					else 
//						motor_pra.motor1[0] = 0;
//					if(motor_pra.motor4[3])
//					{
//						HAL_GPIO_TogglePin(PUL4_GPIO_Port,PUL4_Pin);
//						t4 = 250000/(motor4_speed[0]+(motor4_speed[1]<<8));
//						while(t4--);
//						HAL_GPIO_TogglePin(PUL4_GPIO_Port,PUL4_Pin);
//						t4 = 250000/(motor4_speed[0]+(motor4_speed[1]<<8));
//						while(t4--);
//						motor_pra.motor4[3]--;
//					}
//					else 
//						motor_pra.motor4[3] = 0;
//				}
//			}		
//			/*βɴ���׹�*/
				out(3,0);//δ��
//			motor_en(1,1);
//			/*��ɴ����������ת*/
				TMC5160_CS4_Move(motor_pra.motor4[4]);
				while(1)
				{
					if(SPI1_CS4_ReadData(0x21)==motor_pra.motor4[4] || in(3))
					{
						TMC5160_CS4_Move(0);
						break;
					}
					vTaskDelay(50);
				}
//			for(;motor_pra.motor4[4];motor_pra.motor4[4]--)
//			{
//				HAL_GPIO_TogglePin(PUL4_GPIO_Port,PUL4_Pin);
//				t4 = 250000/(motor4_speed[0]+(motor4_speed[1]<<8));
//				while(t4--);
//				HAL_GPIO_TogglePin(PUL4_GPIO_Port,PUL4_Pin);
//				t4 = 250000/(motor4_speed[0]+(motor4_speed[1]<<8));
//				while(t4--);
//				if(in(3))
//					motor_pra.motor4[4] = 1;
//			}
//			motor_en(4,1);
//			motor_en(5,1);
//			/*֧�۵���ڶ�����ת*/
				TMC5160_CS3_Move(motor_pra.motor3[2]);
				while(1)
				{
					if(SPI1_CS3_ReadData(0x21)==motor_pra.motor3[2] || in(2))
					{
						TMC5160_CS3_Move(0);
						break;
					}
					vTaskDelay(50);
				}
//			motor_dir(3,1);
//			for(;motor_pra.motor3[2];motor_pra.motor3[2]--)
//			{
//				HAL_GPIO_TogglePin(PUL3_GPIO_Port,PUL3_Pin);
//				t3 = 200000/(motor3_speed[0]+(motor3_speed[1]<<8));
//				while(t3--);
//				HAL_GPIO_TogglePin(PUL3_GPIO_Port,PUL3_Pin);
//				t3 = 200000/(motor3_speed[0]+(motor3_speed[1]<<8));
//				while(t3--);
//				if(in(2))
//				{
//					motor_pra.motor3[2] = 0;
//					break;
//				}
//			}
//			motor_en(3,1);
				printf("b14.bco=50712\xff\xff\xff");
				vTaskSuspend(NULL);
	}
}
/*�ŷ�������ݴ���*/
void task_send_to_servo(void *Pra)
{
	static uint8_t servo_rx_data[50];
	while(1)
	{
		if(xQueueReceive(servo_rx_queue,servo_rx_data,portMAX_DELAY) == pdPASS)
		{
		/*��ȡ����ֵ*/
		get_servo_encoder();
		
		}
		vTaskDelay(200);
	}
}

void task_step_motor1(void* Pra)
{	
	static uint32_t t;
	//static uint8_t rx_data[5];
	while(1)
	{
//		motor_en(1,0);//���1ʹ��
//		motor_dir(1,motor_debug.motor1[0]);//���1����
//		motor_debug.motor1[2] = motor_debug.motor1[2]==0?1:motor_debug.motor1[2]; //ת������Ϊ1
//		for(;motor_debug.motor1[1];motor_debug.motor1[1]--)												//�����ת
//		{
//			HAL_GPIO_TogglePin(PUL1_GPIO_Port,PUL1_Pin);
//			t = 500000/motor_debug.motor1[2];														//ת��
//			while(t--);
//			HAL_GPIO_TogglePin(PUL1_GPIO_Port,PUL1_Pin);
//			t = 500000/motor_debug.motor1[2];														//ת��
//			while(t--);
//		}
//		motor_en(1,1);//���1ʧ��
		TMC5160_CS1_Init(motor_debug.motor1[2]);
		printf("b2.bco=1024\xff\xff\xff");
		motor_en(1,1);
		TMC5160_CS1_Move(motor_debug.motor1[0]?motor_debug.motor1[1]:(-1)*motor_debug.motor1[1]);
		while(1)
		{
			vTaskDelay(100);
			if(SPI1_CS1_ReadData(0x21)==(motor_debug.motor1[0]?motor_debug.motor1[1]:(-1)*motor_debug.motor1[1]))
				break;
		}
		printf("b2.bco=50712\xff\xff\xff");
		vTaskDelay(100);
		vTaskSuspend(NULL);
	}
}
void task_step_motor2(void* Pra)
{
	static uint32_t t;
	while(1)
	{
//		motor_en(2,0);
//		vTaskSuspend(step_motor_in_Handle);
//		motor_dir(2,motor_debug.motor2[0]);
//		motor_debug.motor2[2] = motor_debug.motor2[2]==0?1:motor_debug.motor2[2];
//		for(;motor_debug.motor2[1];motor_debug.motor2[1]--)
//		{
//			HAL_GPIO_TogglePin(PUL2_GPIO_Port,PUL2_Pin);
//			t = 500000/motor_debug.motor2[2];
//			while(t--);
//			HAL_GPIO_TogglePin(PUL2_GPIO_Port,PUL2_Pin);
//			t = 500000/motor_debug.motor2[2];
//			while(t--);
//			/*����ֹ��ת*/
//			if(in(1) && !motor_debug.motor2[0])
//			{
//				motor_debug.motor2[1] = 0;
//				break;
//			}
//			/*�յ��ֹ��ת*/
//			if(in(8) && motor_debug.motor2[0])
//			{
//				motor_debug.motor2[1] = 0;
//				break;
//			}
//		}
//		motor_en(2,1);
//		vTaskSuspend(NULL);
		TMC5160_CS2_Init(motor_debug.motor2[2]);
		printf("b3.bco=1024\xff\xff\xff");
		motor_en(2,1);
		TMC5160_CS2_Move(motor_debug.motor2[0]?motor_debug.motor2[1]:(-1)*motor_debug.motor2[1]);
		while(1)
		{
			vTaskDelay(100);
			if(SPI1_CS2_ReadData(0x21)==(motor_debug.motor2[0]?motor_debug.motor2[1]:(-1)*motor_debug.motor2[1]))
				break;
		}
		printf("b3.bco=50712\xff\xff\xff");
		vTaskDelay(100);
		vTaskSuspend(NULL);
	}
}
void task_step_motor3(void* Pra)
{
	static uint32_t t;
	while(1)
	{
//		motor_en(3,0);
//		motor_dir(3,motor_debug.motor3[0]);
//		motor_debug.motor3[2] = motor_debug.motor3[2]==0?1:motor_debug.motor3[2];
//		for(;motor_debug.motor3[1];motor_debug.motor3[1]--)
//		{
//			t = 500000/motor_debug.motor3[2];
//			HAL_GPIO_TogglePin(PUL3_GPIO_Port,PUL3_Pin);
//			while(t--);
//			t = 500000/motor_debug.motor3[2];
//			HAL_GPIO_TogglePin(PUL3_GPIO_Port,PUL3_Pin);
//			while(t--);
//			/*����ֹ��ת*/
//			if(in(2) && motor_debug.motor3[0])
//			{
//				motor_debug.motor3[1] = 0;
//				break;
//			}
//		}
//		motor_en(3,1);
//		vTaskSuspend(NULL);
		TMC5160_CS3_Init(motor_debug.motor3[2]);
		printf("b4.bco=1024\xff\xff\xff");
		motor_en(3,1);
		TMC5160_CS3_Move(motor_debug.motor3[0]?motor_debug.motor3[1]:(-1)*motor_debug.motor3[1]);
		while(1)
		{
			vTaskDelay(100);
			if(SPI1_CS3_ReadData(0x21)==(motor_debug.motor3[0]?motor_debug.motor3[1]:(-1)*motor_debug.motor3[1]))
				break;
		}
		printf("b4.bco=50712\xff\xff\xff");
		vTaskDelay(100);
		vTaskSuspend(NULL);
	}
}
void task_step_motor4(void* Pra)
{
	static uint32_t t;
	while(1)
	{
//		motor_en(4,0);
//		motor_dir(4,motor_debug.motor4[0]);
//		motor_debug.motor4[2] = motor_debug.motor4[2]==0?1:motor_debug.motor4[2];
//		for(;motor_debug.motor4[1];motor_debug.motor4[1]--)
//		{
//			HAL_GPIO_TogglePin(PUL4_GPIO_Port,PUL4_Pin);
//			t = 500000/motor_debug.motor4[2];
//			while(t--);
//			HAL_GPIO_TogglePin(PUL4_GPIO_Port,PUL4_Pin);
//			t = 500000/motor_debug.motor4[2];
//			while(t--);
//			if(in(3)&&!motor_debug.motor4[0])
//			{
//				motor_debug.motor4[1] = 0;
//				break;
//			}
//		}
//		motor_en(4,1);
//		vTaskSuspend(NULL);
		TMC5160_CS4_Init(motor_debug.motor4[2]);
		printf("b5.bco=1024\xff\xff\xff");
		motor_en(4,1);
		TMC5160_CS4_Move(motor_debug.motor4[0]?motor_debug.motor4[1]:(-1)*motor_debug.motor4[1]);
		while(1)
		{
			vTaskDelay(100);
			if(SPI1_CS4_ReadData(0x21)==(motor_debug.motor4[0]?motor_debug.motor4[1]:(-1)*motor_debug.motor4[1]))
				break;
		}
		printf("b5.bco=50712\xff\xff\xff");
		vTaskDelay(100);
		vTaskSuspend(NULL);
	}
}
void task_step_motor5(void* Pra)
{
	static uint32_t t;
	while(1)
	{
//		motor_en(5,0);
//		motor_dir(5,motor_debug.motor5[0]);
//		motor_debug.motor5[2] = motor_debug.motor5[2]==0?1:motor_debug.motor5[2];
//		for(;motor_debug.motor5[1];motor_debug.motor5[1]--)
//		{
//			HAL_GPIO_TogglePin(PUL5_GPIO_Port,PUL5_Pin);
//			t = 500000/motor_debug.motor5[2];
//			while(t--);
//			HAL_GPIO_TogglePin(PUL5_GPIO_Port,PUL5_Pin);
//			t = 500000/motor_debug.motor5[2];
//			while(t--);
//			/*����ֹ��ת*/
//			if(in(4) && !motor_debug.motor5[0])
//			{
//				motor_debug.motor5[1] = 0;
//				break;
//			}
//			/*�յ��ֹ��ת*/
//			if(in(5) && motor_debug.motor5[0])
//			{
//				motor_debug.motor5[1] = 0;
//				break;
//			}
//		}
//		motor_en(5,1);
		TMC5160_CS5_Init(motor_debug.motor5[2]);
		printf("b6.bco=1024\xff\xff\xff");
		motor_en(5,1);
		TMC5160_CS5_Move(motor_debug.motor5[0]?motor_debug.motor5[1]:(-1)*motor_debug.motor5[1]);
		while(1)
		{
			vTaskDelay(100);
			if(SPI1_CS5_ReadData(0x21)==(motor_debug.motor5[0]?motor_debug.motor5[1]:(-1)*motor_debug.motor5[1]))
				break;
		}
		printf("b6.bco=50712\xff\xff\xff");
		vTaskDelay(100);
		vTaskSuspend(NULL);
	}
}

/*�ŷ����*/
void task_servo_motor6(void* Pra)
{
	Servo_Init();
	static uint32_t t;
	while(1)
	{
		printf("b7.bco=1024\xff\xff\xff");
		servo_dir(motor_debug.motor6[0]);
		for(;motor_debug.motor6[1];motor_debug.motor6[1]--)
		{
			HAL_GPIO_TogglePin(PUL_GPIO_Port,PUL_Pin);
			t = 500000/motor_debug.motor6[2];
			while(t--);
			HAL_GPIO_TogglePin(PUL_GPIO_Port,PUL_Pin);
			t = 500000/motor_debug.motor6[2];
			while(t--);
		}
		printf("b7.bco=50712\xff\xff\xff");
		vTaskSuspend(NULL);
	}
}
//�ϵ緢���ŷ������ǰλ��
void task_send_location(void *Pra)
{
	static uint8_t save_location[2],servo_location[1];
	while(1)
	{
		vTaskDelay(2000);
		W25Q64_ReadData(0x7FF000,save_location,2);//��ȡ����λ�õĵ�ַ
		W25Q64_ReadData((save_location[0]+(save_location[1]<<8))<<12,servo_location,2);//��ȡ�ŷ����λ��
		printf("servo_location=%d\xff\xff\xff",servo_location[0]);//��λ�÷��͸���Ļ
		vTaskDelay(500);
		vTaskDelete(NULL);
	}
}
/*����������*/
void task_input(void *Pra)
{
	static uint32_t last_input,new_input;
	static uint8_t last_page,flag;
	while(1)
	{
		if(page == 2 || page == 5)
		{
			input = 0;
			input |= HAL_GPIO_ReadPin(IN1_GPIO_Port,IN1_Pin)<<0;
			input |= HAL_GPIO_ReadPin(IN2_GPIO_Port,IN2_Pin)<<1;
			input |= HAL_GPIO_ReadPin(IN3_GPIO_Port,IN3_Pin)<<2;
			input |= HAL_GPIO_ReadPin(IN4_GPIO_Port,IN4_Pin)<<3;
			input |= HAL_GPIO_ReadPin(IN5_GPIO_Port,IN5_Pin)<<4;
			input |= HAL_GPIO_ReadPin(IN6_GPIO_Port,IN6_Pin)<<5;
			input |= HAL_GPIO_ReadPin(IN7_GPIO_Port,IN7_Pin)<<6;
			input |= HAL_GPIO_ReadPin(IN8_GPIO_Port,IN8_Pin)<<7;
			input |= HAL_GPIO_ReadPin(IN9_GPIO_Port,IN9_Pin)<<8;
			input |= HAL_GPIO_ReadPin(IN10_GPIO_Port,IN10_Pin)<<9;
			input |= HAL_GPIO_ReadPin(IN11_GPIO_Port,IN11_Pin)<<10;
			input |= HAL_GPIO_ReadPin(IN12_GPIO_Port,IN12_Pin)<<11;
			input |= HAL_GPIO_ReadPin(IN13_GPIO_Port,IN13_Pin)<<12;
			input |= HAL_GPIO_ReadPin(IN14_GPIO_Port,IN14_Pin)<<13;
			input |= HAL_GPIO_ReadPin(IN15_GPIO_Port,IN15_Pin)<<14;
			input |= HAL_GPIO_ReadPin(IN16_GPIO_Port,IN16_Pin)<<15;
			input |= HAL_GPIO_ReadPin(IN17_GPIO_Port,IN17_Pin)<<16;
			input |= HAL_GPIO_ReadPin(IN18_GPIO_Port,IN18_Pin)<<17;
			input |= HAL_GPIO_ReadPin(IN19_GPIO_Port,IN19_Pin)<<18;
			input |= HAL_GPIO_ReadPin(IN20_GPIO_Port,IN20_Pin)<<19;
			if(page == 5)
			{
				for(uint8_t i=0;i<20;i++)
					printf("r%d.val=%d\xff\xff\xff",i,(input>>i)%2);
			}
			else if(page == 2)
			{
				if(last_page != page)
				{
					for(uint8_t i=0;i<20;i++)
						printf("page2_r%d=%d\xff\xff\xff",i+6,(input>>i)%2);
				}
				else
				{
					new_input = input^last_input;
					for(uint8_t i=0;i<20;i++)
					{	
						if((new_input>>i)%2)
						{
							printf("page2_r%d=%d\xff\xff\xff",i+6,(input>>i)%2);
						}
					}
				}
			}
		}
		if(flag == 0)
		{
			for(uint8_t i=0;i<20;i++)
						printf("page2_r%d=%d\xff\xff\xff",i+6,(input>>i)%2);
			flag = 1;
		}
		last_page = page;
		last_input = input;
		vTaskDelay(300);
	}
}

/*�̵������*/
void task_output(void *Pra)
{
	while(1)
	{
		if(page == 3)
		{
			output = 0;
			output |= HAL_GPIO_ReadPin(OUT1_GPIO_Port,OUT1_Pin)<<0;
			output |= HAL_GPIO_ReadPin(OUT2_GPIO_Port,OUT2_Pin)<<1;
			output |= HAL_GPIO_ReadPin(OUT3_GPIO_Port,OUT3_Pin)<<2;
			output |= HAL_GPIO_ReadPin(OUT4_GPIO_Port,OUT4_Pin)<<3;
			output |= HAL_GPIO_ReadPin(OUT5_GPIO_Port,OUT5_Pin)<<4;
			output |= HAL_GPIO_ReadPin(OUT6_GPIO_Port,OUT6_Pin)<<5;
			output |= HAL_GPIO_ReadPin(OUT7_GPIO_Port,OUT7_Pin)<<6;
			output |= HAL_GPIO_ReadPin(OUT8_GPIO_Port,OUT8_Pin)<<7;
			output |= HAL_GPIO_ReadPin(OUT9_GPIO_Port,OUT9_Pin)<<8;
			output |= HAL_GPIO_ReadPin(OUT10_GPIO_Port,OUT10_Pin)<<9;
			for(uint8_t i=0;i<10;i++)
			{
				printf("r%d.val=%d\xff\xff\xff",i,(output>>i)%2);
			}
		}
		vTaskDelay(500);
	}
}

/*�Լ���*/
void task_motor_check(void *Pra)
{
	while(1)
	{
		if(page == 4)
		{
			printf("n0.val=%d\xff\xff\xff",motor_pra.motor1[0]);
			printf("n1.val=%d\xff\xff\xff",motor_pra.motor2[0]);
			printf("n2.val=%d\xff\xff\xff",motor_pra.motor3[0]);
			printf("n3.val=%d\xff\xff\xff",motor_pra.motor4[0]);
			printf("n4.val=%d\xff\xff\xff",motor_pra.motor5[0]);
			printf("n5.val=%d\xff\xff\xff",motor_pra.motor6[0]);
			printf("n6.val=%d\xff\xff\xff",motor_pra.motor1[1]);
			printf("n7.val=%d\xff\xff\xff",motor_pra.motor2[1]);
			printf("n8.val=%d\xff\xff\xff",motor_pra.motor3[1]);
			printf("n9.val=%d\xff\xff\xff",motor_pra.motor4[1]);
			printf("n10.val=%d\xff\xff\xff",motor_pra.motor5[1]);
			printf("n11.val=%d\xff\xff\xff",motor_pra.motor6[1]);
			printf("r0.val=%d\xff\xff\xff",motor_pra.motor1[0]>0?1:0);
			printf("r1.val=%d\xff\xff\xff",motor_pra.motor2[0]>0?1:0);
			printf("r2.val=%d\xff\xff\xff",motor_pra.motor3[0]>0?1:0);
			printf("r3.val=%d\xff\xff\xff",motor_pra.motor4[0]>0?1:0);
			printf("r4.val=%d\xff\xff\xff",motor_pra.motor5[0]>0?1:0);
			printf("r5.val=%d\xff\xff\xff",motor_pra.motor6[0]>0?1:0);
			for(uint8_t i=7;i<=12;i++)
			{
				printf("r%d.val=%d\xff\xff\xff",i,0);
			}
		}
		vTaskDelay(300);
	}	
}

void get_page(void*Pra)
{
	while(1)
	{
		vTaskDelay(250);
		printf("page_val=%d\xff\xff\xff",page);
		vTaskDelay(250);
		printf("page_val=%d\xff\xff\xff",page);
		vTaskDelete(NULL);
	}
}

void test(void *Pra)
{
	while(1)
	{
		vTaskDelay(1000);
	}
}

void start_task(void)
{
	screen_rx_queue = xQueueCreate(1,200);
	servo_rx_queue  = xQueueCreate(1,50);
	W25Q64_queue = xQueueCreate(1,100);
	xTaskCreate(screen_data_pro,"screen_data",512,NULL,12,NULL);
	xTaskCreate(task_step_motor1,"step_motor1",128,NULL,10,&step_motor1_Handle);
	xTaskCreate(task_step_motor2,"step_motor2",128,NULL,10,&step_motor2_Handle);
	xTaskCreate(task_step_motor3,"step_motor3",128,NULL,10,&step_motor3_Handle);
	xTaskCreate(task_step_motor4,"step_motor4",128,NULL,10,&step_motor4_Handle);
	xTaskCreate(task_step_motor5,"step_motor5",128,NULL,10,&step_motor5_Handle);
	xTaskCreate(task_servo_motor6,"servo_motor6",256,NULL,10,&servo_motor_Handle);
	xTaskCreate(task_input,"input",128,NULL,11,NULL);
	xTaskCreate(task_output,"output",128,NULL,11,NULL);
	xTaskCreate(get_page,"get_page",128,NULL,11,NULL);
	xTaskCreate(task_motor_check,"motor_check",256,NULL,14,NULL);
//	xTaskCreate(task_send_to_servo,"send_to_servo",128,NULL,10,NULL);
	xTaskCreate(save_pra,"save_pra",256,NULL,10,NULL);
	xTaskCreate(task_send_location,"save_pra",128,NULL,10,NULL);
	xTaskCreate(task_run_1,"task_run_1",512,NULL,11,&task_run_1_Handle);
	
//xTaskCreate(test,"test",128,NULL,10,NULL);
	
	vTaskSuspend(task_run_1_Handle);
	//vTaskSuspend(task_run_2_Handle);
	//vTaskSuspend(task_run_3_Handle);
	vTaskSuspend(step_motor1_Handle);
	vTaskSuspend(step_motor2_Handle);
	vTaskSuspend(step_motor3_Handle);
	vTaskSuspend(step_motor4_Handle);
	vTaskSuspend(step_motor5_Handle);
	vTaskSuspend(servo_motor_Handle);
	
	vTaskStartScheduler();
}
