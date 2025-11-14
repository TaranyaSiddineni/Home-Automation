#define BLYNK_TEMPLATE_ID "TMPL3d7FUETWk" 
#define BLYNK_TEMPLATE_NAME "Home Automation" 
#define BLYNK_AUTH_TOKEN "NuUVPkPBmVinsM-0hSoBAjHPu5AllRkt" 

#include <SPI.h> 
#include <Ethernet.h> 
#include <BlynkSimpleEthernet.h> 
#include "ldr.h" 
#include "main.h" 
#include "temperature_system.h" 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 

LiquidCrystal_I2C lcd(0x27, 16, 2); 

#include "serial_tank.h" 
bool heater_sw = 0, inlet_sw = 0, outlet_sw = 0, cooler_sw = 0;
// unsigned int tank_volume; 
// creating object timer to update the temperature on blynk app at particular period 
BlynkTimer timer; 
// This function is called every time the Virtual Pin state changes 
// To turn ON and OFF cooler based virtual PIN value 
BLYNK_WRITE(COOLER_V_PIN) 
{ 
// read the changed value on the pin 
cooler_sw = param.asInt(); 
cooler_control(cooler_sw); 
if(cooler_sw) 
{ 
  lcd.setCursor(8,0); 
  lcd.print("CLR_ON  "); 
} 
else 
{ 
  lcd.setCursor(8,0); 
  lcd.print("CLR_OFF"); 
} 
} 
// To turn ON and OFF heater based virtual PIN value 
BLYNK_WRITE(HEATER_V_PIN) 
{ 
  heater_sw = param.asInt(); 
  heater_control(heater_sw); 
  if(heater_sw) 
  { 
    lcd.setCursor(8,0); 
    lcd.print("HTR_ON "); 
  } 
  else 
  { 
    lcd.setCursor(8,0); 
    lcd.print("HTR_OFF"); 
  } 
}
// To turn ON and OFF inlet valve based virtual PIN value //
BLYNK_WRITE(INLET_V_PIN) 
{
  inlet_sw = param.asInt();
  if(inlet_sw)
  {
   enable_inlet();
    lcd.setCursor(7,1); 
    lcd.print("IN_FL_ON ");
  } 
  else
  {
    disable_inlet();
    lcd.setCursor(7,1); 
    lcd.print("IN_FL_OFF");
  }
} 
// To turn ON and OFF outlet valve based virtual switch value 
BLYNK_WRITE(OUTLET_V_PIN) 
{
  outlet_sw = param.asInt();
  if(outlet_sw)
  {
   enable_outlet();
    lcd.setCursor(7,1); 
    lcd.print("OUT_FL_ON ");
  } 
  else
  {
    disable_outlet();
    lcd.setCursor(7,1); 
    lcd.print("OUT_FL_OFF");
  } 
} 
/* To display temperature and water volume as gauge on the Blynk App */ 
void update_temperature_reading()
{ 
  //send temperature to blynk app on pin V1
  Blynk.virtualWrite(TEMPERATURE_GAUGE, read_temperature()); 

  //send volume of the water in blynk app on pin V3
  Blynk.virtualWrite(WATER_VOL_GAUGE,volume()); 
   
} 
/* To turn off the heater if the temperature raises above 35 deg C */ 
void handle_temp(void) 
{ 
  if (read_temperature() > (float)35 && heater_sw) 
  { 
    heater_sw = 0; heater_control(0); 
    Blynk.virtualWrite(HEATER_V_PIN, 0); 
    // print notification on the CLCD 
    lcd.setCursor(8,0); 
    lcd.print("HTR_OFF"); 
  } 
  
} 

/* To control water volume above 2000ltrs */ 
void handle_tank(void) 
{
if ((volume() < 2000) && (inlet_sw ==0))
  { 
    inlet_sw = 1; 
    enable_inlet(); 
    Blynk.virtualWrite(INLET_V_PIN, 1); 
    // print notification on the CLCD 
    lcd.setCursor(7,1); 
    lcd.print("IN_FL_ON "); 
  } 


} 
void setup(void) 
{ 
  // initialize LDR 
  init_ldr(); 
  // initialize temperature system 
  init_temperature_system(); 
  // connect arduino to blynk cloud 
  Blynk.begin(BLYNK_AUTH_TOKEN); 
  // initialize CLCD 
  lcd.init(); 
  lcd.backlight(); 
  lcd.clear(); 
  lcd.home(); 
  lcd.setCursor(0, 0); 
  lcd.print("Home Automation"); 
  delay(1000); 
  lcd.clear();
  //initialise the serial tank
  init_serial_tank();
  // timer to update temperature every 1 second 
  timer.setInterval(1000, update_temperature_reading); 
} 
float temperature;
unsigned int volume_water;
void loop(void) 
{ 
  // control the heater and cooler from the app 
  Blynk.run(); 
  timer.run(); 
  brightness_control(); 
  temperature = read_temperature(); 
  handle_temp();
  //reading the volume of the water
  volume_water = volume();

  //if volume of water goer less than 2000
  handle_tank();
  //displaying the volume in the CLCD
  lcd.setCursor(0, 0); 
  lcd.print(volume_water); 
   //displaying the temp in the CLCD
  lcd.setCursor(0, 0); 
  lcd.print(temperature); 
  
}
