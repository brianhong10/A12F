/**
  CCP1 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    ccp1.c

  @Summary
    This is the generated driver implementation file for the CCP1 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This source file provides implementations for driver APIs for CCP1.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.6
        Device            :  PIC16F15356
        Driver Version    :  2.1.3
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
#include "ccp1.h"
#include "tmr1.h"

bool UnLock_flag;
bool Lock_flag;
uint8_t Fi = 0;	   //Ƶ����������

//�������β����������
volatile uint16_t Capture_i = 0,Capture_j = 0;

//������δμ���Ƶ��ֵ
volatile uint16_t Freq[] = {0,0,0,0,0};

void falling(void)
{

	Capture_i = TMR1_ReadTimer();

	CCP1CON = 0x85;  //�´�Ϊ�����ز�׽
}

void rising(void)
{
	Capture_j = TMR1_ReadTimer();
	Capture_j= 1000000UL/(Capture_j-Capture_i); 			   //��������õ����ڼ��㣬����͵�ƽʱ��
	Freq[Fi]=Capture_j;							 //�����i�μ�⵽��Ƶ�ʲ���������
	Fi++;
	if(Fi==4) 											   //�ﵽ5�κ�ʼ�жϼ��Ƶ���Ƿ����
    {    
		Fi=0;
		if((Freq[2]>=0x07)&&(Freq[2]<=0x17)) //&&(Freq[1]==0x11))&&(Freq[3]==0x11))	//5�μ��Ƶ����ȣ�����3ms��
		{
			Lock_flag = true;
		}
		else if((Freq[2]>=0x25) &&(Freq[2]<=0x2E)) //&&((Freq[1]==0x28) ||(Freq[1] ==0x29)))//&&((Freq[3]==0x28) ||(Freq[3] == 0x29)))  //5�μ��Ƶ����ȣ�����7ms��PWM��10ms
		{
			UnLock_flag = true;
		}
    }

	TMR1H=TMR1L=Capture_i=Capture_j=0;				//��δ�������5�μ�⣨10�β����������TMR1����ر������㣩

	CCP1CON = 0x84;  //�´�Ϊ�½��ز�׽
}

static void (*CCP1_CallBack)(uint16_t);

/**
  Section: Capture Module APIs:
*/

static void CCP1_DefaultCallBack(uint16_t capturedValue)
{
    // Add your code here
}

void CCP1_Initialize(void)
{
    // Set the CCP1 to the options selected in the User Interface
	
	// MODE Falling edge; EN enabled; CCP1FMT right_aligned; 
	CCP1CON = 0x84;    
	
	// CCP1CTS CCP1 pin; 
	CCP1CAP = 0x00;    
	
	// RH 0; 
	CCPR1H = 0x00;    
	
	// RL 0; 
	CCPR1L = 0x00;    
    
    // Set the default call back function for CCP1
    CCP1_SetCallBack(CCP1_DefaultCallBack);

    // Clear the CCP1 interrupt flag
    PIR6bits.CCP1IF = 0;

    // Enable the CCP1 interrupt
    PIE6bits.CCP1IE = 1;
}

void CCP1_CaptureISR(void)
{
	if(PIR6bits.CCP1IF)	
	{
		if(Capture_i==0)   //��ȡ��һ�β���ֵ���½��� 
		{			
			falling();
		}
   	 	else       //�ڶ��β���������
		{
			rising();
		}

		PIR6bits.CCP1IF=0; //�����0�жϱ�־λ	
	}
}

void CCP1_SetCallBack(void (*customCallBack)(uint16_t)){
    CCP1_CallBack = customCallBack;
}
/**
 End of File
*/
