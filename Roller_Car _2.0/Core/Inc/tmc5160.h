#ifndef  __TMC5160_H
#define  __TMC5160_H

void TMC5160_CS(uint8_t num,uint8_t state);
void SPI1_CS1_sendData(uint8_t addr,long datagram);
void SPI1_CS2_sendData(uint8_t addr,long datagram);
void SPI1_CS3_sendData(uint8_t addr,long datagram);
void SPI1_CS4_sendData(uint8_t addr,long datagram);
void SPI1_CS5_sendData(uint8_t addr,long datagram);
void TMC5160_CS1_Init(uint16_t speed);
void TMC5160_CS2_Init(uint16_t speed);
void TMC5160_CS3_Init(uint16_t speed);
void TMC5160_CS4_Init(uint16_t speed);
void TMC5160_CS5_Init(uint16_t speed);
void TMC5160_CS1_Move(long PosiTionData);
void TMC5160_CS2_Move(long PosiTionData);
void TMC5160_CS3_Move(long PosiTionData);
void TMC5160_CS4_Move(long PosiTionData);
void TMC5160_CS5_Move(long PosiTionData);
long SPI1_CS1_ReadData(char address);
long SPI1_CS2_ReadData(char address);
long SPI1_CS3_ReadData(char address);
long SPI1_CS4_ReadData(char address);
long SPI1_CS5_ReadData(char address);


#endif
