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
/** ============================================================================
 *  @file       MSP_EXP430F5529LP.h
 *
 *  @brief      MSP_EXP430F5529LP Board Specific APIs
 *
 *  The MSP_EXP430F5529LP header file should be included in an application as
 *  follows:
 *  @code
 *  #include <MSP_EXP430F5529LP.h>
 *  @endcode
 *
 *  ============================================================================
 */
#ifndef __MSP_EXP430F5529LP_H
#define __MSP_EXP430F5529LP_H

#ifdef __cplusplus
extern "C" {
#endif

/* LEDs on MSP_EXP430F5529LP are active high. */
#define MSP_EXP430F5529LP_LED_OFF (0)
#define MSP_EXP430F5529LP_LED_ON  (1)

/*!
 *  @def    MSP_EXP430F5529LP_GPIOName
 *  @brief  Enum of GPIO names on the MSP_EXP430F5529LP dev board
 */
typedef enum MSP_EXP430F5529LP_GPIOName {
    MSP_EXP430F5529LP_S1 = 0,
    MSP_EXP430F5529LP_S2,
    MSP_EXP430F5529LP_LED1,
    MSP_EXP430F5529LP_LED2,

    MSP_EXP430F5529LP_GPIOCOUNT
} MSP_EXP430F5529LP_GPIOName;

/*!
 *  @def    MSP_EXP430F5529LP_I2CName
 *  @brief  Enum of I2C names on the MSP_EXP430F5529LP dev board
 */
typedef enum MSP_EXP430F5529LP_I2CName {
    MSP_EXP430F5529LP_I2CB0 = 0,

    MSP_EXP430F5529LP_I2CCOUNT
} MSP_EXP430F5529LP_I2CName;

/*!
 *  @def    MSP_EXP430F5529LP_SDSPIName
 *  @brief  Enum of SDSPI names on the MSP_EXP430F5529LP dev board
 */
typedef enum MSP_EXP430F5529LP_SDSPIName {
    MSP_EXP430F5529LP_SDSPIB0 = 0,

    MSP_EXP430F5529LP_SDSPICOUNT
} EMSP_EXP430F5529LP_SDSPIName;

/*!
 *  @def    MSP_EXP430F5529LP_SPIName
 *  @brief  Enum of SPI names on the MSP_EXP430F5529LP dev board
 */
typedef enum MSP_EXP430F5529LP_SPIName {
    MSP_EXP430F5529LP_SPIB0 = 0,

    MSP_EXP430F5529LP_SPICOUNT
} MSP_EXP430F5529LP_SPIName;

/*!
 *  @def    MSP_EXP430F5529LP_UARTName
 *  @brief  Enum of UART names on the MSP_EXP430F5529LP dev board
 */
typedef enum MSP_EXP430F5529LP_UARTName {
    MSP_EXP430F5529LP_UARTA1 = 0,

    MSP_EXP430F5529LP_UARTCOUNT
} MSP_EXP430F5529LP_UARTName;

/*!
 *  @def    MSP_EXP430F5529LP_WatchdogName
 *  @brief  Enum of Watchdog names on the MSP_EXP430F5529LP dev board
 */
typedef enum MSP_EXP430F5529LP_WatchdogName {
    MSP_EXP430F5529LP_WATCHDOG = 0,

    MSP_EXP430F5529LP_WATCHDOGCOUNT
} MSP_EXP430F5529LP_WatchdogName;

/*!
 *  @def    MSP_EXP430F5529LP_WiFiName
 *  @brief  Enum of WiFi names on the MSP_EXP430F5529LP dev board
 */
typedef enum MSP_EXP430F5529LP_WiFiName {
    MSP_EXP430F5529LP_WIFI = 0,

    MSP_EXP430F5529LP_WIFICOUNT
} MSP_EXP430F5529LP_WiFiName;

/*!
 *  @brief  Initialize the general board specific settings
 *
 *  This function initializes the general board specific settings.
 */
extern void MSP_EXP430F5529LP_initGeneral(void);

/*!
 *  @brief  Initialize board specific GPIO settings
 *
 *  This function initializes the board specific GPIO settings and
 *  then calls the GPIO_init API to initialize the GPIO module.
 *
 *  The GPIOs controlled by the GPIO module are determined by the GPIO_PinConfig
 *  variable.
 */
extern void MSP_EXP430F5529LP_initGPIO(void);

/*!
 *  @brief  Initialize board specific I2C settings
 *
 *  This function initializes the board specific I2C settings and then calls
 *  the I2C_init API to initialize the I2C module.
 *
 *  The I2C peripherals controlled by the I2C module are determined by the
 *  I2C_config variable.
 */
extern void MSP_EXP430F5529LP_initI2C(void);

/*!
 *  @brief  Initialize board specific SDSPI settings
 *
 *  This function initializes the board specific SDSPI settings and then calls
 *  the SDSPI_init API to initialize the SDSPI module.
 *
 *  The SDSPI peripherals controlled by the SDSPI module are determined by the
 *  SDSPI_config variable.
 */
extern void MSP_EXP430F5529LP_initSDSPI(void);

/*!
 *  @brief  Initialize board specific SPI settings
 *
 *  This function initializes the board specific SPI settings and then calls
 *  the SPI_init API to initialize the SPI module.
 *
 *  The SPI peripherals controlled by the SPI module are determined by the
 *  SPI_config variable.
 */
extern void MSP_EXP430F5529LP_initSPI(void);

/*!
 *  @brief  Initialize board specific UART settings
 *
 *  This function initializes the board specific UART settings and then calls
 *  the UART_init API to initialize the UART module.
 *
 *  The UART peripherals controlled by the UART module are determined by the
 *  UART_config variable.
 */
extern void MSP_EXP430F5529LP_initUART(void);

/*!
 *  @brief  Initialize board specific USB settings
 *
 *  This function initializes the board specific USB settings and pins based on
 *  the USB mode of operation.
 *
 *  @param      arg    placeholder variable
 */
extern void MSP_EXP430F5529LP_initUSB(unsigned int arg);

/*!
 *  @brief  Initialize board specific Watchdog settings
 *
 *  This function initializes the board specific Watchdog settings and then
 *  calls the Watchdog_init API to initialize the Watchdog module.
 *
 *  The Watchdog peripherals controlled by the Watchdog module are determined
 *  by the Watchdog_config variable.
 */
extern void MSP_EXP430F5529LP_initWatchdog(void);

/*!
 *  @brief  Initialize board specific WiFi settings
 *
 *  This function initializes the board specific WiFi settings and then calls
 *  the WiFi_init API to initialize the WiFi module.
 *
 *  The hardware resources controlled by the WiFi module are determined by the
 *  WiFi_config variable.
 *
 *  A SimpleLink CC3100 device or module is required and must be connected to
 *  use the WiFi driver.
 */
extern void MSP_EXP430F5529LP_initWiFi(void);

#ifdef __cplusplus
}
#endif

#endif /* __MSP_EXP430F5529LP_H */
