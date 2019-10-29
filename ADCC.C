#include<lpc214x.h>
#include<stdio.h>
#include<lcdarm.h>

char abc[8];
unsigned long adc_data;

void delay(unsigned int d)
{
 unsigned int i;
 for(;d>0;d--)
 {
  for(i=0;i<7000;i++);
 }
}
void ADC0_Init(void)
{
	/*************Initialize ADC AD0.0*************/
	AD0CR = 1<<21;								//A/D is Operational
	AD0CR = 0<<21;								//A/D is in Power Down Mode
	PINSEL0 = 0x00000000;
	PINSEL1 = 0x00000000;					//P0.27 is Configured as Analog to Digital Converter Pin AD0.0
	
	AD0CR = 0x00200401;						//CLKDIV=4,Channel-0.0 Selected,A/D is Operational
	/*
	A/D Clock = PCLK /(CLKDIV+1);
	*/
	/**********************************************/
}

unsigned int ADC0_Read(void)
{
	unsigned long adc_data;
	
	AD0CR |= 1UL<<24;							//Start Conversion
	do
	{
		adc_data = AD0GDR;
	}while(!(adc_data & 0x80000000));        //Wait untill the DONE bits Sets
	AD0CR &= ~0x01000000;					//Stops the A/D Conversion   
	
	adc_data = adc_data >> 6;
	adc_data = adc_data & 0x000003FF;    //Clearing all other Bits

return (adc_data);
}
/*********************************************/


int main()
{
 int i;
   IO1DIR=0XFFFEFFFF;
 PINSEL2=0x00000000;
 
 LCD_Init();
 ADC0_Init();
 
 while(1)
 {	  LCD_Command1(0x01);
 LCD_String("hello world");
  LCD_Command1(0xc0);
  	adc_data = ADC0_Read();
	adc_data = adc_data*3300;
	adc_data = adc_data/1023;			//Value of Voltage in Milli Volts
	i=adc_data;
	
   
  sprintf(abc,"%d",i);
  LCD_String(abc);
  LCD_String("mV");
  delay(50);
  //LCD_Command1(0xC0);
  
  //
 // delay(10);
 }
}






