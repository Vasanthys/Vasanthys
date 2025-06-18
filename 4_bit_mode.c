
#include<lpc21xx.h>

#define LCD_D 0x0f<<20
#define RS 1<<17
#define RW 1<<18
#define E 1<<19
int i;
void LCD_INIT(void);
void LCD_COMMAND(unsigned char);
void LCD_DATA(unsigned char);
void LCD_String(unsigned char *);
void LCD_float(float);
void  LCD_INTEGER(int);
void LCD_String(unsigned char *S)
{
	while(*S)
	{
		  LCD_DATA(*S++);
	}
}
 
void LCD_float(float f){


	 int integerPart = (int)f; 

	 int decimalPart = (int)((f - integerPart) * 100);       

    LCD_INTEGER(integerPart);        

    LCD_DATA('.');                   

      

    LCD_INTEGER(decimalPart);       


}

void  LCD_INTEGER(int n){


	


	unsigned char a[5];


	signed char i=0;


	if(n==0){


		LCD_DATA('0');


	


	}


	else  {


		if(n<0){


			


		   LCD_DATA('-');


		   n=-n;


		}


		while(n>0){


			a[i++] = n%10;


			n=n/10;


		}


		for(--i;i>=0;i--)


		LCD_DATA(a[i]+48);


		   }




}
void LCD_INIT(void){
	IODIR1=LCD_D|RS|E|RW;
	IOCLR1=RW;
	LCD_COMMAND(0x01);
	LCD_COMMAND(0x02);
	LCD_COMMAND(0x0c);
	LCD_COMMAND(0x28); 
	LCD_COMMAND(0x80);
 }
 void LCD_COMMAND(unsigned char CMD){
	IOCLR1=LCD_D;
	IOSET1=((CMD&0xf0)<<16);
	IOCLR1=RS;
	IOSET1=E;
	Delay_milliseconds(2);
	IOCLR1=E;

	IOCLR1=LCD_D;
	IOSET1=((CMD&0x0f)<<20);
	IOCLR1=RS;
	IOSET1=E;
	Delay_milliseconds(2);
	IOCLR1=E;
	 }
void LCD_DATA(unsigned char d)
{
	IOCLR1=LCD_D;
	IOSET1=((d&0xf0)<<16);
	IOSET1=RS;
	IOSET1=E;
	Delay_milliseconds(2);
	IOCLR1=E;

	IOCLR1=LCD_D;
	IOSET1=((d&0x0f)<<20);
	IOSET1=RS;
	IOSET1=E;
	Delay_milliseconds(2);
	IOCLR1=E;
	
}


