#include "Tetris.h"
#include "score.h"
extern unsigned char Local_Picture[84][6];
Score_Class Score;
unsigned char Score_str[5];
const unsigned char block[28][8]=
{
  3,3,3,3,3,3,3,3,
  255,255,0,0,0,0,0,0,
  3,3,3,3,3,3,3,3,
  255,255,0,0,0,0,0,0,
  63,63,48,48,0,0,0,0,
  12,12,12,12,15,15,0,0,
  3,3,63,63,0,0,0,0,
  15,15,3,3,3,3,0,0,
  48,48,63,63,0,0,0,0,
  3,3,3,3,15,15,0,0,
  63,63,3,3,0,0,0,0,
  15,15,12,12,12,12,0,0,
  15,15,60,60,0,0,0,0,
  12,12,15,15,3,3,0,0,
  15,15,60,60,0,0,0,0,
  12,12,15,15,3,3,0,0,
  60,60,15,15,0,0,0,0,
  3,3,15,15,12,12,0,0,
  60,60,15,15,0,0,0,0,
  3,3,15,15,12,12,0,0,
  12,12,15,15,12,12,0,0,
  63,63,12,12,0,0,0,0,
  3,3,15,15,3,3,0,0,
  12,12,63,63,0,0,0,0,
  15,15,15,15,0,0,0,0,
  15,15,15,15,0,0,0,0,
  15,15,15,15,0,0,0,0,
  15,15,15,15,0,0,0,0,
};
Block_Data_Class::Block_Data_Class(void)
{
  x=0;
  y=0;
  type=0;
  direction=0;
}

void Block_Data_Class::Block_Data_Set_Type(unsigned char set_type, unsigned char set_direction)
{
  type = set_type % 7;
  direction = set_direction%4;
}

Tetris_Class::Tetris_Class(unsigned char p[84][6])
{
  p_Pic = p;
}
signed char Block_Data_Class::Block_Data_x(void)
{
  return x;
}

signed char Block_Data_Class::Block_Data_y(void)
{
  return y;
}

void Block_Data_Class::Block_Data_change_position_xy(signed char set_x, signed char set_y)
{
  Block_Data_Class::x = set_x;
  Block_Data_Class::y = set_y;
}


char Tetris_Class::Tetris_Eradication(signed char set_x, signed char set_y, unsigned char set_type, unsigned char set_direction)
{
  unsigned char j, Block_Type= Block_Data.type * 4 + Block_Data.direction, position_x, position_y, remainder, flag;
  
  position_x = Block_Data.Block_Data_x();
  position_y = Block_Data.Block_Data_y();
  
  remainder = position_y % 8;
  position_y /= 8;
   
  for (j=0; j<8; j++)
  {
    p_Pic[position_x+j][position_y] &=  ~(block[Block_Type][j] << remainder);
    p_Pic[position_x+j][position_y+1] &= ~(block[Block_Type][j] >> (8-remainder));
  }
  flag = Tetris_Margin_Check(set_x, set_y, set_type, set_direction);
  if (flag == Success)
  {
    flag = Tetris_Class::Tetris_Block_Bottom_Check(set_x, set_y, set_type, set_direction);
    if (flag == Success && Tetris_Margin_Check(set_x, set_y, set_type, set_direction) == Success)
    {
      Block_Data.Block_Data_change_position_xy(set_x, set_y);
      Block_Data.Block_Data_Set_Type(set_type, set_direction);
    }
  }
  return flag;
}

void Tetris_Class::Tetris_Update()// new blcok
{
  unsigned char position_x = Block_Data.Block_Data_x(), position_y = Block_Data.Block_Data_y();
  unsigned char j, remainder, Block_Type= Block_Data.type * 4 + Block_Data.direction;
  
  remainder = position_y % 8;
  position_y /= 8;
  for (j=0; j<8; j++)
  {
      p_Pic[position_x+j][position_y] |=  (block[Block_Type][j] << remainder);
      p_Pic[position_x+j][position_y+1] |= (block[Block_Type][j] >> (8-remainder));
  }
}
signed char Tetris_Class::Tetris_Margin_Check(signed char Check_x, signed char Check_y, unsigned char Check_type, unsigned char Check_direction)
{
  unsigned char Block_Type = Check_type*4 + Check_direction, i, remainder;
  signed char Status=Success;
  
  if (Check_x <0 || Check_y <0 || Check_x > 83 || Check_y > 47-16)
  {
    Status = False;
  }
  if (Check_y > 40-16) // check y 通过更改40可限定区域
  {
    remainder = Check_y % 8;
    for (i=0; i<8; i++)
    {
      if (block[Block_Type][i] >> (8-remainder))
      {
        Status = False;
        break;
      }
    }
  }
  if (Check_x > 76)                     //check x， 更改数字76可限定区域
  {
    remainder = 84 - Check_x;
    if (block[Block_Type][remainder] !=0)
    {
      Status = Bottom;
    }    
  } 
  return Status;
}
signed char Tetris_Class::Tetris_Block_Bottom_Check(signed char Check_x, signed char Check_y, unsigned char Check_type, unsigned char Check_direction)
{
  unsigned char Block_Type = Check_type*4 + Check_direction, remainder, i, position_x, position_y;
  signed char Status=Success;
  
  if (Check_x > 76)                     //check x， 更改数字76可限定区域
  {
    remainder = 84 - Check_x;
    if (block[Block_Type][remainder] !=0)
    {
      Status = Bottom;
    }    
  } 
  position_x = Check_x;
  position_y = Check_y / 8;
  remainder = Check_y % 8;

  for (i=0; i<8; i++)
  {
      if (p_Pic[position_x+i][position_y] & (block[Block_Type][i] << remainder))
      {
        Status = Blocking;
        break;
      }
      if (p_Pic[position_x+i][position_y+1] & (block[Block_Type][i] >> (8-remainder)))
      {
        Status = Blocking;
        break;
      }
  }
  return Status;
}
void Tetris_Class::Tetris_Check_Full(void)
{
  unsigned char i, j, k;
  signed char flag;
  
  for (i=0; i<84;)
  {
    flag = 1;
    for (j=0; j<4; j++)
    {
      if (p_Pic[83-i][j] != 0xff)
      {
        flag = 0;
        break;
      }
    } 
    if (flag == 1)
    {
      for (k=i; k<83; k++)
      {
        for (j=0; j<4; j++)
        {
          p_Pic[83-k][j] = p_Pic[83-k-1][j];
        }
      }
      Score.Score_Add(5);
      continue;
    }   
    i++;
  }
  Score.Score_int2Char(Score_str, 5);
}