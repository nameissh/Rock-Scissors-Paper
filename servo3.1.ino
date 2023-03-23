#include <Servo.h>
Servo ser1, ser2, ser3;
int angle1 = -90;
int angle2 = -90;
int angle3 = -90;
long randNum;
char hand;

void setup() {
  Serial.begin(115200);
  ser1.attach(13);                             // servo motor
  ser2.attach(10);
  ser3.attach(6);

  randomSeed(analogRead(0));                  // change random function's seed
}

void loop() {
  if (Serial.available())
  {
    ser1.write(angle1);
    ser2.write(angle2);
    ser3.write(angle3);

    char str = Serial.read();

    if (str == 'S')
    {
      randNum = random(1, 4);                       // print a random num from 1 to 3
      Serial.println(randNum);
      
      if (randNum == 1)
      {
        angle1 = 0;
        angle2 = -90;
        angle3 = -90;
        Serial.println("가위");    
      }
      
      else if (randNum == 2)
      {
        angle1 = -90;
        angle2 = 0;
        angle3 = -90;
        Serial.println("바위");
      }
      
      else if (randNum == 3)
      {
        angle1 = -90;
        angle2 = -90;
        angle3 = 0;
        Serial.println("보");
      }
    }

    if (str == 'N')
    {
      angle1 = -90;
      angle2 = -90;
      angle3 = -90;      
    }

    if (str == 'B')
    {
      Serial.end();
    }        
  }
}