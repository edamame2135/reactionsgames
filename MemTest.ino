// Reaction time experiment of one LED. 
// LED will flash 3 times before the start of the experiment.

// LED variables
int ledPick;
int ledPinR = 9;
int ledPinG = 10;
int ledPinB = 11;
int ledBrightness = 75;
int memArray[] = {0, 0, 0, 0, 0}; // Pattern array

// LED power states
int ledStateR = LOW;
int ledStateG = LOW;
int ledStateB = LOW;

// Button variables
int buttonPinR = 6;
int buttonStateR = LOW;
int buttonPinG = 5;
int buttonStateG = LOW;
int buttonPinB = 4;
int buttonStateB = LOW;

// Time variables
long randDelay;
long newT;
long oldT;
long deltaT;

// The setup function runs once when you press reset or power the board
void setup() {
  // initialize analog pins as an output.
  pinMode(ledPinR, OUTPUT);
  pinMode(ledPinR, OUTPUT);
  pinMode(ledPinR, OUTPUT);
  
  // Initialize button pins as input.
  pinMode(buttonPinR, INPUT);
  pinMode(buttonPinG, INPUT);
  pinMode(buttonPinB, INPUT);

  // Intialize serial communication.
  Serial.begin(9600);

  Serial.println("Prepare. Memory test measurements will begin shortly!");
  Serial.println("Instructions: Memorize the pattern of five colors from the LED. A second after the pattern is shown, the LED will turn white.");
  Serial.println("When this happens, repeat the pattern with the buttons on the breadboard and your time will be recorded");
  for (int i = 0; i <= 2; i++) {
    analogWrite(ledPinR, ledBrightness);
    analogWrite(ledPinG, ledBrightness);
    analogWrite(ledPinB, ledBrightness);
    delay(250);
    analogWrite(ledPinR, 0);
    analogWrite(ledPinG, 0);
    analogWrite(ledPinB, 0);
    delay(250);
  }
 
  randomSeed(analogRead(A0));
  randDelay = random(3000, 6000);
  delay(randDelay);
}

// the loop function runs over and over again forever
void loop() {

  //Always check to see if button is being pressed.
  buttonStateR = digitalRead(buttonPinR);
  buttonStateG = digitalRead(buttonPinG);
  buttonStateB = digitalRead(buttonPinB);

  for(int i = 0; i < 5; i++) { // Randomly pick colors for pattern and store them in array
    ledPick = random(0,3);
    memArray[i] = ledPick;
    switch(ledPick) {
      case 0:
        analogWrite(ledPinR, ledBrightness);
        break;
      case 1:
        analogWrite(ledPinG, ledBrightness);
        break;
      case 2:
        analogWrite(ledPinB, ledBrightness);
        break;
    }
    delay(500);
    analogWrite(ledPinR, 0);
    analogWrite(ledPinG, 0);
    analogWrite(ledPinB, 0);
    delay(500);    
  }
  delay(1000);
  oldT = millis();
  analogWrite(ledPinR, ledBrightness);
  analogWrite(ledPinG, ledBrightness);
  analogWrite(ledPinB, ledBrightness);
  int pointer = 0;
  while(1) {          // Progress through array by pressing buttons in the correct order and break when
    if(pointer == 5)  // all 5 buttons are pressed
        break;
    buttonStateR = digitalRead(buttonPinR);
    buttonStateG = digitalRead(buttonPinG);
    buttonStateB = digitalRead(buttonPinB);
    if(buttonStateR == HIGH && memArray[pointer] == 0) {
      pointer++;
      delay(100);
    }
    if(buttonStateG == HIGH && memArray[pointer] == 1) {
      pointer++;
      delay(100);
    }
    if(buttonStateB == HIGH && memArray[pointer] == 2) {
      pointer++;
      delay(100);
    }
  }
  analogWrite(ledPinR, 0);
  analogWrite(ledPinG, 0);
  analogWrite(ledPinB, 0);
  newT = millis();
  deltaT = newT - oldT;
  Serial.println(deltaT);
  delay(1000);
}
