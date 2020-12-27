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

#ifndef __BOARD_H
#define __BOARD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "MSP_EXP430F5529LP.h"

#define Board_initGeneral           MSP_EXP430F5529LP_initGeneral
#define Board_initGPIO              MSP_EXP430F5529LP_initGPIO
#define Board_initI2C               MSP_EXP430F5529LP_initI2C
#define Board_initSDSPI             MSP_EXP430F5529LP_initSDSPI
#define Board_initSPI               MSP_EXP430F5529LP_initSPI
#define Board_initUART              MSP_EXP430F5529LP_initUART
#define Board_initUSB               MSP_EXP430F5529LP_initUSB
#define Board_initWatchdog          MSP_EXP430F5529LP_initWatchdog
#define Board_initWiFi              MSP_EXP430F5529LP_initWiFi

#define Board_LED_ON                MSP_EXP430F5529LP_LED_ON
#define Board_LED_OFF               MSP_EXP430F5529LP_LED_OFF
#define Board_LED0                  MSP_EXP430F5529LP_LED1
#define Board_LED1                  MSP_EXP430F5529LP_LED2
#define Board_LED2                  MSP_EXP430F5529LP_LED2
#define Board_BUTTON0               MSP_EXP430F5529LP_S1
#define Board_BUTTON1               MSP_EXP430F5529LP_S2

#define Board_I2C0                  MSP_EXP430F5529LP_I2CB0
#define Board_I2C_TMP               MSP_EXP430F5529LP_I2CB0
#define Board_I2C_NFC               MSP_EXP430F5529LP_I2CB0
#define Board_I2C_TPL0401           MSP_EXP430F5529LP_I2CB0

#define Board_SDSPI0                MSP_EXP430F5529LP_SDSPIB0

#define Board_SPI0                  MSP_EXP430F5529LP_SPIB0

#define Board_USBDEVICE             0

#define Board_UART0                 MSP_EXP430F5529LP_UARTA1

#define Board_WATCHDOG0             MSP_EXP430F5529LP_WATCHDOG

#define Board_WIFI                  MSP_EXP430F5529LP_WIFI
#define Board_WIFI_SPI              MSP_EXP430F5529LP_SPIB0

#define CPY_BUFF_SIZE               256

/* Board specific I2C addresses */
#define Board_TMP006_ADDR           (0x40)
#define Board_RF430CL330_ADDR       (0x28)
#define Board_TPL0401_ADDR          (0x40)

#ifdef __cplusplus
}
#endif

#endif /* __BOARD_H */
