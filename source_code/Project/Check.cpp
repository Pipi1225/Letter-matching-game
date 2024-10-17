#include <iostream>
#include <algorithm>

#include "Struct.h"
#include "Core.h"

using namespace std;

// ======Medium mode=================================================================


// https://cachhoc.net/2014/03/25/thuat-toan-game-pokemon-pikachu/
// Check if the two cells can be matched together or not in line X (Horizontal line) - for Medium Mode
bool checkLineX(cell** board, int x1, int y1, int x2, int y2) {

	// -------------
	
	// Determine the coordinates of the leftmost and rightmost cell
	int min_x = min(x1, x2);
	int max_x = max(x1, x2);
	int y = y1;

	// Check between the cells (x1 and x2) if there is any cell valid -> return false
	for (int i = min_x + 1; i < max_x; i++) {
		if (board[y][i].isValid) return false;
	}

	// If no valid cell was found between x1 and x2, return true (valid connection)
	return true;
}



// https://cachhoc.net/2014/03/25/thuat-toan-game-pokemon-pikachu/
// Check if the two cells can be matched together or not in line Y (Vertical line) - for Medium Mode
bool checkLineY(cell** board, int x1, int y1, int x2, int y2) {
	
	// |
	// |
	// |

	// Determine the coordinates of the topmost and bottommost cell
	int min_y = min(y1, y2);
	int max_y = max(y1, y2);
	int x = x1;

	// Check between the cells (y1 and y2) if there is any cell valid -> return false
	for (int i = min_y + 1; i < max_y; i++) {
		if (board[i][x].isValid) return false;
	}

	// If no valid cell was found between y1 and y2, return true (valid connection)
	return true;
}

// Check if the two cells can be matched together or not in line I (X line or Y line) - for Medium Mode
bool checkLineI(cell** board, int x1, int y1, int x2, int y2) {

	// If the two cells is on the same line -> Check for vertical match
	if (x1 == x2) {
		if (checkLineY(board, x1, y1, x2, y2)) return true;
	}

	// If the two cells is on the same column -> Check for horizontal match
	if (y1 == y2) {
		if (checkLineX(board, x1, y1, x2, y2)) return true;
	}

	// If none of the check is true, return false (invalid connection)
	return false;
}

// Check if the two cells can be matched together or not in line L - for Medium Mode
bool checkLineL(cell** board, int x1, int y1, int x2, int y2) {
	
	// Ensure x1 <= x2
	if (x1 > x2) {
		swap(x1, x2);
		swap(y1, y2);
	}

	//  A----|          C----B
	//  |    |    and   |    |
	//  C----B          A----|

	// Choose the cell C(x1, y2)
	int x3 = x1;
	int y3 = y2;

	// Check for L - shape with corner at C
	if (board[y3][x3].isValid == 0) { // Check if corner cell is empty
		if (checkLineI(board, x1, y1, x3, y3) && checkLineI(board, x3, y3, x2, y2)) return true; // (Valid connection)
	}

	//  A----C          |----B
	//  |    |    and   |    |
	//  |----B          A----C

	// Rechoose the cell C(x2, y1)
	x3 = x2;
	y3 = y1;

	// Check for L - shape with corner at C
	if (board[y3][x3].isValid == 0) {
		if (checkLineI(board, x1, y1, x3, y3) && checkLineI(board, x3, y3, x2, y2)) return true; // (Valid connection)
	}

	// If none of the check is true, return false (invalid connection)
	return false;
}

// Check if the two cells can be matched together or not in line Z - for Medium Mode
bool checkLineZ(cell** board, int x1, int y1, int x2, int y2) {
	// |__      and     __|
	//    |            |

	// Choose C(x1, i) and C'(x2, i)
	int x3 = x1;
	int x4 = x2;

	// Check for Z-shape with diagonal line going down - right - down (x1 < x2, else diagonal line going up - right - up)
	if (y1 < y2) {
		for (int i = y1 + 1; i < y2; i++) {
			if ((board[i][x3].isValid == 0) && (board[i][x4].isValid == 0)) {
				if (checkLineI(board, x1, y1, x3, i) && checkLineI(board, x3, i, x4, i) && checkLineI(board, x4, i, x2, y2)) return true;
			}
		}
	}

	// Check for Z-shape with diagonal line going up - right - up (x1 < x2, else diagonal line going down - right - down)
	else {
		for (int i = y2 + 1; i < y1; i++) {
			if ((board[i][x3].isValid == 0) && (board[i][x4].isValid == 0)) {
				if (checkLineI(board, x1, y1, x3, i) && checkLineI(board, x3, i, x4, i) && checkLineI(board, x4, i, x2, y2)) return true;
			}
		}
	}

	// __       and      __
	//   |__          __|

	// Rechoose C(i, y1) and C'(i, y2)
	int y3 = y1;
	int y4 = y2;

	// Check for Z-shape with diagonal line going right - down - right (y1 < y2, else diagonal line going right - up - right)
	if (x1 < x2) {
		for (int i = x1 + 1; i < x2; i++) {
			if ((board[y3][i].isValid == 0) && (board[y4][i].isValid == 0)) {
				if (checkLineI(board, x1, y1, i, y3) && checkLineI(board, i, y3, i, y4) && checkLineI(board, i, y4, x2, y2)) return true;
			}
		}
	}

	// Check for Z-shape with diagonal line going right - up - right (y1 < y2, else diagonal line going right - down - right
	else {
		for (int i = x2 + 1; i < x1; i++) {
			if ((board[y3][i].isValid == 0) && (board[y4][i].isValid == 0)) {
				if (checkLineI(board, x1, y1, i, y3) && checkLineI(board, i, y3, i, y4) && checkLineI(board, i, y4, x2, y2)) return true;
			}
		}
	}

	// If none of the check is true, return false (invalid connection)
	return false;
}

// Check if the two cells can be matched together or not in line U - for Medium Mode
bool checkLineU(cell** board, int x1, int y1, int x2, int y2) {

	// Handle cells on edges or corners (instant U-shapes):
	if (x1 == 0 && x2 == 0) return true;
	if ((x1 == (BOARDWIDTH - 1)) && (x2 == (BOARDWIDTH - 1))) return true;
	if (y1 == 0 && y2 == 0) return true;
	if ((y1 == (BOARDHEIGHT - 1)) && (y2 == (BOARDHEIGHT - 1))) return true;

	// Upper U (line going up - right - up)
	if (y1 == 0 || y2 == 0) { // One of them is on the first line
		if (y1 == 0 && (board[0][x2].isValid == 0) && checkLineI(board, x2, 0, x2, y2)) return true;
		if (y2 == 0 && (board[0][x1].isValid == 0) && checkLineI(board, x1, 0, x1, y1)) return true;
	}

	// Choose C(x1, i) and C'(x2, i)
	int x3 = x1;
	int x4 = x2;

	// The line start from the lower cell
	if (y1 <= y2) {
		for (int i = y1 - 1; i >= -1; i--) { // Check line from the lower line to the the highest line

			// If the line reached the two toppest cells
			if (i == -1) {
				if ((board[0][x3].isValid == 0) && (board[0][x4].isValid == 0)) {
					if (checkLineI(board, x1, y1, x3, 0) && checkLineI(board, x4, 0, x2, y2)) return true;
				}
				break;
			}
			if ((board[i][x3].isValid == 0) && (board[i][x4].isValid == 0)) {
				if (checkLineI(board, x1, y1, x3, i) && checkLineI(board, x3, i, x4, i) && checkLineI(board, x4, i, x2, y2)) return true;
			}
		}
	}
	else { // y1 > y2 // The same with the previous case
		for (int i = y2 - 1; i >= -1; i--) {
			if (i == -1) {
				if ((board[0][x3].isValid == 0) && (board[0][x4].isValid == 0)) {
					if (checkLineI(board, x1, y1, x3, 0) && checkLineI(board, x4, 0, x2, y2)) return true;
				}
				break;
			}
			if ((board[i][x3].isValid == 0) && (board[i][x4].isValid == 0)) {
				if (checkLineI(board, x1, y1, x3, i) && checkLineI(board, x3, i, x4, i) && checkLineI(board, x4, i, x2, y2)) return true;
			}
		}
	}

	// Lower U (line going down - right - down)
	if ((y1 == BOARDHEIGHT - 1) || (y2 == BOARDHEIGHT - 1)) { // One of them is on the last line
		if ((y1 == BOARDHEIGHT - 1) && (board[BOARDHEIGHT - 1][x2].isValid == 0) && checkLineI(board, x2, BOARDHEIGHT - 1, x2, y2)) return true;
		if ((y2 == BOARDHEIGHT - 1) && (board[BOARDHEIGHT - 1][x1].isValid == 0) && checkLineI(board, x1, BOARDHEIGHT - 1, x1, y1)) return true;
	}

	// The line start from the upper cell 
	// The code is almost the same at upper U, but in this case we check line from the upper line to the the lowest line
	if (y1 <= y2) {
		for (int i = y2 + 1; i <= BOARDHEIGHT; i++) { // Check line from the upper line to the the lowest line
			
			// If the line reached the lowest line
			if (i == BOARDHEIGHT) {
				if ((board[BOARDHEIGHT - 1][x3].isValid == 0) && (board[BOARDHEIGHT - 1][x4].isValid == 0)) {
					if (checkLineI(board, x1, y1, x3, BOARDHEIGHT - 1) && checkLineI(board, x4, BOARDHEIGHT - 1, x2, y2)) return true;
				}
				break;
			}

			if ((board[i][x3].isValid == 0) && (board[i][x4].isValid == 0)) {
				if (checkLineI(board, x1, y1, x3, i) && checkLineI(board, x3, i, x4, i) && checkLineI(board, x4, i, x2, y2)) return true;
			}
		}
	}
	else { // y1 > y2 // The same with the previous case
		for (int i = y1 + 1; i <= BOARDHEIGHT; i++) {
			if (i == BOARDHEIGHT) {
				if ((board[BOARDHEIGHT - 1][x3].isValid == 0) && (board[BOARDHEIGHT - 1][x4].isValid == 0)) {
					if (checkLineI(board, x1, y1, x3, BOARDHEIGHT - 1) && checkLineI(board, x4, BOARDHEIGHT - 1, x2, y2)) return true;
				}
				break;
			}

			if ((board[i][x3].isValid == 0) && (board[i][x4].isValid == 0)) {
				if (checkLineI(board, x1, y1, x3, i) && checkLineI(board, x3, i, x4, i) && checkLineI(board, x4, i, x2, y2)) return true;
			}
		}
	}

	// Left U (line going left - down - left)
	if (x1 == 0 || x2 == 0) { // One of them is on the fisrt column
		if (x1 == 0 && (board[y2][0].isValid == 0) && checkLineI(board, 0, y2, x2, y2)) return true;
		if (x2 == 0 && (board[y1][0].isValid == 0) && checkLineI(board, 0, y1, x1, y1)) return true;
	}

	// Rechoose C(i, y1) and C'(i, y2)
	int y3 = y1;
	int y4 = y2;

	// The column start from more right cell
	if (x1 <= x2) {
		for (int i = x1 - 1; i >= -1; i--) { // Check column from the more right column to the the most left column

			// If the column reached the two most left cells
			if (i == -1) {
				if ((board[y3][0].isValid == 0) && (board[y4][0].isValid == 0)) {
					if (checkLineI(board, x1, y1, 0, y3) && checkLineI(board, 0, y4, x2, y2)) return true;
				}
				break;
			}
			if ((board[y3][i].isValid == 0) && (board[y4][i].isValid == 0)) {
				if (checkLineI(board, x1, y1, i, y3) && checkLineI(board, i, y3, i, y4) && checkLineI(board, i, y4, x2, y2)) return true;
			}
		}
	}
	else { // x1 > x2 // the same with the previous case
		for (int i = x2 - 1; i >= -1; i--) {
			if (i == -1) {
				if ((board[y3][0].isValid == 0) && (board[y4][0].isValid == 0)) {
					if (checkLineI(board, x1, y1, 0, y3) && checkLineI(board, 0, y4, x2, y2)) return true;
				}
				break;
			}
			if ((board[y3][i].isValid == 0) && (board[y4][i].isValid == 0)) {
				if (checkLineI(board, x1, y1, i, y3) && checkLineI(board, i, y3, i, y4) && checkLineI(board, i, y4, x2, y2)) return true;
			}
		}
	}

	// Right U (line going right - down - right)
	if ((x1 == BOARDWIDTH - 1) || (x2 == BOARDWIDTH - 1)) { // one of them is on the last column
		if ((x1 == BOARDWIDTH - 1) && (board[y2][BOARDWIDTH - 1].isValid == 0) && checkLineI(board, BOARDWIDTH - 1, y2, x2, y2)) return true;
		if ((x2 == BOARDWIDTH - 1) && (board[y1][BOARDWIDTH - 1].isValid == 0) && checkLineI(board, BOARDWIDTH - 1, y1, x1, y1)) return true;
	}

	// The column start from the more left cell 
    // The code is almost the same at left U, but in this case we check column from the more left column to the the most right column
	if (x1 <= x2) {
		for (int i = x2 + 1; i <= BOARDWIDTH; i++) { // Check column from the more left column to the the most right column

			// If the column reached the two most right cells
			if (i == BOARDWIDTH) {
				if ((board[y3][BOARDWIDTH - 1].isValid == 0) && (board[y4][BOARDWIDTH - 1].isValid == 0)) {
					if (checkLineI(board, x1, y1, BOARDWIDTH - 1, y3) && checkLineI(board, BOARDWIDTH - 1, y4, x2, y2)) return true;
				}
				break;
			}
			if ((board[y3][i].isValid == 0) && (board[y4][i].isValid == 0)) {
				if (checkLineI(board, x1, y1, i, y3) && checkLineI(board, i, y3, i, y4) && checkLineI(board, i, y4, x2, y2)) return true;
			}
		}
	}
	else { // x1 > x2 // the same with the previous case
		for (int i = x1 + 1; i <= BOARDWIDTH; i++) {
			if (i == BOARDWIDTH) {
				if ((board[y3][BOARDWIDTH - 1].isValid == 0) && (board[y4][BOARDWIDTH - 1].isValid == 0)) {
					if (checkLineI(board, x1, y1, BOARDWIDTH - 1, y3) && checkLineI(board, BOARDWIDTH - 1, y4, x2, y2)) return true;
				}
				break;
			}
			if ((board[y3][i].isValid == 0) && (board[y4][i].isValid == 0)) {
				if (checkLineI(board, x1, y1, i, y3) && checkLineI(board, i, y3, i, y4) && checkLineI(board, i, y4, x2, y2)) return true;
			}
		}
	}

	// If none of the check is true, return false (invalid connection)
	return false;
}

// 0: False
// 2: Matching I
// 3: Matching L
// 4: Matching Z
// 5: Matching U
// Check if the two cells can be matched together or not in all line (I, L, Z, U) - for Medium Mode
int allCheck(cell** board, int x1, int y1, int x2, int y2) {
	if (board[y1][x1].val != board[y2][x2].val) return false;
	if (x1 == x2 && y1 == y2) return false;
	if (checkLineI(board, x1, y1, x2, y2)) {
		return 2;
	}
	if (checkLineL(board, x1, y1, x2, y2)) {
		return 3;
	}
	if (checkLineZ(board, x1, y1, x2, y2)) {
		return 4;
	}
	if (checkLineU(board, x1, y1, x2, y2)) {
		return 5;
	}
	return 0;
}

// Check if there is any pair that can be matched or not - for Medium Mode
bool checkValidPair(cell** board) {
	for (int i = 0; i < BOARDHEIGHT; i++) {
		for (int j = 0; j < BOARDWIDTH; j++) {

			if (board[i][j].isValid != 0) {
				for (int x = 0; x < BOARDHEIGHT; x++) {
					for (int y = 0; y < BOARDWIDTH; y++) {
						if (x != i || y != j) {
							if (allCheck(board, j, i, y, x) && board[x][y].isValid != 0) return true;
						}						
					}
				}
			}
		}
	}
	return false;
}

// Check if there is any cell still exist or not - for Medium Mode
bool checkCellExist(cell** board) {
	for (int i = 0; i < BOARDHEIGHT; i++) {
		for (int j = 0; j < BOARDWIDTH; j++) {
			if (board[i][j].isValid != 0) {
				return true;
			}
		}
	}
	return false;
}



// ======Hard mode=================================================================


// Check if the two cells can be matched together or not in line X (Horizontal line)- for Hard Mode
bool checkLineX(cell2** board, int x1, int y1, int x2, int y2) { // y1 == y2
	// -------------

	// This code is almost the same as checkLineX for medium mode
	// But instead of check if (board[y][i].isValid), we check if (findTheNode(board, i, y) != NULL)

	// Determine the coordinates of the leftmost and rightmost cell
	int min_x = min(x1, x2);
	int max_x = max(x1, x2);
	int y = y1;

	// Check between the cells (x1 and x2) if there is any cell valid -> return false
	for (int i = min_x + 1; i < max_x; i++) {
		if (findTheNode(board, i, y) != NULL) return false; 
	}

	// If no valid cell was found between x1 and x2, return true (valid connection)
	return true;
}


// Check if the two cells can be matched together or not in line Y (Vertical line) - for Hard Mode
bool checkLineY(cell2** board, int x1, int y1, int x2, int y2) {
	// |
	// |
	// |

	// This code is almost the same as checkLineY for medium mode
	// But instead of check if (board[y][i].isValid), we check if (findTheNode(board, i, y) != NULL)

	// Determine the coordinates of the topmost and bottommost cell
	int min_y = min(y1, y2);
	int max_y = max(y1, y2);
	int x = x1;

	// Check between the cells (y1 and y2) if there is any cell valid -> return false
	for (int i = min_y + 1; i < max_y; i++) {
		if (findTheNode(board, x, i) != NULL) return false;
	}

	// If no valid cell was found between y1 and y2, return true (valid connection)
	return true;
}


// Check if the two cells can be matched together or not in line I (X line or Y line) - for Hard Mode
bool checkLineI(cell2** board, int x1, int y1, int x2, int y2) {

	// This code is almost the same as checkLineI for medium mode

	// If the two cells is on the same line -> Check for vertical match
	if (x1 == x2) {
		if (checkLineY(board, x1, y1, x2, y2)) return true;
	}

	// If the two cells is on the same column -> Check for horizontal match
	if (y1 == y2) {
		if (checkLineX(board, x1, y1, x2, y2)) return true;
	}

	// If none of the check is true, return false (invalid connection)
	return false;
}

// Check if the two cells can be matched together or not in line L - for Hard Mode
bool checkLineL(cell2** board, int x1, int y1, int x2, int y2) {

	// This code is almost the same as checkLineL for medium mode
	// But instead of check if (board[y][i].isValid), we check if (findTheNode(board, i, y) != NULL)

	// Ensure x1 <= x2
	if (x1 > x2) {
		swap(x1, x2);
		swap(y1, y2);
	}

	//  A----|          C----B
	//  |    |    and   |    |
	//  C----B          A----|

	int x3 = x1;
	int y3 = y2;

	if (findTheNode(board, x3, y3) == NULL) {
		if (checkLineI(board, x1, y1, x3, y3) && checkLineI(board, x3, y3, x2, y2)) return true;
	}

	//  A----C          |----B
	//  |    |    and   |    |
	//  |----B          A----C

	x3 = x2;
	y3 = y1;

	if (findTheNode(board, x3, y3) == NULL) {
		if (checkLineI(board, x1, y1, x3, y3) && checkLineI(board, x3, y3, x2, y2)) return true;
	}
	return false;
}

// Check if the two cells can be matched together or not in line Z - for Hard Mode
bool checkLineZ(cell2** board, int x1, int y1, int x2, int y2) {

	// This code is almost the same as checkLineZ for medium mode
	// But instead of check if (board[y][i].isValid), we check if (findTheNode(board, i, y) != NULL)
	 
	// 
	// |__      and     __|
	//    |            |
	int x3 = x1;
	int x4 = x2;
	if (y1 < y2) {
		for (int i = y1 + 1; i < y2; i++) {
			if ((findTheNode(board, x3, i) == NULL) && (findTheNode(board, x4, i) == NULL)) {
				if (checkLineI(board, x1, y1, x3, i) && checkLineI(board, x3, i, x4, i) && checkLineI(board, x4, i, x2, y2)) return true;
			}
		}
	}
	else {
		for (int i = y2 + 1; i < y1; i++) {
			if ((findTheNode(board, x3, i) == NULL) && (findTheNode(board, x4, i) == NULL)) {
				if (checkLineI(board, x1, y1, x3, i) && checkLineI(board, x3, i, x4, i) && checkLineI(board, x4, i, x2, y2)) return true;
			}
		}
	}

	// __       and      __
	//   |__          __|
	int y3 = y1;
	int y4 = y2;
	if (x1 < x2) {
		for (int i = x1 + 1; i < x2; i++) {
			if ((findTheNode(board, i, y3) == NULL) && (findTheNode(board, i, y4) == NULL)) {
				if (checkLineI(board, x1, y1, i, y3) && checkLineI(board, i, y3, i, y4) && checkLineI(board, i, y4, x2, y2)) return true;
			}
		}
	}
	else {
		for (int i = x2 + 1; i < x1; i++) {
			if ((findTheNode(board, i, y3) == NULL) && (findTheNode(board, i, y4) == NULL)) {
				if (checkLineI(board, x1, y1, i, y3) && checkLineI(board, i, y3, i, y4) && checkLineI(board, i, y4, x2, y2)) return true;
			}
		}
	}
	return false;
}

// Check if the two cells can be matched together or not in line U - for Hard Mode
bool checkLineU(cell2** board, int x1, int y1, int x2, int y2) {

	// This code is almost the same as checkLineU for medium mode
	// But instead of check if (board[y][i].isValid), we check if (findTheNode(board, i, y) != NULL) 

	if (x1 == 0 && x2 == 0) return true;
	if ((x1 == (BOARDWIDTH - 1)) && (x2 == (BOARDWIDTH - 1))) return true;
	if (y1 == 0 && y2 == 0) return true;
	if ((y1 == (BOARDHEIGHT - 1)) && (y2 == (BOARDHEIGHT - 1))) return true;


	// upper U
	if (y1 == 0 || y2 == 0) { // one of them is on the first line
		if (y1 == 0 && (findTheNode(board, x2, 0) == NULL) && checkLineI(board, x2, 0, x2, y2)) return true;
		if (y2 == 0 && (findTheNode(board, x1, 0) == NULL) && checkLineI(board, x1, 0, x1, y1)) return true;
	}

	int x3 = x1;
	int x4 = x2;
	if (y1 <= y2) {
		for (int i = y1 - 1; i >= -1; i--) {
			if (i == -1) {
				if ((findTheNode(board, x3, 0) == NULL) && (findTheNode(board, x4, 0) == NULL)) {
					if (checkLineI(board, x1, y1, x3, 0) && checkLineI(board, x4, 0, x2, y2)) return true;
				}
				break;
			}
			if ((findTheNode(board, x3, i) == NULL) && (findTheNode(board, x4, i) == NULL)) {
				if (checkLineI(board, x1, y1, x3, i) && checkLineI(board, x3, i, x4, i) && checkLineI(board, x4, i, x2, y2)) return true;
			}
		}
	}
	else { // y1 > y2
		for (int i = y2 - 1; i >= -1; i--) {
			if (i == -1) {
				if ((findTheNode(board, x3, 0) == NULL) && (findTheNode(board, x4, 0) == NULL)) {
					if (checkLineI(board, x1, y1, x3, 0) && checkLineI(board, x4, 0, x2, y2)) return true;
				}
				break;
			}
			if ((findTheNode(board, x3, i) == NULL) && (findTheNode(board, x4, i) == NULL)) {
				if (checkLineI(board, x1, y1, x3, i) && checkLineI(board, x3, i, x4, i) && checkLineI(board, x4, i, x2, y2)) return true;
			}
		}
	}

	// lower U
	if ((y1 == BOARDHEIGHT - 1) || (y2 == BOARDHEIGHT - 1)) { // one of them is on the last line
		if ((y1 == BOARDHEIGHT - 1) && (findTheNode(board, x2, BOARDHEIGHT - 1) == NULL) && checkLineI(board, x2, BOARDHEIGHT - 1, x2, y2)) return true;
		if ((y2 == BOARDHEIGHT - 1) && (findTheNode(board, x1, BOARDHEIGHT - 1) == NULL) && checkLineI(board, x1, BOARDHEIGHT - 1, x1, y1)) return true;
	}

	if (y1 <= y2) {
		for (int i = y2 + 1; i <= BOARDHEIGHT; i++) {
			if (i == BOARDHEIGHT) {
				if ((findTheNode(board, x3, BOARDHEIGHT - 1) == NULL) && (findTheNode(board, x4, BOARDHEIGHT - 1) == NULL)) {
					if (checkLineI(board, x1, y1, x3, BOARDHEIGHT - 1) && checkLineI(board, x4, BOARDHEIGHT - 1, x2, y2)) return true;
				}
				break;
			}
			if ((findTheNode(board, x3, i) == NULL) && (findTheNode(board, x4, i) == NULL)) {
				if (checkLineI(board, x1, y1, x3, i) && checkLineI(board, x3, i, x4, i) && checkLineI(board, x4, i, x2, y2)) return true;
			}
		}
	}
	else { // y1 > y2
		for (int i = y1 + 1; i <= BOARDHEIGHT; i++) {
			if (i == BOARDHEIGHT) {
				if ((findTheNode(board, x3, BOARDHEIGHT - 1) == NULL) && (findTheNode(board, x4, BOARDHEIGHT - 1) == NULL)) {
					if (checkLineI(board, x1, y1, x3, BOARDHEIGHT - 1) && checkLineI(board, x4, BOARDHEIGHT - 1, x2, y2)) return true;
				}
				break;
			}
			if ((findTheNode(board, x3, i) == NULL) && (findTheNode(board, x4, i) == NULL)) {
				if (checkLineI(board, x1, y1, x3, i) && checkLineI(board, x3, i, x4, i) && checkLineI(board, x4, i, x2, y2)) return true;
			}
		}
	}

	// left U
	if (x1 == 0 || x2 == 0) { // one of them is on the first column
		if (x1 == 0 && (findTheNode(board, 0, y2) == NULL) && checkLineI(board, 0, y2, x2, y2)) return true;
		if (x2 == 0 && (findTheNode(board, 0, y1) == NULL) && checkLineI(board, 0, y1, x1, y1)) return true;
	}

	int y3 = y1;
	int y4 = y2;
	if (x1 <= x2) {
		for (int i = x1 - 1; i >= -1; i--) {
			if (i == -1) {
				if ((findTheNode(board, 0, y3) == NULL) && (findTheNode(board, 0, y4) == NULL)) {
					if (checkLineI(board, x1, y1, 0, y3) && checkLineI(board, 0, y4, x2, y2)) return true;
				}
				break;
			}
			if ((findTheNode(board, i, y3) == NULL) && (findTheNode(board, i, y4) == NULL)) {
				if (checkLineI(board, x1, y1, i, y3) && checkLineI(board, i, y3, i, y4) && checkLineI(board, i, y4, x2, y2)) return true;
			}
		}
	}
	else { // x1 > x2
		for (int i = x2 - 1; i >= -1; i--) {
			if (i == -1) {
				if ((findTheNode(board, 0, y3) == NULL) && (findTheNode(board, 0, y4) == NULL)) {
					if (checkLineI(board, x1, y1, 0, y3) && checkLineI(board, 0, y4, x2, y2)) return true;
				}
				break;
			}
			if ((findTheNode(board, i, y3) == NULL) && (findTheNode(board, i, y4) == NULL)) {
				if (checkLineI(board, x1, y1, i, y3) && checkLineI(board, i, y3, i, y4) && checkLineI(board, i, y4, x2, y2)) return true;
			}
		}
	}

	// right U
	if ((x1 == BOARDWIDTH - 1) || (x2 == BOARDWIDTH - 1)) { // one of them is on the last column
		if ((x1 == BOARDWIDTH - 1) && (findTheNode(board, BOARDWIDTH - 1, y2) == NULL) && checkLineI(board, BOARDWIDTH - 1, y2, x2, y2)) return true;
		if ((x2 == BOARDWIDTH - 1) && (findTheNode(board, BOARDWIDTH - 1, y1) == NULL) && checkLineI(board, BOARDWIDTH - 1, y1, x1, y1)) return true;
	}

	if (x1 <= x2) {
		for (int i = x2 + 1; i <= BOARDWIDTH; i++) {
			if (i == BOARDWIDTH) {
				if ((findTheNode(board, BOARDWIDTH - 1, y3) == NULL) && (findTheNode(board, BOARDWIDTH - 1, y4) == NULL)) {
					if (checkLineI(board, x1, y1, BOARDWIDTH - 1, y3) && checkLineI(board, BOARDWIDTH - 1, y4, x2, y2)) return true;
				}
				break;
			}
			if ((findTheNode(board, i, y3) == NULL) && (findTheNode(board, i, y4) == NULL)) {
				if (checkLineI(board, x1, y1, i, y3) && checkLineI(board, i, y3, i, y4) && checkLineI(board, i, y4, x2, y2)) return true;
			}
		}
	}
	else { // x1 > x2
		for (int i = x1 + 1; i <= BOARDWIDTH; i++) {
			if (i == BOARDWIDTH) {
				if ((findTheNode(board, BOARDWIDTH - 1, y3) == NULL) && (findTheNode(board, BOARDWIDTH - 1, y4) == NULL)) {
					if (checkLineI(board, x1, y1, BOARDWIDTH - 1, y3) && checkLineI(board, BOARDWIDTH - 1, y4, x2, y2)) return true;
				}
				break;
			}
			if ((findTheNode(board, i, y3) == NULL) && (findTheNode(board, i, y4) == NULL)) {
				if (checkLineI(board, x1, y1, i, y3) && checkLineI(board, i, y3, i, y4) && checkLineI(board, i, y4, x2, y2)) return true;
			}
		}
	}
	return false;
}

// 0: False
// 2: Matching I
// 3: Matching L
// 4: Matching Z
// 5: Matching U
// check if the two cells can be matched together or not in all line (I, L, Z, U) - for Hard Mode
int allCheck(cell2** board, int x1, int y1, int x2, int y2) {
	if (findTheNode(board, x1, y1)->val != findTheNode(board, x2, y2)->val) return false;
	if (x1 == x2 && y1 == y2) return false;
	if (checkLineI(board, x1, y1, x2, y2)) {
		return 2;
	}
	if (checkLineL(board, x1, y1, x2, y2)) {
		return 3;
	}
	if (checkLineZ(board, x1, y1, x2, y2)) {
		return 4;
	}
	if (checkLineU(board, x1, y1, x2, y2)) {
		return 5;
	}
	return 0;
}

// Check if there is any pair that can be matched or not - for Hard Mode
bool checkValidPair(cell2** board) {
	for (int i = 0; i < BOARDHEIGHT; i++) {
		for (int j = 0; j < getLineLength(board[i]); j++) {

			if (findTheNode(board, j, i) != NULL) {
				for (int x = 0; x < BOARDHEIGHT; x++) {
					for (int y = 0; y < getLineLength(board[x]); y++) {
						if (x != i || y != j) {
							if (allCheck(board, j, i, y, x) && (findTheNode(board, y, x) != NULL)) return true;
						}
					}
				}
			}
		}
	}
	return false;
}

// Check if there is any cell still exist or not - for Hard Mode
bool checkCellExist(cell2** board) {
	for (int i = 0; i < BOARDHEIGHT; i++) {
		for (int j = 0; j < getLineLength(board[i]); j++) {
			if (findTheNode(board, j, i) != NULL) {
				return true;
			}
		}
	}
	return false;
}