
#ifndef __HEADER_H_
#define __HEADER_H_

#define PORT0 0
#define PORT1 1
#define SET   1
#define CLEAR 0
typedef unsigned int u32;
typedef 	signed int s32;
typedef unsigned char u8;
typedef 	signed char s8;
typedef unsigned short int u16;
typedef   signed short int s16;

typedef struct CAN2
{
	u32 id;
	u32 rtr;
	u32 dlc;
	u32 byteA;
	u32 byteB;
}CAN2_MSG;



void delay_sec(u32 sec);

void delay_ms(unsigned int ms);



void can2_init(void);
void can2_tx(CAN2_MSG m1);
void can2_rx(CAN2_MSG *m1);



#endif


