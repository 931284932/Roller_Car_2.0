#ifndef  __MYTASK_H
#define  __MYTASK_H


struct motor_debug_pra{
	uint32_t motor1[3];
	uint32_t motor2[3];
	uint32_t motor3[4];
	uint32_t motor4[5];
	uint32_t motor5[4];
	uint32_t motor6[3];
	uint32_t t[2];
};
struct u8{
	uint8_t motor1;
	uint8_t motor2;
	uint8_t motor3;
	uint8_t motor4;
	uint8_t motor5;
	uint8_t motor6;
};

void start_task(void);
#endif
