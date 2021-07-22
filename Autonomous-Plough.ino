#include <Servo.h> // Servo library
#define mA1 12   // A motor
#define mA2 11
#define mB1 10   // B motor
#define mB2 9
#define trigPin 8 // trigger pin of ultrasonic sensor
#define echoPin 7 // echo pin of ultrasonic sensor
#define buzzer 5 // buzzer pin 


int input; // input form the serial communication (bluetooth device)
int dist; // distance measured by ultrasonic sensor
Servo servo; // Servo object

void get_data()
{ // calculate the distance measured by ultrasonic sensor 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  dist = (duration / 2) / 29.1;
  // get the serial input from the bluetooth device
  if (Serial.available() > 0) input = Serial.read();
  // print the distance and serial data to searial monitor
  Serial.print(dist);
  Serial.print(" cm ");
  Serial.print("data: ");
  Serial.println(input);
}

void beep() // to play tone from buzzer
{
  tone(buzzer, 800); // play 900Hz tone
  delay(200);
  tone(buzzer, 1000);
  delay(200);
  noTone(buzzer);
}

void proximity() // check for obstacle
{
  get_data();
  if (dist <= 10) // if obstacle is within 10 cm
  {
    wait();
    servo.write(100);
    beep(); 
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

  servo.attach(6); // attach servo to pin 6
  Serial.begin(9600); // set the serial communication to 9600 baud
}

void left() // move the robot to the left
{
  digitalWrite(mA1, LOW);
  digitalWrite(mA2, HIGH);
  digitalWrite(mB1, HIGH);
  digitalWrite(mB2, LOW);
  servo.write(100); // lift the plough while turning
}
void right() // move the robot to the right
{
  digitalWrite(mA1, HIGH);
  digitalWrite(mA2, LOW);
  digitalWrite(mB1, LOW);
  digitalWrite(mB2, HIGH);
  servo.write(100); // lift the plough while turning
}
void backward() // move the robot backward
{
  digitalWrite(mA1, HIGH);
  digitalWrite(mA2, LOW);
  digitalWrite(mB1, HIGH);
  digitalWrite(mB2, LOW);
  servo.write(100); // lift the plough while turning
}
void forward() // move the robot forward
{
  digitalWrite(mA1, LOW);
  digitalWrite(mA2, HIGH);
  digitalWrite(mB1, LOW);
  digitalWrite(mB2, HIGH);
  servo.write(55); // put the plough down while moving forward
}
void wait() // stop the bot
{
  digitalWrite(mA1, LOW);
  digitalWrite(mA2, LOW);
  digitalWrite(mB1, LOW);
  digitalWrite(mB2, LOW);
  servo.write(100); // lift the plough if stopped
}

void auto_forward(int f_length) // move the robot forward for a given distance and wait when obstacle is within 10 
{
  for (int j = 0; j < f_length;)
  {
    proximity();
    if (input == 5) break;
    forward();
    delay(100);
    if (dist <10) continue;  // increase j only when the bot is moving
    j++;
  }
}
void auto_mode(int length, int width)
{
  // if length, width, bot_width, turn_delay don't work on the default setting try adding a 
  // factor to increase or decreadse these value before seeding it in the functions

  int turn_delay = 500; // time taken by bot to turn 90 degrees on either direction
  int bot_width = 20; // bot's width in cm
  int width_loop = width/ bot_width; // number of loops to cover the total width of field

  for (int i = 0; i < width_loop; i++)
    {
      // below code makes the bot to complete a loop and come to initial position 3 bot_width far from 
      // the starting point
      auto_forward(length);
      right();
      delay(turn_delay);
      auto_forward(bot_width);
      right();
      delay(turn_delay);
      auto_forward(length);
      left();
      delay(turn_delay);
      auto_forward(bot_width);
      left();
      if (input == 5) break; // break from outer loop
    }
}

void loop() // main loop
{
  get_data(); // get the senosr and serial data
  servo.write(100); // lift the plough

  if (dist <= 10) // dist is taken from global variable (don't do that)
  { // while there is obstacle within 10cm stop and beep
    wait();
    beep();
  }
  else
  {
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
          // length and width values are given directly to function
          // this can be improved by getting it from bluetooth device or wifi enabled devices
          // some improvement to the hardware and code should be done before that.
          auto_mode(100, 100);// dummy value for lenght and width of the field
          break;
      deafult:
        wait();
    }
  }
}
