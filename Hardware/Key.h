#ifndef _Key_h_
#define _Key_h_
#include "msp430.h"

#define Key_Down  BIT3 //x+2, y
#define Key_Up    BIT0 //x-2, y
#define Key_Left  BIT1 //x, y+2
#define Key_Right BIT2 //x, y-2

class Key_Class
{
public:
  Key_Class();
  unsigned char Key_Scan1(void);
  unsigned char Key_Scan2(void);
 
private :
  
};


#endif