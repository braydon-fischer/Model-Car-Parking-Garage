 //Password Variable
 int password = 40; //Six digit binary password in decimal form for easy password changes, use 40 as the password
 
 //Output Wires
 int red = 41; //Variable name for binary pin connected to red LED
 int yellow = 43; //Variable name for binary pin connected to yellow LED
 int green = 45; //Variable name for binary pin connected to green LED
 int trig1 = 53; //Pin connected to the trigger pin of the first ultrasound sensor (US1)
 int trig2 = 52; //Pin connected to the trigger pin of the second ultrasound sensor (US2)
 int in1 = 22; //Pin connected to the IN1 pin of the L298N controller
 int in2 = 23; //Pin connected to the IN2 pin of the L298N controller
 int in3 = 24; //Pin connected to the IN3 pin of the L298N controller
 int in4 = 25; //Pin connected to the IN4 pin of the L298N controller
 int ena = 3;  //Pin connected to the ENA pin of the L298N controller
 int enb = 2; //Pin connected to the ENB pin of the L298N controller

 //Input wires
 int ir1 = 51; //Pin connected to the out pin of the first IR sensor (IRS1)
 int ir2 = 50; //Pin connected to the out pin of the second IR sensor (IRS2)
 int echo1 = 34; //Pin connected to the echo pin of US1
 int echo2 = 32; //Pin connected to the echo pin of US2

 //Password input wires
 int code0 = 27; //Password input wire for the first digit from the right (lsb) of the password
 int code1 = 29; //Password input wire for the second digit from the right of the password
 int code2 = 31; //Password input wire for the third digit from the right of the password
 int code3 = 33; //Password input wire for the fourth digit from the right of the password
 int code4 = 35; //Password input wire for the fifth digit from the right of the password
 int code5 = 37; //Password input wire for the sixth digit from the right (msb) of the password
 int codedecimal = 0;

 //Variables
 int IRS1 = 0; //Variable to store the reading from IRS1
 int IRS2 = 0; //Variable to store the reading from IRS2
 int duration1 = 0; //Variable to store the length of time it took for US1 to receive the echo
 int distance1 = 0; //Variable to store the distance an object is from US1, calculated with the duration variable
 int duration2 = 0; //Variable to store the length of time it took for US2 to receive the echo
 int distance2 = 0; //Variable to store the distance an object is from US2, calculated with the duration variable

 void gate1(){     // Function that opens and closes gate 1 and will not close gate 1 if US1 detects that the car is still there
      digitalWrite(in1, 1); //Rotates the 1st gate to the open position
      analogWrite(ena, 127); //Uses PWM to run the 1st gate motor at 50% duty cycle
      delay(300); //Delay of 300 ms to allow gate 1 to open fully
      digitalWrite(in1,0); //Stops the 1st gate's rotation
      delay(10000); // Need 10 second delay for the open gate
      do // do-while loop to prevent the first gate from closing on the car
        {
          digitalWrite(trig1, 0); //trig pin set to low
          delayMicroseconds(2); //2 microsecond delay
          digitalWrite(trig1, 1); //trig pin set to high
          delayMicroseconds(10); //10 microsecond delay
          digitalWrite(trig1, 0); //trig pin set to low after 10 microseconds
          duration1 = pulseIn(echo1, HIGH); //stores the amount of time it took for US1 to receive the echo
          distance1 = (duration1 * 0.034) / 2.0; // finds how far away the car is by taking the amount of time it took for US1 to receive the echo and multiplying it by the speed of sound in air in centimeters per microseconds (0.034) and dividing that by two, since the sound had to travel there and back
          delay(500); //0.5 second delay       
        }while (distance1 <= 10); //Prevents the first gate from closing on the car
      digitalWrite(in2, 1); //Rotates the 1st gate to the closed position
      delay(250); //250 ms delay to allow gate 1 to close fully
      digitalWrite(in2, 0); //Stops the 1st gate's rotation
      delay(2000); // 2 second delay
 }

 void gate2() {   // Function that opens and closes gate 2 and will not close gate 2 if US2 detects that the car is still there
      digitalWrite(in3, 1); //Rotates the 2nd gate to the open position
      analogWrite(enb, 127); //Uses PWM to run the 2nd gate motor at 50% duty cycle
      delay(250); // 250 ms delay to allow the 2nd gate to rotate fully to the open position
      digitalWrite(in3,0); //Stops the 2nd gate motor
      delay(10000); // Need 10 seconds delay for the open gate
      do // do-while loop to prevent the second gate from closing on the car
          {
            digitalWrite(trig2, 0); //trig pin set to low
            delayMicroseconds(2); //2 microsecond delay
            digitalWrite(trig2, 1); //trig pin set to high
            delayMicroseconds(10); //10 microsecond delay
            digitalWrite(trig2, 0); //trig pin set to low after 10 microseconds
            duration2 = pulseIn(echo2, HIGH); //stores the amount of time it took for US2 to receive the echo
            distance2 = (duration2 * 0.034) / 2.0; // finds how far away the car is by taking the amount of time it took for US1 to receive the echo and multiplying it by the speed of sound in air in centimeters per microseconds (0.034) and dividing that by two, since the sound had to travel there and back
            delay(500); //0.5 second delay
          }while (distance2 <=6); // US2 will detect if the car is still there and will not let the gate close until it moves
      digitalWrite(in4, 1); //Rotates the 2nd gate to the closed position
      delay(250); // 250 ms delay to allow the 2nd gate to rotate fully to the closed position
      digitalWrite(in4, 0); //Stops the 2nd gate motor
      delay(2000); // 2 second delay
 }

 void setup() {
  //OUTPUT Pins
  pinMode(red, OUTPUT); //Initializes the pin for the red LED as an output pin
  pinMode(yellow, OUTPUT); //Initializes the pin for the yellow LED as an output pin
  pinMode(green, OUTPUT); //Initializes the pin for the greeb LED as an output pin
  pinMode(trig1, OUTPUT); //Initializes the pin for US1's trigger pin as an output pin
  pinMode(trig2, OUTPUT);  //Initializes the pin for US2's trigger pin as an output pin
  pinMode(in1, OUTPUT); //Initializes the pin for the IN1 pin of the L298N as an output pin
  pinMode(in2, OUTPUT); //Initializes the pin for the IN2 pin of the L298N as an output pin
  pinMode(in3, OUTPUT); //Initializes the pin for the IN3 pin of the L298N as an output pin
  pinMode(in4, OUTPUT); //Initializes the pin for the IN4 pin of the L298N as an output pin
  pinMode(ena, OUTPUT); //Initializes the pin for the ENA pin of the L298N as an output pin
  pinMode(enb, OUTPUT); //Initializes the pin for the ENB pin of the L298N as an output pin

  //INPUT Pins
  pinMode(ir1, INPUT); //Initializes the pin for the output pin of the IRS1 as an input pin
  pinMode(ir2, INPUT); //Initializes the pin for the output pin of the IRS1 as an input pin
  pinMode(echo1, INPUT); //Initializes the pin for the echo pin of the US1 as an input pin
  pinMode(echo2, INPUT); //Initializes the pin for the echo pin of the US2 as an input pin
  
}

void loop() {
  //Standbye State: IRS1 and IRS2 are on and scanning, red LED on
  digitalWrite(red, 1);
  IRS1 = digitalRead(ir1);
  IRS2 = digitalRead(ir2);
 
  if (IRS1 || IRS2 == 1) //If IRS1 and IRS2 both equal 0, both spots are full, and the gates will not open
  {
    //First state: US1 on and scanning, red LED on
    digitalWrite(trig1, 0); //trig pin set to low
    delayMicroseconds(2); //2 microsecond delay
    digitalWrite(trig1, 1); //trig pin set to high
    delayMicroseconds(10); //10 microsecond delay
    digitalWrite(trig1, 0); //trig pin set to low after 10 microseconds
    duration1 = pulseIn(echo1, HIGH); //stores the amount of time it took for US1 to receive the echo
    distance1 = (duration1 * 0.034) / 2.0; // finds how far away the car is by taking the amount of time it took for US1 to receive the echo and multiplying it by the speed of sound in air in centimeters per microseconds (0.034) and dividing that by two, since the sound had to travel there and back

    //Second State: US1 detects car, red and yellow LEDs on, waiting for correct code. Does not happen if both parking spots are full.
    if (distance1 <= 10)
    {
      digitalWrite(yellow, 1);
      codedecimal = (digitalRead(code5) * 32) + (digitalRead(code4) * 16) + (digitalRead(code3) * 8) + (digitalRead(code2) * 4) + (digitalRead(code1) * 2) + digitalRead(code0);
      delay(2000);  

      //Third State: Gate 1 opens, only green LED on, delay of 10 seconds before gate 1 closes. Make sure gate does not close on car (US2 must detect car).
      if (password == codedecimal) //chec
      {
      digitalWrite(red, 0); //Turns off the red LED
      digitalWrite(yellow, 0); //Turns off the yellow LED
      digitalWrite(green, 1); //Turns on the green LED
      gate1(); //Executes the gate1 function to open and close the first gate
      
      //Fourth State: Gate 2 opens, only green LED on, delay of 10 seconds before gate 2 closes. Make sure gate does not close on car.
      gate2(); //Executes the gate2 function to open and close the second gate
      }
  }
  if(distance1 > 10) //Turns off the yellow LED light only if the car is gone
  {
  digitalWrite(yellow, 0); //Makes sure that the yellow LED is off
  }
  digitalWrite(green, 0); //Makes sure that the green LED is off
  delay(2000); //2 second delay before restarting the loop
}
}