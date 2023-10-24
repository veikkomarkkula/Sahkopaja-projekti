int solPin = 9;

void setup() 
{
  pinMode(solPin, OUTPUT);
}

void loop() 
{
  digitalWrite(solPin, HIGH);      
  delay(500);                          
  digitalWrite(solPin, LOW);       
  delay(500);                          
}
