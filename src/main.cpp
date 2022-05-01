#include <Arduino.h>
#include <RF24.h>

#define channel 100
#define motorPower 120

#define pinCE 10
#define pinCSN 9

// port motor
#define pinEN12 3
#define pinIN1 2
#define pinIN2 4

// starboard motor
#define pinEN34 5
#define pinIN3 6
#define pinIN4 7

RF24 radio(pinCE,pinCSN);

byte dataReceived;
int leftSignal, rightSignal;

String str ="";

void setup() {
  Serial.begin(9600);
  Serial.println("Hello Boat!");
  
  pinMode(pinEN12,OUTPUT);
  pinMode(pinIN1,OUTPUT);
  pinMode(pinIN2,OUTPUT);

  pinMode(pinEN34,OUTPUT);
  pinMode(pinIN3,OUTPUT);
  pinMode(pinIN4,OUTPUT);

  digitalWrite(pinIN1,LOW);
  digitalWrite(pinIN2,LOW);    
  
  radio.begin();

  radio.setChannel(channel);
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_1MBPS);

  radio.openReadingPipe(0,10101);

  radio.startListening();
}

void loop() {
  if (radio.available()) {
    radio.read(&dataReceived,sizeof(dataReceived));
    Serial.print("Message reçu : ");
    Serial.println(dataReceived,BIN);
    leftSignal = dataReceived >> 4;
    rightSignal = dataReceived & byte(15);
    Serial.println(str+"LeftSignal : "+leftSignal+", rightSignal : "+rightSignal);
    
    switch (leftSignal)
    {
    case 0:
      digitalWrite(pinIN1,HIGH);
      digitalWrite(pinIN2,LOW);
      analogWrite(pinEN12,motorPower);
      break;
    case 1:
      digitalWrite(pinIN1,LOW);
      digitalWrite(pinIN2,LOW);
      analogWrite(pinEN12,0);
      break;
    case 2:
      digitalWrite(pinIN1,LOW);
      digitalWrite(pinIN2,HIGH);
      analogWrite(pinEN12,motorPower);
      break;
    default:
      break;
    }
    switch (rightSignal)
    {
    case 0:
      digitalWrite(pinIN3,HIGH);
      digitalWrite(pinIN4,LOW);
      analogWrite(pinEN34,motorPower);
      break;
    case 1:
      digitalWrite(pinIN3,LOW);
      digitalWrite(pinIN4,LOW);
      analogWrite(pinEN34,0);
      break;
    case 2:
      digitalWrite(pinIN3,LOW);
      digitalWrite(pinIN4,HIGH);
      analogWrite(pinEN34,motorPower);
      default:
      break;
    }
  }
}