#include <NewPing.h> // library for ultrasonic sensor 
#include <LiquidCrystal.h> // libarry for lcd
#include <Servo.h> // libary for servo 

// define ultrasonic sensor, RBG LEDs and buzzer pins
const int trigPin = 2; //trigger pin is connected to pin 2 
const int echoPin = 3; // echo pin is connected to pin 3
const int blueLED = 4; // blue LED pin is connected to pin 4
const int greenLED = 5; // green LED pin is connected to pin 5
const int redLED = 6; // red LED pin is connected to pin 6
const int buzzerPin = 7; // buzzer pin is connected pin 7

// define LCD pins
const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13; // lcd pin connections for rs, en, d4, d5, d6, d7

// define servo pin
const int servoPin = A0; // servo pin is connect to analog pin A0

// define distance

const int MAX_DISTANCE = 200; // Max distance that the sensor will measure (in cm)

// define buzzer tones 
const int 


// create object for libraries
NewPing sonar(trigPin, echoPin, MAX_DISTANCE); // create "sonar" object from NewPing library to configure ultrasonic sensor pins and max distance

LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // create "lcd" object from NewPing libray to configure lcd pins


Servo servo; // create "Servo" object from Servo library


//configure redLED to flash
void flashRedLEDandBuzzer(int times, int interval) {  //function which allows LED and Buzzer to go high x times at an x interval
  for (int i = 0; i < times; i++) {
    digitalWrite(redLED, HIGH); // redLED is on!
    digitalWrite(buzzerPin, HIGH); // buzzerPin is on!
    delay(interval); // time interval
    digitalWrite(redLED, LOW); // redLED is off!
    digitalWrite(buzzerPin,LOW); // buzzerPin is off!
    delay(interval); // time interval
  }
}

void setup() {
  Serial.begin(9600); //Arduino communicates with computer at a speed of 9600 bits per second, via USB-type B

  // Set pinMode to either INPUT or OUTPUT
pinMode(trigPin, OUTPUT); // trigger pin is set as an Output
pinMode(echoPin, INPUT); //echo pin is set as an Input
pinMode(blueLED, OUTPUT); // blue LED pin is set as an Output
pinMode(greenLED, OUTPUT); // green LED pin is set as an Output
pinMode(redLED, OUTPUT); // red LED pin is set as an Output
pinMode(buzzerPin, OUTPUT); // buzzer pin is set as an Output

 // configuring LCD
 lcd.begin(16,2); // Set up number of columns and rows that will be used on LCD
 lcd.print("Getting ready..."); // lcd will print "Getting ready..." while simulation gets ready 

 // configuring servo
 servo.attach(servoPin); // linking "servo" object to servoPin = A0
 servo.write(0); // initial servo position is set at 90 degrees (closed!)

}

void loop() {
 unsigned int distance = sonar.ping_cm(); // Distance will now be measured in cm!

 Serial.print ("Distance "); // prints "Distance" on the serial monitor 
 Serial.print (distance); // prints the measured "distance" on the serial monitor 
 Serial.println (" cm"); // prints " cm" in the serial monitor

// Expressions for when hands is detected or if no hands is detected
  if (distance < 15) { // if an object is less than 10 cm near the sensor

  // LCD will display a warning message when hands are detected.
  lcd.clear(); // lcd will clear its display
  lcd.setCursor(3,0); // position of where the printed text will be 
  lcd.print("! WARNING !"); // LCD will display "! WARNING !" when alarm is triggered
  lcd.setCursor(0,1); // position of where the printed text will be 
  lcd.print("Alarm triggered!"); // LCD will display "Alarm triggered!" when alarm is triggered

   // servo state
  servo.write(90); // servo positions itself at a 0 degree angle (open!)
  delay(100); // gate stays open for about 1.5 seconds
   
  // Red LED will flash, and the Buzzer will be turned on when hands are detected
  digitalWrite(greenLED, LOW); // green LED is off!
  digitalWrite(blueLED, LOW); // blue LED is off!
  flashRedLEDandBuzzer(5,100); // LED and Buzzer will go HIGH 5 times at an interval of 100 milliseconds

} else {
  //LCD will display nothing when no hand is detected
  lcd.clear(); // lcd clears any printed text
  lcd.setCursor(0,0); // position of where next text will be 
  lcd.print("! Do not touch !"); // lcd will print "! Do not touch !" when no hands are detected
  
  // only green LED will be on if nothing is detected
  digitalWrite(greenLED, HIGH); // green LED is on!
  digitalWrite(redLED, LOW); // red LED is off!
  digitalWrite(blueLED, LOW); // blue LED is off!
  digitalWrite(buzzerPin, LOW); // buzzer is off!
 
 // servo state
  servo.write(0); // servo will position itself at a 90 degree angle (closed!)
}

delay(100);
}
