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

#ifndef CAN_PROTOCOL_H
#define CAN_PROTOCOL_H

#include <stdint.h>

extern uint8_t loglevel;

#define CAN_PROTOCOL_NO_ERROR							0//canͨ��û�д���
#define CAN_PROTOCOL_WRITE_ERROR_HEAD_DIFF				1//can д��ʱ ���ͺͽ��յ�ͷ��һ��
#define CAN_PROTOCOL_WRITE_ERROR_NO_RESPONSE			2//can д��ʱ ͨ��û�лظ�
#define CAN_PROTOCOL_WRITE_ERROR_RESPONSE				3//can д��ʱ ͨ��ʱ����Ӧ��(A bus slave device will signal an OKAY response with 0xFC (2 zero-bits), an ERROR response with 0xC0 (6 zero-bits).)
#define CAN_PROTOCOL_WRITE_ERROR_HEAD_DIFF2				4//can д��ʱ ���ͺͽ��յ�ͷ��һ��(��дʱ�еڶ���)
#define CAN_PROTOCOL_WRITE_ERROR_NO_RESPONSE2			5//can д��ʱ ͨ��û�лظ�(��дʱ�еڶ���)
#define CAN_PROTOCOL_WRITE_ERROR_RESPONSE2				6//can д��ʱ ͨ��ʱ����Ӧ��(��дʱ�еڶ���)
#define CAN_PROTOCOL_READ_ERROR_HEAD_DIFF				7//can ��ȡʱ ���ͺͽ��յ�ͷ��һ��
#define CAN_PROTOCOL_READ_ERROR_NO_RESPONSE				8//can ��ȡʱ ͨ��û�лظ�
#define CAN_PROTOCOL_READ_ERROR_RESPONSE				9//can ��ȡʱ ͨ��ʱ����Ӧ��
#define CAN_PROTOCOL_READ_ERROR_RECEIVE_NUM				10//can ��ȡʱ �������ݵ���������
#define CAN_PROTOCOL_READ_ERROR_NO_CRC					11//can ��ȡʱ û�н��յ�CRC
#define CAN_PROTOCOL_READ_ERROR_CRC_FAILED				12//can ��ȡʱ CRCУ��ʧ��

/*---------------------------------------------------------------------*/

 uint8_t can_write_frame(uint8_t devaddr, uint8_t memaddr, uint16_t *data, uint8_t words_per_crc, uint8_t livecnt);

/*---------------------------------------------------------------------*/

 uint8_t can_read_frame(uint8_t devaddr, uint8_t memaddr, uint16_t *data, uint8_t words_per_crc, uint8_t livecnt);

#endif  // CAN_PROTOCOL_H

