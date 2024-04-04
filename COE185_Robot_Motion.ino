
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "motor.h"
#include <Arduino.h>

void test_Drive() {

  Serial.println("FORWARDS");  // d2:d4 == high;low

  configure_Motor(left_W, 2.5, high_value);  //d2 high
  configure_Motor(right_W, 2.5, low_value);  //d4 low
  delay(500);

  configure_Motor(left_W, MAX_PWM + 1, low_value);    //d2 low
  configure_Motor(right_W, MAX_PWM + 1, high_value);  //d4 high

  stop();

  Serial.println("BACKWARDS");  // d2:d4 == low;high

  configure_Motor(left_W, 2.5, low_value);    //d2 high
  configure_Motor(right_W, 2.5, high_value);  //d4 low
  delay(500);

  configure_Motor(left_W, MAX_PWM + 1, high_value);  //d2 low
  configure_Motor(right_W, MAX_PWM + 1, low_value);  //d4 high


  stop();


  Serial.println("Rotate Left < 45");  // d2:d4 == low;low

  configure_Motor(left_W, 2.5, low_value);   //d2 high
  configure_Motor(right_W, 2.5, low_value);  //d4 low
  delay(100);
  configure_Motor(left_W, MAX_PWM + 1, high_value);   //d2 high
  configure_Motor(right_W, MAX_PWM + 1, high_value);  //d4 high

  stop();

  Serial.println("Rotate Right < 45");  // d2:d4 == high;high

  configure_Motor(left_W, 2.5, high_value);   //d2 high
  configure_Motor(right_W, 2.5, high_value);  //d4 high
  delay(100);
  configure_Motor(left_W, MAX_PWM + 1, low_value);   //d2 low
  configure_Motor(right_W, MAX_PWM + 1, low_value);  //d4 low

  stop();

  Serial.println("Rotate Left > 45");  // d2:d4 == low;low

  configure_Motor(left_W, 2.5, low_value);   //d2 high
  configure_Motor(right_W, 2.5, low_value);  //d4 low
  delay(300);
  configure_Motor(left_W, MAX_PWM + 1, high_value);   //d2 high
  configure_Motor(right_W, MAX_PWM + 1, high_value);  //d4 high

  stop();

  Serial.println("Rotate Right > 45");  // d2:d4 == high;high

  configure_Motor(left_W, 2.5, high_value);   //d2 high
  configure_Motor(right_W, 2.5, high_value);  //d4 high
  delay(300);
  configure_Motor(left_W, MAX_PWM + 1, low_value);   //d2 low
  configure_Motor(right_W, MAX_PWM + 1, low_value);  //d4 low

  stop();
}

void loop() {
  test_Drive();
}
