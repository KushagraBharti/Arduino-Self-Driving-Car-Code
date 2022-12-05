#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *motor1 = AFMS.getMotor(1);
//Adafruit_DCMotor *motor2 = AFMS.getMotor(3);

// Ultrasonic Sensor Set-Up
#define frontVCC 0
#define fronttrig 1
#define frontecho 2
#define frontGND 3

#define rightVCC 7
#define righttrig 6
#define rightecho 5
#define rightGND 4

#define leftVCC 8
#define lefttrig 9
#define leftecho 10
#define leftGND 11

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  AFMS.begin();  // create with the default frequency 1.6KHz
  // set motor speed, turn them on for a moment then back off
  Serial.println("initializing");  
  motor1->setSpeed(200);
  motor1->run(FORWARD);
  motor1->run(RELEASE);

  // Ultrasonic Sensor Set-Up
  pinMode(fronttrig, OUTPUT);
  pinMode(frontecho, INPUT);

  pinMode(righttrig, OUTPUT);
  pinMode(rightecho, INPUT);

  pinMode(lefttrig, OUTPUT);
  pinMode(leftecho, INPUT);
}

void loop() { 
    Serial.println("forward");
    motor1->run(FORWARD);
    delay(2000);
    motor1->run(RELEASE);
    delay(1000);
    
    Serial.println("backward");
    motor1->run(BACKWARD);
    delay(2000);
    motor1->run(RELEASE);
    delay(1000);
}



 
 
 
 
