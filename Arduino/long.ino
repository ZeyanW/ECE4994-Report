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
  Serial.println("RFM69 radio init OK!");

  if (!rf69.setFrequency(RF69_FREQ)) {
    Serial.println("setFrequency failed");
  }

  rf69.setTxPower(16, true);// range from 14-20 for power, 2nd arg must be true for 69HCW  
  
  //FSK, Whitening, bit_rate (RB) = 2kbs, Frequency deviation (FD) = 5kHz.
  if (!rf69.setModemConfig(0)){ //FSK_Rb2Fd5 = 0
	Serial.println("set FSK failed, remain default"); 
  }
  
  pinMode(LED, OUTPUT);
  Serial.print("RFM69 radio @");  Serial.print((int)RF69_FREQ);  Serial.println(" MHz");
}

/************ Radio Loop ***************/

void loop() {
  delay(2000);
  char radiopacket1[20] = "abc123hello";
  Serial.print("Sending "); 
  Serial.println(radiopacket1);
  
  rf69.send((uint8_t *)radiopacket1, strlen(radiopacket1));
  rf69.waitPacketSent();

  delay(500);
  char radiopacket2[20] = "xyz789world";
  Serial.print("Sending "); 
  Serial.println(radiopacket2);
  
  rf69.send((uint8_t *)radiopacket2, strlen(radiopacket2));
  rf69.waitPacketSent();
}
