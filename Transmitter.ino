#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

// declaring where the toggle switches are connected in Arduino
static const int toggleSwitchlpin = 5;

// declaring where the Handside joystick is connected
int joystick_VRxPin =A1;
int joystick_VRyPin = A2;


RF24 radio(7,8);   // declaring CE and CSN pins
const byte address[] = "node1"; 

void setup() {
 radio.begin();  // initializes the operations of the chip
 radio.openWritingPipe(address);
 radio.setPALevel(RF24_PA_MIN);
 radio.stopListening();  
 
 pinMode(toggleSwitchlpin, INPUT_PULLUP);

 Serial.begin(9600);  

}

struct datapack{
  int joystick_x ;
  int joystick_y ;
  bool toggleSwitchl = 0 ;
};
datapack data;

void loop() {
  data.toggleSwitchl = digitalRead(toggleSwitchlpin);

  data.joystick_x = analogRead(joystick_VRxPin);
  data.joystick_y = analogRead(joystick_VRyPin);

  Serial.print("Data X:"); Serial.println(data.joystick_x);
  Serial.print("Data Y:"); Serial.println(data.joystick_y);
  Serial.print("Toggle left :"); Serial.println(data.toggleSwitchl);

  radio.write(&data, sizeof(data));

}
