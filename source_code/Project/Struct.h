#pragma once

#include <string>
#include <vector>

using namespace std;

// Position of one cell in the board
struct position {
	int x, y;
};

// Player information
struct player {
	//Player's name
	string name;

	//Player's point
	int point = 0;
	
	//Player's life (each player only have 3 lifes)
	int life = 3;

	//Player's current stage (the less the better)
	int stages = 1;

	//Play mode 
	//0 = NOT PLAYING
	//1 = MEDIUM
	//2 = HARD
	int mode = 0;
};

// List of players
struct lst {
	vector<player> Player;

	// Write the rank data  to file
	void writeRanked();

	// Read the rank data from file text
	void readRanked();
};

// Game background
struct background {
	char bg[33][52];

	// Read the background data from file text
	void getBackground();

	// Print the background on the console window
	void displayBackground(int x, int y);
};

// Cell of Medium Mode
struct cell {
	position pos;
	char val = ' ';

	// isValid = 0: blank space
	// isValid = 1: cell
	// 
	// isSelected = 0: false
	// isSelected = 1: true
	bool isValid = 1, isSelected = 0;

	// Draw box cell on the console window with different colors - for Medium Mode
	void drawBox(int);

	// Delete box cell on the console window - for Medium Mode
	void deleteBox();
};

// Cell of Hard Mode
struct cell2 {
	position pos;
	char val = ' ';


	// isSelected = 0: false
	// isSelected = 1: true
	bool isSelected = 0;


	// Draw box cell on the console window with different colors - for Hard Mode
	void drawBox(int);

	// Delete box cell on the console window - for Hard Mode
	void deleteBox();

	cell2* pNext;
};


