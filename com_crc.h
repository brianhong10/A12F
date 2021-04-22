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

#ifndef COM_CRC_H
#define COM_CRC_H

#include <stdint.h>


/*---------------------------------------------------------------------*/
// frame header CRC6 ...

uint8_t calc_crc6_0x2C(uint8_t data, uint8_t crc);  // for up to 25 bits (3 bytes)


/*---------------------------------------------------------------------*/
// data CRC8 ...

uint8_t calc_crc8_0x97(uint8_t data, uint8_t crc);  // for up to 119 bit (up to 8 data words)
uint8_t calc_crc8_0xA6(uint8_t data, uint8_t crc);  // for up to 247 bit (16 data words)

#endif  // COM_CRC_H

