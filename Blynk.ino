#define BLYNK_TEMPLATE_ID "TMPL3d7FUETWk"
#define BLYNK_TEMPLATE_NAME "Home Automation"
#define BLYNK_AUTH_TOKEN "NuUVPkPBmVinsM-0hSoBAjHPu5AllRkt"

#include <SPI.h>
#include <Ethernet.h>
#include <BlynkSimpleEthernet.h>

#define LED   2

BLYNK_WRITE(V0)
{
  int value = param.asInt();
  if(value)
  {
      digitalWrite(LED,1);

  }
  else
  {
      digitalWrite(LED,0);
    
  }
}
void setup() 
{
  // put your setup code here, to run once:
  pinMode(LED , OUTPUT);
  Blynk.begin("NuUVPkPBmVinsM-0hSoBAjHPu5AllRkt");
}

void loop() 
{
  // put your main code here, to run repeatedly:
  Blynk.run();
}
