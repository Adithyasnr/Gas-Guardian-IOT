#define led_pin 13
#define buzzer_pin 7
#define mq5_pin A0
#include <Servo.h>

int servoPin = 9;
int motionStatus = 0;

Servo scaryServo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(mq5_pin, INPUT);
  pinMode(buzzer_pin, OUTPUT);

  scaryServo.attach(servoPin);
  scaryServo.write(0);

  pinMode(led_pin, OUTPUT);

  //Allow 20 seconds for MQ5 sensor to heatup with 5V current
  Serial.println("MQ5 is heating up!");
  delay(20000);
}

void loop() {
  // put your main code here, to run repeatedly:
  int gas_value,  gv ;
  gv = analogRead(A0);
  //gas_value = map(gv,0,1023,0,100);
  Serial.print("MQ5 Value: ");
  Serial.println(gv);

  //Alert when Gas particles per million(PPM) exceeds 250.
  if (gv > 130) 
  {
    digitalWrite(led_pin, HIGH);
    digitalWrite(buzzer_pin, HIGH);
    delay(1000); 
    scaryServo.write(180);                     // wait for a second
  }
  else
  {
    digitalWrite(led_pin, LOW);
    digitalWrite(buzzer_pin, LOW);
    scaryServo.write(0);
  }
 delay(500);
}