/*********************
	Code of Stupid DrugKit Dumb Edition
	Pull Requests is no longer accepted.
	Final Version - See ./README.md
*********************/

#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>
#include "Resource.h"
#include <avr/pgmspace.h>
#include <EEPROM.h>
#include <OneWire.h>
#include <SPI.h>


#define PlayPin 11
#define RecPin 12
#define SPAKER 6
#define OPENER 9
#define COpen true
#define CClose false
#define TOUCH1 4
#define TOUCH2 5
#define LED 13
#define SpeakerPin 6

Servo Opener;
tmElements_t tm;
Adafruit_SSD1306 OLED(4);

static const int Pitches[9] PROGMEM = { 659,523,587,392,0,392,587,659,523 };
byte AlarmHour[4] = { 9, 12, 19,23 };
byte AlarmMin[4] = { 30, 20, 30,30 };
bool AlarmEnabled[4] = { true, true, true,true };
bool cover = CClose;
bool RecLock = false;
bool Taked = false;
bool DoNotRun;
bool stat = false;
bool missed = false;
byte LastMin;
enum Flag
{
	SET,
	READ,
	ENABLE,
	LOCK,
	OPEN,
	NONE
} Mode;
void Putchar(char id, char xpos, char ypos)
{
	OLED.drawBitmap(xpos, ypos, FontRes[id], 16, 16, 1);
} 
byte MapPulse(int x, int in_min, int in_max, byte out_min, byte out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

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

void Record()
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

void OLEDP(String Inputext) 
{
	OLED.println(Inputext);
}

void OLEDC() 
{
	OLED.clearDisplay();
}

void OLEDOK()
{
	OLED.display();
}

void OLEDPT()
{
	if (tm.Minute < 10)
	{
		OLEDP({ String(tm.Hour) + ":0" + String(tm.Minute) });
	}
	else
	{
		OLEDP({ String(tm.Hour) + ":" + String(tm.Minute) });
	}
}

void OLEDPS(byte alid) 
{
	if (tm.Minute < 10)
	{
		OLEDP({ String(AlarmHour[alid]) + ":0" + String(AlarmMin[alid]) });
	}
	else
	{
		OLEDP({ String(AlarmHour[alid]) + ":" + String(AlarmMin[alid]) });
	}
}
bool Arrived() 
{
	for (char i = 0; i <= 3; i++)
	{
		
		if (tm.Hour == AlarmHour[i])
		{
			if (tm.Minute == AlarmMin[i])
			{

				return true;
			}
			else if (tm.Minute > LastMin)
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
	//  }
}
void SaveSettings()
{
	int addr = 0;
	OLEDC();
	Putchar(17, 16, 24);
	Putchar(19, 32, 24);
	Putchar(31, 48, 24);
	Putchar(32, 64, 24);
	Putchar(12, 80, 24);
	Putchar(2, 96, 24);
	OLEDOK();
	for (addr = 0; addr <= 3; addr++)
	{
		delay(10);
		EEPROM.write(addr, byte(AlarmHour[addr]));
	}
	delay(400);
	for (addr = 10; addr <= 13; addr++)
	{
		delay(10);
		EEPROM.write(addr, byte(AlarmMin[(addr - 10)]));
	}
	for (addr = 20; addr <= 23; addr++)
	{
		delay(10);
		EEPROM.write(addr, byte(AlarmEnabled[(addr - 20)]));
	}
	delay(100);
}

void ReadSettings()
{
	OLEDC();
	Putchar(33, 32, 32);
	Putchar(34, 48, 32);
	Putchar(35, 64, 32);
	Putchar(36, 80, 32);
	OLEDOK();
	int addr = 0;
	for (addr = 0; addr <= 3; addr++)
	{
		delay(10);
		AlarmHour[addr] = EEPROM.read(addr);
	}
	delay(400);
	for (addr = 10; addr <= 13; addr++)
	{
		delay(10);
		AlarmMin[(addr - 10)] = EEPROM.read(addr);
	}
	for (addr = 20; addr <= 23; addr++)
	{
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
			for (int n = 0; n <= 4; n++)
			{
				Putchar((26 + n), (24 + 16 * (n + 1)), 24);
			}
			OLEDOK();
			delay(1000);
			stat = false;
			return;
		}
		OLEDC();
		Putchar(4, 24, 8);
		Putchar(0, 40, 8);
		Putchar(14, 56, 8);
		Putchar(7, 72, 8);
		Putchar(20, 88, 8);
		OLED.setCursor(39, 32);
		OLEDPT();
		OLEDOK();
		for (byte k = 0; k <= 8; k++) {
			if (Pitches[k] == 0) {
				delays(1);
				continue;
			}
			else {
				tone(SpeakerPin, Pitches[k]);
				if (delays(1)) {
					noTone(SpeakerPin);
					return;
				}
				noTone(SpeakerPin);
			}
		}

		for (byte t = 0; t <= 10; t++)
		{



			if (stat)
			{
				stat = false;
				digitalWrite(12, LOW);
				digitalWrite(11, LOW);
				OLEDC();
				for (int q = 0; q <= 4; q++)
				{
					Putchar((26 + q), (24 + 16 * (q + 1)), 24);
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

void CoverControl()
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
		for (int j = 0; j <= 75; j++)
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

void HomeOLED() 
{
	if (tm.Minute < 10)
	{
		if (tm.Second < 10)
		{
			OLEDP({ String(tm.Hour) + ":0" + String(tm.Minute) + ":0" + String(tm.Second) });
		}
		else
		{
			OLEDP({ String(tm.Hour) + ":0" + String(tm.Minute) + ":" + String(tm.Second) });
		}
	}
	else
	{
		if (tm.Second < 10)
		{
			OLEDP({ String(tm.Hour) + ":" + String(tm.Minute) + ":0" + String(tm.Second) });
		}
		else
		{
			OLEDP({ String(tm.Hour) + ":" + String(tm.Minute) + ":" + String(tm.Second) });
		}
	}
}

bool touch1() 
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

bool touch2()
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
	switch (Bt_input[0])
	{
	case 'r':
		Mode = READ;
		break;
	case 's':
		Mode = SET;
		break;
	case 'l':
		Mode = LOCK;
		break;
	case 'e':
		Mode = ENABLE;
		break;
	case 'o':
		CoverControl();
		break;
	default:
		Serial.println("Unknown Command");
		Mode = NONE;
		return false;
	}
	switch (Mode)
	{
	case SET:
	{
		{ 
			if (Bt_input[2] != ',' || Bt_input[5] != ',')
			{
				Serial.println("Unrecongized format");
				return false;
			}
			if (((Bt_input[1] - 48) > 4) || ((Bt_input[1]) <= 0x30))
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
		_aid = (Bt_input[1] - 48) - 1;
		_ahour = ((Bt_input[3] - 48) * 10) + (Bt_input[4] - 48);
		_amin = ((Bt_input[6] - 48) * 10) + (Bt_input[7] - 48);
		if (_ahour > 24) {
			Serial.println("Goodbye you have been transported to an unknown time!")
				return;
		}
		AlarmMin[_aid] = _amin;
		AlarmHour[_aid] = _ahour;
		if (AlarmHour[(_aid)] < 10)
		{
			if (AlarmMin[(_aid)] < 10)
			{
				Serial.println({ "0" + String(AlarmHour[(_aid)]) + ",0" + String(AlarmMin[(_aid)]) });
			}
			else
			{
				Serial.println({ "0" + String(AlarmHour[(_aid)]) + "," + String(AlarmMin[(_aid)]) });
			}
		}
		else
		{
			if (AlarmMin[(_aid)] < 10)
			{
				Serial.println({ String(AlarmHour[(_aid)]) + ",0" + String(AlarmMin[(_aid)]) });
			}
			else
			{
				Serial.println({ String(AlarmHour[(_aid)]) + "," + String(AlarmMin[(_aid)]) });
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
	case READ:
	{
		if (Bt_input[1] == 'l')
		{
			Serial.println(RecLock);
			return true;
		}
		else if (((Bt_input[1] - 48) > 4) || ((Bt_input[1]) <= 0x30))
		{
			Serial.println("Invalid ID");
			return false;
		}
		_aid = (Bt_input[1] - 48);

		if (AlarmHour[(_aid - 1)] < 10)
		{
			if (AlarmMin[(_aid - 1)] < 10)
			{
				Serial.println({ "0" + String(AlarmHour[(_aid - 1)]) + ",0" + String(AlarmMin[(_aid - 1)]) });
			}
			else
			{
				Serial.println({ "0" + String(AlarmHour[(_aid - 1)]) + "," + String(AlarmMin[(_aid - 1)]) });
			}
		}
		else
		{
			if (AlarmMin[(_aid - 1)] < 10)
			{
				Serial.println({ String(AlarmHour[(_aid - 1)]) + ",0" + String(AlarmMin[(_aid - 1)]) });
			}
			else
			{
				Serial.println({ String(AlarmHour[(_aid - 1)]) + "," + String(AlarmMin[(_aid - 1)]) });
			}
		}
		return;
	}
	case ENABLE:
	{
		if (((Bt_input[1] - 48) >4) || ((Bt_input[1]) <= 0x30))
		{
			Serial.println("Invalid ID");
			return false;
		}
		_aid = (Bt_input[1] - 48);
		if (AlarmEnabled[(_aid - 1)])
		{
			AlarmEnabled[(_aid - 1)] = false;
			Serial.println("Alarm " + String(_aid) + " is now disabled.");
		}
		else
		{
			AlarmEnabled[(_aid - 1)] = false;
			Serial.println("Alarm " + String(_aid) + " is now enabled.");
		}
		return;
	}

	}
}

void HomeScr() 
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

void setup() 
{
	pinMode(4, INPUT);
	pinMode(5, INPUT);
	pinMode(7, OUTPUT);
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
	Mode = NONE;
	DoNotRun = false;
}

void loop() 
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
	char Arrival = Arrived();
	if (Arrived())
	{
		if (DoNotRun == false)
		{
			AlarmGo();
			LastMin = tm.Minute;
			DoNotRun = true;
		}
	}
	if (touch1())
	{
		CoverControl();
	}
	if (touch2())
	{
		delay(800);

		Record();


	}
	HomeScr();
	//Serial.println(stat);
}

