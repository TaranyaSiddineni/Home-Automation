/*WAP to toggle LED*/

void setup() 
{
  //config pin 13 as the out PIN
  pinMode(13,OUTPUT);

}

void loop() 
{
  // turn on led
  digitalWrite(13,HIGH);

  //delay
  delay(1000);

  //turn OFF the LED
  digitalWrite(13,LOW);

  //delay
  delay(1000);


}
