#ifndef _Snack_h_
#define _Snack_h_
#include "msp430.h"
#include "score.h"

#define Success         (0)
#define Game_Over       (255)

struct Snake_DataStruct
{
  unsigned char x;
  unsigned char y;
  unsigned char direction;
};
class Snake_Class
{
public:
  Snake_Class(void);
  unsigned char Snake_Update(void);
  void Snake_FoodUpdate(void);
  unsigned char Snake_ChangeDirection(unsigned char &Dir);
  void Snake_Transform(void);
  unsigned char Snake_Data[84][6];
  unsigned char Direction_ChangeSignal;
  void SetSrand(unsigned int set);
private:
  struct Snake_DataStruct Snake_front, Snake_back;
  void Direction_Update(struct Snake_DataStruct & Snake_Data_Point);
  unsigned char direction[84][40];
  unsigned char Snake_FoodCheck(Snake_DataStruct Check_Data);
  void Snake_GetFood(void);
  class Score_Class Score;
  void Snake_NoFood(void);
};

#endif