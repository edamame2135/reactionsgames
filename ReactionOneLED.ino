// LED variables
int ledPick;
int ledPinR = 9;
int ledPinG = 10;
int ledPinB = 11;
int ledBrightness = 75;

// LED power states
int ledStateR = LOW;
int ledStateG = LOW;
int ledStateB = LOW;

// Button variable - one color
int buttonPin = 6;
int buttonState = LOW;

// Time variables
long randDelay;
long newT;
long oldT;
long deltaT;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPinR, OUTPUT);
  pinMode(ledPinR, OUTPUT);
  pinMode(ledPinR, OUTPUT);

  pinMode(buttonPin, INPUT);

  Serial.begin(9600);

  // Set up with flashing lights to signal the start 
  Serial.println("Prepare. Reaction time measurements will begin shortly!");
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
}

void loop() {
  // put your main code here, to run repeatedly:

  buttonState = digitalRead(buttonPin);

  // Critera for trial start.
  if (ledStateR == LOW && ledStateG == LOW && ledStateB == LOW && buttonState == LOW) {
      analogWrite(ledPinR, ledBrightness);
      oldT = millis();
      ledStateR = HIGH;
      ledStateG = LOW;
      ledStateB = LOW;
  }

  if (ledStateR == HIGH && buttonState == HIGH) {
    // Record time when button was pressed and turn off LED
    newT = millis();
    analogWrite(ledPinR, 0);

    // Print to console the time differnce between LED turn off to button pressed.
    deltaT = newT - oldT;
    Serial.print("1;");
    Serial.println(deltaT);

    // Reset trial and wait a random amount of time for next trial.
    ledStateR = LOW;
    randDelay = random(1000, 3000);
    delay(randDelay);
  }

}
