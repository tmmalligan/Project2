/*
 * Project 2: Real World Input and Output (Hardware)
 * By Taylor Malligan
 */
//constant variables
//const int ldrSensor = A1;// LDR sensor
const int pushButton = A0; //push button
int buttonCount = 0;
const int buttonState = 0;
const int redLED = 13; //the number of the LED pin
const int greenLED = 12; //the number of the LED pin
const int blueLED = 27; //the number of the LED pin
const int externalLED = 13;
const int internalLED = 12;
const int tempButton = A1;// LDR sensor

int sensorValue = 0;

//state tracker
int buttonCounter = 0;// counter for the number of button presses
//int buttonState = 0;// current state of the button
int lastButtonState = 0;// previous state of the button
int stateTracker = 0; //state tracker
int colourTracker = 0; //colour tracker
unsigned long previousMillis = 0; //LED timer to see when it was stored last
const long blink = 1000; //blink interval - using 1000 as its measured in milliseconds
int rgbState = HIGH;// RGB LED stat tracker


void setup() {
  Serial.begin(9600); //initialize serial communication at 9600 bits per second
  pinMode(redLED, OUTPUT); //red LED pin as an output
  pinMode(greenLED, OUTPUT); //green LED pin as an output
  pinMode(blueLED, OUTPUT); //blue LED pin as an output
  pinMode(pushButton, INPUT);// pushbutton pin as an input
  pinMode(tempButton, INPUT);//tempbutton pin as an input

  pinMode(externalLED, OUTPUT);//external led pin as an output
  pinMode(internalLED, OUTPUT);//internal led pin as an output
 
  pinMode(tempButton, INPUT);//LDR sensor
  Serial.begin(9600);
}

void loop() {  
  
  int buttonState=digitalRead(pushButton);
  delay(100);// delay
  // found on Arduino -- State Change Detection
  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == 1) {
      buttonCount++;
      Serial.println("On!");
      Serial.print("Number of Button Pushes: ");
      Serial.println(buttonCount);
    } else {
      // if the current state is LOW then the button went from on to off:
      Serial.println("Off!");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  lastButtonState = buttonState;
  
  switch (stateTracker) {
  case 0: // when button == 0
  Serial.println(" Welcome ");
  start();
  delay(100);
  break;

  case 1: //when button == 1
  Serial.println(" Colour Changer ");
  changeColour();
  delay(100);
  break;

  case 2: //when button == 2
  Serial.println(" Blinker ;) ");
  blinker();
  delay(100);
  break;

  case 3: //when button == 3
  Serial.println(" Temperature Colour Change ");
  temperature(); 
  delay(100);
  break;

  case 4: //when button == 4
  Serial.println(" THE END ");
  theEnd();
  delay(100);
  break;
  }
 
}  
 
 void start(){ // start off with rgb to pink
  digitalWrite(greenLED, HIGH);
  digitalWrite(blueLED, HIGH);
  }
  

void changeColour(){
  int change = random(7); // random 7 numbers (0-6) to change colour
 
    //to change colour of rgb using switch statement:
    switch(change){
     case 0: // if change == 0 (red)
     digitalWrite(redLED,HIGH);
     delay(1000);
     digitalWrite(redLED, LOW); //
     break;
     
     case 1: //if change == 1 (green)
     digitalWrite(greenLED, HIGH);
     delay(1000);
     digitalWrite(greenLED,LOW);
     break;
     
     case 2: //if change == 2 (blue)
     digitalWrite(blueLED, HIGH);
     delay(1000);
     digitalWrite(blueLED,LOW);
     break;
     
     case 3: //if change == 3 (yellow)
     digitalWrite(redLED, HIGH);
     digitalWrite(greenLED, HIGH);
     delay(1000);
     digitalWrite(redLED, 0);
     digitalWrite(greenLED, LOW);
     break;
     
     case 4: //if change == 4 (light blue)
     digitalWrite(redLED, 168);
     digitalWrite(blueLED, HIGH);
     delay(1000);
     digitalWrite(redLED, 0);
     digitalWrite(blueLED, LOW);
     break;

     case 5: //if change == 5 (pink)
     digitalWrite(greenLED, HIGH);
     digitalWrite(blueLED, HIGH);
     delay(1000);
     digitalWrite(greenLED, LOW);
     digitalWrite(blueLED, LOW);
     break;
     
     case 6: //if change == 6 (white)
     digitalWrite(redLED, 100);
     digitalWrite(blueLED, HIGH);
     digitalWrite(greenLED, HIGH);
     delay(1000);
     digitalWrite(redLED, 0);
     digitalWrite(blueLED, LOW);
     digitalWrite(greenLED, HIGH);
     break; 
    }
    
    
} 

 void temperature(){//Adjusts lights according to input from LDR sensor
  const int hot = 87;
  const int cold = 75;
 
  int sensorValue = analogRead(tempButton);

  float voltage = (sensorValue / 1024.0) * 5.0;
  float tempC = (voltage - .5) * 100;
  float tempF = (tempC * 1.8) + 32;
  Serial.print("Temp: ");
  Serial.print(tempF);
  
  if(tempF <= cold) // if temperature is cold
  {
    digitalWrite(redLED, HIGH);     
    digitalWrite(blueLED, LOW);      
    digitalWrite(greenLED, LOW);
    Serial.print("brrr it's cold...;(");  
  }
  else if(tempF >= hot) // if temperature is hot
  {
    digitalWrite(redLED, LOW);      
    digitalWrite(blueLED, HIGH);        
    digitalWrite(greenLED, LOW);
    Serial.print("I am sweating! :O");      
  }
  else { // if temperature is perfect

    digitalWrite(redLED, LOW);     
    digitalWrite(blueLED, LOW);   
    digitalWrite(greenLED, HIGH);
    Serial.print("sweater weather :')");  
    }
    delay(100);
 }
 
void blinker(){ // blink state using switch to change colour
  unsigned long currentMillis = millis(); //current blinker

  if (currentMillis - previousMillis > blink) {
    previousMillis = currentMillis;
    if(rgbState == LOW){
     rgbState = HIGH;
     colourTracker++;
    }
    else {
      rgbState == HIGH;
      
    }
    digitalWrite(internalLED, HIGH);
    digitalWrite(externalLED, HIGH );

    if(colourTracker % 6 == 0){
      digitalWrite(blueLED, stateTracker);
    }
    else if(colourTracker % 4 == 0){
      digitalWrite(redLED, stateTracker);
  }
    else if(colourTracker %2 == 0){
      digitalWrite(greenLED, stateTracker);
  }
  }
}  
 
 void theEnd(){ //end of program
  digitalWrite(redLED, LOW);  
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, LOW);
  digitalWrite(externalLED, LOW);
  digitalWrite(internalLED, LOW);
 }
