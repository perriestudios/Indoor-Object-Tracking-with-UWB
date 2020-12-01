#include <SPI.h>
#include <Wire.h>
#include "DW1000Ranging.h"
#include "DW1000Device.h"

// connection pins
const uint8_t PIN_RST = 9; // reset pin
const uint8_t PIN_IRQ = 2; // irq pin
const uint8_t PIN_SS = 10; // spi select pin

// Update this to be the domain associated with your server.
const String DOMAIN = "your-domain.com";

String z;
char Z[10];

void setup() {
  // Serial is for communication between the computer and the board.
  Wire.begin(8);                /* join i2c bus with address 8 */
  Wire.onRequest(requestEvent); /* register request event */
  Serial.begin(115200);
  // Serial1 is for communication between the board and the wifi module.
//  Serial1.begin(115200);
  delay(1000);
//  Serial1.print("AT+UART_CUR=74880,8,1,0,0\r\n");
  delay(2000);
//  Serial1.begin(74880);
  //init the configuration
  DW1000Ranging.initCommunication(PIN_RST, PIN_SS, PIN_IRQ); //Reset, CS, IRQ pin
  //define the sketch as anchor. It will be great to dynamically change the type of module
  DW1000Ranging.attachNewRange(newRange);
  
  //we start the module as an anchor
  DW1000Ranging.startAsAnchor("1A:1A:1A:1A:1A:1A:1A:1A", DW1000.MODE_LONGDATA_RANGE_ACCURACY);
}

int loopCtr = -1;
String request = "";

void loop() {
  byte* addr = DW1000Ranging.getCurrentAddress();

  // If you're having issues, uncommenting this should be useful for debugging.
//  if(Serial1.available() > 0){
//    Serial.write(Serial1.read());
//  }

  if (loopCtr == 0) {
//    Serial1.print("AT+CIPSTART=\"TCP\",\"" + DOMAIN + "\",80\r\n");
      Serial.println("Connect to cloud");
  }

  if (loopCtr == 10000) {
    request = "POST /location?x=" + String(DW1000Ranging.getTagX()) + "&y=" + String(DW1000Ranging.getTagY()) + " HTTP/1.1\r\nHost: " + DOMAIN + "\r\n\r\n\r\n\r\n";
//    Serial1.print("AT+CIPSEND=" + String(request.length()) + "\r\n");
      Serial.print("Request Length : ");
      Serial.print(String(request.length()));
      Serial.println();
      Serial.print("Tag X Co-ordinate : ");
      Serial.print(String(DW1000Ranging.getTagX()));
      Serial.println();
      Serial.print("Tag Y Co-ordinate : ");
      Serial.print(String(DW1000Ranging.getTagY()));
      Serial.println();
      z = String(DW1000Ranging.getTagX()) + "," + String(DW1000Ranging.getTagY());
      z.toCharArray(Z,10);
  }

  if (loopCtr == 20000) {
    // If you're having issues, uncommenting this should be useful for debugging.
//    Serial.print("sending request..." + request);
//    Serial1.print(request);
    loopCtr = -1;
  }

  loopCtr++;
  
  DW1000Ranging.loop();
}

void newRange() {
  // Empty.
}

void requestEvent() {
Wire.write(Z);  /*send string on request */
}
