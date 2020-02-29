#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";
boolean button_state = 0;
int led_pin = 2;
int servoPickPin = 8;
Servo servoPick;
int servoPickAngle = 0;
boolean last_button_state = 0;

void setup() {
  pinMode(led_pin, OUTPUT);
  //  digitalWrite(led_pin, HIGH);
  Serial.begin(9600);
  servoPick.attach(servoPickPin);
  servoPick.write(0);
  radio.begin();
  radio.openReadingPipe(0, address);   //Setting the address at which we will receive the data
  radio.setPALevel(RF24_PA_MAX);       //You can set this as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.startListening();              //This sets the module as receiver
}
void loop()
{
  if (radio.available())              //Looking for the data.
  {
    char text[32] = "";                 //Saving the incoming data
    //    radio.read(&text, sizeof(text));    //Reading the data
    radio.read(&button_state, sizeof(button_state));    //Reading the data
    if (button_state == LOW && last_button_state == HIGH)
    {
      digitalWrite(led_pin, HIGH);
      Serial.println(text);
      servoPick.write(45);
      delay(150);
      servoPick.write(90);
      delay(150);
    }
    else
    {
      digitalWrite(led_pin, LOW);
      Serial.println(text);
    }
  }
  last_button_state = button_state;
  delay(5);
  
}
