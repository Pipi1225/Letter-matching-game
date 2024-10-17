#pragma once

// GAME's CORE DEFINE
#define BOARDWIDTH 5
#define BOARDHEIGHT 8

// MOVE SET
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ESC_KEY 27
#define ENTER_KEY 13

// COLOR CODE
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define AQUA 3
#define RED 4
#define PURPLE 5
#define YELLOW 6
#define WHITE 7
#define GRAY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_AQUA 11
#define LIGHT_RED 12
#define LIGHT_PURPLE 13
#define LIGHT_YELLOW 14
#define BRIGHT_WHITE 15

// DEFINE SOUND EFFECT
#define MOVE_MENU 0
#define ENTER_MENU 1
#define MOVE 2
#define DSELECT 3
#define MATCHING 4
#define WINNING 5
#define LOSING 6
#define S_ERROR 7
#define NOTIFICATION 8

#include "Struct.h"

// Utility (Change color, go to position on console...)

// Setting the color of background and font on the console window
void setColor(int background, int font);

// Go to the position X, Y on the console window
void GoToXY(int posX, int posY);

// Play the sound effect
void playSound(int t);

// Save the new player's record to the Leaderboard
int posInLeaderboard(player p, lst& list);

// Play on the console window after the game ended (Ask if the player want to continue to the next stage or not)
void aftermathAction(player p, lst& list, int status, int index);

// win = true: Winn
// win = false: Lose
// See if you win or lose, then and print out on the console window
void displayStatus(bool win);

// Make W, A, S, D work as arrow keys and turn B -> b
int returnKey(int t);

// Setting player's status at the begining of the game, and let the player enter their name
void getPlayerPlayingInfo(player& p);


// For MEDIUM mode


// Basic Move on console window at game display time - for Medium mode
// KEY_UP, KEY_DOWN, KEY LEFT, KEY RIGHT, ENTER_KEY, ESC KEY
// B, b , W, w, A, a, S, s, D, s
void move(cell** board, position& pos, int& status, player& p, position selectedPos[], background bg, int& couple);

// Suggest two cells that can be matched in legal pattern (I, L, Z, U)
void suggestMove(cell** board);

// Creating the board to contain all essential data to help the game works - for Medium Mode
void initBoard(cell** board);

// flag = 0: There is no new matching cells
// flag > 0: There is A NEW matching cells
// Print out the backgound and all the cells of the board on the console window - for Medium Mode
void renderBoard(cell** board, background bg, int flag);

// Delete dynamic memory of the board
void deleteBoard(cell** &board);

// Print out the box that cover the cell board - for Medium Mode
void drawRectangle(cell** board, int left, int top);


// For HARD mode (Linked List)


// Delete one cell of the line
void deleteNode(cell2*& pLine, int x);

// Rearrange the positions of all the cells on one line
void resetBoard(cell2**& board, int x1, int y1, int x2, int y2);

// Return the length of one row
int getLineLength(cell2* pHead);

// Push information of one cell into board
void push(cell2*& board, cell2* pAdd);

// Find one cell in the board with position x, y
cell2* findTheNode(cell2** board, int x, int y);


// Basic Move on console window at game display time - for Hard mode
// KEY_UP, KEY_DOWN, KEY LEFT, KEY RIGHT, ENTER_KEY, ESC KEY
// B, b , W, w, A, a, S, s, D, s
void move2(cell2** board, position& pos, int& status, player& p, position selectedPos[], background bg, int& couple);

// Suggest two cells that can be matched in legal pattern (I, L, Z, U)
void suggestMove(cell2** board);

// Creating the board to contain all essential data to help the game works - for Hard Mode
void initBoard2(cell2**& board);

// flag = 0: There is no new matching cells
// flag > 0: There is A NEW matching cells
// Print out the backgound and all the cells of the board on the console window - for Hard Mode
void renderBoard(cell2** board, background bg, int flag);

// Delete all the cells of the board after game ended
void deleteBoard(cell2** board, background bg);

// Print out the box that cover the cell board - for Hard Mode
void drawRectangle(cell2** board, int left, int top);









