/*
 * Copyright (c) 2015, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== empty.c ========
 */
/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/runtime/System.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Mailbox.h>
#include <ti/sysbios/knl/Clock.h>
/* TI-RTOS Header files */
#include <ti/drivers/GPIO.h>
// #include <ti/drivers/I2C.h>
// #include <ti/drivers/SDSPI.h>
// #include <ti/drivers/SPI.h>
// #include <ti/drivers/UART.h>
// #include <ti/drivers/Watchdog.h>
// #include <ti/drivers/WiFi.h>

/* Board Header file */
#include "Board.h"
/* Hardware Header file */
#include "LCD5110.h"
#include "Key.h"
#include "Tetris.h"
#include "stdlib.h"
#include "Temp.h"

#define TASKSTACKSIZE     128
#define LCD_TASKSTACKSIZE 256

extern unsigned char Temp_str[];
extern unsigned char Score_str[];
Task_Struct task0Struct;
Task_Struct task1Struct;
Task_Struct task2Struct;

Char task0Stack[TASKSTACKSIZE];
Char task1Stack[TASKSTACKSIZE];
Char task2Stack[LCD_TASKSTACKSIZE];
/*
 *  ======== heartBeatFxn ========
 *  Toggle the Board_LED0. The Task_sleep is determined by arg0 which
 *  is configured for the heartBeat Task instance.
 */
Void heartBeatFxn(UArg arg0, UArg arg1)
{
    unsigned i=0;
    while (1) {
        Task_sleep((unsigned int)arg0);
        GPIO_toggle(Board_LED0);
        if (i==2)
        {
          ADC_Temp_Display();
          i=0;
        }
        else
        {
          i++;
        }
    }
}
char direction_change;
Void Key_Scan(UArg arg0, UArg arg1)
{
  Key_Class Key;
  unsigned char Key_flag;
  
  while (1) {
      Task_sleep((unsigned int)arg0);
      GPIO_toggle(Board_LED1);
      Key_flag = Key.Key_Scan2();
      if (Key_flag)
      {      
        direction_change = Key_flag;
      }
  }
}

Void LCD_Update(UArg arg0, UArg arg1)
{
  Tetris_Class Tetris(Local_Picture);
  unsigned char signal = 0, Key_count =0, Status_Key, Block_Count;
  signed char Status_Block;
  
  LCD5110_str(0,3, (unsigned char *)"Welcome to Tetris Game");
  Tetris.Block_Data.Block_Data_Set_Type(0, 0);
  Tetris.Tetris_Update();
  for (unsigned char i=0; i<84; i++)
  {
    Local_Picture[i][4] = 0x02;
  }
  LCD5110_Str_Pic(Local_Picture, 0, 5, (unsigned char*)"T:");
  LCD5110_Str_Pic(Local_Picture, 42, 5, (unsigned char*)"S:");
  while(1)
  {
    if (direction_change == Key_Up)//up
    {
      signal=(signal+1)%28;
      Tetris.Tetris_Eradication(Tetris.Block_Data.Block_Data_x(),Tetris.Block_Data.Block_Data_y(), Tetris.Block_Data.type, Tetris.Block_Data.direction+1);
      Tetris.Tetris_Update();
      direction_change=0;
      Status_Key = 1;
      Key_count =0;
    }    
    else if (direction_change == Key_Down)//down 
    {
      int state;
      while(1)
      {  
        state = Tetris.Tetris_Eradication(Tetris.Block_Data.Block_Data_x()+2,Tetris.Block_Data.Block_Data_y(), Tetris.Block_Data.type, Tetris.Block_Data.direction);
        Tetris.Tetris_Update();
        if (state != Success)
        {
          break;
        }
      }
      direction_change=0;
      Status_Key =1;
      Key_count =0;
    }
    else if (direction_change == Key_Left)//left 
    {
      Tetris.Tetris_Eradication(Tetris.Block_Data.Block_Data_x(),Tetris.Block_Data.Block_Data_y()+2, Tetris.Block_Data.type, Tetris.Block_Data.direction);
      Tetris.Tetris_Update();
      direction_change=0;
      Status_Key=1;
      Key_count =0;
    }
    else if (direction_change == Key_Right)//right 
    {
      Tetris.Tetris_Eradication(Tetris.Block_Data.Block_Data_x(),Tetris.Block_Data.Block_Data_y()-2, Tetris.Block_Data.type, Tetris.Block_Data.direction);
      Tetris.Tetris_Update();
      direction_change=0;
      Status_Key=1;
      Key_count =0;
    }
    else
    {
      if (Status_Key)
      {
        Key_count++;
        if (Key_count == 5)
        {
          Key_count =0;
          Status_Key = 0;
        }
      }
      else
      {
        Status_Block = Tetris.Tetris_Eradication(Tetris.Block_Data.Block_Data_x()+2,Tetris.Block_Data.Block_Data_y(), Tetris.Block_Data.type, Tetris.Block_Data.direction);
        Tetris.Tetris_Update();
        if (Status_Block == Bottom || Status_Block == Blocking)
        {
          Block_Count++;
          if (Block_Count == 10)
          {            
            Block_Count =0;
            if (Tetris.Tetris_Block_Bottom_Check(Tetris.Block_Data.Block_Data_x()+2,Tetris.Block_Data.Block_Data_y(), Tetris.Block_Data.type, Tetris.Block_Data.direction) != Success)
            {
              Tetris.Tetris_Check_Full();
              Tetris.Block_Data.Block_Data_change_position_xy(0,0);
              Tetris.Block_Data.Block_Data_Set_Type(rand(), rand());
              if (Tetris.Tetris_Block_Bottom_Check(0,0, Tetris.Block_Data.type, Tetris.Block_Data.direction) == Success)
              {
                Tetris.Tetris_Update();
              }
              else
              {
                for (unsigned char i=0; i<84; i++)
                {
                  for (unsigned char j=0; j<6; j++)
                  {
                    Local_Picture[i][j] = 0;
                  }
                }
                LCD5110_Str_Pic(Local_Picture, 10, 2, (unsigned char *)"Game Over");
                LCD5110_Str_Pic(Local_Picture, 0, 3, (unsigned char *)"Your Score:");
                LCD5110_Str_Pic(Local_Picture, 0, 4, Score_str);
                LCD5110_pic(Local_Picture);
                while(1)
                {
                  Task_sleep((unsigned int)100);
                }
              }
            }
          }
        }
      }
    }
    
    LCD5110_Str_Pic(Local_Picture, 10, 5, Temp_str);
    LCD5110_Str_Pic(Local_Picture, 52,5, Score_str);
    LCD5110_pic(Local_Picture);
    Task_sleep((unsigned int)100);
  }
}

/*
 *  ======== main ========
 */
int main(void)
{
    Task_Params taskParams, Key_TaskParams, LCD_TaskParams;

    /* Call board init functions */
        
    Board_initGeneral();
    Board_initGPIO();
 
    LCD5110_init(); 
    ADC_Temp_Init();
    /* Construct heartBeat Task  thread */
    Task_Params_init(&taskParams);
    taskParams.arg0 = 500;
    taskParams.stackSize = TASKSTACKSIZE;
    taskParams.stack = &task0Stack;
    Task_construct(&task0Struct, (Task_FuncPtr)heartBeatFxn, &taskParams, NULL);
    
    Task_Params_init(&Key_TaskParams);
    Key_TaskParams.arg0 = 130;
    Key_TaskParams.stackSize = TASKSTACKSIZE;
    Key_TaskParams.stack = &task1Stack;
    Task_construct(&task1Struct, (Task_FuncPtr)Key_Scan, &Key_TaskParams, NULL);

    Task_Params_init(&LCD_TaskParams);
    LCD_TaskParams.arg0 = 30;
    LCD_TaskParams.stackSize = LCD_TASKSTACKSIZE;
    LCD_TaskParams.stack = &task2Stack;
    Task_construct(&task2Struct, (Task_FuncPtr)LCD_Update, &LCD_TaskParams, NULL);  
    
    System_printf("Starting the example\nSystem provider is set to SysMin. "
                  "Halt the target to view any SysMin contents in ROV.\n");
    /* SysMin will only print to the console when you call flush or exit */
    System_flush();

    /* Start BIOS */
    BIOS_start();

    return (0);
}
