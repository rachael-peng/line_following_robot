/*
 * Author:          Rachael Peng
 * Date created:    Oct. 8, 2022
 * Description:     Code for all actions of line following robot, IGEN 230
*/


// DEFINIING VARIABLES AND FUNCTIONS


// defining names of analog input pins used measure IR sensor response
const int Sensor1 = A1; // Analog input pin that indicates response of IR sensor 1, left-most
const int Sensor2 = A2; // Analog input pin that indicates response of IR sensor 2, left-centre
const int Sensor3 = A3; // Analog input pin that indicates response of IR sensor 3, centre
const int Sensor4 = A4; // Analog input pin that indicates response of IR sensor 4, right-centre
const int Sensor5 = A5; // Analog input pin that indicates response of IR sensor 5, right-most

// defining names of digital pins used to control the DC motors
int LMOTORF = 2; // pin controlling left motor, moves forward; In4 
int LMOTORB = 3; // pin controlling left motor, moves backward; In3
int RMOTORF = 5; // pin controlling right motor, moves forward; In2
int RMOTORB = 6; // pin controlling right motor, moves backward; In1
int LMOTORS = 10; // pin controlling PWM left motor speed
int RMOTORS = 9; // pin controlling PWM right motor speed 

// defining names of LED digital pins
int Sensor1LED = 12; // rightmost sensor
int Sensor2LED = 4; // right middle
int Sensor3LED = 7; // middle sensor
int Sensor4LED = 8; // left middle
int Sensor5LED = 11; // leftmost sensor

// defining names for actions
#define ON HIGH 
#define OFF LOW
#define ONSPEED 200
#define turnspeed 125
#define OFFSPEED 125
#define thresval 250
// Speed range: 0-255


// defining threshold values for each sensor: 
//        if the valSensor#>thresholdSensor#, then the sensor is above black paper
//        if the valSensor#<threshold#, then the sensor is above white paper 
int thresSensor1 = thresval;
int thresSensor2 = thresval;
int thresSensor3 = thresval;
int thresSensor4 = thresval;
int thresSensor5 = thresval;
 

// FUNCTIONS
  
// turn on LED when black paper is sensed
//        if the valSensor#>thresholdSensor#, then turn on LED
//        if the valSensor#<thresholdSensor#, then do not turn on LED
void LED(int sensorVal, int thresVal, int sensorLED) {
  if(sensorVal >= thresVal) {
    digitalWrite(sensorLED, ON);
  }
  else {
    digitalWrite(sensorLED, OFF);
  }
}

//


// the setup function runs once when you press reset or power the board 
void setup() {
  // initialize digital pins as output.
  pinMode(LMOTORF, OUTPUT); // Motor drive input signal pin 
  pinMode(LMOTORB, OUTPUT); // Motor drive input signal pin 
  pinMode(RMOTORF, OUTPUT); // Motor drive input signal pin 
  pinMode(RMOTORB, OUTPUT); // Motor drive input signal pin
  pinMode(RMOTORS, OUTPUT); // Motor drive input signal pin
  pinMode(LMOTORS, OUTPUT); // Motor drive input signal pin
  pinMode(Sensor1LED, OUTPUT); // LED pin
  pinMode(Sensor2LED, OUTPUT); // LED pin
  pinMode(Sensor3LED, OUTPUT); // LED pin
  pinMode(Sensor4LED, OUTPUT); // LED pin
  pinMode(Sensor5LED, OUTPUT); // LED pin
  Serial.begin(9600);
}




void loop() {
  
  // Analog input 
  int valSensor1=analogRead(Sensor1); // Sensor 1 input reading 
  int valSensor2=analogRead(Sensor2); // Sensor 2 input reading 
  int valSensor3=analogRead(Sensor3); // Sensor 3 input reading 
  int valSensor4=analogRead(Sensor4); // Sensor 4 input reading 
  int valSensor5=analogRead(Sensor5); // Sensor 5 input reading 


   // check if LEDs should be on: turn on LED when black paper is sensed
  LED(valSensor1, thresSensor1, Sensor1LED);
  LED(valSensor2, thresSensor2, Sensor2LED);
  LED(valSensor3, thresSensor3, Sensor3LED);
  LED(valSensor4, thresSensor4, Sensor4LED);
  LED(valSensor5, thresSensor5, Sensor5LED);
  
  // print values to serial monitor
  Serial.print("sensor 1 = ");
  Serial.println(valSensor1);
  Serial.print("sensor 2 = ");
  Serial.println(valSensor2);
  Serial.print("sensor 3 = ");
  Serial.println(valSensor3);
  Serial.print("sensor 4 = ");
  Serial.println(valSensor4);
  Serial.print("sensor 5 = ");
  Serial.println(valSensor5);

  // stop/forward/backward motion set-ups
  
  if(valSensor1<thresSensor1 && valSensor2<thresSensor2 && valSensor3>thresSensor3 && valSensor4<thresSensor4 && valSensor5<thresSensor5) {
    //WWBWW means forward
    digitalWrite(LMOTORF, ON); // left wheel forward
    digitalWrite(LMOTORB, OFF);
    analogWrite(LMOTORS, 140); // fast speed
    digitalWrite(RMOTORF, ON); // right wheel forward
    digitalWrite(RMOTORB, OFF);
    analogWrite(RMOTORS, 240); // slow speed
    delay(ONSPEED);

    digitalWrite(RMOTORF, OFF);
    digitalWrite(RMOTORB, OFF);
    analogWrite(RMOTORS, 0);
    digitalWrite(LMOTORF, OFF);
    digitalWrite(LMOTORB, OFF);
    analogWrite(LMOTORS, 0);
    delay(OFFSPEED);
    }
    
  else if((valSensor1<thresSensor1 && valSensor2<thresSensor2 && valSensor3<thresSensor3 && valSensor4>thresSensor4 && valSensor5<thresSensor5) || 
  (valSensor1<thresSensor1 && valSensor2<thresSensor2 && valSensor3>thresSensor3 && valSensor4>thresSensor4 && valSensor5<thresSensor5) || 
  (valSensor1<thresSensor1 && valSensor2<thresSensor2 && valSensor3<thresSensor3 && valSensor4>thresSensor4 && valSensor5>thresSensor5)) {
    //WWWBW or WWBBW or WWWBB means keep right

    digitalWrite(LMOTORF, ON); // left wheel forward
    digitalWrite(LMOTORB, OFF);
    analogWrite(LMOTORS, 110); // slow speed
    digitalWrite(RMOTORF, ON); // right wheel forward
    digitalWrite(RMOTORB, OFF);
    analogWrite(RMOTORS, 240); // fast speed
    delay(110);

    digitalWrite(RMOTORF, OFF);
    digitalWrite(RMOTORB, OFF);
    analogWrite(RMOTORS, 0);
    digitalWrite(LMOTORF, OFF);
    digitalWrite(LMOTORB, OFF);
    analogWrite(LMOTORS, 0);
    delay(100);
    }

  else if(valSensor1<thresSensor1 && valSensor2<thresSensor2 && valSensor3<thresSensor3 && valSensor4<thresSensor4 && valSensor5>thresSensor5) {
    //WWWWB means keep strongly right
    digitalWrite(LMOTORF, ON); // left wheel forward
    digitalWrite(LMOTORB, OFF);
    analogWrite(LMOTORS, 110); // slow speed
    digitalWrite(RMOTORF, ON); // right wheel forward
    digitalWrite(RMOTORB, OFF);
    analogWrite(RMOTORS, 250); // fast speed
    delay(125);

    digitalWrite(RMOTORF, OFF);
    digitalWrite(RMOTORB, OFF);
    analogWrite(RMOTORS, 0);
    digitalWrite(LMOTORF, OFF);
    digitalWrite(LMOTORB, OFF);
    analogWrite(LMOTORS, 0);
    delay(100);
    }
    
  else if((valSensor1<thresSensor1 && valSensor2>thresSensor2 && valSensor3<thresSensor3 && valSensor4<thresSensor4 && valSensor5<thresSensor5) || (valSensor1<thresSensor1 && valSensor2>thresSensor2 && valSensor3>thresSensor3 && valSensor4<thresSensor4 && valSensor5<thresSensor5)) { 
    //WBWWW or WBBWW means keep right
    digitalWrite(LMOTORF, ON); // left wheel forward
    digitalWrite(LMOTORB, OFF);
    analogWrite(LMOTORS, 230); // fast speed
    digitalWrite(RMOTORF, ON); // right wheel forward
    digitalWrite(RMOTORB, OFF);
    analogWrite(RMOTORS, 160); // slow speed
    delay(125);

    digitalWrite(RMOTORF, OFF);
    digitalWrite(RMOTORB, OFF);
    analogWrite(RMOTORS, 0);
    digitalWrite(LMOTORF, OFF);
    digitalWrite(LMOTORB, OFF);
    analogWrite(LMOTORS, 0);
    delay(100);
    }

  else if(valSensor1>thresSensor1 && valSensor2<thresSensor2 && valSensor3<thresSensor3 && valSensor4<thresSensor4 && valSensor5<thresSensor5) { 
    //BWWWW means strongly keep left
    digitalWrite(LMOTORF, ON); // left wheel forward
    digitalWrite(LMOTORB, OFF);
    analogWrite(LMOTORS, 250); // fast speed
    digitalWrite(RMOTORF, ON); // right wheel forward
    digitalWrite(RMOTORB, OFF);
    analogWrite(RMOTORS, 160); // slow speed
    delay(150);

    digitalWrite(RMOTORF, OFF);
    digitalWrite(RMOTORB, OFF);
    analogWrite(RMOTORS, 0);
    digitalWrite(LMOTORF, OFF);
    digitalWrite(LMOTORB, OFF);
    analogWrite(LMOTORS, 0);
    delay(100);
    }
    
  else if((valSensor1>thresSensor1 && valSensor2>thresSensor2 && valSensor3>thresSensor3 && valSensor4>thresSensor4 && valSensor5>thresSensor5)
  ||(valSensor1<thresSensor1 && valSensor2<thresSensor2 && valSensor3<thresSensor3 && valSensor4<thresSensor4 && valSensor5<thresSensor5)
  ||(valSensor1<thresSensor1 && valSensor2>thresSensor2 && valSensor3>thresSensor3 && valSensor4>thresSensor4 && valSensor5>thresSensor5)
  ||(valSensor1>thresSensor1 && valSensor2>thresSensor2 && valSensor3>thresSensor3 && valSensor4>thresSensor4 && valSensor5<thresSensor5)
  ||(valSensor1<thresSensor1 && valSensor2>thresSensor2 && valSensor3>thresSensor3 && valSensor4>thresSensor4 && valSensor5<thresSensor5)) {
   // BBBBB or WWWWW or BBBBW or WBBBB or WBBBW means forward 
    digitalWrite(LMOTORF, ON); // left wheel forward
    digitalWrite(LMOTORB, OFF);
    analogWrite(LMOTORS, 140); // fast speed
    digitalWrite(RMOTORF, ON); // right wheel forward
    digitalWrite(RMOTORB, OFF);
    analogWrite(RMOTORS, 240); // fast speed
    delay(ONSPEED);

    digitalWrite(RMOTORF, OFF);
    digitalWrite(RMOTORB, OFF);
    analogWrite(RMOTORS, 0);
    digitalWrite(LMOTORF, OFF);
    digitalWrite(LMOTORB, OFF);
    analogWrite(LMOTORS, 0);
    delay(OFFSPEED);
   }


  else if(valSensor1>thresSensor1 && valSensor2>thresSensor2 && valSensor3>thresSensor3 && valSensor4<thresSensor4 && valSensor5<thresSensor5){
    //BBBWW means 90 degree left turn - left fast
    digitalWrite(LMOTORF, ON); // left wheel forward
    digitalWrite(LMOTORB, OFF);
    analogWrite(LMOTORS, 250); // fast speed
    digitalWrite(RMOTORF, OFF); // right wheel backward
    digitalWrite(RMOTORB, ON);
    analogWrite(RMOTORS, 120); // fast speed
    delay(525);

    digitalWrite(RMOTORF, OFF);
    digitalWrite(RMOTORB, OFF);
    analogWrite(RMOTORS, 0);
    digitalWrite(LMOTORF, OFF);
    digitalWrite(LMOTORB, OFF);
    analogWrite(LMOTORS, 0);
    delay(500);
    }


  else if(valSensor1<thresSensor1 && valSensor2<thresSensor2 && valSensor3>thresSensor3 && valSensor4>thresSensor4 && valSensor5>thresSensor5){
    //WWBBB means 90 degree right turn - right forward
    digitalWrite(LMOTORF, OFF); // left wheel forward
    digitalWrite(LMOTORB, ON);
    analogWrite(LMOTORS, 130); // fast speed
    digitalWrite(RMOTORF, ON); // right wheel backward
    digitalWrite(RMOTORB, OFF);
    analogWrite(RMOTORS, 250); // fast speed
    delay(525);

    digitalWrite(RMOTORF, OFF);
    digitalWrite(RMOTORB, OFF);
    analogWrite(RMOTORS, 0);
    digitalWrite(LMOTORF, OFF);
    digitalWrite(LMOTORB, OFF);
    analogWrite(LMOTORS, 0);
    delay(500);
    } 

    else if(valSensor1>thresSensor1 && valSensor2<thresSensor2 && valSensor3>thresSensor3 && valSensor4<thresSensor4 && valSensor5<thresSensor5) {
    // BWBWW means more than 90° turn, left
    digitalWrite(LMOTORF, OFF); // left wheel forward
    digitalWrite(LMOTORB, ON);
    analogWrite(LMOTORS, 250); // fast speed
    digitalWrite(RMOTORF, ON); // right wheel backward
    digitalWrite(RMOTORB, OFF);
    analogWrite(RMOTORS, 150); // fast speed
    delay(900);

    digitalWrite(RMOTORF, OFF);
    digitalWrite(RMOTORB, OFF);
    analogWrite(RMOTORS, 0);
    digitalWrite(LMOTORF, OFF);
    digitalWrite(LMOTORB, OFF);
    analogWrite(LMOTORS, 0);
    delay(500);
    }

    else if(valSensor1<thresSensor1 && valSensor2<thresSensor2 && valSensor3>thresSensor3 && valSensor4<thresSensor4 && valSensor5>thresSensor5) {
    // WWBWB means more than 90° turn, right
    digitalWrite(LMOTORF, OFF); // left wheel forward
    digitalWrite(LMOTORB, ON);
    analogWrite(LMOTORS, 150); // fast speed
    digitalWrite(RMOTORF, ON); // right wheel backward
    digitalWrite(RMOTORB, OFF);
    analogWrite(RMOTORS, 250); // fast speed
    delay(900);

    digitalWrite(RMOTORF, OFF);
    digitalWrite(RMOTORB, OFF);
    analogWrite(RMOTORS, 0);
    digitalWrite(LMOTORF, OFF);
    digitalWrite(LMOTORB, OFF);
    analogWrite(LMOTORS, 0);
    delay(500);
    }
}
