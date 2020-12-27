#include "score.h"
#include "stdio.h"
#include "TAB.h"
Score_Class::Score_Class(void)
{
  Score_Set(0);
}
void Score_Class::Score_Add(unsigned int Add)
{
  Score_Value += Add;
}
void Score_Class::Score_Set(unsigned int Set)
{
  Score_Value = Set;
}
void Score_Class::Score_int2Char(unsigned char *str, unsigned int length)
{
  unsigned int i, Value=Score_Value;
  
  for (i=0; i<length-1; i++)
  {
    str[i]=' ';
  }
  str[i-1]='0';
  str[i] = 0;
  i=0;
  while(Value)
  {
    str[length-2-i] = (Value%10)+'0';
    Value/=10;
    i++;
  }
}
unsigned int Score_Class::Score_Get(void)
{
  return Score_Value;
}
