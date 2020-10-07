 /*
  Rotary Encoder Demo
  rot-encode-demo.ino
  Demonstrates operation of Rotary Encoder
  Displays results on Serial Monitor
  DroneBot Workshop 2019
  https://dronebotworkshop.com
*/
 
 // Rotary Encoder Inputs
 #define inputCLK 4
 #define inputDT 5
 
 // LED Outputs
 #define ledCW 8
 #define ledCCW 9

 int counter = 0;
 int setpCounter = 0;
 int currentStateCLK;
 int previousStateCLK; 

 String encdir ="";

 void setup() { 
   
   // Set encoder pins as inputs  
   pinMode (inputCLK,INPUT);
   pinMode (inputDT,INPUT);
   
   // Set LED pins as outputs
   pinMode (ledCW,OUTPUT);
   pinMode (ledCCW,OUTPUT);
   
   // Setup Serial Monitor
   Serial.begin (19200);
   
   // Read the initial state of inputCLK
   // Assign to previousStateCLK variable
   previousStateCLK = digitalRead(inputCLK);

 } 

 void loop() { 
  
  // Read the current state of inputCLK
   currentStateCLK = digitalRead(inputCLK);
    
   // If the previous and the current state of the inputCLK are different then a pulse has occured
   if (currentStateCLK != previousStateCLK){ 
       
     // If the inputDT state is different than the inputCLK state then 
     // the encoder is rotating counterclockwise
     if (digitalRead(inputDT) != currentStateCLK) { 
       counter =-1;
       setpCounter += 1;
       encdir ="CCW";
       digitalWrite(ledCW, LOW);
       digitalWrite(ledCCW, HIGH);
       
     } 
     else {
       // Encoder is rotating clockwise
       counter =1;
       setpCounter += 1;
       encdir ="CW";
       digitalWrite(ledCW, HIGH);
       digitalWrite(ledCCW, LOW);
       
     }
   
   // if(setpCounter % 2 ==0)
     Serial.println(counter);
   } 
   // Update previousStateCLK with the current state
   previousStateCLK = currentStateCLK; 
 }
