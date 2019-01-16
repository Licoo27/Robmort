/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */
toto
#include <IRremote.h>
#include <Servo.h>
int RECV_PIN = 11;
int pos = 0;
int phase = 1;
Servo myservo;
IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  myservo.attach(8);
  //Serial.begin(9600);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  //Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  //Serial.println("Enabled IRin");
}

void loop() {
  if (irrecv.decode(&results)) 
  {
    if (results.value == 1005677252)
    {
      //Serial.println("BOM");
      phase =0;
      pos=0;
     
    }
    
    irrecv.resume(); // Receive the next value
  }

  //Serial.println(pos);
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
  
