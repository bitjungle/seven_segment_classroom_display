/*************************************************************************
 * Classroom display using Arduino and TM1638 modules
 * 
 * Used for learning classmates names, combined with
 * teaching about bits and bytes. 
 * 
 * For information on the TM1638 library used, see: 
 * https://github.com/rjbatista/tm1638-library
 * 
 * Copyright (C) 2018 BITJUNGLE Rune Mathisen
 * This code is licensed under a GPLv3 license 
 * See http://www.gnu.org/licenses/gpl-3.0.html 
 * 
 *************************************************************************/
 
#include <TM1638.h>

const int TOT_NAMES = 3; // Total number of names/lines to display
const int MODULES = 2; // Number of chained TM1638 modules

TM1638 modules[MODULES] = {
  // TM1638 dataPin, clockPin, strobe
  TM1638(9, 8, 7),
  TM1638(9, 8, 6)
};

// Each name is stored in a sequence of 16 bytes (two TM1638 modules)
byte names[TOT_NAMES][8*MODULES] = {
     { 80, 28, 84, 121, 0, 55, 119, 112, 116, 16, 109, 121, 84, 0, 0, 0}, // runE MAthiSEn
     { 124, 4, 112, 30, 28, 84, 111, 6, 121, 0, 0, 0, 0, 0, 0, 0}, // bitjungle
     { 109, 118, 4, 121, 84, 0, 62, 111, 109, 0, 0, 0, 0, 0, 0, 0} // SKien VgS
};


void setup() {
  // Clear all 7-segment display modules
  for (int i = 0; i < MODULES; i++) {
    modules[i].clearDisplay(); 
  }
  // Clear all LEDs
  for (int k = 0; k < MODULES; k++) {
    modules[k].setLEDs(0x0);
  }
}

void loop() {
  for (int i = 0; i < TOT_NAMES; i++) {
    // Split the 16 byte name array into two 8 byte arrays
    byte curr_name[MODULES][8];
    for (int j = 0; j < 16; j++) {
      if (j < 8) {
        curr_name[0][j] = names[i][j];
      } else { 
        curr_name[1][j-8] = names[i][j];
      }
    }

    // Set all 7-segment display modules
    for (int k = 0; k < MODULES; k++) {
      modules[k].setDisplay(curr_name[k]);
    }

    // Hold the display for x milliseconds before clearing it
    wait(3000);

    // Clear the 7-segment display modules
    for (int k = 0; k < MODULES; k++) {
      modules[k].clearDisplay();
    }
  }
}

void wait(int ms) { // argument ms is wait time in milliseconds
  int waitstep = floor(ms/3);
    // Do some fun with the LEDs
    modules[0].setLEDs(0x926D);
    modules[1].setLEDs(0x24DB);
    delay(waitstep);
    modules[0].setLEDs(0x24DB);
    modules[1].setLEDs(0x49B6);
    delay(waitstep);
    modules[0].setLEDs(0x49B6);
    modules[1].setLEDs(0x926D);
    delay(waitstep);
}

