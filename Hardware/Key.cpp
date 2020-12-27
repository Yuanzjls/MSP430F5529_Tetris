#include "Key.h"

#define Key1_Mask (BIT2 + BIT3 + BIT4)
#define Key2_Mask (BIT3)
Key_Class::Key_Class()
{
  P1REN |= BIT2 + BIT3 + BIT4;
  P1OUT |= BIT2 + BIT3 + BIT4;
  P4REN |= BIT3;
  P4OUT |= BIT3;
}
unsigned char Key_Class::Key_Scan1(void)
{
  unsigned char flag=0;
  flag = (P1IN & Key1_Mask) >> 1;
  flag |= (P4IN & Key2_Mask) >> 3;
  flag ^= 0x0f;
  return flag;
} 
unsigned char Key_Class::Key_Scan2(void)
  {
    unsigned char flag;
    for (int i=0; i<3; i++)
    {
      flag = P1IN&(BIT0<<(i+2));
      if (flag==0)
      {
        return BIT0<<(i+1);
      }
    }
    flag = P4IN&BIT3;
    if (flag == 0)
    {
      return BIT0;
    }
    else
    {
      return 0;
    }
}

