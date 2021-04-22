/*                                                                               
 * Demo Code Usage Restrictions:                                                  
 * Elmos Semiconductor AG provides this source code file simply and solely for    
 * IC evaluation purposes in laboratory and this file must not be used for other   
 * purposes or within non laboratory environments. Especially, the use or the     
 * integration in production systems, appliances or other installations is        
 * prohibited.                                                                    
 *                                                                                
 * Disclaimer:                                                                    
 * Elmos Semiconductor AG shall not be liable for any damages arising out of      
 * defects resulting from                                                         
 * (1) delivered hardware or software,                                            
 * (2) non observance of instructions contained in this document, or              
 * (3) misuse, abuse, use under abnormal conditions or alteration by anyone       
 * other than Elmos Semiconductor AG. To the extend permitted by law              
 * Elmos Semiconductor AG hereby expressively disclaims and user expressively     
 * waives any and all warranties of merchantability and of fitness for a          
 * particular purpose, statutory warranty of non-infringement and any other       
 * warranty or product liability that may arise by reason of usage of trade,      
 * custom or course of dealing.                                                   
 */                                                                               

#include <string.h>
#include <stdio.h>
#include "uart_e0.h"
#include "mcc_generated_files/eusart1.h"

// USART_E0 Receiver buffer
uint8_t rx_buffer_usarte0[RX_BUFFER_SIZE_USARTE0];

unsigned char rx_wr_index_usarte0=0,rx_rd_index_usarte0=0;
uint8_t rx_counter_usarte0=0;

// USART0 Transmitter buffer
uint8_t tx_buffer_usarte0[TX_BUFFER_SIZE_USARTE0];

unsigned char tx_wr_index_usarte0=0,tx_rd_index_usarte0=0;
uint8_t tx_counter_usarte0=0;


/*---------------------------------------------------------------------*/
// Receive a character from USARTE0
char getchar_usarte0(void)
{
	char data;

	while (rx_counter_usarte0==0);
	data=rx_buffer_usarte0[rx_rd_index_usarte0++];
	RC1REG =data ;// EUSART Receive Data Register

	if (rx_rd_index_usarte0 == RX_BUFFER_SIZE_USARTE0)
	{
		rx_rd_index_usarte0=0;
	}

	--rx_counter_usarte0;

	return data;
}


/*---------------------------------------------------------------------*/
// Receive a character from USARTE0 extended 
char getchar_usarte0_bufcheck(uint8_t *filled_buffer)
{
	char data;


	if (rx_counter_usarte0 == 0) 
	{
		*filled_buffer=0; 
		return(rx_counter_usarte0);
	}
	else 
	{
		*filled_buffer=1; 
	}
	data=rx_buffer_usarte0[rx_rd_index_usarte0++];
	RC1REG =data ;// EUSART Receive Data Register

	if (rx_rd_index_usarte0 == RX_BUFFER_SIZE_USARTE0) 
	{
		rx_rd_index_usarte0=0;
	}

	--rx_counter_usarte0;

	return data;
}


/*---------------------------------------------------------------------*/
// Write a character to the USARTE0 Transmitter buffer

/*void putchar_usarte0(char c)
{
	while (tx_counter_usarte0 == TX_BUFFER_SIZE_USARTE0); //如果缓冲区满则等待
	
	if (tx_counter_usarte0 )//|| ((USARTE0.STATUS & USART_DREIF_bm)==0))  //如果缓冲区有数据或者UDR不空闲
	{
	   tx_buffer_usarte0[tx_wr_index_usarte0++]=c;  //将数据写入缓冲
	#if TX_BUFFER_SIZE_USARTE0 != 256
	   if (tx_wr_index_usarte0 == TX_BUFFER_SIZE_USARTE0)  //如果已经写满
	   {
	   		tx_wr_index_usarte0=0;   //写指针置0
	   }
	#endif
	   ++tx_counter_usarte0;
	 }
	else       //如果缓冲区没有数据且UDR空闲
	{
			
			SERCOM0->USART.DATA.reg = c;    

	}

}*/



/*---------------------------------------------------------------------*/
// Write only one character to the USARTE0 Transmitter buffer

uint8_t queue_usarte0(uint8_t c)
{
	while (tx_counter_usarte0 == TX_BUFFER_SIZE_USARTE0);

	tx_buffer_usarte0[tx_wr_index_usarte0++]=c;

	if (tx_wr_index_usarte0 == TX_BUFFER_SIZE_USARTE0) 
	{
		tx_wr_index_usarte0=0;
	}

	++tx_counter_usarte0;

	return(tx_counter_usarte0);
}


/*---------------------------------------------------------------------*/
// Set new amount of bytes in tx_buffer_usarte0 to be send in IRQ automatically
void usarte0_set_counter(uint8_t n)
{
  tx_counter_usarte0 = n;
}


/*---------------------------------------------------------------------*/
// Set new amount of bytes in tx_buffer_usarte0 to be send in IRQ automatically
void usarte0_reset_tx(void)
{
  tx_wr_index_usarte0=0,    // index for putchar
  tx_rd_index_usarte0=0,    // index for IRQ interrupt [USARTE0_TXC_vect]
  tx_counter_usarte0=0;     // counter of the amount of bytes to be send
}


/*---------------------------------------------------------------------*/
// Write only one character to the USARTE0 Transmitter buffer
uint8_t usarte0_get_tx_buffer_value(void)
{
  uint8_t val=0x00;
  
  if (tx_counter_usarte0) 
  {
   	--tx_counter_usarte0;  
   	val=tx_buffer_usarte0[tx_rd_index_usarte0++];
   	if (tx_rd_index_usarte0 == TX_BUFFER_SIZE_USARTE0)
	{
		tx_rd_index_usarte0=0;
   	}
  } 
  return (val);
}


/*---------------------------------------------------------------------*/
void empty_UARTE_receive(void)
{

  while (rx_counter_usarte0>0)
  {
  	  getchar_usarte0();
  }
}

