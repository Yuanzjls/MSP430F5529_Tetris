#ifndef _Tetris_h_
#define _Tetris_h_

#define Success 0
#define Bottom   -1
#define Blocking -2
#define False    -3
extern const unsigned char block[28][8];

class Block_Data_Class
{
public:
  Block_Data_Class();
  signed char Block_Data_x(void);
  signed char Block_Data_y(void);
  void Block_Data_change_position_xy(signed char , signed char );
  void Block_Data_Set_Type(unsigned char , unsigned char);
  unsigned char type;
  unsigned char direction;  
private:
  signed char x;
  signed char y;
};
class Tetris_Class
{
public:
  Tetris_Class(unsigned char p[84][6]);
  char Tetris_Eradication(signed char , signed char , unsigned char , unsigned char );
  void Tetris_Update();
  Block_Data_Class Block_Data;
  signed char Tetris_Block_Bottom_Check(signed char, signed char, unsigned char, unsigned char);
  void Tetris_Check_Full(void);
private:  
  unsigned char (*p_Pic)[6];  
  signed char Tetris_Margin_Check(signed char, signed char, unsigned char, unsigned char);
};
#endif
