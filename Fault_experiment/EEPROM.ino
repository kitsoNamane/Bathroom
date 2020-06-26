#include <EEPROM.h>
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int flowrate;     // value from the flowmeter in Liters
int memo = 1024;  //size in bytes of the arduino board memory
int address_counter = 0;
void setup() 
{
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
flowrate = random(1,100);
  

  EEPROM.write(address_counter,flowrate); // writes the flowrate value into address i
  Read();
  address_counter++; // increments the address to store another flowrate value



}

void Read()
{
  //flowrate=EEPROM.read(address_counter); // reads the flowrate value stored in address i
  lcd.print("addr: ");
  lcd.print(address_counter);
  lcd.print("-");
  lcd.print(EEPROM.read(address_counter));
  delay(2000); 
  lcd.clear();
  }
