#include "temperature_system.h"
#include "Arduino.h"
#include "main.h"


void init_temperature_system(void)
{
  //setting heater and cooler GPIO pins as output pins
  pinMode(HEATER,OUTPUT);
  pinMode(COOLER,OUTPUT);

    
}
float read_temperature(void)
{
  float temperature; // declare local variable

  // read the temperature sensor and return the temperature 
  temperature = ((analogRead(A0) * 5.0 / 1024.0) / 0.01);
  return temperature;
}

void cooler_control(bool control)
{
  if(control)
  {
      //turn on the cooler -> assign digital value 1 to the cooler gpio pin
      digitalWrite(COOLER,HIGH);
    
  }
  else
  {
    digitalWrite(COOLER,LOW);
    
  }
}
void heater_control(bool control)
{
   if(control)
  {
      //turn on the cooler -> assign digital value 1 to the cooler gpio pin
      digitalWrite(HEATER,1);
   
  }
  else
  {
    digitalWrite(HEATER,0);
    
  }  
}
