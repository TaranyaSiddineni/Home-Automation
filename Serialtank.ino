//WAP to test the tank serial function

#include <LiquidCrystal_I2C.h>
#include <wire.h>

LiquidCrystal_I2C lcd(0x27,16,2);


#define INLET_VALVE   0x00
#define OUTLET_VALVE  0x01
#define ENABLE        0x01
#define DISABLE       0x00

#define VOLUME        0x30

void setup()
{
  Serial.begin(19200);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.home();
  
  lcd.setCursor(0,0);
  lcd.print("volume");
}
unsigned int value_h , value_l, volume;

void loop()
{
  Serial.write(INLET_VALVE);
  Serial.write(ENABLE);

  //read the volume of the water

  Serial.write(VOLUME);
  //check if data is available
  while(!Serial.available());
  value_h = Serial.read();
  while(!Serial.available());
  value_l = Serial.read();
  volume = value_h << 8 | value_l;

  lcd.setCursor(0,1);
  lcd.print("       ");   // clear old value (6 spaces)    lcd.setCursor(0,1);
  lcd.print(volume);
  lcd.print(" L"); 
}
