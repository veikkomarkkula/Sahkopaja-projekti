// Brushless motor kokeilu   

// Recommend to run 13.5 V, 0,15 A   

#include <Servo.h>  
// create servos object to control the ESC // positions of motors per servo still undecided 
Servo ESC1, ESC2;       
// value from the analog pin  
// Potvalue is the read value of potentiometer, pot1 and pot2 are the values inputted into ESC's to drive motors 
int potValue, potValue1, potValue2;   
// Limit run speed of inputs for ESC's // Makes running smoother  // Built in max would be 180 
int max_speed = 22; 
void setup() {  
  // Attach the ESC1 on pin 9  
  // Attach the ESC nro  2 on pin 12 // Actual pins do not matter, they just need to be somewhere 
  ESC1.attach(9,1000,2000); // (pin, min pulse width, max pulse width in microseconds)   
  ESC2.attach(12,1000,2000); // (pin, min pulse width, max pulse width in microseconds)   
  //Serial for debugging 
  Serial.begin(9600); 
}  
void autorun(Servo ESC1,Servo ESC2){ 
  // Here will be a funtion about automatic running of the two motors  
  // Main loop of autorun, when final then the autorun ends 
  int time = millis() + 5000; 
  // Kerroin is to make numbers more easy to read  
  int kerroin = 1000;  
  // Here would be max limits for autorun time 
  if( time > 0 ) { 
    if( time / kerroin < max_speed ) { 
        ESC1.write(time / kerroin ); 
        ESC2.write(time / kerroin ); 
    }   
    else { 
      // Limits max speed to make run smoother 
        ESC1.write(max_speed ); 
        ESC2.write(max_speed ); 
    } 
  } 
} 
void runwithPOT( int potValue, Servo ESC1,Servo ESC2) { 
  // Säätää potValue sopivan kokoiseksi ESC:eille 
  potValue1 = map(potValue, 0, 1023, 0, 180);    
  potValue2 = map(potValue, 0, 1023, 0, 180);  
  // Limit the input speeds to make run smoother // Max_speed is global variable 
  if(potValue1 > max_speed) { 
      potValue1 = max_speed; 
  } 
  if(potValue2 > max_speed) { 
      potValue2 = max_speed; 
  } 
  // Commands to move the motor 
  ESC1.write(potValue1);    // Send the signal to the ESC 
  ESC2.write(potValue2);    // Send the signal to the ESC 
} 

void loop() {  
  // reads the value of the potentiometer (value between 0 and 1023) 
  potValue = analogRead(A0);     
  // This makes the actual movement of motors, use only one of two options 
  // Run with potentiometer // Option 1  
  runwithPOT(potValue, ESC1, ESC2); 
  //autorun                 // Option 2  
  //autorun(ESC1, ESC2); 
  // Printing some debug values 
  Serial.print(ESC1.read());  
  Serial.print("   "); 
  Serial.print(ESC2.read()); 
  Serial.print("   "); 
  Serial.println(""); 
} 
