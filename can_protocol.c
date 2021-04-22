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
#include <stdlib.h>
#include "com_crc.h"
#include "uart_e0.h"
#include "can_protocol.h"
#include "app.h"
#include "mcc_generated_files/eusart1.h"
#include "mcc_generated_files/delay.h"

#define VALID       1
#define INVALID     0

/*
TXD=0 => CANH=3.5V     CANL=1.5V
TXD=1 => CANH=2.5V     CANL=2.5V
*/
/* Dafault CAN Config :
250k Baud CAN Baudrate
Device Address is 0x00
3 Byte Header

ansonsten sieht die Default-UART-Konfiguration (solange noch keine anderen Werte im OTP stehen) wie folgt aus:
  uart_config.bf.format      = 0;
  uart_config.bf.turn_around = 2;
  uart_config.bf.parity      = 0;
  uart_config.bf.stop        = 0;
  uart_config.bf.break_sel   = 1;
  uart_config.bf.auto_baud   = 1;
  uart_config.bf.invert_rxd  = 0;
  uart_config.bf.invert_txd  = 0;
*/
#if    0//是否启动调试，注意: loglevel 不可以有 0x80 这个位
uint8_t loglevel = 0x7f;
#else
uint8_t loglevel = 0x40;
#endif

/*---------------------------------------------------------------------*/
// return the amount of 0 in a byte
static uint8_t count_0Bits(uint8_t c) {
  uint8_t zeros=0, i, mask=0x80;
  
  for (i=8;i;i--) {
    if ((c & mask)==0) zeros++;
    mask>>=1;
  }
  return (zeros);
}
        

/*---------------------------------------------------------------------*/
// devaddr = device address
// memaddr = memory address of one 522.48
// data = words buffer, 1..16 words are allowed
// words_per_crc = number of data word to send, can be 1 to 16 datawords, corresponding binary valzue is 0..15
// livecnt = if value <= 63 then use 4 Byte Header and use 6 LSBs for live count value, if >=64 then use 3 Byte Header (live count value is not used)

uint8_t can_write_frame(uint8_t devaddr, uint8_t memaddr, uint16_t *data, uint8_t words_per_crc, uint8_t livecnt)
{
  uint8_t a, b, d, s, di;
  uint32_t wdata;
  uint8_t byte, b1, b2;
  uint8_t crc;
  uint8_t errres;         // error response
  uint8_t rxbuf;          // data byte from UARTE receive buffer
  uint8_t tout;           // timeout counter
  uint8_t txcnt;          // counter value from queue_usarte0(uint8_t c)
  uint8_t txcnt_header;   // number of bytes in tx_buffer to be send for header, normally 3 or 4 bytes
  uint8_t txcnt_data;     // number of bytes in tx_buffer to be send for data array, normally 2 up to 20 bytes
  uint8_t numwords;       // number of 10Bit to be send, values from 0..15 are possible
  uint8_t FourByte_Header;    // if true then 4 Byte Header is used;
  uint8_t dpf[50];        // for storing all send data
 // struct io_descriptor *io;
  uint16_t rate_reg;
  usarte0_reset_tx();      // reset all internal values for TXDE

  numwords = words_per_crc - 1;    // e.g. four 10Bit words to send will end in a binary value of 3 => 1..16 lead to 0..15
  if (numwords > 0x0F) numwords=0x0F;
  
  if (livecnt<64) FourByte_Header=1;     // 4 byte Header
             else FourByte_Header=0;     // 3 Byte Header
  
  //--------------------------------------
  // send frame start header
  // break will be 13 times TBIT 
  di=0;
  byte = 0x00;           // BREAK
  txcnt = queue_usarte0(byte);
  dpf[di++]=byte;

  byte = 0x55;           // SYNC BYTE
  txcnt = queue_usarte0(byte);
  dpf[di++]=byte;
  
  byte = memaddr;        // Memory address ...
  if (FourByte_Header) crc = calc_crc8_0x97(byte, 0xFF);
                  else crc = calc_crc6_0x2C(byte, 0x3F);
  txcnt = queue_usarte0(byte);
  dpf[di++]=byte;

  // Device address + W-Bit and 2 LSBs from words_per_crc
  byte = devaddr&0x1F;                   // 5 Bit LSBs
  byte |= 0x20;                          // set write bit, 1 is write
  if (numwords&0x01) byte |= 0x40;       // Bit6 in byte is Bit0 in numwords
  if (numwords&0x02) byte |= 0x80;       // Bit7 in byte is Bit1 in numwords
  if (FourByte_Header) crc = calc_crc8_0x97(byte, crc);
                  else crc = calc_crc6_0x2C(byte, crc);
  txcnt = queue_usarte0(byte);
  dpf[di++]=byte;

  if (FourByte_Header)
  {    // OK, we have to send 4 Byte header
    byte = 0;
    if (numwords&0x04) byte |= 0x01;       // Bit6 in byte is Bit0 in numwords
    if (numwords&0x08) byte |= 0x02;       // Bit7 in byte is Bit1 in numwords
    byte = byte | ((livecnt<<2)&0xFC);        
    txcnt = queue_usarte0(byte);
    dpf[di++]=byte;

    crc = calc_crc8_0x97(byte, crc);
	byte = crc;//后来加上来的
    txcnt = queue_usarte0(crc);
    dpf[di++]=byte;
  }
  else
  {    // OK, we have to send only 3 Byte header
       // upper 2 Bits from words_per_crc and CRC6  
    byte = 0;
    if (numwords&0x04) byte |= 0x01;       // Bit6 in byte is Bit0 in numwords
    if (numwords&0x08) byte |= 0x02;       // Bit7 in byte is Bit1 in numwords
    crc = calc_crc6_0x2C(byte, crc);       // CRC calculation with 2 upper numwords bits placed in the 2 LSBs from byte to send
    byte = byte | ((crc<<2)&0xFC);        
    txcnt = queue_usarte0(byte);
    dpf[di++]=byte;
  }
  txcnt_header = txcnt;                    // save number of bytes in txbuffer for header

 

  //--------------------------------------
  // calculate data to be send
  // and count the the number of bytes to send
  a = 0;      // index of data array
  b = 0;      // number of initial valid bits = 0
  wdata = 0;  // initial sub-frame wdata is 0
  crc = 0xFF;
  for (d = 0; d < words_per_crc; d++) 
  {
    wdata = wdata | ((uint32_t)data[a]<<b);
    b += 10;

    // send all bytes included in wdata ...
    while (b >= 8)                              // ?????????????????????????????? must be corrected for e.g. 3*10 Bits
//    while (b>0)                               
    {
//      byte = data_8msbs(wdata, b);
      byte = (uint8_t) wdata;     // get 8 LSBs
      wdata = wdata >> 8;
      wdata = wdata & 0x00FFFFFF;
      txcnt = queue_usarte0(byte);
      dpf[di++]=byte;

      if (words_per_crc < 12)  crc = calc_crc8_0x97(byte, crc);
      else crc = calc_crc8_0xA6(byte, crc);
      b -= 8;

    }
    a++;
  }
  if (b)    // are there some ramining bits to send ???
  {
    byte = (uint8_t) wdata;     // get 2 or 4 or 6 remaining bits
    txcnt = queue_usarte0(byte);
    dpf[di++]=byte;

    if (words_per_crc < 12)  crc = calc_crc8_0x97(byte, crc);
                        else crc = calc_crc8_0xA6(byte, crc);
  }  
  txcnt = queue_usarte0(crc);
  dpf[di++]=crc;
  
  txcnt_data = txcnt - txcnt_header;   // save number of bytes in txbuffer for data, either 5 or 6 
  
  
  empty_UARTE_receive();               // clear receive buffer
  DELAY_microseconds(250);                
  
  //--------------------------------------
  // start sending header data, either 3 Byte Header variant or 4 Byte Header Variant
  usarte0_set_counter(txcnt_header);      // Set counter with number of header bytes, 5 or 6 Bytes should be send
  
  /* 76800kBaud *10/13  for 13TBit low */
   b1 = usarte0_get_tx_buffer_value(); 
   b2 = usarte0_get_tx_buffer_value();	   // get 2nd data byte (0x55) to be send and decrement tx_counter_usarte0, now 3 or 4 bytes to be send 	   

   RC1STA = 0x10;// SPEN disabled;
         
   SP1BRGL = 0x67;// Baud Rate = 76800; SP1BRGL 0x52; 
 
   SP1BRGH = 0x00;// Baud Rate = 76800; SP1BRGH 0; 
   
   RC1STA = 0x90; // SPEN enabled;

   EUSART1_Write(b1); // get first data byte (0x00) to be send and decrement tx_counter_usarte0, now 4 or 5 bytes to be send   
	
   //while( !(SERCOM3->USART.INTFLAG.reg & SERCOM_USART_INTFLAG_DRE) );

   DELAY_microseconds(120); //DELAY_microseconds(230);  //根据波特率的不同，delay时间不一样，baud越小，延时越长，等待数据发完
                           // data is transferred from data register in shift register, so check for cleared data register
                                          // makes no sense just wait 13/250000
  /*96000  */

  RC1STA = 0x10;// SPEN disabled;
		
  SP1BRGL = 0x52;// Baud Rate = 96000; SP1BRGL 68; 
  
  SP1BRGH = 0x00;// Baud Rate = 96000; SP1BRGH 0; 
  
  RC1STA = 0x90; // SPEN enabled;

  EUSART1_Write(b2);  // after one byte is send a interrupt will occur and in IRQ routine txcnt_header number bytes 
                                        
  //while( !(SERCOM3->USART.INTFLAG.reg & SERCOM_USART_INTFLAG_DRE) );// will be send automatically with TXDE0
                                             
//  while( !(USARTC0_STATUS & USART_DREIF_bm) ); // Wait until DATA buffer is empty
                                               // OK, byte is transferred in UART shift register and now data register is ready for new data byte to be send
  DELAY_microseconds(120);                                // Wait until last byte + START + PARITY + STOP in shift register is also send

  // In case of logging output all is working fine
  // with no logging output the TXDE receiver buffer has not stored all received data in the RXD buffer 
  // in case of additional 125us for RXDE receive routine all bytes are received that have been send !!!! 
  //delay_us(150);                               // Wait for all received bytes trandferred from RXD data register into rxd buffer array
  
     
  //--------------------------------------
  // 521.21 sends all data back that has been received => all header data has also been received and
  // are in the receive buffer now => read this header buffer and ignore it  
  a=0;
  do {      
    rxbuf = getchar_usarte0_bufcheck(&s);
    if (dpf[a]!=rxbuf) { 
       return(CAN_PROTOCOL_WRITE_ERROR_HEAD_DIFF); }
    a++;
  }
  while ((s==VALID) && (a<txcnt_header));     // exit in case of an empty RXbuffer or all header bytes read
  
  //--------------------------------------
  // read response byte after header
  tout=0;
  do
  {
    errres = getchar_usarte0_bufcheck(&s);
	if (loglevel&0x40) 
	{
		s=VALID; 
		errres=0x3F;

	}
	DELAY_microseconds(5);
    tout++;
  }
  while ((tout<20) && (s==INVALID));    // 25.01.18 changed from tout<15 to tout<20, v1.4.5

  if (s==INVALID)
  {
    return(CAN_PROTOCOL_WRITE_ERROR_NO_RESPONSE);           // NO RESPONSE from CAN device
  }     
  else
  { 
    a = count_0Bits(errres);     // count the number of 0 Bits, 0..4 zero Bits are OKAY response    
  
    if (a>4) return(CAN_PROTOCOL_WRITE_ERROR_RESPONSE);
  }
           
  //--------------------------------------
  // start sending data area
  usarte0_set_counter(txcnt_data);        // set number of data bytes in TX buffer to calculated value
  byte = usarte0_get_tx_buffer_value();   // get first data byte to be send and decrement value of number of transmitted bytes by 1

  EUSART1_Write(tx_buffer_usarte0[2]);

  EUSART1_Write(tx_buffer_usarte0[3]);

  EUSART1_Write(tx_buffer_usarte0[4]);

  DELAY_microseconds(800);

  EUSART1_Write(tx_buffer_usarte0[5]);
  EUSART1_Write(tx_buffer_usarte0[6]);
  EUSART1_Write(tx_buffer_usarte0[7]); 
	//while( !(SERCOM3->USART.INTFLAG.reg & SERCOM_USART_INTFLAG_DRE) );
  DELAY_microseconds(44);                                // Wait until last byte + START + PARITY + STOP in shift register is send
  DELAY_microseconds(200);                               // Wait for all received bytes trandferred from RXD data register into rxd buffer array
  
  DELAY_milliseconds(1);                                 // 25.01.18, v1.4.5
       
   //--------------------------------------
  // 521.31 sends all data back that has been received => all header data has also been received and
  // are in the receive buffer now => read this header buffer and ignore it  

  a=txcnt_header;    // header values are index values in dpf[index] from 0..txcnt_header-1, so first index value for data is txcnt_header
  do {      
    rxbuf = getchar_usarte0_bufcheck(&s);    
    if (dpf[a]!=rxbuf) { 
      return(CAN_PROTOCOL_WRITE_ERROR_HEAD_DIFF2); }
    
    a++;
  }while ((s==VALID) && (a<(txcnt_header+txcnt_data)));     // exit in case of an empty RXbuffer or all data bytes read
  
  DELAY_microseconds(100);               
  
  //--------------------------------------
  // read response byte after header
  tout=0;
  do
  {
    errres = getchar_usarte0_bufcheck(&s);
	if (loglevel&0x40) 
	{
		s=VALID; 
		errres=0x3F;
	}
	DELAY_microseconds(4);
    tout++;
  }
  while ((tout<15) && (s==INVALID));

  if (s==INVALID)
  {

    return(CAN_PROTOCOL_WRITE_ERROR_NO_RESPONSE2);           // NO RESPONSE from CAN device
  }     
  else
  { 
    a = count_0Bits(errres);     // count the number of 0 Bits, 0..4 zero Bits are OKAY response    
   
    if (a>4) return(CAN_PROTOCOL_WRITE_ERROR_RESPONSE2);
  }
  
  return (CAN_PROTOCOL_NO_ERROR);
}

/*---------------------------------------------------------------------*/
/*---------------------------------------------------------------------*/
// 注意，如果 4 Byte Header 要启用的话，需要 otp=0x01 寄存器地址=0xfd ，寄存器位bit0=1，才行(page 29)
uint8_t can_read_frame(uint8_t devaddr, uint8_t memaddr, uint16_t *data, uint8_t words_per_crc, uint8_t livecnt)
{
  uint8_t a, b, s, r, di;
  uint32_t rdata;
  uint8_t byte, b1, b2, amax;
  uint8_t crc;
  uint8_t errres;         // error response
  uint8_t rxbuf;          // data byte from UARTE receive buffer
  uint8_t tout;           // timeout counter
  uint8_t txcnt;          // counter value from queue_usarte0(uint8_t c)
  uint8_t txcnt_header;   // number of bytes in tx_buffer to be send for header, normally 3 or 4 bytes
  uint8_t txcnt_data;     // number of bytes in tx_buffer to be send for data array, normally 2 up to 20 bytes
  uint8_t numwords;       // number of 10Bit to be send, values from 0..15 are possible
  uint8_t FourByte_Header;    // if true then 4 Byte Header is used;
  uint8_t dpf[50];        // for storing read data
  
//  if (loglevel&0x02) {
//  printf("can_read_frame: 0x%04x, %d\r", memaddr, words_per_crc);
//  }

  usarte0_reset_tx();      // reset all internal values for TXDE
  
  numwords = words_per_crc - 1;    // e.g. four 10Bit words to send will end in a binary value of 3 => 1..16 lead to 0..15
  if (numwords > 0x0F) numwords=0x0F;

  if (livecnt<64) FourByte_Header=1;     // 4 byte Header
             else FourByte_Header=0;     // 3 Byte Header
   
  //--------------------------------------
  // send frame start header
  // break will be 13 times TBIT 
  di=0;
  byte = 0x00;           // BREAK
  txcnt = queue_usarte0(byte);
  dpf[di++]=byte;

  byte = 0x55;           // SYNC BYTE
  txcnt = queue_usarte0(byte);
  dpf[di++]=byte;
  
  byte = memaddr;        // Memory address ...
  if (FourByte_Header) crc = calc_crc8_0x97(byte, 0xFF);
                  else crc = calc_crc6_0x2C(byte, 0x3F);
  txcnt = queue_usarte0(byte);
  dpf[di++]=byte;

  // Device address + W-Bit and 2 LSBs from words_per_crc
  byte = devaddr&0x1F;                   // 5 Bit LCBs
  byte &= 0xDF;                          // clear write bit, 0 is read !!!
  if (numwords&0x01) byte |= 0x40;       // Bit6 in byte is Bit0 in numwords
  if (numwords&0x02) byte |= 0x80;       // Bit7 in byte is Bit1 in numwords
  if (FourByte_Header) crc = calc_crc8_0x97(byte, crc);
                  else crc = calc_crc6_0x2C(byte, crc);
  txcnt = queue_usarte0(byte);
  dpf[di++]=byte;

  if (FourByte_Header)
  {    // OK, we have to send 4 Byte header
    byte = 0;
    if (numwords&0x04) byte |= 0x01;       // Bit6 in byte is Bit0 in numwords
    if (numwords&0x08) byte |= 0x02;       // Bit7 in byte is Bit1 in numwords
    byte = byte | ((livecnt<<2)&0xFC);        
    txcnt = queue_usarte0(byte);
    dpf[di++]=byte;

    crc = calc_crc8_0x97(byte, crc);
	byte = crc;//后来加上来的
    txcnt = queue_usarte0(crc);
    dpf[di++]=byte;
  }
  else
  {    // OK, we have to send only 3 Byte header
       // upper 2 Bits from words_per_crc and CRC6  
    byte = 0;
    if (numwords&0x04) byte |= 0x01;       // Bit6 in byte is Bit0 in numwords
    if (numwords&0x08) byte |= 0x02;       // Bit7 in byte is Bit1 in numwords
    crc = calc_crc6_0x2C(byte, crc);       // CRC calculation with 2 upper numwords bits placed in the 2 LSBs from byte to send
    byte = byte | ((crc<<2)&0xFC);        
    txcnt = queue_usarte0(byte);
    dpf[di++]=byte;
  }
  txcnt_header = txcnt;                    // save number of bytes in txbuffer for header

  txcnt_data = 1 + (words_per_crc * 10)/8;  // 1 CRC byte and x number of bytes for holding words_per_crc 10 Bit data   
 
  
  
  empty_UARTE_receive();                  // clear receive buffer
  //delay_us(250);                          // 25.01.18, v1.4.5
               
  
  //--------------------------------------
  // start sending header data, either 3 Byte Header variant or 4 Byte Header Variant
  usarte0_set_counter(txcnt_header);      // Set counter with number of header bytes, 5 or 6 Bytes should be send
  
//#asm("cli")                             // disable interrupt

  /*500kBaud *10/13  for 13TBit low */   
  
  //usart_async_set_baud_rate(&USART_LED,400000);
/***
  USARTE0.BAUDCTRLA=0x4B;
  USARTE0.BAUDCTRLB=((0x09 << USART_BSCALE_gp) & USART_BSCALE_gm) | 0x04;   
***/
   b1 = usarte0_get_tx_buffer_value(); 
   b2 = usarte0_get_tx_buffer_value();	   // get 2nd data byte (0x55) to be send and decrement tx_counter_usarte0, now 3 or 4 bytes to be send 	   
  
   RC1STA = 0x10;// SPEN disabled;
         
   SP1BRGL = 0x67;// Baud Rate = 76800; SP1BRGL 0x52; 
 
   SP1BRGH = 0x00;// Baud Rate = 76800; SP1BRGH 0; 
   
   RC1STA = 0x90; // SPEN enabled;

   EUSART1_Write(b1); // get first data byte (0x00) to be send and decrement tx_counter_usarte0, now 4 or 5 bytes to be send   
	
   //while( !(SERCOM3->USART.INTFLAG.reg & SERCOM_USART_INTFLAG_DRE) );

   DELAY_microseconds(120); //DELAY_microseconds(230);  //根据波特率的不同，delay时间不一样，baud越小，延时越长，等待数据发完
                           // data is transferred from data register in shift register, so check for cleared data register
                                          // makes no sense just wait 13/250000
  /*96000  */

  RC1STA = 0x10;// SPEN disabled;
		
  SP1BRGL = 0x52;// Baud Rate = 96000; SP1BRGL 68; 
  
  SP1BRGH = 0x00;// Baud Rate = 96000; SP1BRGH 0; 
  
  RC1STA = 0x90; // SPEN enabled;

  EUSART1_Write(b2);  // after one byte is send a interrupt will occur and in IRQ routine txcnt_header number bytes 

  // In case of logging output all is working fine
  // with no logging output the TXDE receiver buffer has not stored all received data in the RXD buffer 
  // in case of additional 125us for RXDE receive routine all bytes are received that have been send !!!! 
  DELAY_microseconds(120);                                // Wait for all received bytes trandferred from RXD data register into rxd buffer array
  
     
  //--------------------------------------
  // 521.21 sends all data back that has been received => all header data has also been received and
  // are in the receive buffer now => read this header buffer and ignore it  
  a=0;
  do 
  {      
    rxbuf = getchar_usarte0_bufcheck(&s);
	if (dpf[a]!=rxbuf) 
	{	
      return(CAN_PROTOCOL_READ_ERROR_HEAD_DIFF); 
	}
    a++;
  }
  while ((s==VALID) && (a<txcnt_header));     // exit in case of an empty RXbuffer or all header bytes read
  
  //--------------------------------------
  // read response byte after header
  tout=0;
  do
  {
    errres = getchar_usarte0_bufcheck(&s);
	if (loglevel&0x80) 
	{
		s=VALID; errres=0x3F;

	}
	DELAY_microseconds(4);
    tout++;
  }
  while ((tout<20) && (s==INVALID));    // 25.01.18 changed from tout<15 to tout<20, v1.4.5

  if (s==INVALID)
  {

    return(CAN_PROTOCOL_READ_ERROR_NO_RESPONSE);           // NO RESPONSE from CAN device
  }     
  else
  { 
    a = count_0Bits(errres);     // count the number of 0 Bits, 0..4 zero Bits are OKAY response    

    if (a>4) return(CAN_PROTOCOL_READ_ERROR_RESPONSE);
  }


  DELAY_microseconds(400);                               // Wait for all received bytes trandferred from RXD data register into rxd buffer data array
  DELAY_milliseconds(1);                                 // 25.01.18, v1.4.5

  //--------------------------------------
  // read response data bytes
  crc = 0xFF;
  #if   0
  amax = (words_per_crc*10)/8;//这是原来的数据量计算方式
  #else	//后来加上来的，使用这种计算方式，才能准确计算出数据量大小
  if((words_per_crc*10)%8==0)
	amax = (words_per_crc*10)/8;
  else
	amax = (words_per_crc*10)/8+1;
  #endif
  for (r = 0; r < amax; r++) 
  {
    rxbuf = getchar_usarte0_bufcheck(&s);
    dpf[r]=rxbuf;
    if (words_per_crc < 12)  crc = calc_crc8_0x97(rxbuf, crc);
                        else crc = calc_crc8_0xA6(rxbuf, crc);
    if (s==INVALID) return (CAN_PROTOCOL_READ_ERROR_RECEIVE_NUM);
  }
  
    
  a = 0;      // index for target data array
  b = 0;      // number of initial valid bits = 0
  rdata = 0;  // initial sub-frame rdata is 0
  for (r = 0; r < amax; r++) 
  {
    byte = dpf[r];                         // get data from uart array
    rdata = ((uint32_t)byte<<b) | rdata;   // shift next byte to MSB place, old dara remain in LSB position
    b += 8;                                // count number of bits shifted in
    while (b >= 10)                        // are 10 bits available ?? 
    {
      data[a] = (uint16_t)rdata & 0x03FF; // take 10 bits
      rdata = rdata >> 10;                // shift remaining bits to the right
      rdata = rdata & 0x003FFFFF;        // make sure 0 bits get in
      a++;                                // increment index for target data array
      b -= 10;                            // reduce number of available bits by 10 
    }     
  }

    
  errres = getchar_usarte0_bufcheck(&s);       
  if (s==INVALID) return (CAN_PROTOCOL_READ_ERROR_NO_CRC);
  if (crc != errres) {

	return (CAN_PROTOCOL_READ_ERROR_CRC_FAILED);
  }

  return (CAN_PROTOCOL_NO_ERROR);
}

