/*

  Morse Code Blinker by Ratanak Sovann (219339559)
  This file was created as part of Task 1.1P – SIT210 Embedded System Development.


  Description
  ––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
  This program blinks an LED to spell out a name in Morse code when a button is pressed.
  It defines the pin configurations, timing for Morse code symbols, and the Morse code
  for each letter. The LED blinks according to the Morse code of the name defined in the program.
  Pressing the button starts or restarts the blinking sequence.

*/




// Pin definitions for LED and button
const int ledPin = LED_BUILTIN;
const int buttonPin = 2;

// Timing definitions for Morse code units
const int dotTime = 250; // Duration of a dot
const int dashTime = dotTime * 3; // Duration of a dash
const int partGap = dotTime; // Gap between dots and dashes within a letter
const int letterGap = dotTime * 3; // Gap between letters
const int wordGap = dotTime * 7; // Gap between words

// Morse code for each letter of the alphabet (A-Z)
const String morseCode[26] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
  "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
  "..-", "...-", ".--", "-..-", "-.--", "--.."
};

// The name to blink in Morse code.
String name = "RATANAK";

// Flag to track button state
bool buttonPressed = false;

void setup() {
  pinMode(ledPin, OUTPUT); // Set the LED pin as output
  pinMode(buttonPin, INPUT_PULLUP); // Set the button pin as input with internal pull-up
  attachInterrupt(digitalPinToInterrupt(buttonPin), pressButton, FALLING); // Setup interrupt for button press
}

void loop() {
  if (buttonPressed) {
    for (int i = 0; i < name.length(); i++) {
      if (!buttonPressed) { // Check if button was pressed again during blinking
        pressButton(); // Revert buttonPressed state
        break; // Exit the for loop
      }
      blinkLetter(name[i]); // Blink the current letter in Morse code
      delay(letterGap); // Wait after blinking each letter
    }
  }
}

// Blinks an LED to represent a letter in Morse code
void blinkLetter(char letter) {
  if (letter == ' ') {
    delay(wordGap); // If letter is a space, delay for word gap
    return;
  }
  String code = morseCode[letter - 'A']; // Convert char to index using its ASCII value
  for (int i = 0; i < code.length(); i++) {
    digitalWrite(ledPin, HIGH); // Turn on LED
    // Determine whether to blink for a dot or a dash
    if (code[i] == '.') {
      delay(dotTime); // Blink duration for dot
    } else if (code[i] == '-') {
      delay(dashTime); // Blink duration for dash
    }
    digitalWrite(ledPin, LOW); // Turn off LED
    delay(partGap); // Gap between parts of the same letter
  }
}

// This function is triggered when buttonPin is interupted (pressed).
void pressButton() {
  buttonPressed = !buttonPressed; // Toggle flag on button press
}








