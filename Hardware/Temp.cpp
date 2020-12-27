#include "Temp.h"
#include "LCD5110.h"

#define CALADC12_15V_30C  *((unsigned int *)0x1A1A)   // Temperature Sensor Calibration-30 C
                                                      //See device datasheet for TLV table memory mapping
#define CALADC12_15V_85C  *((unsigned int *)0x1A1C)   // Temperature Sensor Calibration-85 C

volatile float temperatureDegC;
void ADC_Temp_Int2Char(unsigned char *str, unsigned int length, float value);
void ADC_Temp_Init(void)
{
  REFCTL0 &= ~REFMSTR;                      // Reset REFMSTR to hand over control to
                                            // ADC12_A ref control registers
  ADC12CTL0 = ADC12SHT0_15 + ADC12REFON + ADC12ON;
                                            // Internal ref = 1.5V
  ADC12CTL1 = ADC12SHP + ADC12CONSEQ_2;     // enable sample timer
  ADC12MCTL0 = ADC12SREF_1 + ADC12INCH_10;  // ADC i/p ch A10 = temp sense i/p
  //ADC12IE = 0x001;                          // ADC_IFG upon conv result-ADCMEMO
  __delay_cycles(100);                       // delay to allow Ref to settle
  ADC12CTL0 |= ADC12ENC + ADC12MSC;
  ADC12CTL0 &= ~ADC12SC; 
  ADC12CTL0 |= ADC12SC;                   // Sampling and conversion start

}
void ADC_Temp_Get(unsigned int *temp)
{
  *temp = ADC12MEM0;
}
#define Length 5
unsigned char Temp_str[Length];
void ADC_Temp_Display()
{
  unsigned int temp;

  
  ADC_Temp_Get(&temp);
  temperatureDegC = (float)(((long)temp - CALADC12_15V_30C) * (85 - 30)) /
        (CALADC12_15V_85C - CALADC12_15V_30C) + 30.0f;
  ADC_Temp_Int2Char(Temp_str, Length, temperatureDegC);

}
void ADC_Temp_Int2Char(unsigned char *str, unsigned int length, float value)
{
  unsigned int i = 0, integer, decimal; 
  
  for (i=0; i<length-1; i++)
  {
    str[i]=' ';
  }
  str[i-1]='0';
  str[i-2]='.';
  str[i-3]='0';
  str[i] = 0;
  i=0;
  integer = value;
  decimal = (value-integer)*10;
  str[length-2] = decimal + '0';
  while(integer)
  {
    str[length-i-4]=(integer%10)+'0';
    integer /= 10;
    i++;
  }
}

