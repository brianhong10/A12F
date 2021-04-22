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

#ifndef UART_E0_H
#define UART_E0_H

#include <stdint.h>

/*************** UART ***************************/
#define RX_BUFFER_SIZE_USARTE0 50    // for RS232 receive
#define TX_BUFFER_SIZE_USARTE0 50    // for RS232 transmit

#define CAN_3BYTE_HEADER 0x80
#define CAN_4BYTE_HEADER 0x00

extern uint8_t rx_buffer_usarte0[RX_BUFFER_SIZE_USARTE0];
extern uint8_t tx_buffer_usarte0[TX_BUFFER_SIZE_USARTE0];
extern unsigned char tx_rd_index_usarte0;
extern unsigned char rx_rd_index_usarte0;
extern uint8_t rx_counter_usarte0;
extern uint8_t rx_wr_index_usarte0;
extern uint8_t tx_counter_usarte0;


/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
//extern void putchar_usarte0(char c);
extern uint8_t queue_usarte0(uint8_t c);
extern void usarte0_set_counter(uint8_t n);
extern void usarte0_reset_tx(void);
extern uint8_t usarte0_get_tx_buffer_value(void);
extern char getchar_usarte0_bufcheck(uint8_t *filled_buffer);
extern void empty_UARTE_receive(void);
extern void usarte0_reset_rx(void);

#endif /* __UART_E0_H__ */
