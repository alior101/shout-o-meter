/*
 * Blink
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */
#include <Servo.h>
#include "Arduino.h"
int per = 0;
Servo servo;
int trig  = 0;
int cnt=0;
int lastcnt=0;
int silence = 0;

void setup()
{
  // initialize LED digital pin as an output.
  //pinMode(LED_BUILTIN, OUTPUT);
  //digitalWrite(LED_BUILTIN, HIGH);
  pinMode(D7,INPUT);
  Serial.begin(115200);
  servo.attach(14); //D4
  servo.write(20);
}

char buffer[30];

void loop()
{
 
 /* // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_BUILTIN, HIGH);
  // wait for a second
  delay(150);
  // turn the LED off by making the voltage LOW
  digitalWrite(LED_BUILTIN, LOW);
  */

    if (digitalRead(D7) == LOW)
    {
        cnt++;
    }
    else
    {
        silence ++;
    }
    
    if ((silence > 900) && cnt)
    {
        sprintf(buffer, "Clearing...");
        Serial.println(buffer);
        silence = 0;
        cnt = 0;
        per = 10;
        servo.write(per);
    }
    
    if (cnt != lastcnt)
    {
        sprintf(buffer, "cnt is %d ", cnt);
        Serial.println(buffer);
        lastcnt = cnt;
        per++;
        if (per > 180)
        {
            per = 180;
        }
        // do not move the servo for short noises
        if (cnt> 20) trig =1;
    }

    // wait for a second
    delay(1);

    if (trig && (per > 20))
    {
        trig = 0;
        sprintf(buffer, "pwd is %d ", per);
        Serial.println(buffer);
        servo.write(per);
    }
}
