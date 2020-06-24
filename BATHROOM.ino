
// include the library code:
#include <LiquidCrystal.h>
#include "PinChangeInterrupt.h"

int flowPin = 2;    //This is the input pin on the Arduino
int levelPin = 3;
int flushPin = 4;
int faultPin = 5;
int okPin = 6;
int valvePin = 7;
//double flowRate;    //This is the value we intend to calculate. 
volatile int count; //This integer needs to be set as volatile to ensure it updates correctly during the interrupt process.
volatile double flowrate;
volatile int flushed = 0;
volatile int levelHigh = 0;
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void setup() {
  pinMode(faultPin, OUTPUT);
  pinMode(okPin, OUTPUT);
  pinMode(flowPin, INPUT);           //Sets the pin as an input
  pinMode(levelPin, INPUT);
  pinMode(flushPin, INPUT);
  pinMode(valvePin, OUTPUT);
  digitalWrite(flushPin, HIGH);
  attachInterrupt(digitalPinToInterrupt(flowPin), Flow, RISING);  //Configures interrupt 0 (pin 2 on the Arduino Uno) to run the function "Flow"
  attachInterrupt(digitalPinToInterrupt(levelPin), Level, RISING);
  attachPCINT(digitalPinToPCINT(flushPin), Flush, CHANGE);
}

void loop() {
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("BATHROOM WATER");
  lcd.setCursor(0, 1);
  lcd.print("FLOW SYSTEM");
  delay(2000);
  Fault();
}

void Fault(){
  if(count > 4150 && levelHigh == 0) {
    // stop selonoid valve
    lcd.begin(16, 2);
    lcd.print("Leak Detected");
    digitalWrite(faultPin, HIGH);
    digitalWrite(okPin, LOW);
    digitalWrite(valvePin, HIGH);
  }
  digitalWrite(faultPin, LOW);
  digitalWrite(okPin, HIGH);
}

void Flush() {
  //lcd.clear();
  flushed = 1;
  lcd.begin(16, 2);
  lcd.print("Flushing...");
  delay(2000);
}

void Flow() {
  // Increment the pulse counter
  count++;
  flowrate = count * 2.25;
  flowrate = flowrate / 1000;
  lcd.begin(16, 2);
  lcd.print("Watering...");
  lcd.setCursor(0, 1);
  lcd.print(flowrate);
  lcd.print(" Litres");
  delay(2000); 
}

void Level() {
  levelHigh = 1;
  int litres = flowrate;
  count = 0;
  lcd.begin(16, 2);
  lcd.print("Tank Full");
  lcd.setCursor(0, 1);
  lcd.print(litres);
  lcd.print(" Litres");
  delay(2000);
}
