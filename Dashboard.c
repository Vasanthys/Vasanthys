

#include <lpc21xx.h>
#include "header.h"
#include "Delay.c"
#include "4_bit_mode.c"

CAN2_MSG m1;
CAN2_MSG m2;
CAN2_MSG m3;
CAN2_MSG m4;
void can_isr(void) __irq {

	
	if (C2GSR & (1 << 0)) { 
        m4.id = C2RID;
        m4.dlc = (C2RFS >> 16) & 0xF;
        m4.rtr = (C2RFS >> 30) & 0x1;
        m4.byteA = C2RDA;
        //m4.byteB = C2RDB;

        if ((m4.rtr == 0) && (m4.id == 0x03)) {
            LCD_COMMAND(0xC0);
            LCD_String("FUEL:     "); 
            LCD_COMMAND(0xC5);
            LCD_INTEGER(m4.byteA);
			LCD_DATA('%');    
        }

        C2CMR = (1 << 2);   
    }

    VICVectAddr = 0;        
}
void can2_init(void) {
    PINSEL1 |= 0x00014000;  
    VPBDIV = 0x01;          
    C2MOD = 0x1;            
    C2BTR = 0x001C001D;     
    AFMR = 0x02;            
    C2IER |= (1 << 0);      
    C2MOD = 0x0;           
}

void can2_tx(CAN2_MSG m1)
{
  
  
  
  C2TID1=m1.id;
	C2TFI1=(m1.dlc<<16);	
	if(m1.rtr==0) 
	{
		C2TFI1&=~(1<<30);
		C2TDA1=m1.byteA;
		C2TDB1=m1.byteB;
	}
	else{
		C2TFI1|=(1<<30); 
	}
	C2CMR=(1<<0)|(1<<5);
	
	while((C2GSR&(1<<3))==0);
    

}

void CAN_RX_Interrupt(void) {
    VICIntSelect = 0;                    
    VICVectCntl1 = (1 << 5) | 27;         
    VICVectAddr1 = (unsigned int)can_isr;
    VICIntEnable |= (1 << 27);           
}



int main() {
	int wiper_flag=0,left_flag=0,right_flag=0;
    can2_init();
    LCD_INIT();
    CAN_RX_Interrupt();
	m1.id=0x00;
	m1.rtr=0;
	m1.dlc=1;
	m1.byteA=0x0;

	m2.id=0x01;
	m2.rtr=0;
	m2.dlc=1;
	m2.byteA=0x0;

	m3.id=0x02;
	m3.rtr=0;
	m3.dlc=1;
	m3.byteA=0x0;
	
	LCD_COMMAND(0x80);
	LCD_String("W:OFF  I:OFF");
	LCD_COMMAND(0xC0);
	LCD_String("FUEL:0%");

    while (1)
	{
		  if(((IOPIN0>>14)&1)==0)
		  {
		  	  wiper_flag = !wiper_flag;
		  	  can2_tx(m1);
			  if(wiper_flag)
			  {
			  	LCD_COMMAND(0x82);
				LCD_String("ON ");
			  }
			  else
			  {
			  	LCD_COMMAND(0x82);
				LCD_String("OFF");
			  }
			  while(((IOPIN0>>14)&1)==0);
		  }

		  if(((IOPIN0>>15)&1)==0)
		  {
		  	  left_flag = !left_flag;
			  if(left_flag)
			  {
			  	right_flag=0;
			  }
		  	  can2_tx(m2);
			  if(left_flag)
			  {
			  	LCD_COMMAND(0x89);
				LCD_String("LEFT ");
			  }
			  else
			  {
			  	LCD_COMMAND(0x89);
				LCD_String("OFF  ");
			  }
			  while(((IOPIN0>>15)&1)==0);
		  }

		  if(((IOPIN0>>16)&1)==0)
		  {
		  	  right_flag = !right_flag;
			  if(right_flag)
			  {
			  	left_flag=0;
			  }
		  	  can2_tx(m3);
			  if(right_flag)
			  {
			  	LCD_COMMAND(0x89);
				LCD_String("RIGHT");
			  }
			  else
			  {
			  	LCD_COMMAND(0x89);
				LCD_String("OFF  ");
			  }

			  while(((IOPIN0>>16)&1)==0);
		  }
	
	}  
}


	