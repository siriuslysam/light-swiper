#include <Arduino.h>
#include <Servo.h>

Servo sweeper;

const int ldr_pin = A1;
const int swpr_pin = 5;

int ldr_val;
int swpr_status;
int mode = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // read photoresistor and servo state
  ldr_val = analogRead(ldr_pin);
  swpr_status = sweeper.attached();
  Serial.println(ldr_val);

  // condition for lights off
  if (ldr_val < 500){
    if (!swpr_status) {
      sweeper.attach(swpr_pin);
    }
    sweeper.write(10);
    delay(2000);
    sweeper.write(180);
    delay(2000);
    mode = 1;
  }

  // condition for lights on
  else
  {
    if (swpr_status) {
      sweeper.write(180);
      sweeper.detach();
    }

    // wait for 20 mins before reading again
    if (mode == 1) {
      delay(1000L*60L*20L);
      mode = 0;
    }
    else
    {
      delay(1000);
    }
  }
}