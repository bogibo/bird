#include <Servo.h>
Servo servo;

// motor 4-reley logic
#define motorForward1 5
#define motorForward2 6
#define motorBackward1 2
#define motorBackward2 3

#define servoPin 11
#define sensPinStartWings 12
#define sensPinStartBeak 9

int distance = 180; // servo angle
int motorDelayForward = 500; // motorForward work time
int motorDelayBackward = 500; // motorBackward work time
boolean motorWorkLogic = HIGH; // default state for motor off

int sensStartWings, sensStartBeak;

void setup()
{
  pinMode(sensPinStartWings, INPUT);
  pinMode(sensPinStartBeak, INPUT);
  digitalWrite(sensPinStartWings, HIGH);
  digitalWrite(sensPinStartBeak, HIGH);

  pinMode(motorBackward1, OUTPUT);
  pinMode(motorBackward2, OUTPUT);
  pinMode(motorForward1, OUTPUT);
  pinMode(motorForward2, OUTPUT);

  digitalWrite(motorBackward1, motorWorkLogic);
  digitalWrite(motorBackward2, motorWorkLogic);
  digitalWrite(motorForward1, motorWorkLogic);
  digitalWrite(motorForward2, motorWorkLogic);

  servo.attach(servoPin);
}

void checkSens()
{
  sensStartWings = digitalRead(sensPinStartWings);
  sensStartBeak = digitalRead(sensPinStartBeak);
}

void moveBeak(int action)
{
  switch (action)
  {
  case 1: // open beak
    servo.write(distance);
    break;
  case 2: // close beak
    servo.write(0);
    break;
  }
}

void moveWings(int action)
{
  switch (action)
  {
  case 1: // wings Up
    digitalWrite(motorForward1, !motorWorkLogic);
    digitalWrite(motorForward2, !motorWorkLogic);
    delay(motorDelayForward);
    digitalWrite(motorForward1, motorWorkLogic);
    digitalWrite(motorForward2, motorWorkLogic);
    break;
  case 2: // wings Down
    digitalWrite(motorBackward1, !motorWorkLogic);
    digitalWrite(motorBackward1, !motorWorkLogic);
    delay(motorDelayBackward);
    digitalWrite(motorBackward1, motorWorkLogic);
    digitalWrite(motorBackward2, motorWorkLogic);
    break;
  }
}

void loop()
{
  checkSens();
  if (!sensStartWings)
  {
    moveWings(1);
    delay(100);
    moveWings(2);
    delay(100);
  }
  if (!sensStartBeak)
  {
    moveBeak(1);
    delay(200);
    moveBeak(2);
    delay(200);
  }
  delay(50);
}
