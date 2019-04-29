#include <Wire.h>
#include <LiquidCrystal_I2C.h>
const int motorIn1 = 9;  //in3
const int motorIn2 = 10; //in4

const int redPin = 5;
const int greenPin = 6;
const int bluePin = 7;

int incomedate;
#define rank1 150
#define rank2 200
#define rank3 250

long lastDebounceTime = 0;
long debounceDelay = 50;
int tim = 500;
LiquidCrystal_I2C lcd(0x27, 16, 2); //A4~A5 : SDA~SCL

void setup()
{
  pinMode(motorIn1, OUTPUT);
  pinMode(motorIn2, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.begin(16, 2);
  lcd.print("Fan Speed is:");
  lcd.setCursor(0, 1);
  lcd.print("Enjoy Fan");
  Serial.begin(9600);
  analogWrite(motorIn1, 0);
  analogWrite(motorIn2, 0);
}

void loop()
{
  if (Serial.available() > 0)//串口接收到数据
  {
    incomedate = Serial.read();//获取串口接收到的数据

    if (incomedate == 'X')
    {
      fan_pow(0);
      Serial.println("风扇关闭!");
    }

    if (incomedate == 'A')
    {
      fan_pow(1);
      Serial.println("当前为一档!");
    }
    if (incomedate == 'B')
    {
      fan_pow(2);
      Serial.println("当前为二档!");
    }
    if (incomedate == 'C')
    {
      fan_pow(3);
      Serial.println("当前为三档!");
    }
  }

  delay(500);
}

void clockwise(int Speed) {
  analogWrite(motorIn1, 0);
  analogWrite(motorIn2, Speed);
}

void color(unsigned char red, unsigned char green, unsigned char blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

void fan_pow(int stat)
{
  switch (stat) {
    case 1:
      clockwise(rank1);
      lcd.setCursor(0, 1);
      lcd.print("1-Spend");
      color(0,0,255);
      break;
    case 2:
      clockwise(rank2);
      lcd.setCursor(0, 1);
      lcd.print("2-Spend");
      color(0,255,0);
      break;
    case 3:
      clockwise(rank3);
      lcd.setCursor(0, 1);
      lcd.print("3-Spend");
      color(255,255,255);
      break;
    default:
      clockwise(0);
      lcd.setCursor(0, 1);
      lcd.print("Power Off!");
      color(255,0,0);
  }
}
