#include "spi.h"
#include "main.h"
static char Spi_Status;
/*片选*/
void TMC5160_CS(uint8_t num,uint8_t state)
{
	switch(num)
	{
		case 1:HAL_GPIO_WritePin(CS1_GPIO_Port,CS1_Pin,(GPIO_PinState)state);break;
		case 2:HAL_GPIO_WritePin(CS2_GPIO_Port,CS2_Pin,(GPIO_PinState)state);break;
		case 3:HAL_GPIO_WritePin(CS3_GPIO_Port,CS3_Pin,(GPIO_PinState)state);break;
		case 4:HAL_GPIO_WritePin(CS4_GPIO_Port,CS4_Pin,(GPIO_PinState)state);break;
		case 5:HAL_GPIO_WritePin(CS5_GPIO_Port,CS5_Pin,(GPIO_PinState)state);break;
		default: break;
	}
}
void SPI1_CS1_sendData(uint8_t addr,long datagram)
{	
	unsigned char	cmd[5];
  TMC5160_CS(1,0); 
	cmd[0]=addr;
	cmd[1]=(uint8_t)(datagram >> 24);
	cmd[2]=(uint8_t)(datagram >> 16);
	cmd[3]=(uint8_t)(datagram >> 8);
	cmd[4]=(uint8_t)(datagram);	
	if(HAL_SPI_TransmitReceive(&hspi1,cmd,cmd,5,500) == HAL_OK)
	{
		TMC5160_CS(1,1); 
	}
	else;
	TMC5160_CS(1,1);
}
void SPI1_CS2_sendData(uint8_t addr,long datagram)
{	
	unsigned char	cmd[5];
  TMC5160_CS(2,0); 
	cmd[0]=addr;
	cmd[1]=(uint8_t)(datagram >> 24);
	cmd[2]=(uint8_t)(datagram >> 16);
	cmd[3]=(uint8_t)(datagram >> 8);
	cmd[4]=(uint8_t)(datagram);	
	if(HAL_SPI_TransmitReceive(&hspi1,cmd,cmd,5,500) == HAL_OK)
	{
		TMC5160_CS(2,1); 
	}
	else;
	TMC5160_CS(2,1);
}
void SPI1_CS3_sendData(uint8_t addr,long datagram)
{	
	unsigned char	cmd[5];
  TMC5160_CS(3,0); 
	cmd[0]=addr;
	cmd[1]=(uint8_t)(datagram >> 24);
	cmd[2]=(uint8_t)(datagram >> 16);
	cmd[3]=(uint8_t)(datagram >> 8);
	cmd[4]=(uint8_t)(datagram);	
	if(HAL_SPI_TransmitReceive(&hspi1,cmd,cmd,5,500) == HAL_OK)
	{
		TMC5160_CS(3,1); 
	}
	else;
	TMC5160_CS(3,1);
}
void SPI1_CS4_sendData(uint8_t addr,long datagram)
{	
	unsigned char	cmd[5];
  TMC5160_CS(4,0); 
	cmd[0]=addr;
	cmd[1]=(uint8_t)(datagram >> 24);
	cmd[2]=(uint8_t)(datagram >> 16);
	cmd[3]=(uint8_t)(datagram >> 8);
	cmd[4]=(uint8_t)(datagram);	
	if(HAL_SPI_TransmitReceive(&hspi1,cmd,cmd,5,500) == HAL_OK)
	{
		TMC5160_CS(4,1); 
	}
	else;
	TMC5160_CS(4,1);
}
void SPI1_CS5_sendData(uint8_t addr,long datagram)
{	
	unsigned char	cmd[5];
  TMC5160_CS(5,0); 
	cmd[0]=addr;
	cmd[1]=(uint8_t)(datagram >> 24);
	cmd[2]=(uint8_t)(datagram >> 16);
	cmd[3]=(uint8_t)(datagram >> 8);
	cmd[4]=(uint8_t)(datagram);	
	if(HAL_SPI_TransmitReceive(&hspi1,cmd,cmd,5,500) == HAL_OK)
	{
		TMC5160_CS(5,1); 
	}
	else;
	TMC5160_CS(5,1);
}
void TMC5160_CS5_Init(uint16_t speed)
{
  SPI1_CS5_sendData(0xEC,0x000100C3); 				//PAGE46:CHOPCONF: TOFF=3, HSTRT=4, HEND=1, TBL=2, CHM=0 (spreadcycle)
	SPI1_CS5_sendData(0xED,0x0100E313); 				//PAGE48:
	SPI1_CS5_sendData(0x8A,0x00180710); 				//PAGE30:死区时间10：200nS，BBMCLKS：7，驱动电流19、18BIT：10，滤波时间21、20BIT：01：200nS 
	SPI1_CS5_sendData(0x90,0x00000700); 				//PAGE33:IHOLD_IRUN: IHOLD=06(默认10), IRUN=20 (31max.current), IHOLDDELAY=6  
	SPI1_CS5_sendData(0x91,0x0000000A);				//PAGE33:TPOWERDOWN=10:电机静止到电流减小之间的延时
	SPI1_CS5_sendData(0x80,0x00000004);				//PAGE27:EN_PWM_MODE=1，使能STEALTHCHOP
	SPI1_CS5_sendData(0xF0,0x000C0000);				//PAGE43:PWMCONF--STEALTHCHOP:
	SPI1_CS5_sendData(0x93,0x000001F4);				//PAGE33:TPWM_THRS=500,对应切换速度35000=ca.30RPM
	SPI1_CS5_sendData(0xA4,100*speed);     				//PAGE35:A1=1000 第一阶段加速度
	SPI1_CS5_sendData(0xA5,500*speed);     				//PAGE35:V1=50000加速度阀值速度V1
	SPI1_CS5_sendData(0xA6,50*speed);     					//PAGE35:AMAX=500大于V1的加速度 	
	SPI1_CS5_sendData(0xA7,13000*speed);     			//PAGE35:VMAX=200000 
	SPI1_CS5_sendData(0xA8,700*speed);							//PAGE35:DMAX=700大于V1的减速度 
	SPI1_CS5_sendData(0xAA,140*speed);     				//PAGE35:D1=1400小于V1的减速度 
	SPI1_CS5_sendData(0xAB,10);     					//PAGE35:VSTOP=10停止速度，接近于0		
	SPI1_CS5_sendData(0xA0,0); 								//PAGE35:RAMPMODE=0位置模式，使用所有A、V、D参数	
	SPI1_CS5_sendData(0x6D,0x00000000);
	SPI1_CS5_sendData(0x13,0x00000000);
	SPI1_CS5_sendData(0x70,0x000401C8);

	SPI1_CS5_sendData(0x10,0x0004FF1F);
}
void TMC5160_CS1_Init(uint16_t speed)
{
  SPI1_CS1_sendData(0xEC,0x000100C3); 				//PAGE46:CHOPCONF: TOFF=3, HSTRT=4, HEND=1, TBL=2, CHM=0 (spreadcycle)
	SPI1_CS1_sendData(0xED,0x0100E313); 				//PAGE48:
	SPI1_CS1_sendData(0x8A,0x00180710); 				//PAGE30:死区时间10：200nS，BBMCLKS：7，驱动电流19、18BIT：10，滤波时间21、20BIT：01：200nS 
	SPI1_CS1_sendData(0x90,0x00000700); 				//PAGE33:IHOLD_IRUN: IHOLD=06(默认10), IRUN=20 (31max.current), IHOLDDELAY=6  
	SPI1_CS1_sendData(0x91,0x0000000A);				//PAGE33:TPOWERDOWN=10:电机静止到电流减小之间的延时
	SPI1_CS1_sendData(0x80,0x00000004);				//PAGE27:EN_PWM_MODE=1，使能STEALTHCHOP
	SPI1_CS1_sendData(0xF0,0x000C0000);				//PAGE43:PWMCONF--STEALTHCHOP:
	SPI1_CS1_sendData(0x93,0x000001F4);				//PAGE33:TPWM_THRS=500,对应切换速度35000=ca.30RPM
	SPI1_CS1_sendData(0xA4,100*speed);     				//PAGE35:A1=1000 第一阶段加速度
	SPI1_CS1_sendData(0xA5,500*speed);     				//PAGE35:V1=50000加速度阀值速度V1
	SPI1_CS1_sendData(0xA6,50*speed);     					//PAGE35:AMAX=500大于V1的加速度 	
	SPI1_CS1_sendData(0xA7,13000*speed);     			//PAGE35:VMAX=200000 
	SPI1_CS1_sendData(0xA8,700*speed);							//PAGE35:DMAX=700大于V1的减速度 
	SPI1_CS1_sendData(0xAA,140*speed);     				//PAGE35:D1=1400小于V1的减速度 
	SPI1_CS1_sendData(0xAB,10);     					//PAGE35:VSTOP=10停止速度，接近于0		
	SPI1_CS1_sendData(0xA0,0); 								//PAGE35:RAMPMODE=0位置模式，使用所有A、V、D参数	
	SPI1_CS1_sendData(0x6D,0x00000000);
	SPI1_CS1_sendData(0x13,0x00000000);
	SPI1_CS1_sendData(0x70,0x000401C8);

	SPI1_CS1_sendData(0x10,0x0004FF1F);
}
void TMC5160_CS2_Init(uint16_t speed)
{
  SPI1_CS2_sendData(0xEC,0x000100C3); 				//PAGE46:CHOPCONF: TOFF=3, HSTRT=4, HEND=1, TBL=2, CHM=0 (spreadcycle)
	SPI1_CS2_sendData(0xED,0x0100E313); 				//PAGE48:
	SPI1_CS2_sendData(0x8A,0x00180710); 				//PAGE30:死区时间10：200nS，BBMCLKS：7，驱动电流19、18BIT：10，滤波时间21、20BIT：01：200nS 
	SPI1_CS2_sendData(0x90,0x00000700); 				//PAGE33:IHOLD_IRUN: IHOLD=06(默认10), IRUN=20 (31max.current), IHOLDDELAY=6  
	SPI1_CS2_sendData(0x91,0x0000000A);				//PAGE33:TPOWERDOWN=10:电机静止到电流减小之间的延时
	SPI1_CS2_sendData(0x80,0x00000004);				//PAGE27:EN_PWM_MODE=1，使能STEALTHCHOP
	SPI1_CS2_sendData(0xF0,0x000C0000);				//PAGE43:PWMCONF--STEALTHCHOP:
	SPI1_CS2_sendData(0x93,0x000001F4);				//PAGE33:TPWM_THRS=500,对应切换速度35000=ca.30RPM
	SPI1_CS2_sendData(0xA4,100*speed);     				//PAGE35:A1=1000 第一阶段加速度
	SPI1_CS2_sendData(0xA5,500*speed);     				//PAGE35:V1=50000加速度阀值速度V1
	SPI1_CS2_sendData(0xA6,50*speed);     					//PAGE35:AMAX=500大于V1的加速度 	
	SPI1_CS2_sendData(0xA7,13000*speed);     			//PAGE35:VMAX=200000 
	SPI1_CS2_sendData(0xA8,700*speed);							//PAGE35:DMAX=700大于V1的减速度 
	SPI1_CS2_sendData(0xAA,140*speed);     				//PAGE35:D1=1400小于V1的减速度
	SPI1_CS2_sendData(0xAB,10);     					//PAGE35:VSTOP=10停止速度，接近于0		
	SPI1_CS2_sendData(0xA0,0); 								//PAGE35:RAMPMODE=0位置模式，使用所有A、V、D参数	
	SPI1_CS2_sendData(0x6D,0x00000000);
	SPI1_CS2_sendData(0x13,0x00000000);
	SPI1_CS2_sendData(0x70,0x000401C8);
         
	SPI1_CS2_sendData(0x10,0x0004FF1F);
}
void TMC5160_CS3_Init(uint16_t speed)
{
  SPI1_CS3_sendData(0xEC,0x000100C3); 				//PAGE46:CHOPCONF: TOFF=3, HSTRT=4, HEND=1, TBL=2, CHM=0 (spreadcycle)
	SPI1_CS3_sendData(0xED,0x0100E313); 				//PAGE48:
	SPI1_CS3_sendData(0x8A,0x00180710); 				//PAGE30:死区时间10：200nS，BBMCLKS：7，驱动电流19、18BIT：10，滤波时间21、20BIT：01：200nS 
	SPI1_CS3_sendData(0x90,0x00000700); 				//PAGE33:IHOLD_IRUN: IHOLD=06(默认10), IRUN=20 (31max.current), IHOLDDELAY=6  
	SPI1_CS3_sendData(0x91,0x0000000A);				//PAGE33:TPOWERDOWN=10:电机静止到电流减小之间的延时
	SPI1_CS3_sendData(0x80,0x00000004);				//PAGE27:EN_PWM_MODE=1，使能STEALTHCHOP
	SPI1_CS3_sendData(0xF0,0x000C0000);				//PAGE43:PWMCONF--STEALTHCHOP:
	SPI1_CS3_sendData(0x93,0x000001F4);				//PAGE33:TPWM_THRS=500,对应切换速度35000=ca.30RPM
	SPI1_CS3_sendData(0xA4,100*speed);     				//PAGE35:A1=1000 第一阶段加速度
	SPI1_CS3_sendData(0xA5,500*speed);     				//PAGE35:V1=50000加速度阀值速度V1
	SPI1_CS3_sendData(0xA6,50*speed);     					//PAGE35:AMAX=500大于V1的加速度 	
	SPI1_CS3_sendData(0xA7,13000*speed);     			//PAGE35:VMAX=200000 
	SPI1_CS3_sendData(0xA8,700*speed);							//PAGE35:DMAX=700大于V1的减速度 
	SPI1_CS3_sendData(0xAA,140*speed);     				//PAGE35:D1=1400小于V1的减速度 
	SPI1_CS3_sendData(0xAB,10);     					//PAGE35:VSTOP=10停止速度，接近于0		
	SPI1_CS3_sendData(0xA0,0); 								//PAGE35:RAMPMODE=0位置模式，使用所有A、V、D参数	
	SPI1_CS3_sendData(0x6D,0x00000000);
	SPI1_CS3_sendData(0x13,0x00000000);
	SPI1_CS3_sendData(0x70,0x000401C8);

	SPI1_CS3_sendData(0x10,0x0004FF1F);
}
void TMC5160_CS4_Init(uint16_t speed)
{
  SPI1_CS4_sendData(0xEC,0x000100C3); 				//PAGE46:CHOPCONF: TOFF=3, HSTRT=4, HEND=1, TBL=2, CHM=0 (spreadcycle)
	SPI1_CS4_sendData(0xED,0x0100E313); 				//PAGE48:
	SPI1_CS4_sendData(0x8A,0x00180710); 				//PAGE30:死区时间10：200nS，BBMCLKS：7，驱动电流19、18BIT：10，滤波时间21、20BIT：01：200nS 
	SPI1_CS4_sendData(0x90,0x00000700); 				//PAGE33:IHOLD_IRUN: IHOLD=06(默认10), IRUN=20 (31max.current), IHOLDDELAY=6  
	SPI1_CS4_sendData(0x91,0x0000000A);				//PAGE33:TPOWERDOWN=10:电机静止到电流减小之间的延时
	SPI1_CS4_sendData(0x80,0x00000004);				//PAGE27:EN_PWM_MODE=1，使能STEALTHCHOP
	SPI1_CS4_sendData(0xF0,0x000C0000);				//PAGE43:PWMCONF--STEALTHCHOP:
	SPI1_CS4_sendData(0x93,0x000001F4);				//PAGE33:TPWM_THRS=500,对应切换速度35000=ca.30RPM
	SPI1_CS4_sendData(0xA4,100*speed);     				//PAGE35:A1=1000 第一阶段加速度
	SPI1_CS4_sendData(0xA5,500*speed);     				//PAGE35:V1=50000加速度阀值速度V1
	SPI1_CS4_sendData(0xA6,50*speed);     					//PAGE35:AMAX=500大于V1的加速度 	
	SPI1_CS4_sendData(0xA7,13000*speed);     			//PAGE35:VMAX=200000 
	SPI1_CS4_sendData(0xA8,700*speed);							//PAGE35:DMAX=700大于V1的减速度 
	SPI1_CS4_sendData(0xAA,140*speed);     				//PAGE35:D1=1400小于V1的减速度
	SPI1_CS4_sendData(0xAB,10);     					//PAGE35:VSTOP=10停止速度，接近于0		
	SPI1_CS4_sendData(0xA0,0); 								//PAGE35:RAMPMODE=0位置模式，使用所有A、V、D参数	
	SPI1_CS4_sendData(0x6D,0x00000000);
	SPI1_CS4_sendData(0x13,0x00000000);
	SPI1_CS4_sendData(0x70,0x000401C8);

	SPI1_CS4_sendData(0x10,0x0004FF1F);
}
void TMC5160_CS1_Move(long PosiTionData)				//移动数据
{	
	SPI1_CS1_sendData(0xAD,PosiTionData);			//PAGE36:XTARGET=-51200(逆时针旋转1圈(1圈：200*256微步))
	SPI1_CS1_sendData(0xA1,0);									//PAGE35:启动电机，参考位置清0
}
void TMC5160_CS2_Move(long PosiTionData)				//移动数据
{	
	SPI1_CS2_sendData(0xAD,PosiTionData);			//PAGE36:XTARGET=-51200(逆时针旋转1圈(1圈：200*256微步))
	SPI1_CS2_sendData(0xA1,0);									//PAGE35:启动电机，参考位置清0
}
void TMC5160_CS3_Move(long PosiTionData)				//移动数据
{	
	SPI1_CS3_sendData(0xAD,PosiTionData);			//PAGE36:XTARGET=-51200(逆时针旋转1圈(1圈：200*256微步))
	SPI1_CS3_sendData(0xA1,0);									//PAGE35:启动电机，参考位置清0
}
void TMC5160_CS4_Move(long PosiTionData)				//移动数据
{	
	SPI1_CS4_sendData(0xAD,PosiTionData);			//PAGE36:XTARGET=-51200(逆时针旋转1圈(1圈：200*256微步))
	SPI1_CS4_sendData(0xA1,0);									//PAGE35:启动电机，参考位置清0
}
void TMC5160_CS5_Move(long PosiTionData)				//移动数据
{	
	SPI1_CS5_sendData(0xAD,PosiTionData);			//PAGE36:XTARGET=-51200(逆时针旋转1圈(1圈：200*256微步))
	SPI1_CS5_sendData(0xA1,0);									//PAGE35:启动电机，参考位置清0
}

long SPI1_CS1_ReadData(char address)
{
	long datagram;
	unsigned char	cmd[5],ReadData5160[5];
	TMC5160_CS(1,0);
	cmd[0]=address;																											
	if(HAL_SPI_TransmitReceive(&hspi1,cmd,ReadData5160,5,500) == HAL_OK)
	{
		datagram = (ReadData5160[1] << 24) | (ReadData5160[2] << 16) | (ReadData5160[3] << 8) | ReadData5160[4];			
	}
	else	datagram=0x5a5a5a5a;
	Spi_Status=ReadData5160[0];																					//PAGE23:SPI返回状态	
	TMC5160_CS(1,1);

	return datagram;
}
long SPI1_CS2_ReadData(char address)
{
	long datagram;
	unsigned char	cmd[5],ReadData5160[5];
	TMC5160_CS(2,0);
	cmd[0]=address;																											
	if(HAL_SPI_TransmitReceive(&hspi1,cmd,ReadData5160,5,500) == HAL_OK)
	{
		datagram = (ReadData5160[1] << 24) | (ReadData5160[2] << 16) | (ReadData5160[3] << 8) | ReadData5160[4];			
	}
	else	datagram=0x5a5a5a5a;
	Spi_Status=ReadData5160[0];																					//PAGE23:SPI返回状态	
	TMC5160_CS(2,1);

	return datagram;
}
long SPI1_CS3_ReadData(char address)
{
	long datagram;
	unsigned char	cmd[5],ReadData5160[5];
	TMC5160_CS(3,0);
	cmd[0]=address;																											
	if(HAL_SPI_TransmitReceive(&hspi1,cmd,ReadData5160,5,500) == HAL_OK)
	{
		datagram = (ReadData5160[1] << 24) | (ReadData5160[2] << 16) | (ReadData5160[3] << 8) | ReadData5160[4];			
	}
	else	datagram=0x5a5a5a5a;
	Spi_Status=ReadData5160[0];																					//PAGE23:SPI返回状态	
	TMC5160_CS(3,1);

	return datagram;
}
long SPI1_CS4_ReadData(char address)
{
	long datagram;
	unsigned char	cmd[5],ReadData5160[5];
	TMC5160_CS(4,0);
	cmd[0]=address;																											
	if(HAL_SPI_TransmitReceive(&hspi1,cmd,ReadData5160,5,500) == HAL_OK)
	{
		datagram = (ReadData5160[1] << 24) | (ReadData5160[2] << 16) | (ReadData5160[3] << 8) | ReadData5160[4];			
	}
	else	datagram=0x5a5a5a5a;
	Spi_Status=ReadData5160[0];																					//PAGE23:SPI返回状态	
	TMC5160_CS(4,1);

	return datagram;
}
long SPI1_CS5_ReadData(char address)
{
	long datagram;
	unsigned char	cmd[5],ReadData5160[5];
	TMC5160_CS(5,0);
	cmd[0]=address;																											
	if(HAL_SPI_TransmitReceive(&hspi1,cmd,ReadData5160,5,500) == HAL_OK)
	{
		datagram = (ReadData5160[1] << 24) | (ReadData5160[2] << 16) | (ReadData5160[3] << 8) | ReadData5160[4];			
	}
	else	datagram=0x5a5a5a5a;
	Spi_Status=ReadData5160[0];																					//PAGE23:SPI返回状态	
	TMC5160_CS(5,1);

	return datagram;
}