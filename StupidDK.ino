/*
    《智能药盒》 By Cinhi Young
    版本 V1.3
*/
#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>
#include "Resource.h"
#include <avr/pgmspace.h>
#include <EEPROM.h>

#define PlayPin 11
#define RecPin 12
#define SPAKER 6
#define OPENER 9
#define COpen true
#define CClose false
#define TOUCH1 4
#define TOUCH2 5

// 生成对象
Servo Opener;
tmElements_t tm;
Adafruit_SSD1306 OLED(4);
// 定义变量

byte AlarmHour[3] = {9, 12, 19};
byte AlarmMin[3] = {30, 20, 30};
bool AlarmEnabled[3] = {true, true, true};
bool cover = CClose;
bool RecLock = false;
bool Taked = false;
bool DoNotRun;
bool stat = false;
bool missed = false;
void Putchar(char id, char xpos, char ypos)
{
  OLED.drawBitmap(xpos, ypos, FontRes[id], 16, 16, 1);
} //s1,08,05
//

bool delays(int duration)
{
  int curr = millis() / 100;
  while (1)
  {
    int noww = millis() / 100;
    if (noww == ((duration * 10) + curr))
    {
      return false;
    }
    if (touch1())
    {
      
      return true;
    }
  }
}

bool delays2(int duration)
{
  int curr = millis() / 100;
  while (1)
  {
    int noww = millis() / 100;
    if (noww == ((duration * 10) + curr))
    {
      return false;
    }
    if (touch2())
    {
      
      return true;
    }
  }
}

void Record() // Finished
{

  if (RecLock)
  {

    OLEDC();
    Putchar(23, 16, 24);
    Putchar(24, 32, 24);
    Putchar(25, 48, 24);
    Putchar(8, 64, 24);
    Putchar(16, 80, 24);
    Putchar(20, 96, 24);
    OLEDOK();
    delay(1500);
    OLEDC();
    return;
  }
  digitalWrite(12, HIGH);
  OLED.setCursor(16, 48);
  int sec = 0;
  for (byte i = 0; i <= 10; i++)
  {
    OLEDC();
    Putchar(17, 24, 8);
    Putchar(19, 40, 8);
    Putchar(8, 56, 8);
    Putchar(16, 72, 8);
    Putchar(9, 64, 48);
    OLED.setCursor(36, 48);
    OLEDP(String(i));
    OLEDOK();
    if (delays2(1))
      {
        digitalWrite(12, LOW);
        digitalWrite(11, LOW);
        sec = i + 1;
       break;
      }
    sec = 11;
  }
    digitalWrite(12, LOW);
  OLEDC();
  Putchar(17, 24, 32);
  Putchar(19, 40, 32);
  Putchar(3, 56, 32);
  Putchar(16, 72, 32);
  OLEDOK();
  digitalWrite(11, HIGH);
  delay(sec * 1000);
  digitalWrite(11, LOW);
  OLEDC();
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
}



void OLEDP(String Inputext) // Finished
{
  OLED.println(Inputext);
}

void OLEDC() // Finished
{
  OLED.clearDisplay();
}

void OLEDOK() // Finished
{
  OLED.display();
}

void OLEDPT() // Finished
{
  if (tm.Minute < 10)
  {
    OLEDP({String(tm.Hour) + ":0" + String(tm.Minute)});
  }
  else
  {
    OLEDP({String(tm.Hour) + ":" + String(tm.Minute)});
  }
}

void OLEDPS(byte alid) // Finished
{
  if (tm.Minute < 10)
  {
    OLEDP({String(AlarmHour[alid]) + ":0" + String(AlarmMin[alid])});
  }
  else
  {
    OLEDP({String(AlarmHour[alid]) + ":" + String(AlarmMin[alid])});
  }
}
bool Arrived() // Finished
{
  for (char i = 0; i <= 2; i++)
  { 
    if(AlarmEnabled[i]) {
    if (tm.Hour == AlarmHour[i])
    {
      if (tm.Minute == AlarmMin[i])
      {

        return true;
      }
      else if (tm.Minute > AlarmMin[i])
      {
        DoNotRun = false;
      }
      else
      {
        return false;
      }
    }
    else
    {
      return false;
    }
  }
  }
}
void SaveSettings() {
  int addr = 0;
  OLEDC();
  Putchar(17,16,24);
  Putchar(19,32,24);
  Putchar(31,48,24);
  Putchar(32,64,24);
  Putchar(12,16,24);
  Putchar(2,16,24);
  OLEDOK();
  for(addr = 0; addr <=2; addr++ ) {
    delay(10);
    EEPROM.write(addr,byte(AlarmHour[addr]));
  }
  delay(400);
  for(addr = 10; addr <=12; addr++ ) {
    delay(10);
    EEPROM.write(addr,byte(AlarmMin[(addr - 10)]));
  }
    for(addr =20; addr <=22; addr++ ) {
    delay(10);
    EEPROM.write(addr,byte(AlarmEnabled[(addr - 20)]));
  }
  delay(100);
}

void ReadSettings() {
  OLEDC();
  Putchar(33,32,32);
  Putchar(34,48,32);
  Putchar(35,64,32);
  Putchar(36,80,32);
  OLEDOK();
    int addr = 0;
  for(addr = 0; addr <=2; addr++ ) {
    delay(10);
    AlarmHour[addr] = EEPROM.read(addr);
  }
  delay(400);
  for(addr = 10; addr <=12; addr++ ) {
    delay(10);
    AlarmMin[(addr -10)] = EEPROM.read(addr);
  }
    for(addr =20; addr <=22; addr++ ) {
    delay(10);
    AlarmEnabled[(addr - 20)] = EEPROM.read(addr);
  }
  delay(100);
}
void AlarmGo()
{
  cover = false;
  CoverControl();
  if (stat)
  {
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    return;
  }
  for (char i = 0; i <= 2; i++)
  {
    if (stat)
    {
      digitalWrite(12, LOW);
      digitalWrite(11, LOW);
        OLEDC();
         for(int i = 0; i<=4;i++) {
        Putchar((26+i),(24+16*(i+1)),24);
      }
      OLEDOK();
      delay(1000);
      stat = false;
      return;
    }
    digitalWrite(PlayPin, HIGH);

    for (byte i = 0; i <= 10; i++)
    {
      OLEDC();
      Putchar(4, 24, 8);
      Putchar(0, 40, 8);
      Putchar(14, 56, 8);
      Putchar(7, 72, 8);
      Putchar(20, 88, 8);
      OLED.setCursor(39, 32);
      OLEDPT();
      OLEDOK();
      if (stat)
      {
        stat = false;
        digitalWrite(12, LOW);
        digitalWrite(11, LOW);
        OLEDC();
         for(int i = 0; i<=4;i++) {
        Putchar((26+i),(24+16*(i+1)),24);
      }
      OLEDOK();
      delay(1000);
        return;
      }
      if (delays(1))
      {
        stat = true;
      }
      else
      {
        stat = false;
      }
    }
    digitalWrite(PlayPin, LOW);
    delay(200);
  }
  if (cover)
  {
    missed = true;
  }
  else
  {
    missed = false;
  }
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
}

void CoverControl() // Finished
{
  OLEDC();
  if (!cover)
  {
    OLEDC();
    for (int i = 0; i <= 3; i++)
    {
      Putchar(ScreenRes[5][i], (16 + (16 * (i + 1))), 32);
    }
    OLEDOK();
    for (int j = 75; j >= 0; j -= 5)
    {
      Opener.write(j);
      delay(30);
    }
    delay(1000);
    cover = true;
    return;
  }
  else if (cover)
  {
    for (int i = 0; i <= 3; i++)
    {
      Putchar(ScreenRes[6][i], (16 + (16 * (i + 1))), 32);
    }
    OLEDOK();
    for (int j = 0;j <= 75; j ++)
    {
      Opener.write(j);
      delay(30);
    }
    Opener.write(75);
    delay(1000);
    cover = false;
    return;
  }
}

void HomeOLED() // Finished
{
  if (tm.Minute < 10)
  {
    if (tm.Second < 10)
    {
      OLEDP({String(tm.Hour) + ":0" + String(tm.Minute) + ":0" + String(tm.Second)});
    }
    else
    {
      OLEDP({String(tm.Hour) + ":0" + String(tm.Minute) + ":" + String(tm.Second)});
    }
  }
  else
  {
    if (tm.Second < 10)
    {
      OLEDP({String(tm.Hour) + ":" + String(tm.Minute) + ":0" + String(tm.Second)});
    }
    else
    {
      OLEDP({String(tm.Hour) + ":" + String(tm.Minute) + ":" + String(tm.Second)});
    }
  }
}

bool touch1() // Finished
{
  if (analogRead(A1) < 350)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool touch2() // Finished
{
  if (analogRead(A2) < 350)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool PromptCommand(char Bt_input[])
{
  byte _ahour, _amin, _aid;
  bool setflag, readflag , enableflag;
  // 处理错误
  if (Bt_input[0] != 'r' && Bt_input[0] != 's' && Bt_input[0] != 'l' && Bt_input[0] != 'o' && Bt_input[0] != 'e')
  {
    Serial.println("Unrecongized format");
    return 0;
  }
  if (Bt_input[0] == 'r')
  {

    readflag = true;
    setflag = false;
    enableflag = false;
  }
  else if (Bt_input[0] == 's')
  {

    setflag = true;
    readflag = false;
enableflag = false;
  }
    else if (Bt_input[0] == 'e')
  {
    setflag = false;
    readflag = false;
    enableflag = true;
  }
  else if (Bt_input[0] == 'l')
  {
    if (RecLock)
    {
      RecLock = false;
    }
    else
    {
      RecLock = true;
    }
  }
   else if (Bt_input[0] == 'o')
  {
 CoverControl();
  }
  if (setflag)
  {
    { //处理错误
      if (Bt_input[2] != ',' || Bt_input[5] != ',')
      {
        Serial.println("Unrecongized format");
        return false;
      }
      if (((Bt_input[1] - 48) > 3) || ((Bt_input[1]) <= 0x30))
      {
        Serial.println("Invalid ID");
        return false;
      }
      if (((Bt_input[3] - 48) > 2) || ((Bt_input[5] - 48) > 5))
      {
        Serial.println("Invalid Time");
        return false;
      }
    }
    //Serial.println("Debug : Set Mode");
    _aid = (Bt_input[1] - 48) - 1;
    _ahour = ((Bt_input[3] - 48) * 10) + (Bt_input[4] - 48);
    _amin = ((Bt_input[6] - 48) * 10) + (Bt_input[7] - 48);
    //Serial.println("Setting...");
    AlarmMin[_aid] = _amin;
    AlarmHour[_aid] = _ahour;
    //Serial.println({ + String(_aid) + "," + String(_ahour) + "\nMinute = " + String(_amin)});

    //Serial.println({String(_aid) + "," + String(AlarmHour[_aid]) + "," + String(AlarmMin[_aid])});
    if (AlarmHour[(_aid)] < 10)
    {
      if (AlarmMin[(_aid)] < 10)
      {
        Serial.println({"0" + String(AlarmHour[(_aid)]) + ",0" + String(AlarmMin[(_aid)])});
      }
      else
      {
        Serial.println({"0" + String(AlarmHour[(_aid)]) + "," + String(AlarmMin[(_aid)])});
      }
    }
    else
    {
      if (AlarmMin[(_aid)] < 10)
      {
        Serial.println({String(AlarmHour[(_aid)]) + ",0" + String(AlarmMin[(_aid)])});
      }
      else
      {
        Serial.println({String(AlarmHour[(_aid)]) + "," + String(AlarmMin[(_aid)])});
      }
    }
    SaveSettings();
    OLEDC();
    Putchar(13, 20, 24);
    Putchar(6, 36, 24);
    Putchar(15, 52, 24);
    Putchar(12, 68, 24);
    Putchar(2, 84, 24);
    Putchar(20, 100, 24);
    OLED.setCursor(32, 48);
    OLEDPS(_aid);
    OLEDOK();
    delay(2000);
    OLEDC();
    return true;
  }
  if (readflag)
  {
    if (Bt_input[1] == 'l')
    {
      Serial.println(RecLock);
      return true;
    }
    else if (((Bt_input[1] - 48) > 3) || ((Bt_input[1]) <= 0x30))
    {
      Serial.println("Invalid ID");
      return false;
    }
    //Serial.println("Debug : Read Mode");
    _aid = (Bt_input[1] - 48);

    if (AlarmHour[(_aid - 1)] < 10)
    {
      if (AlarmMin[(_aid - 1)] < 10)
      {
        Serial.println({"0" + String(AlarmHour[(_aid - 1)]) + ",0" + String(AlarmMin[(_aid - 1)])});
      }
      else
      {
        Serial.println({"0" + String(AlarmHour[(_aid - 1)]) + "," + String(AlarmMin[(_aid - 1)])});
      }
    }
    else
    {
      if (AlarmMin[(_aid - 1)] < 10)
      {
        Serial.println({String(AlarmHour[(_aid - 1)]) + ",0" + String(AlarmMin[(_aid - 1)])});
      }
      else
      {
        Serial.println({String(AlarmHour[(_aid - 1)]) + "," + String(AlarmMin[(_aid - 1)])});
      }
    }
  }
  if(enableflag) {
    if (((Bt_input[1] - 48) > 3) || ((Bt_input[1]) <= 0x30))
    {
      Serial.println("Invalid ID");
      return false;
    }
    _aid = (Bt_input[1] - 48);
    if(AlarmEnabled[(_aid -1)]){
      AlarmEnabled[(_aid -1)] = false;
      Serial.println("Alarm " + String(_aid) + "is now disabled.");
    } else {
      AlarmEnabled[(_aid -1)] = false;
      Serial.println("Alarm " + String(_aid) + "is now enabled.");
    }

  }
}
void HomeScr() // Finished
{
  OLED.clearDisplay();
  for (byte i = 0; i <= 3; i++)
  {
    Putchar(ScreenRes[0][i], (16 + (16 * (i + 1))), 0);
  }
  for (byte i = 0; i <= 3; i++)
  {
    Putchar(ScreenRes[1][i], (16 + (16 * (i + 1))), 24);
  }
  if (RTC.read(tm))
  {
    OLED.setTextSize(2);
    OLED.setCursor(16, 48);
    HomeOLED();
  }
  OLED.display();
}

void setup() // Finished
{
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  Serial.begin(38400);
  OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  OLED.setTextSize(1);
  OLED.setTextColor(WHITE);
  OLED.clearDisplay();
  Opener.attach(OPENER);
  cover = true;
  CoverControl();
  cover = false;
  ReadSettings();
  /*for (int i = 0; i <= 2; i++)
  {
    Serial.println({"ID = " + String(i) + "\nHour = " + String(AlarmHour[i]) + "\nMinute = " + String(AlarmMin[i])});
    delay(250);
  }*/
  DoNotRun = false;
}

void loop() // Finished
{
  if (Serial.available() > 0)
  {
    char SINPUT[9];
    String Test;
    delay(100);
    Test = Serial.readString();
    Test.toCharArray(SINPUT, 9);
    PromptCommand(SINPUT);
    Serial.flush();
  }
  if (Arrived())
  {
    if (DoNotRun == false)
    {
      
      AlarmGo();
      
      DoNotRun = true;
    }
  }
  if (touch1())
  {
    CoverControl();
  }
  if (touch2())
  {
    delay(500);
    Record();
  }
  HomeScr();
  //Serial.println(stat);
}
