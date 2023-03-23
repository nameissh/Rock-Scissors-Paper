#include <Servo.h>
Servo ser1, ser2, ser3;
int angle1, angle2, angle3 = -90;
long randNum;

void setup() {
  Serial.begin(115200);
  ser1.attach(13);                             // servo motor
  ser2.attach(10);
  ser3.attach(6);

  randomSeed(analogRead(0));                  // change random function's seed

}

void loop() {
  ser1.write(angle1);
  ser2.write(angle2);
  ser3.write(angle3);

  randNum = random(1, 4);                       // print a random num from 1 to 3
  Serial.println(randNum);
  delay(1000);
  
  if (Serial.available())
  {
    //char str = Serial.read();
    
    if (randNum == 1)
    {
      angle1 = 0;

      Serial.println(str == "가위");
    }

    else if (randNum == 2)
    {
      angle2 = 0;

      Serial.println("바위");
    }

    else if (randNum == 3)
    {
      angle3 = 0;

      Serial.println("보");
    }
  }  
}
