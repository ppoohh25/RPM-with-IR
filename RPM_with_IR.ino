#define IR_Sensor 2 /*D2 IR pin defined*/
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

volatile int tick = 0;
volatile unsigned long time1 = 0;
volatile unsigned long time2 = 0;
volatile unsigned long rev = 0;

LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup()
{
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  pinMode(IR_Sensor, INPUT);   /*IR Pin D2 defined as Input*/
  attachInterrupt(digitalPinToInterrupt(IR_Sensor), REV, FALLING); // Change to RISING if IR sensor triggers on rising edge
  Serial.begin(9600);
}

void loop()
{
  unsigned long time_diff = time2 - time1;
  float rpm = 0;
  rpm = (1 / (time_diff/  60000.0));
  //rev =0;
  lcd.setCursor(0, 0);
  lcd.print("RPM is");
  lcd.setCursor(0, 1);
  lcd.print(rpm);
  Serial.println(rpm);
  delay(200);
  lcd.clear();
}


void REV()
{
  if (tick == 0)
  {
    time1 = millis();
    tick = 1;
  }
  else if (tick == 1)
  {
    time2 = millis();
    tick = 0;
    rev++;
  }
}
