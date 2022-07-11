#include <Arduino.h>
#include <RF24.h>

/* channels configuration :
*  white  100
*  blue   102
*  green  104
*  red    106
*  yellow 108
*/
#define channel 100

#define pinCSN 9
#define pinCE 10
RF24 radio(pinCE,pinCSN);

byte dataSent;

void setup() {
  Serial.begin(9600);
  Serial.println("test radio!");

    radio.begin();

  radio.setChannel(channel);
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_1MBPS);

  radio.openWritingPipe(10101);

  radio.stopListening();

}

void loop() {
  delay(2000);
  dataSent = byte(2);
  radio.write(&dataSent,sizeof(dataSent));
  Serial.println(dataSent,BIN);
}