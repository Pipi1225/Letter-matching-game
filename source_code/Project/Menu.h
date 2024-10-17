#pragma once

#include "Struct.h"

using namespace std;

// Console setup

// Make console window have the resolution of the game
void makeFullScreen();

// Disable user resizing console window
void disableResizeWindow();

// Disable user using buttons: Minimize, Maximize
void disableCtrButton();

// Hide the scrollbar
void hideScrollbar(bool status);

// Hide the console cursor
void hideConsoleCursor(bool status);

// Setup the console window when run code
void setupConsole();

// Starting menu when run code
void startingMenu();

// Display Medium mode on the console window
void mediumMode(player& p, lst& list);

// Display Hard mode on the console window
void hardMode(player& p, lst& list);


// Print out the New Game menu on the console window
void NewGameMenu(lst& list);

// Print out the leader board on the console window (Top 10 player's record)
void LeaderBoardMenu(lst list);

// Print out the Information menu on the console window
void InformationMenu();
