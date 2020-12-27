#ifndef _LCD5110_h_
#define _LCD5110_h_
extern unsigned char Local_Picture[84][6];
extern void LCD5110_init(void);
void LCD5110_write(unsigned char select, unsigned char date);
void LCD5110_clear(void);
void LCD5110_SETxy(unsigned char x, unsigned char y);
void LCD5110_char(unsigned char date);
void LCD5110_str(unsigned char x, unsigned char y, unsigned char *str);
void LCD5110_number(int date);
void LCD5110_float(float);
void LCD5110_DrawPoint(unsigned char x, unsigned char y);
void LCD5110_RefreshPic(void);
void LCD5110_DrawPointPic(unsigned char x, unsigned char y);
void LCD5110_ClearPic(void);
void LCD5110_DrawLine(int x0, int y0, int x1, int y1);
void LCD5110_DrawAllLine(unsigned char *data, unsigned char count);
void LCD51110_DrawBar(unsigned char high, unsigned char pos_x,unsigned char length);
void LCD5110_pic(unsigned char pic[84][6]);
void LCD5110_Str_Pic(unsigned char pic[84][6], unsigned char Position_X, unsigned char Position_Y, unsigned char* str );
#endif

