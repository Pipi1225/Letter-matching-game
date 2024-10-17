#pragma once

#include "Struct.h"

// For medium mode


// Check if the two cells can be matched together or not in line X (Horizontal line) - for Medium Mode
bool checkLineX(cell** board, int x1, int y1, int x2, int y2);

// Check if the two cells can be matched together or not in line Y (Vertical line) - for Medium Mode
bool checkLineY(cell** board, int x1, int y1, int x2, int y2);

// Check if the two cells can be matched together or not in line I (X line or Y line) - for Medium Mode
bool checkLineI(cell** board, int x1, int y1, int x2, int y2);

// Check if the two cells can be matched together or not in line L - for Medium Mode
bool checkLineL(cell** board, int x1, int y1, int x2, int y2);

// Check if the two cells can be matched together or not in line Z - for Medium Mode
bool checkLineZ(cell** board, int x1, int y1, int x2, int y2);

// Check if the two cells can be matched together or not in line U - for Medium Mode
bool checkLineU(cell** board, int x1, int y1, int x2, int y2);

// 0: False
// 2: Matching I
// 3: Matching L
// 4: Matching Z
// 5: Matching U
// Check if the two cells can be matched together or not in all line (I, L, Z, U) - for Medium Mode
int allCheck(cell** board, int x1, int y1, int x2, int y2);

// Check if there is any pair that can be matched or not - for Medium Mode
bool checkValidPair(cell** board);

// Check if there is any cell still exist or not - for Medium Mode
bool checkCellExist(cell** board);


// For hard mode


// Check if the two cells can be matched together or not in line X (Horizontal line)- for Hard Mode
bool checkLineX(cell2** board, int x1, int y1, int x2, int y2);

// Check if the two cells can be matched together or not in line Y (Vertical line) - for Hard Mode
bool checkLineY(cell2** board, int x1, int y1, int x2, int y2);

// Check if the two cells can be matched together or not in line I (X line or Y line) - for Hard Mode
bool checkLineI(cell2** board, int x1, int y1, int x2, int y2);

// Check if the two cells can be matched together or not in line L - for Hard Mode
bool checkLineL(cell2** board, int x1, int y1, int x2, int y2);

// Check if the two cells can be matched together or not in line Z - for Hard Mode
bool checkLineZ(cell2** board, int x1, int y1, int x2, int y2);

// Check if the two cells can be matched together or not in line U - for Hard Mode
bool checkLineU(cell2** board, int x1, int y1, int x2, int y2);

// 0: False
// 2: Matching I
// 3: Matching L
// 4: Matching Z
// 5: Matching U
// check if the two cells can be matched together or not in all line (I, L, Z, U) - for Hard Mode
int allCheck(cell2** board, int x1, int y1, int x2, int y2);

// Check if there is any pair that can be matched or not - for Hard Mode
bool checkValidPair(cell2** board);

// Check if there is any cell still exist or not - for Hard Mode
bool checkCellExist(cell2** board);