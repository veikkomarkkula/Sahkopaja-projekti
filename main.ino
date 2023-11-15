// Brushless motor kokeilu
// Recommend to run 13.5 V, Amppeerit about puoleenväliin pöydän säädintä

#include <Servo.h>
#include <Stepper.h>
#include <AccelStepper.h>


// create servos object to control the ESC // positions of motors per servo still undecided
Servo ESC1, ESC2;

// First values are for driving brushless motorrs
// value from the analog pin
// Potvalue is the read value of potentiometer, pot1 and pot2 are the values inputted into ESC's to drive motors
int potValue, potValue1, potValue2;
// Limit run speed of inputs for ESC's // Makes running smoother  // Built in max would be 180
int max_speed = 40;
//Time until slowdown used into autorun
int slowdown_time = max_speed;

// For stepper motor
#define dirPin 22
#define stepPin 3
#define motorInterfaceType 1
AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);
int stepperspeed = 400;

// For servo // aka tilting barrel up and down
int servopos = 0;
int servopin = 4;
Servo myservo;
long servo_last_active = millis();
int servo_next_point = 25;


void setup() {

  // Attach the ESC1 on pin 9
  // Attach the ESC nro  2 on pin 10 // Actual pins do not matter, they just need to be somewhere
  ESC1.attach(9, 1000, 2000); // (pin, min pulse width, max pulse width in microseconds)
  ESC2.attach(10, 1000, 2000); // (pin, min pulse width, max pulse width in microseconds)

  //Serial for debugging
  Serial.begin(9600);

  // Declare pins as output: // For stepper motor
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  // Define variables for steppers
  // For some reason this has to be in void setup();
  stepper.setMaxSpeed(  1000);

  // Servo setup
  myservo.attach( servopin );

}


void steppermotor() { // Continuous run
  stepper.setSpeed( stepperspeed );
  stepper.runSpeed();

  // Turning back and forth
  if ( stepper.currentPosition() > 50 ) {
    stepperspeed = -40;
  }
  if ( stepper.currentPosition() < 0 ) {
    stepperspeed = 40;
  }
}
void running_servo() {
  // Here we run servo that tilt the shooting pipe higher and lower
  if ( millis() > servo_last_active + 500) {
    myservo.write(servo_next_point )  ;
    servo_last_active = millis();
    servo_next_point = -1 * servo_next_point;
  }
}
void autorun(Servo ESC1, Servo ESC2) {
  // Here will be a funtion about automatic running of the two motors
  // Main loop of autorun, when final then the autorun ends
  long time = millis() ;

  // Kerroin is to make numbers more easy to read
  int kerroin = 1000;

  // This variable is used to save value for running the motors
  int use_speed = 0;



  // Here would be max limits for autorun time
  if ( time > 0 )
  {
    if ( time / kerroin < max_speed ) {
      use_speed = time / kerroin;
    }

    else {
      // Limits max speed to make run smoother
      use_speed = max_speed;
    }
  }

  // RUN
  ESC1.write(use_speed);
  ESC2.write(use_speed);

  //Print debug values
  Serial.print("Time : ");
  Serial.print(time);
  Serial.print("  Speed : ");
  Serial.print(use_speed );
  Serial.println("");

}
void print_esc_values(Servo ESC1, Servo ESC2) {
  Serial.print(ESC1.read());
  Serial.print("   ");
  Serial.print(ESC2.read());
  Serial.print("   ");
  Serial.println("");
}

void runwithPOT( int potValue, Servo ESC1, Servo ESC2) {
  // Säätää potValue sopivan kokoiseksi ESC:eille
  potValue1 = map(potValue, 0, 1023, 0, 180);
  potValue2 = map(potValue, 0, 1023, 0, 180);

  // Limit the input speeds to make run smoother // Max_speed is global variable
  if (potValue1 > max_speed) {
    potValue1 = max_speed;
  }
  if (potValue2 > max_speed) {
    potValue2 = max_speed;
  }

  // Commands to move the motor
  ESC1.write(potValue1);    // Send the signal to the ESC
  ESC2.write(potValue2);    // Send the signal to the ESC
  print_esc_values( ESC1,  ESC2);
}

void loop() {
  // reads the value of the potentiometer (value between 0 and 1023)
  potValue = analogRead(A0);

  // This makes the actual movement of motors, use only one of two options
  // Run with potentiometer // Option 1
  runwithPOT(potValue, ESC1, ESC2);

  //autorun                 // Option 2
  //autorun(ESC1, ESC2);

  // Stuff related to steppermotor
  //steppermotor();

  // Tilt the pipe high and low with servo
  //running_servo();

  // Printing some debug values

}
