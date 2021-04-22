/**
  TMR0 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    tmr0.c

  @Summary
    This is the generated driver implementation file for the TMR0 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This source file provides APIs for TMR0.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.6
        Device            :  PIC16F15356
        Driver Version    :  3.10
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

/**
  Section: Included Files
*/

#include <xc.h>
#include "tmr0.h"


TMR_FLAGS_T TmrFlags;			/* timer flags */
/**
  Section: TMR0 APIs
*/

void (*TMR0_InterruptHandler)(void);

void TMR0_Initialize(void)
{
    // Set TMR0 to the options selected in the User Interface

    // T0CS FOSC/4; T0CKPS 1:4; T0ASYNC synchronised; 
    T0CON1 = 0x42;

    // TMR0H 124; 
    TMR0H = 0x7C;

    // TMR0L 0; 
    TMR0L = 0x00;

    // Clear Interrupt flag before enabling the interrupt
    PIR0bits.TMR0IF = 0;

    // Enabling TMR0 interrupt.
    PIE0bits.TMR0IE = 1;

    // Set Default Interrupt Handler
    TMR0_SetInterruptHandler(TMR0_DefaultInterruptHandler);

    // T0OUTPS 1:16; T0EN enabled; T016BIT 8-bit; 
    T0CON0 = 0x8F;
}

void TMR0_StartTimer(void)
{
    // Start the Timer by writing to TMR0ON bit
    T0CON0bits.T0EN = 1;
}

void TMR0_StopTimer(void)
{
    // Stop the Timer by writing to TMR0ON bit
    T0CON0bits.T0EN = 0;
}

uint8_t TMR0_ReadTimer(void)
{
    uint8_t readVal;

    // read Timer0, low register only
    readVal = TMR0L;

    return readVal;
}

void TMR0_WriteTimer(uint8_t timerVal)
{
    // Write to Timer0 registers, low register only
    TMR0L = timerVal;
 }

void TMR0_Reload(uint8_t periodVal)
{
   // Write to Timer0 registers, high register only
   TMR0H = periodVal;
}

void TMR0_ISR(void)
{
    static uint8_t cntr2ms = 0, cntr5ms = 0;
	static uint16_t cntr2500ms = 0, cntr3000ms = 0;

    // clear the TMR0 interrupt flag
    PIR0bits.TMR0IF = 0;
    // ticker function call;
    // ticker is 1 -> Callback function gets called every time this ISR executes
    
    TmrFlags.tmr1ms_f = 1;
	cntr2ms++;
	if(cntr2ms == 2)
    {
 	 	TmrFlags.tmr2ms_f = 1; 					 //2ms timer flag
 	 	cntr2ms = 0;
	}

	cntr5ms++;
 	if(cntr5ms == 5)
 	{
	  	TmrFlags.tmr5ms_f = 1;				  //5ms timer flag  
	 	cntr5ms = 0;
	}
	
	cntr2500ms++;
 	if(cntr2500ms == 2500)
 	{
	  	TmrFlags.tmr2500ms_f = 1;				  //2.5s timer flag  
	 	cntr2500ms = 0;
	}

	cntr3000ms++;
 	if(cntr3000ms == 3000)
 	{
	  	TmrFlags.tmr3000ms_f = 1;				  //3s timer flag  
	 	cntr3000ms = 0;
	}
    // add your TMR0 interrupt custom code
}


void TMR0_SetInterruptHandler(void (* InterruptHandler)(void)){
    TMR0_InterruptHandler = InterruptHandler;
}

void TMR0_DefaultInterruptHandler(void){
    // add your TMR0 interrupt custom code
    // or set custom function using TMR0_SetInterruptHandler()
}

/**
  End of File
*/
