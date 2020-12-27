#include "LCD5110.h"
#include "delay.h"
#include "TAB.h"
#include "stdio.h"
#include "math.h"
#define RST0    P3OUT &= ~BIT7 
#define RST1    P3OUT |= BIT7  
#define CS0     P2OUT &= ~BIT5
#define CS1     P2OUT |= BIT5
#define DC0     P2OUT &= ~BIT4
#define DC1     P2OUT |= BIT4
#define DIN0    P8OUT &= ~BIT1
#define DIN1    P8OUT |= BIT1
#define CLK0    P8OUT &= ~BIT2
#define CLK1    P8OUT |= BIT2
unsigned char Local_Picture[84][6];
void LCD5110_init(void)
{
  P2DIR |= BIT5 + BIT4;
  P8DIR |= BIT1 + BIT2;
  P3DIR |= BIT7;
  RST0;
  delay_ms(100);
  RST1;
  
  LCD5110_write(0, 0x21);
  LCD5110_write(0, 0xd0);
  LCD5110_write(0, 0x20);
  LCD5110_write(0, 0x0c);
  LCD5110_clear();
  LCD5110_SETxy(0, 0);
}
void LCD5110_write(unsigned char select, unsigned char date)
{
  unsigned char i;
  CS0;
  if (select)
  {
    DC1;
  }
  else
  {
    DC0;
  }
  for (i=0; i<8; i++)
  {
    if (date & 0x80)
    {
      DIN1;
    }
    else
    {
      DIN0;
    }
    date = date << 1;
    CLK0;
    CLK1;
  }
  CS1;
}
void LCD5110_clear(void)
{
  unsigned char i, j;
  
  for (i=0; i<48; i++)
  {
    for (j=0; j<84; j++)
    { 
      LCD5110_write(1, 0);
    }
  }    
}
void LCD5110_SETxy(unsigned char x, unsigned char y)
{
  LCD5110_write(0, 0x40 | y);
  LCD5110_write(0, 0x80 | x);
}
void LCD5110_char(unsigned char date)
{
  unsigned char i;
  date = date - 32;
  
  for(i=0; i<6; i++)
  {
    LCD5110_write(1, font6x8[date][i]);
  }
}
void LCD5110_str(unsigned char x, unsigned char y, unsigned char *str)
{
  LCD5110_SETxy(x, y);
  
  while (*str)
  {
    LCD5110_char(*str);
    str++;
  }
}
void LCD5110_number(int date)
{
  unsigned char table[8], i=0;;
  sprintf((char *)table, "%d", date);
  while (table[i])
  {
    LCD5110_char(table[i]);
    i++;
  }
}
void LCD5110_float(float date)
{
  unsigned char i = 0, table[12];
  sprintf((char*)(table), "%.2f", date);
  while (table[i])
  {
    LCD5110_char(table[i]);
    i++;
  }  
}
void LCD5110_DrawPoint(unsigned char x, unsigned char y)
{
  unsigned char pos_x, pos_y, pos_bit;
  
  pos_x = x;
  pos_y = y / 8;
  pos_bit = y % 8;
  
  LCD5110_SETxy(pos_x, pos_y);
  LCD5110_write(1, BIT0 << pos_bit);  
}

void LCD5110_pic(unsigned char pic[84][6])
{
  unsigned char i, j;
  LCD5110_SETxy(0, 0);
  for (i=0; i<6; i++)
  {
    for (j=0; j<84; j++)
    LCD5110_write(1, pic[j][i]);
  }
}
void LCD5110_Str_Pic(unsigned char pic[84][6], unsigned char Position_X, unsigned char Position_Y, unsigned char* str)
{
  unsigned char *str_position = str;
  while(*str)
  {
    for (int i=0, offset=str-str_position; i<6; i++)
    {
      pic[Position_X+i+offset*6][Position_Y] = font6x8[*str-32][i];
    }
    str++;
  }
}
