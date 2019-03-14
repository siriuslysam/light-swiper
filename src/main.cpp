#include <Arduino.h>

const byte ldr_pin = A1;
const byte iled_pin = 5;

int ldr_val;
byte mode = 0;

void setup() {
  Serial.begin(9600);
  pinMode(iled_pin, OUTPUT);
}

void loop() {
  // read photoresistor
  ldr_val = analogRead(ldr_pin);
  Serial.println(ldr_val);

  // condition for lights off
  if (ldr_val < 500){
    digitalWrite(iled_pin, HIGH);
    delay(1000);
    digitalWrite(iled_pin, LOW);
    delay(1000);
    mode = 1;
  }

  // condition for lights on
  else
  {
    if (mode == 1) {

      // wait for 20 mins before reading again
      delay(1000L*60L*20L);
      mode = 0;
    }
    else
    {
      delay(1000);
    }
  }
}
