#define IR_Sensor 2 /*D2 IR pin defined*/
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
int IR;
float rev;
float value=0;
int rpm;
int oldtime=0;
int time;

LiquidCrystal_I2C lcd(0x27,20,4);

void setup()
{
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  pinMode(IR_Sensor, INPUT);   /*IR Pin D2 defined as Input*/
  attachInterrupt(digitalPinToInterrupt(IR_Sensor), REV, FALLING);
}
void loop(){
  IR=digitalRead(IR_Sensor);  /*digital read function to check IR pin status*/
  time=millis()-oldtime; //finds the time
  rpm=(rev/time)*60000; //calculates rpm for blades
  oldtime=millis(); //saves the current time
  rev=0;
  lcd.setCursor(0,0);
  lcd.print("RPM is");
  lcd.setCursor(0,1);
  lcd.print(rpm);
  delay(1000);
  lcd.clear();
}
void REV(){
  rev++;
}