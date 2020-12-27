#ifndef _score_h_
#define _score_h_

//******************
//
// CLASS: Score_Class
//
// DESCRIPTION:
//  This is used to deal with the score you get
//
class Score_Class
{
public:
  Score_Class();
  void Score_Add(unsigned int Add);
  void Score_Set(unsigned int Set);
  unsigned int Score_Get(void);
  void Score_int2Char(unsigned char *str, unsigned int);
private:
  unsigned int Score_Value;
  
};



#endif