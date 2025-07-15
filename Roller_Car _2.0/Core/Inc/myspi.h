#ifndef __MYSPI_H
#define __MYSPI_H

void SPI_Init(void);
void SPI_Start(void);
void SPI_Stop(void);
unsigned char SPI_SwapByte(unsigned char ByteSend);

#endif
