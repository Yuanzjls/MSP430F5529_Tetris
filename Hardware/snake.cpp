#include "snake.h"
#include "lcd5110.h"
#include "stdlib.h"
#include "TAB.h"

#define Direction_Left  (BIT0)
#define Direction_Up    (BIT1)
#define Direction_Down  (BIT2)
#define Direction_Right (BIT3)
#define Direction_Food  (BIT4)
#define Direction_None  (0)

#define Border_X          (84)
#define Border_Y          (40)

#define food_count        (40)

extern unsigned char Temp_str[];

void Snake_Class::Direction_Update(struct Snake_DataStruct & Snake_Data_Point)
{
  if (Snake_Data_Point.direction == Direction_Left)
  {
    if (Snake_Data_Point.x > 0)  Snake_Data_Point.x -= 1;    
    else Snake_Data_Point.x = Border_X-1;
  }
  else if (Snake_Data_Point.direction == Direction_Up)
  {
    if (Snake_Data_Point.y >0)Snake_Data_Point.y -= 1; 
    else Snake_Data_Point.y = Border_Y-1;
  }
  else if (Snake_Data_Point.direction == Direction_Down)
  {
    Snake_Data_Point.y=(Snake_Data_Point.y+1)%Border_Y;
  }
  else if (Snake_Data_Point.direction == Direction_Right)
  {
    Snake_Data_Point.x=(Snake_Data_Point.x+1)%Border_X;
  }
}

Snake_Class::Snake_Class(void)
{
  Snake_back.x = 4;
  Snake_back.y = 6;
  Snake_back.direction = Direction_Right;
  
  Snake_front.x = 7;
  Snake_front.y = 6;
  Snake_front.direction = Direction_Right;
    
  for (int i=Snake_back.x ; i<=Snake_front.x;i++)
  {
    direction[i][6] = Direction_Right;
  }
  Direction_ChangeSignal = 0; 
  for (int i=0; i<food_count; i++)
  {
    Snake_FoodUpdate();
  }
  LCD5110_Str_Pic(Snake_Data, 0, 0, (unsigned char*)"Score:");
}

unsigned char Snake_Class::Snake_FoodCheck(Snake_DataStruct Check_Data)
{

  Direction_Update(Check_Data);
  return direction[Check_Data.x][Check_Data.y];
}

void Snake_Class::Snake_NoFood(void)
{
  direction[Snake_back.x][Snake_back.y] = Direction_None;
  Direction_Update(Snake_back);
  Snake_back.direction = direction[Snake_back.x][Snake_back.y];
  direction[Snake_front.x][Snake_front.y] = Snake_front.direction;
  Direction_Update(Snake_front);
  direction[Snake_front.x][Snake_front.y] = Snake_front.direction;
}

void Snake_Class::Snake_GetFood(void)
{
  direction[Snake_front.x][Snake_front.y] = Snake_front.direction;
  Direction_Update(Snake_front);
  direction[Snake_front.x][Snake_front.y] = Snake_front.direction;  
}

unsigned char Snake_Class::Snake_Update(void)
{
  unsigned char Check_flag = Snake_FoodCheck(Snake_front);
  if (Check_flag == Direction_None)
  {
    Snake_NoFood();
    Check_flag = Success;
  }
  else if (Check_flag == Direction_Food)
  {
    Snake_GetFood();
    Snake_FoodUpdate();
    Score.Score_Add(5);
    Check_flag = Success;
  }
  else
  {
    Check_flag = Game_Over;
  }
  return Check_flag;
}
#define Str_length 4u
void Snake_Class::Snake_Transform(void)
{
  int i,j;
  unsigned char str[Str_length];

  for (i=0; i<Border_X; i++)
  {
    for (j=0; j<Border_Y; j++)
    {
      if (j%8==0)
      {
        Snake_Data[i][j/8+1] = 0;
      }
      if (direction[i][j])
      {
        Snake_Data[i][j/8+1] |= BIT0 << (j % 8);
      }
    }
  }
  Score.Score_int2Char(str, Str_length);
  LCD5110_Str_Pic(Snake_Data, 34, 0, str);
  LCD5110_Str_Pic(Snake_Data, 60, 0, Temp_str);
  LCD5110_pic(Snake_Data);

}

unsigned char Snake_Class::Snake_ChangeDirection(unsigned char &Dir)
{
  unsigned char flag = 255;
  if(Dir==Snake_front.direction)
  {
    return flag;
  }
  if (Snake_front.direction==Direction_Left)
  {
    if (Dir != Direction_Right)
    {
      Snake_front.direction = Dir;
      flag = 0;
    }
  }
  else if (Snake_front.direction==Direction_Right)
  {
    if (Dir != Direction_Left)
    {
      Snake_front.direction = Dir;
      flag = 0;
    }    
  }
  else if (Snake_front.direction==Direction_Up)
  {
    if (Dir != Direction_Down)
    {
      Snake_front.direction = Dir;
      flag = 0;
    }    
  }    
  else if (Snake_front.direction==Direction_Down)
  {
    if (Dir != Direction_Up)
    {
      Snake_front.direction = Dir;
      flag = 0;
    }    
  }
  Dir = Direction_None;
  return flag;
}

void Snake_Class::SetSrand(unsigned int set)
{
  srand(set);
}
void Snake_Class::Snake_FoodUpdate(void)
{
  unsigned char Posstion_x, Posstion_y;
  do
  {
    Posstion_x = rand()%Border_X;
    Posstion_y = rand()%Border_Y;
  }while(direction[Posstion_x][Posstion_y]);
  direction[Posstion_x][Posstion_y] = Direction_Food; 
}