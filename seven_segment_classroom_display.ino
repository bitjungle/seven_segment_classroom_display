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

const int TOT_NAMES = 28; // Total number of names/lines to display
const int MODULES = 2; // Number of chained TM1638 modules

TM1638 modules[MODULES] = {
  // TM1638 dataPin, clockPin, strobe
  TM1638(9, 8, 7),
  TM1638(9, 8, 6)
};

// Each name is stored in a sequence of 16 bytes (two TM1638 modules)
byte names[TOT_NAMES][8*MODULES] = {
     {109, 118, 4, 121, 84, 0, 0, 0, 62, 111, 109, 0, 0, 0, 0, 0}, // SKien VgS
     {4, 112, 64, 6, 4, 84, 30, 119, 0, 0, 0, 0, 0, 0, 0, 0}, // it-linJA
     {64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64}, // ----------------
     {80, 28, 84, 121, 0, 55, 119, 112, 116, 16, 109, 121, 84, 0, 0, 0}, // runE MAthiSEn
     {55, 48, 55, 95, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Nina 
     {119, 84, 84, 16, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Amir
     {113, 80, 123, 94, 80, 16, 88, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Fredrik
     {120, 121, 63, 0, 56, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Teo
     {94, 121, 84, 48, 107, 0, 0, 0, 122, 121, 80, 111, 55, 119, 84, 84}, // Denis
     {80, 63, 84, 119, 56, 92, 0, 0, 63, 55, 63, 88, 96, 48, 0, 0}, // Ronald 
     {29, 63, 55, 119, 109, 0, 0, 0, 109, 63, 56, 127, 121, 49, 125, 0}, // Jonas S
     {91, 220, 116, 80, 220, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // zahra
     {118, 121, 49, 55, 55, 119, 84, 128, 128, 0, 0, 0, 0, 0, 0, 0}, // Herman 
     {118, 121, 84, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Kent 
     {55, 7, 119, 120, 118, 48, 119, 109, 0, 0, 0, 0, 0, 0, 0, 0}, // Mathias
     {62, 52, 123, 48, 122, 0, 122, 117, 109, 88, 88, 110, 80, 0, 0, 0}, // Ulrik
     {63, 119, 84, 16, 129, 56, 0, 0, 109, 119, 49, 14, 63, 55, 119, 119}, // Daniel 
     {109, 28, 56, 121, 110, 55, 119, 84, 0, 0, 109, 121,56,57,28, 118}, // Suleyman
     {109, 48, 125, 62, 121, 0, 0, 0, 84, 119, 121, 109, 109, 0, 0, 0}, // Sigve
     {62, 119, 109, 62, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // VASU
     {118, 119, 119, 112, 92, 84, 0, 212, 62, 62, 48, 84, 124, 121, 80, 125}, // Håkon
     {48, 109, 119, 118, 0, 0, 0, 0, 55, 121, 121, 84, 0, 0, 0, 0}, // Isak
     {62, 48, 56, 56, 48, 119, 55, 0, 56, 48, 119, 0, 0, 0, 0, 0}, // William
     {109, 62, 117, 80, 80, 117, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Sverre
     {109, 48, 84, 94, 80, 111, 0, 0, 119, 55, 119, 94, 121, 62, 109, 0}, // Sindre Amadeus
     {30, 92, 84, 119, 109, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Jonas
     {55, 117, 49, 73, 48, 84, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Martin
     {109, 125, 112, 125, 49, 48, 125, 109, 0, 0, 0, 0, 0, 0, 0, 0} //  Sakarias
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
    delay(3000);

    // Clear the 7-segment display modules
    for (int k = 0; k < MODULES; k++) {
      modules[k].clearDisplay();
    }
  }
}

