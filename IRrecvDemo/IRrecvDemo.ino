/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>
#include <Servo.h>

//pins to connect the different sensors and laser
#define LASER_PIN 5
#define RECEP_PIN 3
#define RECV_PIN 11
#define SERVO_PIN 8

//useful variables
int pos = 0;
int phase = 1;
int laserTime =0;
int laserSpan = 100;


//servo to move the character on the car
Servo myservo;

//objects to receive the info of the remote controller
IRrecv irrecv(RECV_PIN);
decode_results results;


void setup()
{
  //init the differents objects and pins
  myservo.attach(SERVO_PIN);
  pinMode(LASER_PIN,OUTPUT);
  pinMode(RECEP_PIN,INPUT);
  
  Serial.begin(9600);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");
  digitalWrite(LASER_PIN,LOW);
}

void loop() {
  //if we receive smthing
 if (irrecv.decode(&results)) 
  {
    //print the value of the msg
    Serial.println(results.value);
    //check if the value is the value of a shooting action
    if (results.value == 1005677252 && laserTime < laserSpan/4)
    {
      laserTime = laserSpan;//lauch a counter of a number of loop
    }
    irrecv.resume(); // Receive the next value
  }


  if(laserTime > 0)//if the laser counter is positive
  {//light of the laser to shoot
    if (laserTime <= laserSpan*2/3 && laserTime >= laserSpan/3){
      digitalWrite(LASER_PIN,LOW);
      
    }
    else {
      digitalWrite(LASER_PIN,HIGH);
    }
      
      laserTime--;//discrease the laser counter
  }
  else
  {
    digitalWrite(LASER_PIN,LOW);//shut down the laser
  }


  
  //if we get hit by a laser
  if (digitalRead(RECEP_PIN) == HIGH && phase == 1)
  {
    //print boom
    Serial.println("BOM");
    //create a move with the servo
    phase =0;
    pos=0;
  }
  if(phase == 0 && pos < 90)
  {
    pos++;
  }
  else
  {
    phase = 1;
    if(pos > 0)
    {
      pos--;  
    }
  }
  myservo.write(pos);
  
  delay(10);
}
  
