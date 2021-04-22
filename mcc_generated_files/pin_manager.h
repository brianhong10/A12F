/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.6
        Device            :  PIC16F15356
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.30 and above
        MPLAB 	          :  MPLAB X 5.40	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set Wake_detect aliases
#define Wake_detect_TRIS                 TRISAbits.TRISA0
#define Wake_detect_LAT                  LATAbits.LATA0
#define Wake_detect_PORT                 PORTAbits.RA0
#define Wake_detect_WPU                  WPUAbits.WPUA0
#define Wake_detect_OD                   ODCONAbits.ODCA0
#define Wake_detect_ANS                  ANSELAbits.ANSA0
#define Wake_detect_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)    	//将引脚设置为高电平
#define Wake_detect_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define Wake_detect_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define Wake_detect_GetValue()           PORTAbits.RA0							//读取引脚的当前状态
#define Wake_detect_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define Wake_detect_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define Wake_detect_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define Wake_detect_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define Wake_detect_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define Wake_detect_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define Wake_detect_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define Wake_detect_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set Welcome_detect aliases
#define Welcome_detect_TRIS                 TRISAbits.TRISA1
#define Welcome_detect_LAT                  LATAbits.LATA1
#define Welcome_detect_PORT                 PORTAbits.RA1
#define Welcome_detect_WPU                  WPUAbits.WPUA1
#define Welcome_detect_OD                   ODCONAbits.ODCA1
#define Welcome_detect_ANS                  ANSELAbits.ANSA1
#define Welcome_detect_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define Welcome_detect_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define Welcome_detect_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define Welcome_detect_GetValue()           PORTAbits.RA1
#define Welcome_detect_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define Welcome_detect_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define Welcome_detect_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define Welcome_detect_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define Welcome_detect_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define Welcome_detect_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define Welcome_detect_SetAnalogMode()      do { ANSELAbits.ANSA1 = 1; } while(0)
#define Welcome_detect_SetDigitalMode()     do { ANSELAbits.ANSA1 = 0; } while(0)

// get/set ADC_Left_Temp aliases
#define ADC_Left_Temp_TRIS                 TRISAbits.TRISA2
#define ADC_Left_Temp_LAT                  LATAbits.LATA2
#define ADC_Left_Temp_PORT                 PORTAbits.RA2
#define ADC_Left_Temp_WPU                  WPUAbits.WPUA2
#define ADC_Left_Temp_OD                   ODCONAbits.ODCA2
#define ADC_Left_Temp_ANS                  ANSELAbits.ANSA2
#define ADC_Left_Temp_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define ADC_Left_Temp_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define ADC_Left_Temp_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define ADC_Left_Temp_GetValue()           PORTAbits.RA2
#define ADC_Left_Temp_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define ADC_Left_Temp_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define ADC_Left_Temp_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define ADC_Left_Temp_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define ADC_Left_Temp_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define ADC_Left_Temp_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define ADC_Left_Temp_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define ADC_Left_Temp_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set LED_PWR aliases
#define LED_PWR_TRIS                 TRISAbits.TRISA3
#define LED_PWR_LAT                  LATAbits.LATA3
#define LED_PWR_PORT                 PORTAbits.RA3
#define LED_PWR_WPU                  WPUAbits.WPUA3
#define LED_PWR_OD                   ODCONAbits.ODCA3
#define LED_PWR_ANS                  ANSELAbits.ANSA3
#define LED_PWR_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define LED_PWR_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define LED_PWR_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define LED_PWR_GetValue()           PORTAbits.RA3
#define LED_PWR_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define LED_PWR_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define LED_PWR_SetPullup()          do { WPUAbits.WPUA3 = 1; } while(0)
#define LED_PWR_ResetPullup()        do { WPUAbits.WPUA3 = 0; } while(0)
#define LED_PWR_SetPushPull()        do { ODCONAbits.ODCA3 = 0; } while(0)
#define LED_PWR_SetOpenDrain()       do { ODCONAbits.ODCA3 = 1; } while(0)
#define LED_PWR_SetAnalogMode()      do { ANSELAbits.ANSA3 = 1; } while(0)
#define LED_PWR_SetDigitalMode()     do { ANSELAbits.ANSA3 = 0; } while(0)

// get/set RA4 procedures
#define RA4_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define RA4_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define RA4_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define RA4_GetValue()              PORTAbits.RA4
#define RA4_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define RA4_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define RA4_SetPullup()             do { WPUAbits.WPUA4 = 1; } while(0)
#define RA4_ResetPullup()           do { WPUAbits.WPUA4 = 0; } while(0)
#define RA4_SetAnalogMode()         do { ANSELAbits.ANSA4 = 1; } while(0)
#define RA4_SetDigitalMode()        do { ANSELAbits.ANSA4 = 0; } while(0)

// get/set ADC_Left_Vol aliases
#define ADC_Left_Vol_TRIS                 TRISAbits.TRISA5
#define ADC_Left_Vol_LAT                  LATAbits.LATA5
#define ADC_Left_Vol_PORT                 PORTAbits.RA5
#define ADC_Left_Vol_WPU                  WPUAbits.WPUA5
#define ADC_Left_Vol_OD                   ODCONAbits.ODCA5
#define ADC_Left_Vol_ANS                  ANSELAbits.ANSA5
#define ADC_Left_Vol_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define ADC_Left_Vol_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define ADC_Left_Vol_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define ADC_Left_Vol_GetValue()           PORTAbits.RA5
#define ADC_Left_Vol_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define ADC_Left_Vol_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define ADC_Left_Vol_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define ADC_Left_Vol_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define ADC_Left_Vol_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define ADC_Left_Vol_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define ADC_Left_Vol_SetAnalogMode()      do { ANSELAbits.ANSA5 = 1; } while(0)
#define ADC_Left_Vol_SetDigitalMode()     do { ANSELAbits.ANSA5 = 0; } while(0)

// get/set ADC_DC_LTemp aliases
#define ADC_DC_LTemp_TRIS                 TRISAbits.TRISA6
#define ADC_DC_LTemp_LAT                  LATAbits.LATA6
#define ADC_DC_LTemp_PORT                 PORTAbits.RA6
#define ADC_DC_LTemp_WPU                  WPUAbits.WPUA6
#define ADC_DC_LTemp_OD                   ODCONAbits.ODCA6
#define ADC_DC_LTemp_ANS                  ANSELAbits.ANSA6
#define ADC_DC_LTemp_SetHigh()            do { LATAbits.LATA6 = 1; } while(0)
#define ADC_DC_LTemp_SetLow()             do { LATAbits.LATA6 = 0; } while(0)
#define ADC_DC_LTemp_Toggle()             do { LATAbits.LATA6 = ~LATAbits.LATA6; } while(0)
#define ADC_DC_LTemp_GetValue()           PORTAbits.RA6
#define ADC_DC_LTemp_SetDigitalInput()    do { TRISAbits.TRISA6 = 1; } while(0)
#define ADC_DC_LTemp_SetDigitalOutput()   do { TRISAbits.TRISA6 = 0; } while(0)
#define ADC_DC_LTemp_SetPullup()          do { WPUAbits.WPUA6 = 1; } while(0)
#define ADC_DC_LTemp_ResetPullup()        do { WPUAbits.WPUA6 = 0; } while(0)
#define ADC_DC_LTemp_SetPushPull()        do { ODCONAbits.ODCA6 = 0; } while(0)
#define ADC_DC_LTemp_SetOpenDrain()       do { ODCONAbits.ODCA6 = 1; } while(0)
#define ADC_DC_LTemp_SetAnalogMode()      do { ANSELAbits.ANSA6 = 1; } while(0)
#define ADC_DC_LTemp_SetDigitalMode()     do { ANSELAbits.ANSA6 = 0; } while(0)

// get/set ADC_Right_Vol aliases
#define ADC_Right_Vol_TRIS                 TRISAbits.TRISA7
#define ADC_Right_Vol_LAT                  LATAbits.LATA7
#define ADC_Right_Vol_PORT                 PORTAbits.RA7
#define ADC_Right_Vol_WPU                  WPUAbits.WPUA7
#define ADC_Right_Vol_OD                   ODCONAbits.ODCA7
#define ADC_Right_Vol_ANS                  ANSELAbits.ANSA7
#define ADC_Right_Vol_SetHigh()            do { LATAbits.LATA7 = 1; } while(0)
#define ADC_Right_Vol_SetLow()             do { LATAbits.LATA7 = 0; } while(0)
#define ADC_Right_Vol_Toggle()             do { LATAbits.LATA7 = ~LATAbits.LATA7; } while(0)
#define ADC_Right_Vol_GetValue()           PORTAbits.RA7
#define ADC_Right_Vol_SetDigitalInput()    do { TRISAbits.TRISA7 = 1; } while(0)
#define ADC_Right_Vol_SetDigitalOutput()   do { TRISAbits.TRISA7 = 0; } while(0)
#define ADC_Right_Vol_SetPullup()          do { WPUAbits.WPUA7 = 1; } while(0)
#define ADC_Right_Vol_ResetPullup()        do { WPUAbits.WPUA7 = 0; } while(0)
#define ADC_Right_Vol_SetPushPull()        do { ODCONAbits.ODCA7 = 0; } while(0)
#define ADC_Right_Vol_SetOpenDrain()       do { ODCONAbits.ODCA7 = 1; } while(0)
#define ADC_Right_Vol_SetAnalogMode()      do { ANSELAbits.ANSA7 = 1; } while(0)
#define ADC_Right_Vol_SetDigitalMode()     do { ANSELAbits.ANSA7 = 0; } while(0)

// get/set MCU_Vol aliases
#define MCU_Vol_TRIS                 TRISBbits.TRISB1
#define MCU_Vol_LAT                  LATBbits.LATB1
#define MCU_Vol_PORT                 PORTBbits.RB1
#define MCU_Vol_WPU                  WPUBbits.WPUB1
#define MCU_Vol_OD                   ODCONBbits.ODCB1
#define MCU_Vol_ANS                  ANSELBbits.ANSB1
#define MCU_Vol_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define MCU_Vol_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define MCU_Vol_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define MCU_Vol_GetValue()           PORTBbits.RB1
#define MCU_Vol_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define MCU_Vol_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define MCU_Vol_SetPullup()          do { WPUBbits.WPUB1 = 1; } while(0)
#define MCU_Vol_ResetPullup()        do { WPUBbits.WPUB1 = 0; } while(0)
#define MCU_Vol_SetPushPull()        do { ODCONBbits.ODCB1 = 0; } while(0)
#define MCU_Vol_SetOpenDrain()       do { ODCONBbits.ODCB1 = 1; } while(0)
#define MCU_Vol_SetAnalogMode()      do { ANSELBbits.ANSB1 = 1; } while(0)
#define MCU_Vol_SetDigitalMode()     do { ANSELBbits.ANSB1 = 0; } while(0)

// get/set LED_BIN1 aliases
#define LED_BIN1_TRIS                 TRISBbits.TRISB2
#define LED_BIN1_LAT                  LATBbits.LATB2
#define LED_BIN1_PORT                 PORTBbits.RB2
#define LED_BIN1_WPU                  WPUBbits.WPUB2
#define LED_BIN1_OD                   ODCONBbits.ODCB2
#define LED_BIN1_ANS                  ANSELBbits.ANSB2
#define LED_BIN1_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define LED_BIN1_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define LED_BIN1_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define LED_BIN1_GetValue()           PORTBbits.RB2
#define LED_BIN1_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define LED_BIN1_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define LED_BIN1_SetPullup()          do { WPUBbits.WPUB2 = 1; } while(0)
#define LED_BIN1_ResetPullup()        do { WPUBbits.WPUB2 = 0; } while(0)
#define LED_BIN1_SetPushPull()        do { ODCONBbits.ODCB2 = 0; } while(0)
#define LED_BIN1_SetOpenDrain()       do { ODCONBbits.ODCB2 = 1; } while(0)
#define LED_BIN1_SetAnalogMode()      do { ANSELBbits.ANSB2 = 1; } while(0)
#define LED_BIN1_SetDigitalMode()     do { ANSELBbits.ANSB2 = 0; } while(0)

// get/set LED_BIN2 aliases
#define LED_BIN2_TRIS                 TRISBbits.TRISB3
#define LED_BIN2_LAT                  LATBbits.LATB3
#define LED_BIN2_PORT                 PORTBbits.RB3
#define LED_BIN2_WPU                  WPUBbits.WPUB3
#define LED_BIN2_OD                   ODCONBbits.ODCB3
#define LED_BIN2_ANS                  ANSELBbits.ANSB3
#define LED_BIN2_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define LED_BIN2_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define LED_BIN2_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define LED_BIN2_GetValue()           PORTBbits.RB3
#define LED_BIN2_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define LED_BIN2_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define LED_BIN2_SetPullup()          do { WPUBbits.WPUB3 = 1; } while(0)
#define LED_BIN2_ResetPullup()        do { WPUBbits.WPUB3 = 0; } while(0)
#define LED_BIN2_SetPushPull()        do { ODCONBbits.ODCB3 = 0; } while(0)
#define LED_BIN2_SetOpenDrain()       do { ODCONBbits.ODCB3 = 1; } while(0)
#define LED_BIN2_SetAnalogMode()      do { ANSELBbits.ANSB3 = 1; } while(0)
#define LED_BIN2_SetDigitalMode()     do { ANSELBbits.ANSB3 = 0; } while(0)

// get/set LED_BIN3 aliases
#define LED_BIN3_TRIS                 TRISBbits.TRISB4
#define LED_BIN3_LAT                  LATBbits.LATB4
#define LED_BIN3_PORT                 PORTBbits.RB4
#define LED_BIN3_WPU                  WPUBbits.WPUB4
#define LED_BIN3_OD                   ODCONBbits.ODCB4
#define LED_BIN3_ANS                  ANSELBbits.ANSB4
#define LED_BIN3_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define LED_BIN3_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define LED_BIN3_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define LED_BIN3_GetValue()           PORTBbits.RB4
#define LED_BIN3_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define LED_BIN3_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define LED_BIN3_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define LED_BIN3_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define LED_BIN3_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define LED_BIN3_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define LED_BIN3_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define LED_BIN3_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set Signal3 aliases
#define Signal3_TRIS                 TRISBbits.TRISB5
#define Signal3_LAT                  LATBbits.LATB5
#define Signal3_PORT                 PORTBbits.RB5
#define Signal3_WPU                  WPUBbits.WPUB5
#define Signal3_OD                   ODCONBbits.ODCB5
#define Signal3_ANS                  ANSELBbits.ANSB5
#define Signal3_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define Signal3_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define Signal3_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define Signal3_GetValue()           PORTBbits.RB5
#define Signal3_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define Signal3_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define Signal3_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define Signal3_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define Signal3_SetPushPull()        do { ODCONBbits.ODCB5 = 0; } while(0)
#define Signal3_SetOpenDrain()       do { ODCONBbits.ODCB5 = 1; } while(0)
#define Signal3_SetAnalogMode()      do { ANSELBbits.ANSB5 = 1; } while(0)
#define Signal3_SetDigitalMode()     do { ANSELBbits.ANSB5 = 0; } while(0)

// get/set Signal1 aliases
#define Signal1_TRIS                 TRISCbits.TRISC0
#define Signal1_LAT                  LATCbits.LATC0
#define Signal1_PORT                 PORTCbits.RC0
#define Signal1_WPU                  WPUCbits.WPUC0
#define Signal1_OD                   ODCONCbits.ODCC0
#define Signal1_ANS                  ANSELCbits.ANSC0
#define Signal1_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define Signal1_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define Signal1_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define Signal1_GetValue()           PORTCbits.RC0
#define Signal1_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define Signal1_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define Signal1_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define Signal1_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define Signal1_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define Signal1_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define Signal1_SetAnalogMode()      do { ANSELCbits.ANSC0 = 1; } while(0)
#define Signal1_SetDigitalMode()     do { ANSELCbits.ANSC0 = 0; } while(0)

// get/set Signal2 aliases
#define Signal2_TRIS                 TRISCbits.TRISC1
#define Signal2_LAT                  LATCbits.LATC1
#define Signal2_PORT                 PORTCbits.RC1
#define Signal2_WPU                  WPUCbits.WPUC1
#define Signal2_OD                   ODCONCbits.ODCC1
#define Signal2_ANS                  ANSELCbits.ANSC1
#define Signal2_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define Signal2_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define Signal2_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define Signal2_GetValue()           PORTCbits.RC1
#define Signal2_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define Signal2_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define Signal2_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define Signal2_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define Signal2_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define Signal2_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define Signal2_SetAnalogMode()      do { ANSELCbits.ANSC1 = 1; } while(0)
#define Signal2_SetDigitalMode()     do { ANSELCbits.ANSC1 = 0; } while(0)

// get/set ADC_DC_RTemp aliases
#define ADC_DC_RTemp_TRIS                 TRISCbits.TRISC2
#define ADC_DC_RTemp_LAT                  LATCbits.LATC2
#define ADC_DC_RTemp_PORT                 PORTCbits.RC2
#define ADC_DC_RTemp_WPU                  WPUCbits.WPUC2
#define ADC_DC_RTemp_OD                   ODCONCbits.ODCC2
#define ADC_DC_RTemp_ANS                  ANSELCbits.ANSC2
#define ADC_DC_RTemp_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define ADC_DC_RTemp_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define ADC_DC_RTemp_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define ADC_DC_RTemp_GetValue()           PORTCbits.RC2
#define ADC_DC_RTemp_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define ADC_DC_RTemp_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define ADC_DC_RTemp_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define ADC_DC_RTemp_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define ADC_DC_RTemp_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define ADC_DC_RTemp_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define ADC_DC_RTemp_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define ADC_DC_RTemp_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set RC3 procedures
#define RC3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define RC3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define RC3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define RC3_GetValue()              PORTCbits.RC3
#define RC3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define RC3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define RC3_SetPullup()             do { WPUCbits.WPUC3 = 1; } while(0)
#define RC3_ResetPullup()           do { WPUCbits.WPUC3 = 0; } while(0)
#define RC3_SetAnalogMode()         do { ANSELCbits.ANSC3 = 1; } while(0)
#define RC3_SetDigitalMode()        do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set LED_PWM_EN aliases
#define LED_PWM_EN_TRIS                 TRISCbits.TRISC4
#define LED_PWM_EN_LAT                  LATCbits.LATC4
#define LED_PWM_EN_PORT                 PORTCbits.RC4
#define LED_PWM_EN_WPU                  WPUCbits.WPUC4
#define LED_PWM_EN_OD                   ODCONCbits.ODCC4
#define LED_PWM_EN_ANS                  ANSELCbits.ANSC4
#define LED_PWM_EN_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define LED_PWM_EN_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define LED_PWM_EN_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define LED_PWM_EN_GetValue()           PORTCbits.RC4
#define LED_PWM_EN_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define LED_PWM_EN_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define LED_PWM_EN_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define LED_PWM_EN_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define LED_PWM_EN_SetPushPull()        do { ODCONCbits.ODCC4 = 0; } while(0)
#define LED_PWM_EN_SetOpenDrain()       do { ODCONCbits.ODCC4 = 1; } while(0)
#define LED_PWM_EN_SetAnalogMode()      do { ANSELCbits.ANSC4 = 1; } while(0)
#define LED_PWM_EN_SetDigitalMode()     do { ANSELCbits.ANSC4 = 0; } while(0)

// get/set RC6 procedures
#define RC6_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define RC6_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define RC6_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define RC6_GetValue()              PORTCbits.RC6
#define RC6_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define RC6_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define RC6_SetPullup()             do { WPUCbits.WPUC6 = 1; } while(0)
#define RC6_ResetPullup()           do { WPUCbits.WPUC6 = 0; } while(0)
#define RC6_SetAnalogMode()         do { ANSELCbits.ANSC6 = 1; } while(0)
#define RC6_SetDigitalMode()        do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set RC7 procedures
#define RC7_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define RC7_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define RC7_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define RC7_GetValue()              PORTCbits.RC7
#define RC7_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define RC7_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define RC7_SetPullup()             do { WPUCbits.WPUC7 = 1; } while(0)
#define RC7_ResetPullup()           do { WPUCbits.WPUC7 = 0; } while(0)
#define RC7_SetAnalogMode()         do { ANSELCbits.ANSC7 = 1; } while(0)
#define RC7_SetDigitalMode()        do { ANSELCbits.ANSC7 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/