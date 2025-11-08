/*WAP to control brightness of the LED using analog write*/

#define LED     3

void setup() 
{
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
}

void loop() 
{
  for(unsigned char duty = 0; duty <= 255; duty++)
  {
    //vary dutycycle from 0 to 255: 
  analogWrite(LED , duty );
  delay(100);
  }
 

}
