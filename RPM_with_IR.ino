#define IR_Sensor 2 /*D2 IR pin defined*/
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

volatile int tick = 0;
volatile unsigned long time1 = 0;
volatile unsigned long time2 = 0;
volatile unsigned long rev = 0;
float r = 0.05; //change radius
float rpm_old;
unsigned long time_diff;
float rpm;
float acc;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  pinMode(IR_Sensor, INPUT);   /*IR Pin D2 defined as Input*/
  attachInterrupt(digitalPinToInterrupt(IR_Sensor), REV, FALLING); // Change to RISING if IR sensor triggers on rising edge
  //Serial.begin(9600);
}

void loop()
{
  
  rpm_old = rpm;
  rpm = (1 / (time_diff/  60000.0));
  lcd.setCursor(0, 0);
  lcd.print("RPM is ");
  //lcd.setCursor(0, 1);
  lcd.print(rpm);
  if(rpm_old == rpm){
      acc = 0;
    }
    else{
      acc = rpm*3.14*2/60*r;
    }
  //Serial.println(rpm);
  //delay(800);
  //lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Acc is ");
  //lcd.setCursor(0, 1);
  lcd.print(acc); // acceleration
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
    time_diff = time2 - time1;
  }
}
