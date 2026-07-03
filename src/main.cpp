#include <Arduino.h>
#include <Servo.h>
#include <IRremote.hpp>
#define ENA 9
#define ENB 11
#define IN1 6
#define IN2 4
#define IN3 2
#define IN4 12
#define turret_pin  3
#define trigger_pin 5

Servo turretservo;
Servo triggerservo;


const uint32_t BUTTON_UP = 0xE718FF00;
const uint32_t BUTTON_DOWN = 0xAD52FF00;
const uint32_t BUTTON_LEFT = 0xF708FF00;
const uint32_t BUTTON_RIGHT = 0xA55AFF00;
const uint32_t BUTTON_OK = 0xE31CFF00;
const uint32_t BUTTON_4 = 0xBB44FF00;
const uint32_t BUTTON_6 = 0xBC43FF00;
const uint32_t BUTTON_5 = 0xBF40FF00;

const int irpin = 10;
const int turret_step = 25;
const int trigger_lock = 90;
const int trigger_fire = 0;
const int dl = 2000;

int turret_pos = 175;




void setup() {

  Serial.begin(9600);
  
  turretservo.attach(turret_pin);
  triggerservo.attach(trigger_pin);
  IrReceiver.begin(irpin,ENABLE_LED_FEEDBACK);
  turretservo.write(turret_pos);
  triggerservo.write(trigger_lock);
  pinMode(IN1,OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN4, OUTPUT);
  Serial.println("Tank Ready...");
  
  
}

void forward(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN4, HIGH);
  digitalWrite(IN3, LOW);

  analogWrite(ENA,255);
  analogWrite(ENB,255);
}

void backward(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN4, LOW);
  digitalWrite(IN3, HIGH);

  analogWrite(ENA,255);
  analogWrite(ENB,255);
}
void left(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN4, HIGH);
  digitalWrite(IN3, LOW);

  analogWrite(ENA,255);
  analogWrite(ENB,255);
}
void right(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN4, LOW);
  digitalWrite(IN3, HIGH);

  analogWrite(ENA,255);
  analogWrite(ENB,255);
}
void stop(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN4, LOW);
  digitalWrite(IN3, LOW);

  analogWrite(ENA,0);
  analogWrite(ENB,0);
}
void fire(){
  triggerservo.write(trigger_fire);
  delay(dl);
  triggerservo.write(trigger_lock);
}
void loop() {
  if (!IrReceiver.decode()) {
    return;
   }
  const uint32_t cmd = IrReceiver.decodedIRData.decodedRawData;
  
  Serial.println(cmd, HEX);
 if(cmd == BUTTON_UP){
  Serial.println("motor forward");

  forward();
}

else if(cmd == BUTTON_DOWN){
  Serial.println("motor backward");

  backward();
}
else if(cmd == BUTTON_LEFT){
  Serial.println("motor left");

  left();
}
else if(cmd == BUTTON_RIGHT){
  Serial.println("motor right");

  right();
}

else if(cmd == BUTTON_OK){
  Serial.println("motor stop");

  stop();
}

 
else if(cmd==BUTTON_4){
  turret_pos+=turret_step;
 
  if(turret_pos>180){
    turret_pos=180;
  }
  turretservo.write(turret_pos);
}
else if(cmd==BUTTON_6){
  turret_pos-=turret_step;
  
  if(turret_pos<0){
    turret_pos=0;
  }
  turretservo.write(turret_pos);
}
else if(cmd==BUTTON_5){
 fire();
}
  IrReceiver.resume();
}