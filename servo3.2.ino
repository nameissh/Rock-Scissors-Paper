#include <Servo.h>
Servo ser1, ser2, ser3;
int angle1 = -90;
int angle2 = -90;
int angle3 = -90;
long randNum;
//char hand;

void setup() {
  Serial.begin(115200);
  ser1.attach(13);                             // servo motor
  ser2.attach(10);
  ser3.attach(6);

  randomSeed(analogRead(0));                  // change random function's seed

  ser1.write(-90);
  ser2.write(-90);
  ser3.write(-90);
}

void loop() {
  if (Serial.available())
  {
    char str = Serial.read();

    if (str == 'S')
    {
      randNum = random(1, 4);                 // print a random num from 1 to 3
      Serial.println(randNum);
      
      if (randNum == 1)
      {
        ser1.write(90);
        Serial.println("가위");    
      }
      
      else if (randNum == 2)
      {
        ser2.write(90);
        Serial.println("바위");
      }
      
      else if (randNum == 3)
      {
        ser3.write(90); 
        Serial.println("보");
      }
    }   
    
    if (str == 'N')
    {
      ser1.write(-90);
      ser2.write(-90);
      ser3.write(-90);      
    }

    if (str == 'B')
    {
      Serial.end();
    }        
  }
}