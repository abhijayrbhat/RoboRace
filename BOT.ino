#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

#define ENA 2
#define ENB 7
#define IN1 3
#define IN2 4
#define IN3 5
#define IN4 6
#define MOTOR_SPEED_1 255
#define MOTOR_SPEED_2 100
#define MOTOR_SPEED_3 150


RF24 radio(9,10);
const byte address[] = "node1";

void setup() {
  radio.begin();
  radio.openReadingPipe(0,address);
  radio.startListening();

  Serial.begin(9600);

  
  
}

struct datapack{
  int joystick1_x ;
  int joystick1_y ;
  int joystick2_x ;
  int joystick2_y ;
  int toggle_r;
  int toggle_l;
};
datapack data;

void loop() {
  while(radio.available()){
    radio.read(&data, sizeof(data));
    
    int a;
    a = data.toggle_l ;
    Serial.println(data.joystick1_x);
    Serial.println(data.joystick1_y);
    Serial.println(data.joystick2_x);
    Serial.println(data.joystick2_y);
    Serial.println(data.toggle_r);
    Serial.println(data.toggle_l);
    
      //high rpm

      analogWrite(ENA, MOTOR_SPEED_1);
      analogWrite(ENB, MOTOR_SPEED_1);
      //data X
      if (data.joystick2_y > 550) {
       moveForward();
      Serial.println("FORWARD");
      }

      //data X
      if (data.joystick2_y < 400) {
      moveBackward();
      Serial.println("BACKWARD");
      }

      //data Y
      if (data.joystick1_x > 550 ) {
      turnRight();
      Serial.println("TURN RIGHT");
      }

      //data Y
      if (data.joystick1_x < 400 ) {
      turnLeft();
      Serial.println("TURN LEFT");
      }
 
      if (data.joystick1_x < 550 && data.joystick1_x > 400 && data.joystick2_y < 550 && data.joystick2_y > 400) {
      stop();
      Serial.println("STOP");
      }
  }

}

void stop(){
  
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
}
void turnLeft(){
 

  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}
void turnRight() {
 

  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}

// Function to turn the robot right
void moveBackward() {
  
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

}

// Function to turn the robot left
void moveForward() {
 
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

