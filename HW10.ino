
const int greenLedPins[] = {2, 3, 4, 5, 6};  // pin for the green LED
const int blueLedPin = 7;       //pin for the blue LED
const int yellowLedPin = 8;     // pin for the yellow LED
const int greenLedCount = 5;    // Number of green LEDs

void setup() {
  // setting pinmode for all leds
  for (int i = 0; i < greenLedCount; i++) {
    pinMode(greenLedPins[i], OUTPUT);
  }

  pinMode(blueLedPin, OUTPUT);

  pinMode(yellowLedPin, OUTPUT);
}

void loop() {
  // Get the current time in milliseconds
  unsigned long currentTime = millis(); //due to my research c++ need to use "unsigned long" to extend size variables for number storage?

  int secondNow = (currentTime / 1000) % 60; // current second in the minute (0-59)

  // Count the progress in milliseconds of the current minute (0-59999)
  int minuteProgress = currentTime % 60000;

  // Control the state of each green LED based on the current second
  for (int i = 0; i < greenLedCount; i++) {
    // Turn on the LED if the current second is equal to or has already past the line (every 10 seconds)
    digitalWrite(greenLedPins[i], secondNow >= (i + 1) * 10 ? HIGH : LOW);
  }

  // Blink the blue LED every second, turn on/off every half second
  digitalWrite(blueLedPin, (secondNow % 2) == 0);

  // using map() to turn the minuteProgress into brightness
  int brightness = map(minuteProgress, 0, 60000, 0, 2000);

  //I can't get analogWrite() to work, but I found a tutoral using ledc to control fading of light, so I followed that for this assignment.
  // Attach the yellow LED to LEDC channel 0 for PWM control
  ledcAttachPin(yellowLedPin, 0);

  ledcSetup(0, 5000, 8);

  ledcWrite(0, brightness);

  delay(50);
}