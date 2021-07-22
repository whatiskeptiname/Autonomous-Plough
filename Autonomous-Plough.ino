#define mA1 12   // A motor
#define mA2 11
#define mB1 10   // B motor
#define mB2 9
#define  trigPin 8
#define  echoPin 7
#define buzzer 5
#include <Servo.h>
Servo servo;

long int dist, duration, input;
void sensor_check()
{
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:

  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.

  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance

  dist = (duration / 2) / 29.1;

  //read tx inputa
  if (Serial.available() > 0)
  {
    input = Serial.read();
  }
  else
  {
    wait();
  }

  Serial.print(dist);
  Serial.print(" cm ");
  Serial.print("data: ");
  Serial.print(input);
  Serial.println();
}

void beep()
{
  tone(buzzer, 900);
  delay(200);
  tone(buzzer, 1000);
  delay(200);
}

void dist_check()
{
  if (dist <= 10)
  {
    wait();
    beep(); 
    servo.write(90);
  }
  else
  {
    noTone(buzzer);
  }
}

void setup()
{
  pinMode(mA1, OUTPUT);
  pinMode(mA2, OUTPUT);
  pinMode(mB1, OUTPUT);
  pinMode(mB2, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  servo.attach(6);
  Serial.begin(9600);
}

void left()
{
  digitalWrite(mA1, LOW);
  digitalWrite(mA2, HIGH);
  digitalWrite(mB1, HIGH);
  digitalWrite(mB2, LOW);
  //servo.write(100);
}
void right()
{
  digitalWrite(mA1, HIGH);
  digitalWrite(mA2, LOW);
  digitalWrite(mB1, LOW);
  digitalWrite(mB2, HIGH);
  //servo.write(100);
}
void backward()
{
  digitalWrite(mA1, HIGH);
  digitalWrite(mA2, LOW);
  digitalWrite(mB1, HIGH);
  digitalWrite(mB2, LOW);
  //servo.write(  100);
}
void forward()
{
  digitalWrite(mA1, LOW);
  digitalWrite(mA2, HIGH);
  digitalWrite(mB1, LOW);
  digitalWrite(mB2, HIGH);
  //servo.write(55);
}
void wait()
{
  digitalWrite(mA1, LOW);
  digitalWrite(mA2, LOW);
  digitalWrite(mB1, LOW);
  digitalWrite(mB2, LOW);
  //servo.write(100);
}

void AI()
{
  /*for (long int i = 1; i <= 50; i++)
    {
    sensor_check();
    dist_check();
    forward();

    if (input == 5)
    {
      break;
    }
    }

    for (long int i = 1; i <= 10; i++)
    {
    sensor_check();
    dist_check();
    right();

    if (input == 5)
    {
      break;
    }
    }

    for (long int i = 1; i <= 5; i++)
    {
    sensor_check();
    dist_check();
    forward();

    if (input == 5)
    {
      break;
    }
    }

    for (long int i = 1; i <= 10; i++)
    {
    sensor_check();
    dist_check();
    right();

    if (input == 5)
    {
      break;
    }
    }
    for (long int i = 1; i <= 50; i++)
    {
    sensor_check();
    dist_check();
    forward();

    if (input == 5)
    {
      break;
    }
    }

    for (long int i = 1; i <= 10; i++)
    {
    sensor_check();
    dist_check();
    left();

    if (input == 5)
    {
      break;
    }
    }


    for (long int i = 1; i <= 5; i++)
    {
    sensor_check();
    dist_check();
    forward();
    }


    for (long int i = 1; i <= 10; i++)
    {
    sensor_check();
    dist_check();
    left();
    }
  */
  forward();
  delay(2000);
  right();
  delay(400);
  forward();
  delay(100);
  right();
  delay(1000);
  forward();
  delay(3000);

}

void loop()
{
  sensor_check();

  servo.write(100);

  if (dist <= 10)
  {
    wait();
    beep();
  }

  else
  {
    noTone(buzzer);

    switch (input)
    {
      case '0':
        wait();
        break;

      case '1':
        forward();
        break;

      case '2':
        right();
        break;

      case '3':
        backward();
        break;

      case '4':
        left();
        break;

      case 'a':
        servo.write(55);
        break;

      case 'b':
        servo.write(100);
        break;

      case '7':
        beep();
        break;

      case '8':
        noTone(buzzer);
        break;

      case '9':
        for (int j = 1; j <= 1; j++)
        {
          AI();
          if (input == 5)
          {
            break;
          }
        }
        break;a

deafult:
        wait();
        break;
    }
  }
}
