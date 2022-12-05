#include <Wire.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Accelaration Motor
Adafruit_DCMotor *motor1 = AFMS.getMotor(1);
// Turning Motor
Adafruit_DCMotor *motor2 = AFMS.getMotor(2);

#define fronttrig 3
#define frontecho 2

#define righttrig 6
#define rightecho 7

#define lefttrig 4
#define leftecho 5

const int motor1sp = 150;
const int motor2sp = 200;

const int turnd = 75;

void setup() {
  Serial.begin(9600);
  AFMS.begin();

  Serial.println("Initializing");
  motor1->setSpeed(motor1sp);
  motor1->run(FORWARD);
  motor1->run(RELEASE);
  motor2->setSpeed(motor2sp);
  motor2->run(FORWARD);
  motor2->run(RELEASE);

  char buffer[60];
  sprintf(buffer, "Motor1 Speed Set to %d", motor1sp);
  Serial.println(buffer);
  sprintf(buffer, "Motor2 Speed Set to %d", motor2sp);
  Serial.println(buffer);

  pinMode(fronttrig, OUTPUT);
  pinMode(frontecho, INPUT);

  pinMode(righttrig, OUTPUT);
  pinMode(rightecho, INPUT);

  pinMode(lefttrig, OUTPUT);
  pinMode(leftecho, INPUT);

  Serial.println("All 3 Ultrasonic Sensors Set-Up");
}

int front() {

  long durationfront, cmfront;

  digitalWrite(fronttrig, LOW);
  delayMicroseconds(2);
  digitalWrite(fronttrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(fronttrig,LOW);

  durationfront = pulseIn(frontecho, HIGH);

  cmfront = durationfront / 29 / 2;

  return(cmfront);
}

int right() {

  long durationright, cmright;

  digitalWrite(righttrig, LOW);
  delayMicroseconds(2);
  digitalWrite(righttrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(righttrig,LOW);

  durationright = pulseIn(rightecho, HIGH);

  cmright = durationright / 29 / 2;

  return(cmright);
}

int left() {

  long durationleft, cmleft;

  digitalWrite(lefttrig, LOW);
  delayMicroseconds(2);
  digitalWrite(lefttrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(lefttrig,LOW);

  durationleft = pulseIn(leftecho, HIGH);

  cmleft = durationleft / 29 / 2;

  return(cmleft);
}

void loop() {

  digitalWrite(7,HIGH);

  char buffer[100];
  sprintf(buffer, "(%d),(%d),(%d)", front(), right(), left());
  Serial.println(buffer);
  Serial.println("main body");
  
  bool x = true;
  while (x == true) {
    sprintf(buffer, "(%d),(%d),(%d)", front(), right(), left());
    Serial.println(buffer);
    if (front() > turnd) {
      Serial.println("In the while loop going forward");
      motor1->run(FORWARD);
      delay(1000);
    }

    else {
      motor1->run(RELEASE);
      Serial.println("in the while loop releasing");
      x = false;
    }
  }

  bool y = true;
  while (y == true) {
    if (front() < turnd) {
      sprintf(buffer, "(%d),(%d),(%d)", front(), right(), left());
      Serial.println(buffer);
      if (right() > left()) {
        Serial.println("Start turning right or continuing right");
        motor2->run(FORWARD);
        motor1->run(FORWARD);
        if (front() > turnd) {
          Serial.println("stop turning right");
          motor2->run(RELEASE);
          motor1->run(RELEASE);
          y = false;
        }
      } 

      else if (left() > right()) {
        Serial.println("start turning left or continuing left");
        motor2->run(BACKWARD);
        motor1->run(FORWARD);
        if (front() > turnd) {
        
          motor2->run(RELEASE);
          motor1->run(RELEASE);
          y - false;
        }
      }
    }
  }
}
