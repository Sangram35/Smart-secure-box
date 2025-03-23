#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>

// Initialize LCD (RS, EN, D4, D5, D6, D7 pins)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Define keypad rows and columns
const byte ROWS = 4;
const byte COLS = 3;

// Keypad layout
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

// Connect keypad to pins
byte rowPins[ROWS] = {22, 23, 24, 25}; // Row pins
byte colPins[COLS] = {26, 27, 28};     // Column pins

// Create keypad object
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Predefined password
String password = "1234";
String input = "";

// Create Servo object
Servo myServo;

// Define servo pin
const int servoPin = 9;

void setup() {
  lcd.begin(16, 2);  // Set up LCD
  lcd.print("Enter code:");
  
  // Attach servo to the pin
  myServo.attach(servoPin);
  myServo.write(0);  // Start at 0 degrees (locked position)
}

void loop() {
  char key = keypad.getKey();  // Get key press

  if (key) {
    // If key is #, check password
    if (key == '#') {
      if (input == password) {
        lcd.clear();
        lcd.print("Access Granted");
        
        // Move servo to 90 degrees
        myServo.write(90);
        delay(2000);  // Keep open for 2 seconds

        // Return servo to 0 degrees (locked)
        myServo.write(0);
        delay(1000);  // Delay for smooth motion
        
        lcd.clear();
        lcd.print("Enter code:");
      } else {
        lcd.clear();
        lcd.print("Access Denied");
        delay(2000);  // Display for 2 seconds
        lcd.clear();
        lcd.print("Enter code:");
      }
      input = "";  // Reset input
    } else if (key == '*') {
      input = "";  // Reset input if * is pressed
      lcd.clear();
      lcd.print("Enter code:");
    } else {
      // Append key to input and display on LCD
      if (input.length() < 4) {
        input += key;
        lcd.setCursor(input.length() - 1, 1);
        lcd.print("*");  // Mask input with *
      }
    }
  }
}
