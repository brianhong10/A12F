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

#include <stdio.h>
//#include <stdlib.h>
#include "com_crc.h"

/*---------------------------------------------------------------------*/
// frame header CRC6 ...
uint8_t calc_crc6_0x2C(uint8_t data, uint8_t crc) {

  int n;
  for (n = 0; n < 8; n++) {
    if ((data & 1) ^ (crc & 1)) {
      crc = (crc >> 1) ^ 0x26;  // 0x2C reversed
    } else {
      crc = (crc >> 1);
    }
    data >>= 1;
  }
  return crc;
}


/*---------------------------------------------------------------------*/
// data CRC8 ...

uint8_t calc_crc8_0x97(uint8_t data, uint8_t crc) {

  int n;

//  if (loglevel&0x02) {
//  printf("CRC8_0x97 data    : 0x%04x\r", data);
//  printf("CRC8_0x97 crc in  : 0x%04x\r", crc);
//  }
  for (n = 0; n < 8; n++) {
    if ((data & 1) ^ (crc & 1)) {
      crc = (crc >> 1) ^ 0xF4;  // 0x97 reversed
    } else {
      crc = (crc >> 1);
    }
    data >>= 1;
  }
  return crc;
}


/*---------------------------------------------------------------------*/
uint8_t calc_crc8_0xA6(uint8_t data, uint8_t crc) {

  int n;
  for (n = 0; n < 8; n++) {
    if ((data & 1) ^ (crc & 1)) {
      crc = (crc >> 1) ^ 0xB2;  // 0xA6 reversed
    } else {
      crc = (crc >> 1);
    }
    data >>= 1;
  }
  
  return crc;
}


