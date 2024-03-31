
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define LEFT_PWM_PIN DDD5   //DIG5
#define RIGHT_PWM_PIN DDD6  //DIG6

#define LEFT_PIN DDD2   //DIG2
#define RIGHT_PIN DDD4  //DIG4


#define PWM_FREQ 100  // Desired PWM frequency in Hz
#define MAX_PWM 255   // Maximum PWM value


void initMotorDirection() {

  // Set pins as output
  DDRD |= (1 << LEFT_PIN);   //D2
  DDRD |= (1 << RIGHT_PIN);  //D4
}

void initPWMsignal() {

  // Set pins as output
  DDRD |= (1 << LEFT_PWM_PIN);   //D5
  DDRD |= (1 << RIGHT_PWM_PIN);  //D6
}

void init_Timer() {

  // MODE TIMER 8-BIT
  TCCR0A |= (1 << WGM00);
  TCCR0A |= (1 << WGM01);

  // Set prescaler to 1 (no prescaling)
  TCCR0B |= (1 << CS00);

  // // Initial PWM duty cycle (50%)
  // OCR0A = MAX_PWM;
  // OCR0B = MAX_PWM;

  // Clear OC0A and OC0B on compare match, set at BOTTOM
  TCCR0A |= (1 << COM0A1) | (1 << COM0B1);
}

void setup() {
  Serial.begin(9600);
  initMotorDirection();
  initPWMsignal();
  init_Timer();
  // put your setup code here, to run once:
}

void forward() {
  PORTD |= (1 << LEFT_PIN);
  OCR0A = MAX_PWM / 2;
  PORTD &= ~(1 << RIGHT_PIN);
  OCR0B = MAX_PWM / 2;
  // for (int i = 0; i < (MAX_PWM/2); i+= 10){
  //   Serial.println(i);
  //   OCR0A = i;
  //   OCR0B = i;
  // }
  // OCR0A = MAX_PWM;
  // PORTD &= ~(1 << RIGHT_PIN);
  // OCR0B = MAX_PWM;
  delay(500);
}

void backward() {
  PORTD &= ~(1 << LEFT_PIN);
  OCR0A = MAX_PWM / 2;
  PORTD |= (1 << RIGHT_PIN);
  OCR0B = MAX_PWM / 2;
  // for (int i = 0; i < (MAX_PWM/2); i+= 10){
  //   Serial.println(i);
  //   OCR0A = i;
  //   OCR0B = i;
  // }
  delay(500);
}

void rotate_left(int degree) {
  PORTD &= ~(1 << LEFT_PIN);
  OCR0A = MAX_PWM / 2;
  PORTD &= ~(1 << RIGHT_PIN);
  OCR0B = MAX_PWM / 2;
  // for (int i = 0; i < (MAX_PWM/2); i+= 10){
  //   OCR0A = i;
  //   OCR0B = i;
  // }
  delay(degree);
}

void rotate_right(int degree) {
  PORTD |= (1 << LEFT_PIN);
  OCR0A = MAX_PWM / 2;
  PORTD |= (1 << RIGHT_PIN);
  OCR0B = MAX_PWM / 2;
  // for (int i = 0; i < (MAX_PWM/2); i+= 10){
  //   OCR0A = i;
  //   OCR0B = i;
  // }
  delay(degree);
}

void calculate_rotation(int degree) {
  PORTD |= (1 << LEFT_PIN);
  // OCR0A = MAX_PWM;
  PORTD |= (1 << RIGHT_PIN);
  // OCR0B = MAX_PWM;
  for (int i = 0; i < (MAX_PWM / 2); i++) {
    OCR0A = i;
    OCR0B = i;
  }
  delay(degree);
}

void stop() {
  OCR0A = 0;
  OCR0B = 0;
  delay(500);
}

/* approximately 1 rotation or 360 = 1200ms
  360/1200 = 180deg/600ms
          =90deg/300ms
          =45deg/150ms
          =15deg/50ms
*/

void loop() {
  // put your main code here, to run repeatedly:

  // Move forward
  forward();
  Serial.println("forward");

  stop();
  backward();
  Serial.println("backward");
  stop();


  Serial.println("left  <45");

  rotate_left(100);
  stop();

  delay(1000);

  Serial.println("center");
  rotate_right(100);
  stop();
  delay(2000);

  Serial.println("right <45");

  rotate_right(100);
  stop();
  delay(1000);

  Serial.println("center");
  rotate_left(100);
  stop();
  delay(1000);

  // greater than 45

  Serial.println("left  >45");

  rotate_left(300);
  stop();

  delay(1000);

  Serial.println("center");
  rotate_right(300);
  stop();
  delay(2000);

  Serial.println("right >45");

  rotate_right(300);
  stop();
  delay(1000);

  Serial.println("center >45");
  rotate_left(300);
  stop();
  delay(1000);


  // rotate_right(100);

  // rotate_left(1000);

  // rotate_left(500);
  // // 360
  // calculate_rotation(1200);
  // stop();
  // delay(2000);

  //  // 180
  // calculate_rotation(600);
  // stop();
  // delay(2000);

  //  // 90
  // calculate_rotation(300);
  // stop();
  // delay(2000);

  //    // 45
  // calculate_rotation(150);
  // stop();
  // delay(2000);

  //      // 15
  // calculate_rotation(50);
  // stop();
  // delay(2000);
}
