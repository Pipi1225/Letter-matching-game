#pragma once

#include "Struct.h"

// Print the game logo on the console window
void printLogo();

// Creating box to contain other things and print out the infomation
void setupPlayInfo(player& p);


// For both mode


// Draw the horizontal line (X line) when matching X success
void drawLineX(int x1, int y1, int x2, int y2);

// Draw the vertical line (Y line) when matching Y success
void drawLineY(int x1, int y1, int x2, int y2);

// Draw the vertical line (Y line) or horizontal line (X line) when matching I success
void drawLineI(int x1, int y1, int x2, int y2);


// For mode MEDIUM

// Draw the L line when matching L success - for Medium Mode
void drawLineL(cell** board, int x1, int y1, int x2, int y2);

// Draw the Z line when matching Z success - for Medium Mode
void drawLineZ(cell** board, int x1, int y1, int x2, int y2);

// Draw the U line when matching U success - for Medium Mode
void drawLineU(cell** board, int x1, int y1, int x2, int y2);


// For mode HARD

// Draw the L line when matching L success - for Hard Mode
void drawLineL(cell2** board, int x1, int y1, int x2, int y2);

// Draw the Z line when matching Z success - for Hard Mode
void drawLineZ(cell2** board, int x1, int y1, int x2, int y2);

// Draw the U line when matching U success - for Hard Mode
void drawLineU(cell2** board, int x1, int y1, int x2, int y2);

