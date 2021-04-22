/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 *  application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include "app.h"
#include "can_protocol.h"
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/ccp1.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************
bool Wake_detect_flag;
bool Welcome_detect_flag;
bool Signal1_flag;
bool Signal2_flag;
bool Signal3_flag;

uint16_t Wake_detect_cont;
uint16_t Welcome_detect_cont;
uint8_t Signal1_cont;
uint8_t Signal2_cont;
uint8_t Signal3_cont;

bool LED_BIN1_flag;
bool LED_BIN2_flag;
bool LED_BIN3_flag;
bool Init_LED_flag;
bool Unlock_run_flag;

uint8_t Current_select_flag; //0x01 ����42.5ma ,0x02����60ma��0x03����75ma
bool Normal_temp_flag;
bool Over_62_flag;
bool Over_65_flag;
bool Over_70_flag;
bool Over_75_flag;
bool Over_80_flag;
bool Over_84_flag;
bool Over_60_write_flag;
bool Over_85_flag;
bool Over_85_flag;
bool Over_85_LED_off_flag;

uint8_t LED_Power_error;
uint8_t LED_Power_ok;

uint16_t LED_Power_Low;
bool LED_Power_flag;

//bool delay_flag;
//uint16_t delay_cont;

bool LED_Power_Low_flag;

// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************
void LED_OFF(void);

/* TODO:  Add any necessary callback functions.
*/

/* TODO:  Add any necessary local functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */
void APP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
	LED_PWM_EN_SetHigh();  //LED�ϵ� 

	DELAY_milliseconds(80);  //LED�ϵ����80ms����ú��ٸ�522.49����

	LED_PWR_SetLow();       //52249 startup��ѹ
}

/*PWM 100% =3FF,current 10ma= num100*/
void LED_Init ( void )
{
	uint16_t data[1] = {0x0} ,data1[1] = {0x1A9},data2[1] = {0x258},data3[1] = {0x2EE},data4[1] = {0x3FF};

	can_write_frame(0x00, 0x62, data, 0x01, 0x40);
	can_write_frame(0x00, 0x63, data, 0x01, 0x40);   //�õ��Ȳ�����Ȼ��дPWM��current�Ĵ���

	LED_BIN1_flag = LED_BIN1_GetValue(); 
	LED_BIN2_flag = LED_BIN2_GetValue(); 
	LED_BIN3_flag = LED_BIN3_GetValue(); 
	if((LED_BIN1_flag ==1)&&(LED_BIN2_flag ==0)&&(LED_BIN3_flag ==0))//���FA BIN���� 42.5ma
	{
		can_write_frame(0x00, 0x7d, data1, 0x01, 0x40);   //all channel Current setting
		Current_select_flag = 0x01;
	}
	else if((LED_BIN1_flag ==0)&&(LED_BIN2_flag ==1)&&(LED_BIN3_flag ==0)) //���EB BIN���� 60ma	
	{
		can_write_frame(0x00, 0x7d, data2, 0x01, 0x40);   //all channel Current setting
		Current_select_flag = 0x02;
	}
	else if((LED_BIN1_flag ==0)&&(LED_BIN2_flag ==0)&&(LED_BIN3_flag ==1)) //���EA BIN���� 75ma
	{
		can_write_frame(0x00, 0x7d, data3, 0x01, 0x40);   //all channel Current setting
		Current_select_flag = 0x03;
	}

	can_write_frame(0x00, 0x7c, data4, 0x01, 0x40);    //all channel PWM setting		
}
//����
void LED_ON(void)
{
	uint16_t data[1] ={0xFF};
	
	can_write_frame(0x00, 0x62, data, 0x01, 0x40);
	can_write_frame(0x00, 0x63, data, 0x01, 0x40);   
}
//����
void LED_OFF(void)
{
	uint16_t data[1] = {0x0}; 

	can_write_frame(0x00, 0x62, data, 0x01, 0x40);
	can_write_frame(0x00, 0x63, data, 0x01, 0x40);
}
//���߸�25�ŵƣ�12+13��ģʽ��ɣ�ǰ4channel����(12�Ŷ���)��ǰ3channel����(13�Ŷ���)��addr=       1    ,2ͬһ�ߣ�addr=3,4ͬһ�ߡ�1��3����һ����2��4����һ����
void addr_LED1_On(uint8_t devaddr1, uint8_t devaddr2)
{	
	uint16_t data[1] = {0x10},data1[1] = {0x08}; 
	
	if(devaddr1 == 0x01)
	{
		can_write_frame(devaddr1, 0x62, data, 0x01, 0x40);
		can_write_frame(devaddr2, 0x62, data, 0x01, 0x40);	
	}
	else if(devaddr1 == 0x02)
	{
		can_write_frame(devaddr1, 0x62, data1, 0x01, 0x40);
		can_write_frame(devaddr2, 0x62, data1, 0x01, 0x40);
	}
}
void addr_LED2_On(uint8_t devaddr1, uint8_t devaddr2)
{
	uint16_t data[1] = {0x30},data1[1] = {0x18}; 

	if(devaddr1 == 0x01)
	{	
		can_write_frame(devaddr1, 0x62, data, 0x01, 0x40);
		can_write_frame(devaddr2, 0x62, data, 0x01, 0x40);	
	}
	else if(devaddr1 == 0x02)
	{	
		can_write_frame(devaddr1, 0x62, data1, 0x01, 0x40);
		can_write_frame(devaddr2, 0x62, data1, 0x01, 0x40);
	}
}
void addr_LED3_On(uint8_t devaddr1, uint8_t devaddr2)
{
	uint16_t data[1] = {0x70},data1[1] = {0x38}; 

	if(devaddr1 == 0x01)
	{	
		can_write_frame(devaddr1, 0x62, data, 0x01, 0x40);	
		can_write_frame(devaddr2, 0x62, data, 0x01, 0x40);	
	}
	else if(devaddr1 == 0x02)
	{	
		can_write_frame(devaddr1, 0x62, data1, 0x01, 0x40);
		can_write_frame(devaddr2, 0x62, data1, 0x01, 0x40);
	}
}
void addr_LED4_On(uint8_t devaddr1, uint8_t devaddr2)
{
	uint16_t data[1] = {0xF0},data1[1] = {0x78}; 

	if(devaddr1 == 0x01)
	{	
		can_write_frame(devaddr1, 0x62, data, 0x01, 0x40);	
		can_write_frame(devaddr2, 0x62, data, 0x01, 0x40);	
	}
	else if(devaddr1 == 0x02)
	{	
		can_write_frame(devaddr1, 0x62, data1, 0x01, 0x40);
		can_write_frame(devaddr2, 0x62, data1, 0x01, 0x40);
	}
}
void addr_LED5_On(uint8_t devaddr1, uint8_t devaddr2)
{
	uint16_t data[1] = {0x01},data1[1] = {0xF8} ; 

	if(devaddr1 == 0x01)
	{	
		can_write_frame(devaddr1, 0x63, data, 0x01, 0x40);	
		can_write_frame(devaddr2, 0x63, data, 0x01, 0x40);	
	}
	else if(devaddr1 == 0x02)
	{	
		can_write_frame(devaddr1, 0x62, data1, 0x01, 0x40);
		can_write_frame(devaddr2, 0x62, data1, 0x01, 0x40);
	}
}

void addr_LED6_On(uint8_t devaddr1, uint8_t devaddr2)
{
	uint16_t data[1] = {0x03},data1[1] = {0x01}; 

	if(devaddr1 == 0x01)
	{	
		can_write_frame(devaddr1, 0x63, data, 0x01, 0x40);	
		can_write_frame(devaddr2, 0x63, data, 0x01, 0x40);	
	}
	else if(devaddr1 == 0x02)
	{	
		can_write_frame(devaddr1, 0x63, data1, 0x01, 0x40);
		can_write_frame(devaddr2, 0x63, data1, 0x01, 0x40);
	}
}
void addr_LED7_On(uint8_t devaddr1, uint8_t devaddr2)
{
	uint16_t data[1] = {0x07},data1[1] = {0x03}; 

	if(devaddr1 == 0x01)
	{	
		can_write_frame(devaddr1, 0x63, data, 0x01, 0x40);	
		can_write_frame(devaddr2, 0x63, data, 0x01, 0x40);	
	}
	else if(devaddr1 == 0x02)
	{	
		can_write_frame(devaddr1, 0x63, data1, 0x01, 0x40);
		can_write_frame(devaddr2, 0x63, data1, 0x01, 0x40);
	}
}
void addr_LED8_On(uint8_t devaddr1, uint8_t devaddr2)
{
	uint16_t data[1] = {0x0F},data1[1] = {0x07}; 

	if(devaddr1 == 0x01)
	{	
		can_write_frame(devaddr1, 0x63, data, 0x01, 0x40);	
		can_write_frame(devaddr2, 0x63, data, 0x01, 0x40);	
	}
	else if(devaddr1 == 0x02)
	{	
		can_write_frame(devaddr1, 0x63, data1, 0x01, 0x40);
		can_write_frame(devaddr2, 0x63, data1, 0x01, 0x40);
	}
}
void addr_LED9_On(uint8_t devaddr1, uint8_t devaddr2)
{
	uint16_t data[1] = {0x1F},data1[1] = {0x0F}; 

	if(devaddr1 == 0x01)
	{	
		can_write_frame(devaddr1, 0x63, data, 0x01, 0x40);	
		can_write_frame(devaddr2, 0x63, data, 0x01, 0x40);	
	}
	else if(devaddr1 == 0x02)
	{
		can_write_frame(devaddr1, 0x63, data1, 0x01, 0x40);
		can_write_frame(devaddr2, 0x63, data1, 0x01, 0x40);
	}
}
void addr_LED10_On(uint8_t devaddr1, uint8_t devaddr2)
{
	uint16_t data[1] = {0x03F},data1[1] = {0x1F}; 

	if(devaddr1 == 0x01)
	{	
		can_write_frame(devaddr1, 0x63, data, 0x01, 0x40);	
		can_write_frame(devaddr2, 0x63, data, 0x01, 0x40);	
	}
	else if(devaddr1 == 0x02)
	{	
		can_write_frame(devaddr1, 0x63, data1, 0x01, 0x40);
		can_write_frame(devaddr2, 0x63, data1, 0x01, 0x40);
	}
}
void addr_LED11_On(uint8_t devaddr1, uint8_t devaddr2)
{
	uint16_t data[1] = {0x7F},data1[1] = {0x3F}; 

	if(devaddr1 == 0x01)
	{	
		can_write_frame(devaddr1, 0x63, data, 0x01, 0x40);	
		can_write_frame(devaddr2, 0x63, data, 0x01, 0x40);	
	}
	else if(devaddr1 == 0x02)
	{	
		can_write_frame(devaddr1, 0x63, data1, 0x01, 0x40);
		can_write_frame(devaddr2, 0x63, data1, 0x01, 0x40);
	}
}
void addr_LED12_On(uint8_t devaddr1, uint8_t devaddr2)
{
	uint16_t data[1] = {0xFF},data1[1] = {0x7F}; 

	if(devaddr1 == 0x01)
	{	
		can_write_frame(devaddr1, 0x63, data, 0x01, 0x40);	
		can_write_frame(devaddr2, 0x63, data, 0x01, 0x40);	
	}
	else if(devaddr1 == 0x02)
	{	
		can_write_frame(devaddr1, 0x63, data1, 0x01, 0x40);
		can_write_frame(devaddr2, 0x63, data1, 0x01, 0x40);
	}
}
void addr_LED13_On(uint8_t devaddr1, uint8_t devaddr2)
{
	uint16_t data[1] = {0xFF}; 

	if(devaddr1 == 0x02)
	{	
		can_write_frame(devaddr1, 0x63, data, 0x01, 0x40);
		can_write_frame(devaddr2, 0x63, data, 0x01, 0x40);
	}
}

void addr_LED1_reverse_On(uint8_t devaddr1, uint8_t devaddr2)
{	
	uint16_t data[1] = {0xF0},data1[1] = {0xF8}; 
	
	if(devaddr1 == 0x01)
	{	
		can_write_frame(devaddr1, 0x62, data, 0x01, 0x40);
		can_write_frame(devaddr2, 0x62, data, 0x01, 0x40);	
	}
	else if(devaddr1 == 0x02)
	{	
		can_write_frame(devaddr1, 0x62, data1, 0x01, 0x40);
		can_write_frame(devaddr2, 0x62, data1, 0x01, 0x40);
	}
}
void addr_LED2_reverse_On(uint8_t devaddr1, uint8_t devaddr2)
{
	uint16_t data[1] = {0xE0},data1[1] = {0xF0}; 
	
	if(devaddr1 == 0x01)
	{	
		can_write_frame(devaddr1, 0x62, data, 0x01, 0x40);
		can_write_frame(devaddr2, 0x62, data, 0x01, 0x40);	
	}
	else if(devaddr1 == 0x02)
	{	
		can_write_frame(devaddr1, 0x62, data1, 0x01, 0x40);
		can_write_frame(devaddr2, 0x62, data1, 0x01, 0x40);
	}
}
void addr_LED3_reverse_On(uint8_t devaddr1, uint8_t devaddr2)
{
	uint16_t data[1] = {0xC0},data1[1] = {0xE0}; 
	
	if(devaddr1 == 0x01)
	{	
		can_write_frame(devaddr1, 0x62, data, 0x01, 0x40);
		can_write_frame(devaddr2, 0x62, data, 0x01, 0x40);	
	}
	else if(devaddr1 == 0x02)
	{	
		can_write_frame(devaddr1, 0x62, data1, 0x01, 0x40);
		can_write_frame(devaddr2, 0x62, data1, 0x01, 0x40);
	}
}
void addr_LED4_reverse_On(uint8_t devaddr1, uint8_t devaddr2)
{
	uint16_t data[1] = {0x80},data1[1] = {0xC0}; 
	
	if(devaddr1 == 0x01)
	{	
		can_write_frame(devaddr1, 0x62, data, 0x01, 0x40);
		can_write_frame(devaddr2, 0x62, data, 0x01, 0x40);	
	}
	else if(devaddr1 == 0x02)
	{	
		can_write_frame(devaddr1, 0x62, data1, 0x01, 0x40);
		can_write_frame(devaddr2, 0x62, data1, 0x01, 0x40);
	}
}
void addr_LED5_reverse_On(uint8_t devaddr1, uint8_t devaddr2)
{
	uint16_t data[1] = {0xFF},data1[1] = {0x80}; 
	
	if(devaddr1 == 0x01)
	{	
		can_write_frame(devaddr1, 0x63, data, 0x01, 0x40);
		can_write_frame(devaddr2, 0x63, data, 0x01, 0x40);	
	}
	else if(devaddr1 == 0x02)
	{	
		can_write_frame(devaddr1, 0x62, data1, 0x01, 0x40);
		can_write_frame(devaddr2, 0x62, data1, 0x01, 0x40);
	}
}
void addr_LED6_reverse_On(uint8_t devaddr1, uint8_t devaddr2)
{
	uint16_t data[1] = {0xFE},data1[1] = {0xFF}; 
	
	if(devaddr1 == 0x01)
	{	
		can_write_frame(devaddr1, 0x63, data, 0x01, 0x40);
		can_write_frame(devaddr2, 0x63, data, 0x01, 0x40);	
	}
	else if(devaddr1 == 0x02)
	{	
		can_write_frame(devaddr1, 0x63, data1, 0x01, 0x40);
		can_write_frame(devaddr2, 0x63, data1, 0x01, 0x40);
	}
}
void addr_LED7_reverse_On(uint8_t devaddr1, uint8_t devaddr2)
{
	uint16_t data[1] = {0xFC},data1[1] = {0xFE}; 
	
	if(devaddr1 == 0x01)
	{	
		can_write_frame(devaddr1, 0x63, data, 0x01, 0x40);
		can_write_frame(devaddr2, 0x63, data, 0x01, 0x40);	
	}
	else if(devaddr1 == 0x02)
	{	
		can_write_frame(devaddr1, 0x63, data1, 0x01, 0x40);
		can_write_frame(devaddr2, 0x63, data1, 0x01, 0x40);
	}
}
void addr_LED8_reverse_On(uint8_t devaddr1, uint8_t devaddr2)
{
	uint16_t data[1] = {0xF8},data1[1] = {0xFC}; 
	
	if(devaddr1 == 0x01)
	{	
		can_write_frame(devaddr1, 0x63, data, 0x01, 0x40);
		can_write_frame(devaddr2, 0x63, data, 0x01, 0x40);	
	}
	else if(devaddr1 == 0x02)
	{	
		can_write_frame(devaddr1, 0x63, data1, 0x01, 0x40);
		can_write_frame(devaddr2, 0x63, data1, 0x01, 0x40);
	}
}
void addr_LED9_reverse_On(uint8_t devaddr1, uint8_t devaddr2)
{	
	uint16_t data[1] = {0xF0},data1[1] = {0xF8}; 
	
	if(devaddr1 == 0x01)
	{	
		can_write_frame(devaddr1, 0x63, data, 0x01, 0x40);
		can_write_frame(devaddr2, 0x63, data, 0x01, 0x40);	
	}
	else if(devaddr1 == 0x02)
	{	
		can_write_frame(devaddr1, 0x63, data1, 0x01, 0x40);
		can_write_frame(devaddr2, 0x63, data1, 0x01, 0x40);
	}
}
void addr_LED10_reverse_On(uint8_t devaddr1, uint8_t devaddr2)
{	
	uint16_t data[1] = {0xE0},data1[1] = {0xF0}; 
	
	if(devaddr1 == 0x01)
	{	
		can_write_frame(devaddr1, 0x63, data, 0x01, 0x40);
		can_write_frame(devaddr2, 0x63, data, 0x01, 0x40);	
	}
	else if(devaddr1 == 0x02)
	{	
		can_write_frame(devaddr1, 0x63, data1, 0x01, 0x40);
		can_write_frame(devaddr2, 0x63, data1, 0x01, 0x40);
	}
}
void addr_LED11_reverse_On(uint8_t devaddr1, uint8_t devaddr2)
{	
	uint16_t data[1] = {0xC0},data1[1] = {0xE0}; 
	
	if(devaddr1 == 0x01)
	{	
		can_write_frame(devaddr1, 0x63, data, 0x01, 0x40);
		can_write_frame(devaddr2, 0x63, data, 0x01, 0x40);	
	}
	else if(devaddr1 == 0x02)
	{	
		can_write_frame(devaddr1, 0x63, data1, 0x01, 0x40);
		can_write_frame(devaddr2, 0x63, data1, 0x01, 0x40);
	}
}
void addr_LED12_reverse_On(uint8_t devaddr1, uint8_t devaddr2)
{	
	uint16_t data[1] = {0x80},data1[1] = {0xC0}; 
	
	if(devaddr1 == 0x01)
	{	
		can_write_frame(devaddr1, 0x63, data, 0x01, 0x40);
		can_write_frame(devaddr2, 0x63, data, 0x01, 0x40);	
	}
	else if(devaddr1 == 0x02)
	{	
		can_write_frame(devaddr1, 0x63, data1, 0x01, 0x40);
		can_write_frame(devaddr2, 0x63, data1, 0x01, 0x40);
	}
}
void addr_LED13_reverse_On(uint8_t devaddr1, uint8_t devaddr2)
{	
	uint16_t data[1] = {0x80}; 
	
	if(devaddr1 == 0x02)
	{	
		can_write_frame(devaddr1, 0x63, data, 0x01, 0x40);
		can_write_frame(devaddr2, 0x63, data, 0x01, 0x40);
	}
}

void addr_LED1_reverse_Off(uint8_t devaddr1, uint8_t devaddr2)
{	
	uint16_t data[1] = {0x0}; 
	
	if(devaddr1 == 0x01)
	{	
		can_write_frame(devaddr1, 0x62, data, 0x01, 0x40);
		can_write_frame(devaddr2, 0x62, data, 0x01, 0x40);	
	}
	else if(devaddr1 == 0x02)
	{	
		can_write_frame(devaddr1, 0x62, data, 0x01, 0x40);
		can_write_frame(devaddr2, 0x62, data, 0x01, 0x40);
	}
}
void addr_LED2_reverse_Off(uint8_t devaddr1, uint8_t devaddr2)
{
	uint16_t data[1] = {0x10},data1[1] = {0x08}; 
	
	if(devaddr1 == 0x01)
	{	
		can_write_frame(devaddr1, 0x62, data, 0x01, 0x40);
		can_write_frame(devaddr2, 0x62, data, 0x01, 0x40);	
	}
	else if(devaddr1 == 0x02)
	{	
		can_write_frame(devaddr1, 0x62, data1, 0x01, 0x40);
		can_write_frame(devaddr2, 0x62, data1, 0x01, 0x40);
	}
}
void addr_LED3_reverse_Off(uint8_t devaddr1, uint8_t devaddr2)
{
	uint16_t data[1] = {0x30},data1[1] = {0x18}; 
	
	if(devaddr1 == 0x01)
	{	
		can_write_frame(devaddr1, 0x62, data, 0x01, 0x40);
		can_write_frame(devaddr2, 0x62, data, 0x01, 0x40);	
	}
	else if(devaddr1 == 0x02)
	{	
		can_write_frame(devaddr1, 0x62, data1, 0x01, 0x40);
		can_write_frame(devaddr2, 0x62, data1, 0x01, 0x40);
	}
}
void addr_LED4_reverse_Off(uint8_t devaddr1, uint8_t devaddr2)
{
	uint16_t data[1] = {0x70},data1[1] = {0x38}; 
	
	if(devaddr1 == 0x01)
	{	
		can_write_frame(devaddr1, 0x62, data, 0x01, 0x40);
		can_write_frame(devaddr2, 0x62, data, 0x01, 0x40);	
	}
	else if(devaddr1 == 0x02)
	{	
		can_write_frame(devaddr1, 0x62, data1, 0x01, 0x40);
		can_write_frame(devaddr2, 0x62, data1, 0x01, 0x40);
	}
}
void addr_LED5_reverse_Off(uint8_t devaddr1, uint8_t devaddr2)
{
	uint16_t data[1] = {0x0},data1[1] = {0x78}; 
	
	if(devaddr1 == 0x01)
	{	
		can_write_frame(devaddr1, 0x63, data, 0x01, 0x40);
		can_write_frame(devaddr2, 0x63, data, 0x01, 0x40);	
	}
	else if(devaddr1 == 0x02)
	{	
		can_write_frame(devaddr1, 0x62, data1, 0x01, 0x40);
		can_write_frame(devaddr2, 0x62, data1, 0x01, 0x40);
	}
}
void addr_LED6_reverse_Off(uint8_t devaddr1, uint8_t devaddr2)
{
	uint16_t data[1] = {0x01},data1[1] = {0x0}; 
	
	if(devaddr1 == 0x01)
	{	
		can_write_frame(devaddr1, 0x63, data, 0x01, 0x40);
		can_write_frame(devaddr2, 0x63, data, 0x01, 0x40);	
	}
	else if(devaddr1 == 0x02)
	{	
		can_write_frame(devaddr1, 0x63, data1, 0x01, 0x40);
		can_write_frame(devaddr2, 0x63, data1, 0x01, 0x40);
	}
}
void addr_LED7_reverse_Off(uint8_t devaddr1, uint8_t devaddr2)
{
	uint16_t data[1] = {0x03},data1[1] = {0x01}; 
	
	if(devaddr1 == 0x01)
	{	
		can_write_frame(devaddr1, 0x63, data, 0x01, 0x40);
		can_write_frame(devaddr2, 0x63, data, 0x01, 0x40);	
	}
	else if(devaddr1 == 0x02)
	{	
		can_write_frame(devaddr1, 0x63, data1, 0x01, 0x40);
		can_write_frame(devaddr2, 0x63, data1, 0x01, 0x40);
	}
}
void addr_LED8_reverse_Off(uint8_t devaddr1, uint8_t devaddr2)
{
	uint16_t data[1] = {0x07},data1[1] = {0x03}; 
	
	if(devaddr1 == 0x01)
	{	
		can_write_frame(devaddr1, 0x63, data, 0x01, 0x40);
		can_write_frame(devaddr2, 0x63, data, 0x01, 0x40);	
	}
	else if(devaddr1 == 0x02)
	{	
		can_write_frame(devaddr1, 0x63, data1, 0x01, 0x40);
		can_write_frame(devaddr2, 0x63, data1, 0x01, 0x40);
	}
}
void addr_LED9_reverse_Off(uint8_t devaddr1, uint8_t devaddr2)
{
	uint16_t data[1] = {0x0F},data1[1] = {0x07}; 
	
	if(devaddr1 == 0x01)
	{	
		can_write_frame(devaddr1, 0x63, data, 0x01, 0x40);
		can_write_frame(devaddr2, 0x63, data, 0x01, 0x40);	
	}
	else if(devaddr1 == 0x02)
	{	
		can_write_frame(devaddr1, 0x63, data1, 0x01, 0x40);
		can_write_frame(devaddr2, 0x63, data1, 0x01, 0x40);
	}
}
void addr_LED10_reverse_Off(uint8_t devaddr1, uint8_t devaddr2)
{
	uint16_t data[1] = {0x1F},data1[1] = {0x0F}; 
	
	if(devaddr1 == 0x01)
	{	
		can_write_frame(devaddr1, 0x63, data, 0x01, 0x40);
		can_write_frame(devaddr2, 0x63, data, 0x01, 0x40);	
	}
	else if(devaddr1 == 0x02)
	{	
		can_write_frame(devaddr1, 0x63, data1, 0x01, 0x40);
		can_write_frame(devaddr2, 0x63, data1, 0x01, 0x40);
	}
}
void addr_LED11_reverse_Off(uint8_t devaddr1, uint8_t devaddr2)
{
	uint16_t data[1] = {0x3F},data1[1] = {0x1F}; 
	
	if(devaddr1 == 0x01)
	{	
		can_write_frame(devaddr1, 0x63, data, 0x01, 0x40);
		can_write_frame(devaddr2, 0x63, data, 0x01, 0x40);	
	}
	else if(devaddr1 == 0x02)
	{	
		can_write_frame(devaddr1, 0x63, data1, 0x01, 0x40);
		can_write_frame(devaddr2, 0x63, data1, 0x01, 0x40);
	}
}
void addr_LED12_reverse_Off(uint8_t devaddr1, uint8_t devaddr2)
{
	uint16_t data[1] = {0x07F},data1[1] = {0x3F}; 
	
	if(devaddr1 == 0x01)
	{	
		can_write_frame(devaddr1, 0x63, data, 0x01, 0x40);
		can_write_frame(devaddr2, 0x63, data, 0x01, 0x40);	
	}
	else if(devaddr1 == 0x02)
	{	
		can_write_frame(devaddr1, 0x63, data1, 0x01, 0x40);
		can_write_frame(devaddr2, 0x63, data1, 0x01, 0x40);
	}
}
void addr_LED13_reverse_Off(uint8_t devaddr1, uint8_t devaddr2)
{
	uint16_t data[1] = {0x7F}; 
	
	if(devaddr1 == 0x02)
	{	
		can_write_frame(devaddr1, 0x63, data, 0x01, 0x40);
		can_write_frame(devaddr2, 0x63, data, 0x01, 0x40);
	}
}

void All_Led_On(uint8_t devaddr1, uint8_t devaddr2,uint16_t delaytimes)
{
	addr_LED1_On(devaddr1,devaddr2);
	DELAY_milliseconds(delaytimes);
	addr_LED2_On(devaddr1,devaddr2);
	DELAY_milliseconds(delaytimes);
	addr_LED3_On(devaddr1,devaddr2);	
	DELAY_milliseconds(delaytimes);
	addr_LED4_On(devaddr1,devaddr2);	
	DELAY_milliseconds(delaytimes);
	addr_LED5_On(devaddr1,devaddr2);
	DELAY_milliseconds(delaytimes);
	addr_LED6_On(devaddr1,devaddr2);	
	DELAY_milliseconds(delaytimes);
	addr_LED7_On(devaddr1,devaddr2);	
	DELAY_milliseconds(delaytimes);
	addr_LED8_On(devaddr1,devaddr2);
	DELAY_milliseconds(delaytimes);
	addr_LED9_On(devaddr1,devaddr2);
	DELAY_milliseconds(delaytimes);
	addr_LED10_On(devaddr1,devaddr2);
	DELAY_milliseconds(delaytimes);
	addr_LED11_On(devaddr1,devaddr2);
	DELAY_milliseconds(delaytimes);
	addr_LED12_On(devaddr1,devaddr2);
	DELAY_milliseconds(delaytimes);
	
	if(devaddr1 == 0x02)//�������delay�ķ���
	{
		addr_LED13_On(devaddr1,devaddr2);
		DELAY_milliseconds(delaytimes);
	}
}

void All_Led_Reverse_On(uint8_t devaddr1, uint8_t devaddr2,uint16_t delaytimes)
{
	if(devaddr1 == 0x02)//�������delay�ķ���
	{
		addr_LED13_reverse_On(devaddr1,devaddr2);
		DELAY_milliseconds(delaytimes);
	}
	addr_LED12_reverse_On(devaddr1,devaddr2);
	DELAY_milliseconds(delaytimes);
	addr_LED11_reverse_On(devaddr1,devaddr2);
	DELAY_milliseconds(delaytimes);
	addr_LED10_reverse_On(devaddr1,devaddr2);
	DELAY_milliseconds(delaytimes);
	addr_LED9_reverse_On(devaddr1,devaddr2);
	DELAY_milliseconds(delaytimes);
	addr_LED8_reverse_On(devaddr1,devaddr2);
	DELAY_milliseconds(delaytimes);
	addr_LED7_reverse_On(devaddr1,devaddr2);
	DELAY_milliseconds(delaytimes);
	addr_LED6_reverse_On(devaddr1,devaddr2);	
	DELAY_milliseconds(delaytimes);
	addr_LED5_reverse_On(devaddr1,devaddr2);	
	DELAY_milliseconds(delaytimes);
	addr_LED4_reverse_On(devaddr1,devaddr2);
	DELAY_milliseconds(delaytimes);
	addr_LED3_reverse_On(devaddr1,devaddr2);	
	DELAY_milliseconds(delaytimes);
	addr_LED2_reverse_On(devaddr1,devaddr2);	
	DELAY_milliseconds(delaytimes);
	addr_LED1_reverse_On(devaddr1,devaddr2);
	DELAY_milliseconds(delaytimes);
}

void All_Led_Reverse_Off(uint8_t devaddr1, uint8_t devaddr2,uint16_t delaytimes)
{
	if(devaddr1 == 0x02)//�������delay�ķ���
	{
		addr_LED13_reverse_Off(devaddr1,devaddr2);
		DELAY_milliseconds(delaytimes);
	}
	addr_LED12_reverse_Off(devaddr1,devaddr2);
	DELAY_milliseconds(delaytimes);
	addr_LED11_reverse_Off(devaddr1,devaddr2);
	DELAY_milliseconds(delaytimes);
	addr_LED10_reverse_Off(devaddr1,devaddr2);
	DELAY_milliseconds(delaytimes);
	addr_LED9_reverse_Off(devaddr1,devaddr2);
	DELAY_milliseconds(delaytimes);
	addr_LED8_reverse_Off(devaddr1,devaddr2);
	DELAY_milliseconds(delaytimes);
	addr_LED7_reverse_Off(devaddr1,devaddr2);
	DELAY_milliseconds(delaytimes);
	addr_LED6_reverse_Off(devaddr1,devaddr2);	
	DELAY_milliseconds(delaytimes);
	addr_LED5_reverse_Off(devaddr1,devaddr2);	
	DELAY_milliseconds(delaytimes);
	addr_LED4_reverse_Off(devaddr1,devaddr2);
	DELAY_milliseconds(delaytimes);
	addr_LED3_reverse_Off(devaddr1,devaddr2);	
	DELAY_milliseconds(delaytimes);
	addr_LED2_reverse_Off(devaddr1,devaddr2);	
	DELAY_milliseconds(delaytimes);
	addr_LED1_reverse_Off(devaddr1,devaddr2);
	DELAY_milliseconds(delaytimes);
}

void UnLock_processing(void )
{
	uint16_t data[1],data1[1] = {0x3FF};
	if(Over_85_LED_off_flag == false)
	{
		Unlock_run_flag = 1;
		LED_OFF();
		DELAY_milliseconds(796);  //����800ms
		
		All_Led_On(0x01,0x03,55);
		All_Led_On(0x02,0x04,15);//��ˮ���м���������ˮ����1�Σ����������죬Լ1�룩
		DELAY_milliseconds(2000); //����2S����
		if(Lock_flag == true)
		{
			return;
		}
		/*����Լ1.5��*/
		for(data[0] =0x3FF;data[0]>0x200;data[0]=data[0]-0xA) 
		{
			can_write_frame(0x00, 0x7c, data, 0x01, 0x40);
			DELAY_milliseconds(7);
		}
		for(data[0] =0x200;data[0]>0x30;data[0]=data[0]-0x5)
		{
			can_write_frame(0x00, 0x7c, data, 0x01, 0x40);
			DELAY_milliseconds(7);
		}
		if(Lock_flag == true)
		{
			return;
		}
		/*����Լ1.5��*/
		for(data[0] =0x3;data[0]<0x200;data[0]=data[0]+0x5)
		{
			can_write_frame(0x00, 0x7c, data, 0x01, 0x40);
			DELAY_milliseconds(7);
		}
		for(data[0] =0x200;data[0]<0x3FF;data[0]=data[0]+0xA)
		{
			can_write_frame(0x00, 0x7c, data, 0x01, 0x40);
			DELAY_milliseconds(6);
		}
		if(Lock_flag == true)
		{
			return;
		}
		/*����Լ1.5��*/
		for(data[0] =0x3FF;data[0]>0x200;data[0]=data[0]-0xA)
		{
			can_write_frame(0x00, 0x7c, data, 0x01, 0x40);
			DELAY_milliseconds(7);
		}
		for(data[0] =0x200;data[0]>0x30;data[0]=data[0]-0x5)
		{
			can_write_frame(0x00, 0x7c, data, 0x01, 0x40);
			DELAY_milliseconds(7);
		}
		LED_OFF();
		
		can_write_frame(0x00, 0x7c, data1, 0x01, 0x40);    //all channel PWM setting

		Unlock_run_flag = 0;
	}
}

void Lock_processing(void )
{
	uint16_t data[1],data1[1] = {0x3FF},data2[1] = {0x0};
	if(Over_85_LED_off_flag == false)
	{
		if(Unlock_run_flag == 1)	//�ڽ��������н��������
		{	
			LED_OFF();		
			can_write_frame(0x00, 0x7c, data1, 0x01, 0x40);    //all channel PWM setting
			DELAY_milliseconds(1000);  //����1000ms
			Unlock_run_flag = 0;
		}
		can_write_frame(0x00, 0x7c, data2, 0x01, 0x40);
		LED_ON();
		
		//��դ�ƽ�����Լ0.8�룩
		for(data[0] =0x3;data[0]<0x200;data[0]=data[0]+0x5)
		{
			can_write_frame(0x00, 0x7c, data, 0x01, 0x40);
			DELAY_milliseconds(2);
		}
		for(data[0] =0x200;data[0]<0x3FF;data[0]=data[0]+0xA)
		{
			can_write_frame(0x00, 0x7c, data, 0x01, 0x40);
			DELAY_milliseconds(2);
		}	
		DELAY_milliseconds(2000); //����Լ2��
		All_Led_Reverse_Off(0x02,0x04,15);
		All_Led_Reverse_Off(0x01,0x03,55);//��դ����ˮ�����ൽ�м����1�Σ��ӿ쵽����Լ1�룩
		
		LED_OFF();	
	}
}

void APP_charging(void )
{
	if(Over_85_LED_off_flag == false)//((delay_flag == false)&&(Over_85_LED_off_flag == false))
	{
		LED_OFF();

		All_Led_On(0x01,0x03,63);
		All_Led_On(0x02,0x04,23);//��ˮ���м���������ˮ����1�Σ�������Լ1.2�룩����Ҫ���Ϸ������ʱ��

		LED_OFF();

		//delay_flag = true;
		//delay_cont = 300;
		DELAY_milliseconds(1500);//��դ������Ϩ�� (����Լ1.5��)������ѭ��
	}
}

void APP_charge_complete(void )
{
	if(Over_85_LED_off_flag == false)
	{
		LED_ON();//����
	}
}

void APP_charge_error(void )
{
	if(Over_85_LED_off_flag == false)
	{
		LED_ON();		
		DELAY_milliseconds(92);
		LED_OFF();
		DELAY_milliseconds(92);
	}
}
void APP_charge_to_power(void )
{
	if(Over_85_LED_off_flag == false)//((delay_flag == false)&&(Over_85_LED_off_flag == false))
	{
		LED_OFF();

		All_Led_Reverse_On(0x02,0x04,23);
		All_Led_Reverse_On(0x01,0x03,63);//��ˮ���������м���ˮ����������Լ1.2�룩

		LED_OFF();

		//delay_flag = true;
		//delay_cont = 300;

		DELAY_milliseconds(1500);//��դ������Ϩ�� (����Լ1.5��)������ѭ��
	}
}
//ADC ��ֵ��0��65535������ɵ�ѹ��V= ADC /(1023+1)*VDD
void AdcPro(void)
{	
	uint16_t data1[1] = {0x1A9},data2[1] = {0x258},data3[1] = {0x2EE},data4[1] = {0x19A},data5[1] = {0x240},data6[1] = {0x29E};
	uint16_t data7[1] = {0x17C},data8[1] = {0x21C},data9[1] = {0x271},data10[1] = {0x154},data11[1] = {0x1E0},data12[1] = {0x226};
	uint16_t data13[1] = {0x12C},data14[1] = {0x1A4},data15[1] = {0x1DB},data16[1] = {0x104},data17[1] = {0x168},data18[1] = {0x190};
	uint16_t data19[1] = {0x104},data20[1] = {0x12C},data21[1] = {0x177},data22[1] = {0x3FF},data[1]= {0x0};
	uint16_t Left_Temp_Value,Left_Vol_Value,Right_Vol_Value,DC_LTemp_Value,DC_RTemp_Value;

	Left_Temp_Value = ADC_GetConversion(ADC_Left_Temp);

	Left_Vol_Value = ADC_GetConversion(ADC_Left_Vol);   //normal:599
	
	Right_Vol_Value = ADC_GetConversion(ADC_Right_Vol);	//normal:606

	DC_LTemp_Value = ADC_GetConversion(ADC_DC_LTemp);	
    
	DC_RTemp_Value = ADC_GetConversion(ADC_DC_RTemp);

	if((Left_Temp_Value > 278)&&(DC_LTemp_Value >538 )&&(DC_RTemp_Value > 452)) //60��������������
	{
		Normal_temp_flag = true;
		Over_62_flag = false;
		Over_65_flag = false;
		Over_70_flag = false;
		Over_75_flag = false;
		Over_80_flag = false;
		Over_84_flag = false;
		Over_85_flag = false;
	}
	else if(((Left_Temp_Value >269 )&&(Left_Temp_Value <278)) ||((DC_LTemp_Value > 519)&&(DC_LTemp_Value < 538)) ||((DC_RTemp_Value > 439)&&(DC_RTemp_Value <452 ))) //62���ʱ������������½�
	{
		Normal_temp_flag = false;
		Over_62_flag = true;
		Over_65_flag = false;
		Over_70_flag = false;
		Over_75_flag = false;
		Over_80_flag = false;
		Over_84_flag = false;
		Over_85_flag = false;
	}
	else if(((Left_Temp_Value >256 )&&(Left_Temp_Value <269)) ||((DC_LTemp_Value > 496)&&(DC_LTemp_Value < 519)) ||((DC_RTemp_Value > 420)&&(DC_RTemp_Value <439 ))) //65���ʱ������������½�
	{
		Normal_temp_flag = false;
		Over_62_flag = false;
		Over_65_flag = true;
		Over_70_flag = false;
		Over_75_flag = false;
		Over_80_flag = false;
		Over_84_flag = false;
		Over_85_flag = false;
	}
	else if(((Left_Temp_Value >234 )&&(Left_Temp_Value <256)) ||((DC_LTemp_Value > 453)&&(DC_LTemp_Value < 496)) ||((DC_RTemp_Value > 390)&&(DC_RTemp_Value <420 ))) //70���ʱ������������½�
	{
		Normal_temp_flag = false;
		Over_62_flag = false;
		Over_65_flag = false;
		Over_70_flag = true;
		Over_75_flag = false;
		Over_80_flag = false;
		Over_84_flag = false;
		Over_85_flag = false;
	}
	else if(((Left_Temp_Value >212 )&&(Left_Temp_Value <234)) ||((DC_LTemp_Value > 411)&&(DC_LTemp_Value < 453)) ||((DC_RTemp_Value > 358)&&(DC_RTemp_Value <390 ))) //75���ʱ������������½�
	{
		Normal_temp_flag = false;
		Over_62_flag = false;
		Over_65_flag = false;
		Over_70_flag = false;
		Over_75_flag = true;
		Over_80_flag = false;
		Over_84_flag = false;
		Over_85_flag = false;
	}
	else if(((Left_Temp_Value >190 )&&(Left_Temp_Value <212)) ||((DC_LTemp_Value > 368)&&(DC_LTemp_Value < 411)) ||((DC_RTemp_Value > 327)&&(DC_RTemp_Value <358 ))) //80���ʱ������������½�
	{
		Normal_temp_flag = false;
		Over_62_flag = false;
		Over_65_flag = false;
		Over_70_flag = false;
		Over_75_flag = false;
		Over_80_flag = true;
		Over_84_flag = false;
		Over_85_flag = false;
	}
	else if(((Left_Temp_Value >173 )&&(Left_Temp_Value <190)) ||((DC_LTemp_Value > 334)&&(DC_LTemp_Value < 368)) ||((DC_RTemp_Value > 302)&&(DC_RTemp_Value <327 ))) //84���ʱ������������½�
	{
		Normal_temp_flag = false;
		Over_62_flag = false;
		Over_65_flag = false;
		Over_70_flag = false;
		Over_75_flag = false;
		Over_80_flag = false;
		Over_84_flag = true;
		Over_85_flag = false;
	}
	else if((Left_Temp_Value <168 )||(DC_LTemp_Value <326 )||(DC_RTemp_Value <296 )) //85���ʱ�򲻹���
	{
		Normal_temp_flag = false;
		Over_62_flag = false;
		Over_65_flag = false;
		Over_70_flag = false;
		Over_75_flag = false;
		Over_80_flag = false;
		Over_84_flag = false;
		Over_85_flag = true;		
	}
	
	if(Normal_temp_flag == true)
	{
		if(Over_60_write_flag == true)           //ֻ�д�60���������½��µ�ʱ�򣬲Ż�run������������ʼ��ʱ�Ѿ����õ���
		{
			if(Current_select_flag == 0x01)
			{
				can_write_frame(0x00, 0x7d, data1, 0x01, 0x40);   //all channel Current setting  42.5ma
			}
			else if(Current_select_flag == 0x02)
			{
				can_write_frame(0x00, 0x7d, data2, 0x01, 0x40);   //all channel Current setting  60ma
			}
			else if(Current_select_flag == 0x03)
			{
				can_write_frame(0x00, 0x7d, data3, 0x01, 0x40);   //all channel Current setting  75ma
			}			
			Over_60_write_flag = false;
		}
	}
	
	if(Over_62_flag == true)
	{
		if(Over_60_write_flag == false)
		{
			if(Current_select_flag == 0x01)
			{
				can_write_frame(0x00, 0x7d, data4, 0x01, 0x40);   //all channel Current setting  42.5ma
			}
			else if(Current_select_flag == 0x02)
			{
				can_write_frame(0x00, 0x7d, data5, 0x01, 0x40);   //all channel Current setting  60ma
			}
			else if(Current_select_flag == 0x03)
			{
				can_write_frame(0x00, 0x7d, data6, 0x01, 0x40);   //all channel Current setting  75ma
			}	
			Over_60_write_flag = true;
		}
	}
	if(Over_65_flag == true)
	{
    	if(Current_select_flag == 0x01)
	   	{
			can_write_frame(0x00, 0x7d, data7, 0x01, 0x40);   //all channel Current setting  
	   	}
		else if(Current_select_flag == 0x02)
	   	{
			can_write_frame(0x00, 0x7d, data8, 0x01, 0x40);   //all channel Current setting  
	   	}
		else if(Current_select_flag == 0x03)
		{
			can_write_frame(0x00, 0x7d, data9, 0x01, 0x40);   //all channel Current setting  
		}
	}
	if(Over_70_flag == true)
	{
    	if(Current_select_flag == 0x01)
	   	{
			can_write_frame(0x00, 0x7d, data10, 0x01, 0x40);   //all channel Current setting  
	   	}
		else if(Current_select_flag == 0x02)
	   	{
			can_write_frame(0x00, 0x7d, data11, 0x01, 0x40);   //all channel Current setting  
	   	}
		else if(Current_select_flag == 0x03)
		{
			can_write_frame(0x00, 0x7d, data12, 0x01, 0x40);   //all channel Current setting  
		}
	}
	if(Over_75_flag == true)
	{
   		if(Over_85_LED_off_flag == true)
		{
			APP_Initialize();

			can_write_frame(0x00, 0x7c, data22, 0x01, 0x40);    //all channel PWM setting
			can_write_frame(0x00, 0x62, data, 0x01, 0x40);
			can_write_frame(0x00, 0x63, data, 0x01, 0x40);	 //�õ��Ȳ�����Ȼ��дPWM��current�Ĵ���
			Over_85_LED_off_flag = false;
	    } 	

		if(Current_select_flag == 0x01)
	   	{
			can_write_frame(0x00, 0x7d, data13, 0x01, 0x40);   //all channel Current setting  
	   	}
		else if(Current_select_flag == 0x02)
	   	{
			can_write_frame(0x00, 0x7d, data14, 0x01, 0x40);   //all channel Current setting  
	   	}
		else if(Current_select_flag == 0x03)
		{
			can_write_frame(0x00, 0x7d, data15, 0x01, 0x40);   //all channel Current setting  
		}
	}
	if(Over_80_flag == true)
	{
    	if(Current_select_flag == 0x01)
	   	{
			can_write_frame(0x00, 0x7d, data16, 0x01, 0x40);   //all channel Current setting 
	   	}
		else if(Current_select_flag == 0x02)
	   	{
			can_write_frame(0x00, 0x7d, data17, 0x01, 0x40);   //all channel Current setting  
	   	}
		else if(Current_select_flag == 0x03)
		{
			can_write_frame(0x00, 0x7d, data18, 0x01, 0x40);   //all channel Current setting  
		}
	}
	if(Over_84_flag == true)
	{		
		if(Current_select_flag == 0x01)
	   	{
			can_write_frame(0x00, 0x7d, data19, 0x01, 0x40);   //all channel Current setting  42.5ma*0.6
	   	}
		else if(Current_select_flag == 0x02)
	   	{
			can_write_frame(0x00, 0x7d, data20, 0x01, 0x40);   //all channel Current setting   60ma/2
	   	}
		else if(Current_select_flag == 0x03)
		{
			can_write_frame(0x00, 0x7d, data21, 0x01, 0x40);   //all channel Current setting  75ma/2
		}
	}
	if(Over_85_flag == true)
	{			
		LED_PWM_EN_SetLow();//LED�µ� 
		Over_85_LED_off_flag =true;
	}

	if(((Left_Vol_Value > 569)&&(Left_Vol_Value < 629)) && ((Right_Vol_Value >576 )&&(Right_Vol_Value <636 ))) //������ѹ+-5%��Χ��Ҫ��LED Power����  569<Left_Vol_Value<629   576< Right_Vol_Value <636
	{
		if(LED_Power_Low_flag == true)
		{
			LED_Power_ok++;
			if(LED_Power_ok >= 100)
			{
				LED_Init();
				LED_Power_ok =0;
				LED_Power_Low_flag = false;
			}
		}
	}
	else
	{
		if(LED_Power_flag == false)
		{
			LED_Power_error++;
			if(LED_Power_error >=100)
			{		
				LED_PWM_EN_SetLow();
				LED_Power_error =0;
				LED_Power_Low_flag = true;
				LED_Power_flag = true;
			}
		}
	}
	
	if(LED_Power_flag == true)
	{	
		LED_Power_Low++;
		if(LED_Power_Low == 10000)
		{
			APP_Initialize();
			LED_Power_Low = 0;			
			LED_Power_flag = false;
		}
	}
}

/*void Delay_function(void)
{
	if(delay_flag ==true)
	{
		delay_cont--;
		if(delay_cont ==0)
		{
			delay_flag = false;
		}
	}
}*/

void LED_Error_function(void)
{
	uint16_t res[5];
	uint8_t r;
	r=can_read_frame(0x00, 0xb8, res, 0x01, 0x40); //LED0~7ͨ����·״̬
	if (r==0x01)
	{
		if((((res[0]&0xff)<<7)==0x01) ||(((res[0]&0x7f)<<6)==0x01) ||(((res[0]&0x3f)<<5)==0x01) ||(((res[0]&0x1f)<<4)==0x01) ||(((res[0]&0xf)<<3)==0x01) ||(((res[0]&0x7)<<2)==0x01) ||(((res[0]&0x3)<<1)==0x01) ||((res[0]&0x1)==0x01))
		{
			LED_OFF();
		}
	}

}

void Timer1MS(void)
{
	TmrFlags.tmr1ms_f = 0u;

	Signal1_flag = Signal1_GetValue(); 
	if(Signal1_flag == false)
	{
		if(Signal1_cont<=45)
		{
			Signal1_cont++;
		}
	}
	else
	{
		Signal1_cont = 0;
	}
	
	Signal2_flag = Signal2_GetValue();
	if(Signal2_flag == false)
	{
		if(Signal2_cont<=45)
		{
			Signal2_cont++;
		}
	}
	else
	{
		Signal2_cont = 0;	
	}
	
	Signal3_flag = Signal3_GetValue();
	if(Signal3_flag == false)
	{
		if(Signal3_cont<=45)
		{
			Signal3_cont++;
		}
	}
	else
	{
		Signal3_cont = 0;		
	}
}

void Timer2MS(void)
{
	TmrFlags.tmr2ms_f = 0u;

	AdcPro();
}

void Timer5MS(void)
{
	TmrFlags.tmr5ms_f = 0u;
	//Delay_function();
	//LED_Error_function();
}

void Timer2500MS(void)
{
	TmrFlags.tmr2500ms_f = 0u;

	Wake_detect_flag = Wake_detect_GetValue();//wake ����⣬��ȡ���ŵĵ�ǰ״̬��
	if(Wake_detect_flag == true)
	{
		if(Wake_detect_cont<=2)
		{
			Wake_detect_cont++;
		}
	}
	else
	{
		Wake_detect_cont = 0;
	}
		
	if((Wake_detect_cont >2)&&(Welcome_detect_cont > 2))	//wake�ź�high����5s��welcome�ź�high����6s
	{
		MCU_Vol_SetLow();//MCU�ϵ�
	}
}
void Timer3000MS(void)
{
	TmrFlags.tmr3000ms_f = 0u;
	
	Welcome_detect_flag = Welcome_detect_GetValue(); //welcome �����
	if(Welcome_detect_flag == true)
	{
		if(Welcome_detect_cont<=2)
		{
			Welcome_detect_cont++;
		}
	}
	else
 	{
		Welcome_detect_cont = 0;
 	}
}

void Timer_Control(void)
{
	if(TmrFlags.tmr1ms_f)
	{
		Timer1MS(); 
	}
    if(TmrFlags.tmr2ms_f) 
	{
		Timer2MS();
	}
    if(TmrFlags.tmr5ms_f)
	{
		Timer5MS();
	}
    if(TmrFlags.tmr2500ms_f) 
	{
		Timer2500MS();
	}
	if(TmrFlags.tmr3000ms_f) 
	{
		Timer3000MS();
	}
}

/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */
void APP_Tasks ( void )
{
	if(Init_LED_flag == false)
	{	
		APP_Initialize();//����ϵ����������
		LED_Init();
		Init_LED_flag = true;
	}

	Timer_Control();
	
	//4�ֳ��״̬�£����յ�ӭ��ģʽʱ������ӭ�����ٻص����״̬
	if((UnLock_flag == false)&&(Lock_flag == false))
	{
		if((Signal1_cont == 0)&&(Signal2_cont >=45 )&&(Signal3_cont == 0)) 
		{	
			APP_charging();
		}
		else if((Signal1_cont >= 45)&&(Signal2_cont >=45 )&&(Signal3_cont == 0))
		{
			APP_charge_complete();
		}
		else if((Signal1_cont >= 45)&&(Signal2_cont == 0 )&&(Signal3_cont == 0))
		{
			APP_charge_error();
		}
		else if((Signal1_cont == 0)&&(Signal2_cont == 0 )&&(Signal3_cont >= 45))
		{
			APP_charge_to_power();
		}
		else
		{
			LED_OFF();
		}
	}
	if(UnLock_flag == true)
	{
		//Fi=0;

		UnLock_processing();
		UnLock_flag = false;		
	}
	else if(Lock_flag == true)
	{
		//Fi=0;
		
		Lock_processing();
		Lock_flag = false;				
	}
}

/*******************************************************************************
 End of File
 */
