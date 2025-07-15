#ifndef  	__MOTOR_H
#define		__MOTOR_H



uint16_t CRC16_MudBus(uint8_t *Data, uint8_t usDataLen);
void Send_To_Servo(uint8_t *arr,uint8_t lenth);
void Servo_Init(void);
uint64_t get_servo_encoder(void);
void servo_en(uint8_t state);
void servo_dir(uint8_t state);
void motor_en(uint8_t num,uint8_t state);
void out(uint8_t addr,uint8_t state);
uint8_t in(uint8_t addr);
#endif
