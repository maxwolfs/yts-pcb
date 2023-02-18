#include <Keyboard.h>

#define COLS 8
#define ROWS 4

int colPins[COLS] = { 21, 20, 19, 18, 15, 14, 16, 10 };
int rowPins[ROWS] = { 6, 7, 8, 9 };

// Define the keyboard matrix layout
char keys[ROWS][COLS] = {
  { '1', '2', '3', '4', '5', '6', '7', '8' },
  { 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i' },
  { 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k' },
  { 'z', 'x', 'c', 'v', 'b', 'n', 'm', '.' }
};

void setup() {
  //set up the column pins as outputs
  for (int i = 0; i < COLS; i++) {
    pinMode(colPins[i], INPUT_PULLUP);
  }

  //set up the row pins as outputs
  for (int i = 0; i < ROWS; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], HIGH);
  }

  //initialize the keyboard library
  Keyboard.begin();
}

void loop() {
  //scan the keyboard matrix
  for (int i = 0; i < ROWS; i++) {
    //activate the current row
    digitalWrite(rowPins[i], LOW);

    //check the columns for a key press
    for (int j = 0; j < COLS; j++) {
      if (digitalRead(colPins[j]) == LOW) {
        //send the key press to the computer
        Keyboard.write(keys[i][j]);
        // debounce
        delay(50);
      }
      // Wait for key to be released
      while (digitalRead(colPins[j]) == LOW) {}
    }

    //deactivate the current row
    digitalWrite(rowPins[i], HIGH);
  }
}