#include <SPI.h>
#include <RH_RF69.h>

/************ Radio Setup ***************/

#define RF69_FREQ 433.0 //Frequency at 433Mhz

#if defined (__AVR_ATmega328P__)  // Arduino UNO
  #define RFM69_INT     3  // 
  #define RFM69_CS      4  //
  #define RFM69_RST     2  // "A"
  #define LED           13
#endif
RH_RF69 rf69(RFM69_CS, RFM69_INT);

void setup() 
{
  Serial.begin(9600);

  pinMode(LED, OUTPUT);
  pinMode(RFM69_RST, OUTPUT);
  digitalWrite(RFM69_RST, LOW);

  Serial.println("RFM69 Transmit Test!");
  Serial.println();

  // manual reset
  digitalWrite(RFM69_RST, HIGH);
  delay(10);
  digitalWrite(RFM69_RST, LOW);
  delay(10);
  
  if (!rf69.init()) {
    Serial.println("RFM69 radio init failed");
    while (1);
  }
  if (!rf69.setFrequency(RF69_FREQ)) { //frequency at 433Mhz
    Serial.println("setFrequency failed");
  }
  rf69.setTxPower(16, true);// range from 14-20 for power, 2nd arg must be true for 69HCW  
  rf69.setPreambleLength(1);// Preamble length to 1 byte
  
  //FSK, Whitening, bit_rate (RB) = 2kbs, Frequency deviation (FD) = 5kHz.
  if (!rf69.setModemConfig(0)){ //FSK_Rb2Fd5 = 0
	  Serial.println("set FSK failed, remain default"); 
  }
  
  //display frequency
  pinMode(LED, OUTPUT);
  Serial.println("RFM69 radio init OK!");
}

/************ Radio Loop ***************/

void loop() {
  //Send 3 bytes every 2 seconds
  delay(2000);
  uint8_t packet1[3] = {255,170,0};
  Serial.print("Sending test packet\n"); 
  
  if(!rf69.send((uint8_t *)packet1, 3)){
	Serial.print("Sending packet failed");
  }
  rf69.waitPacketSent();
}
