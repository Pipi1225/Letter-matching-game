#include <iostream>
#include <algorithm>

#include "Struct.h"
#include "Core.h"
#include "Check.h"

using namespace std;


// Creating box to contain other things and print out the infomation
void setupPlayInfo(player& p) {
    // Box 1: 
    // Contain player's info like name, stages, point...
    // Cout the plus/subtract of point and subtract of lifes, pattern of matching player choose
    // 
    // Top line: Y = 0
    // Bottom line: Y = 16
    // Left line: X = 76
    // Right line: X = 125

    setColor(BLACK, GRAY);

    // Creating the left and right line
    for (int i = 0; i < 50; i++)
    {
        GoToXY(76 + i, 0);
        putchar(205);
        GoToXY(76 + i, 16);
        putchar(205);
    }

    // Creating the top and bottom line
    for (int i = 0; i < 15; i++)
    {
        GoToXY(76, 1 + i);
        putchar(186);

        GoToXY(126, 1 + i);
        putchar(186);
    }

    // Creating the joints of vertical and horizontal lines
    GoToXY(76, 0);
    putchar(201);
    GoToXY(126, 0);
    putchar(187);
    GoToXY(76, 16);
    putchar(200);
    GoToXY(126, 16);
    putchar(188);

    // Print out the player's info
    setColor(BLACK, YELLOW);
    GoToXY(92, 2);
    cout << "- Player's Info -";

    setColor(BLACK, BRIGHT_WHITE);
    GoToXY(80, 4);
    cout << "NAME:";
    GoToXY(80, 6);
    cout << "LIFE:";
    GoToXY(80, 8);
    cout << "STAGES:";
    GoToXY(80, 10);
    cout << "POINT:";

    GoToXY(88, 4);
    cout << p.name;
    GoToXY(88, 6);
    setColor(BLACK, LIGHT_GREEN);
    for (int i = 1; i <= p.life; i++)
    {
        cout << "* ";
    }
    setColor(BLACK, BRIGHT_WHITE);
    GoToXY(88, 8);
    cout << p.stages;
    GoToXY(88, 10);
    cout << p.point;

    // Box 2: 
    // Contain all possible sets move like moving up and down, left and right,
    // 
    // Top line: Y = 18
    // Bottom line: Y = 30
    // Left line: X = 76
    // Right line: X = 125

    setColor(BLACK, GRAY);

    // Creating the top and bottom line
    for (int i = 0; i < 50; i++)
    {
        GoToXY(76 + i, 18);
        putchar(205);
        GoToXY(76 + i, 30);
        putchar(205);
    }

    // Creating the left and right line
    for (int i = 0; i < 12; i++)
    {
        GoToXY(76, 19 + i);
        putchar(186);
        GoToXY(126, 19 + i);
        putchar(186);
    }

    // Creating the joints of vertical and horizontal lines
    GoToXY(76, 18);
    putchar(201);
    GoToXY(126, 18);
    putchar(187);
    GoToXY(76, 30);
    putchar(200);
    GoToXY(126, 30);
    putchar(188);

    // Print out all move sets
    setColor(BLACK, BRIGHT_WHITE);
    GoToXY(80, 20);
    cout << "Select/Deselect:";
    GoToXY(80, 23);
    cout << "Up:";
    GoToXY(80, 25);
    cout << "Down:";
    GoToXY(102, 23);
    cout << "Right:";
    GoToXY(102, 25);
    cout << "Left:";
    setColor(BLACK, LIGHT_YELLOW);
    GoToXY(92, 28);
    cout << "Move Suggestion: B";
    setColor(BLACK, BRIGHT_WHITE);
    GoToXY(80, 32);
    cout << "Press EXIT to quit game";

    setColor(BLACK, WHITE);
    GoToXY(98, 20);
    cout << "Enter";
    GoToXY(86, 23);
    cout << "W/ Up arrow";
    GoToXY(86, 25);
    cout << "S/ Down arrow";
    GoToXY(109, 23);
    cout << "D/ Right arrow";
    GoToXY(109, 25);
    cout << "A/ Left arrow";
}

// Print the game logo on the console window
void printLogo() {
    unsigned char logo1[] = R"(





                               ooooooooo.  ooooo ooooo    oooo      .o.         .oooooo.   ooooo   ooooo  ooooo     ooo 
                               888    Y88.  888'  888   .8P'       .888.       d8P'  `Y8b   888'    888'   888'     `8' 
                               888   .d88'  888   888  d8'        .8"888.     888           888     888    888       8  
                               888ooo88P'   888   88888[         .8' `888.    888           888ooooo888    888       8  
                               888          888   888`88b.      .88ooo8888.   888           888     888    888       8  
                               888          888   888  88b.    .8'      888.   88b    ooo   888     888     88.    .8'  
                              o888o        o888o o888o  o888o o88o     o8888o   Y8bood8P'  o888o   o888o      YbodP'     
    )";
    setColor(BLACK, YELLOW);
    cout << logo1;

    unsigned char logo2[] = R"(
                                                       _____ _  _ ___   __ __  __ _____ ____  _ _ __  _  __    __  __  __ __ ___  
                                                      |_   _| || | __| |  V  |/  \_   _/ _/ || | |  \| |/ _]  / _]/  \|  V  | __| 
                                                ~ ---   | | | >< | _|  | \_/ | /\ || || \_| >< | | | ' | [/\ | [/\ /\ | \_/ | _|   --- ~
                                                        |_| |_||_|___| |_| |_|_||_||_| \__/_||_|_|_|\__|\__/  \__/_||_|_| |_|___|  
    )";
    setColor(BLACK, WHITE);
    cout << logo2;
}


// ======Both mode=================================================================

// Draw the horizontal line (X line) when matching X success
void drawLineX(int x1, int y1, int x2, int y2)
{
    // Position of the character on the console
    int min_x = min(x1 * 10 + 15, x2 * 10 + 15);
    int max_x = max(x1 * 10 + 15, x2 * 10 + 15);
    int y = y1 * 4 + 6;

    // Draw the vertical line from position min_x, y to max_x, y on the console
    for (int i = min_x; i <= max_x; i++) {
        GoToXY(i, y);
        putchar(196);
    }
}

// Draw the vertical line (Y line) when matching Y success
void drawLineY(int x1, int y1, int x2, int y2)
{
    // Position of the character on the console
    int min_y = min(y1 * 4 + 6, y2 * 4 + 6);
    int max_y = max(y1 * 4 + 6, y2 * 4 + 6);
    int x = x1 * 10 + 15;

    // Draw the horizontal line from position x, min_y to x, max_y on the console
    for (int i = min_y; i <= max_y; i++) {
        GoToXY(x, i);
        putchar(179);
    }
}

// Draw the vertical line (Y line) or horizontal line (X line) when matching I success
void drawLineI(int x1, int y1, int x2, int y2) {

    // If the two cells is on the same line -> Draw vertical line
    if (x1 == x2) {
        drawLineY(x1, y1, x2, y2);

        return;
    }

    // If the two cells is on the same column -> Draw horizontal line
    if (y1 == y2) {
        drawLineX(x1, y1, x2, y2);

        return;
    }
}


// ======Medium mode=================================================================

// Draw the L line when matching L success - for Medium Mode
void drawLineL(cell** board, int x1, int y1, int x2, int y2) {

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
        // If it has a valid connection from x1, y1 to x3, y3 and x3, y3 to x2, y2
        if (checkLineI(board, x1, y1, x3, y3) && checkLineI(board, x3, y3, x2, y2))
        {
            // Draw line from x1, y1 to x3, y3 and x3, y3 to x2, y2
            drawLineI(x1, y1, x3, y3);
            drawLineI(x3, y3, x2, y2);

            GoToXY(x3 * 10 + 15, y3 * 4 + 6);

            // Draw the joint of vertical and horizontal line
            if (y2 > y1)
            {
                putchar(192);
            }
            else
            {
                putchar(218);
            }

            return;
        }
    }

    //  A----C          |----B
    //  |    |    and   |    |
    //  |----B          A----C

    // Rechoose the cell C(x2, y1)
    x3 = x2;
    y3 = y1;

    // Check for L - shape with corner at C
    if (board[y3][x3].isValid == 0) { // Check if corner cell is empty
        // If it has a valid connection from x1, y1 to x3, y3 and x3, y3 to x2, y2
        if (checkLineI(board, x1, y1, x3, y3) && checkLineI(board, x3, y3, x2, y2))
        {
            // Draw line from x1, y1 to x3, y3 and x3, y3 to x2, y2
            drawLineI(x1, y1, x3, y3);
            drawLineI(x3, y3, x2, y2);

            GoToXY(x3 * 10 + 15, y3 * 4 + 6);

            // Draw the joint of vertical and horizontal line
            if (y2 > y1)
            {
                putchar(191);
            }
            else
            {
                putchar(217);
            }

            return;

        }
    }
}

// Draw the Z line when matching Z success - for Medium Mode
void drawLineZ(cell** board, int x1, int y1, int x2, int y2) {
    // 1                  1
    // |__      and     __|
    //    |            |
    //    2            2

    // Choose the cell C(x1, y2)
    int x3 = x1;
    int x4 = x2;

    // Check for Z-shape with diagonal line going down - right - down (x1 < x2, else diagonal line going up - right - up)
    if (y1 < y2) {
        for (int i = y1 + 1; i < y2; i++) {
            if ((board[i][x3].isValid == 0) && (board[i][x4].isValid == 0)) { // Check if C and C' is inValid -> Check the line between 4 cells)

                // If it has a valid connection from (x1, y1) to (x3, i) and (x3, i) to (x4, i) and (x4, i) to (x2, y2)
                if (checkLineI(board, x1, y1, x3, i) && checkLineI(board, x3, i, x4, i) && checkLineI(board, x4, i, x2, y2))
                {
                    // Draw line from (x1, y1) to (x3, i) and (x3, i) to (x4, i) and (x4, i) to (x2, y2)
                    drawLineI(x1, y1, x3, i);
                    drawLineI(x3, i, x4, i);
                    drawLineI(x4, i, x2, y2);

                    // Draw the joint of vertical and horizontal line
                    if (x2 > x1)
                    {
                        GoToXY(x3 * 10 + 15, i * 4 + 6);
                        putchar(192);

                        GoToXY(x4 * 10 + 15, i * 4 + 6);
                        putchar(191);

                    }
                    else
                    {
                        GoToXY(x3 * 10 + 15, i * 4 + 6);
                        putchar(217);

                        GoToXY(x4 * 10 + 15, i * 4 + 6);
                        putchar(218);

                    }

                    return;
                }
            }
        }
    }
    // 2                  2
    // |__      and     __|
    //    |            |
    //    1            1

    // Check for Z-shape with diagonal line going up - right - up (x1 < x2, else diagonal line going down - right - down)
    else {
        for (int i = y2 + 1; i < y1; i++) {
            if ((board[i][x3].isValid == 0) && (board[i][x4].isValid == 0)) { // Check if C and C' is inValid -> Check the line between 4 cells)

                // If it has a valid connection from (x1, y1) to (x3, i) and (x3, i) to (x4, i) and (x4, i) to (x2, y2)
                if (checkLineI(board, x1, y1, x3, i) && checkLineI(board, x3, i, x4, i) && checkLineI(board, x4, i, x2, y2))
                {
                    // Draw line from (x1, y1) to (x3, i) and (x3, i) to (x4, i) and (x4, i) to (x2, y2)
                    drawLineI(x1, y1, x3, i);
                    drawLineI(x3, i, x4, i);
                    drawLineI(x4, i, x2, y2);

                    // Draw the joint of vertical and horizontal line
                    if (x2 > x1)
                    {
                        GoToXY(x3 * 10 + 15, i * 4 + 6);
                        putchar(218);


                        GoToXY(x4 * 10 + 15, i * 4 + 6);
                        putchar(217);
                    }
                    else
                    {
                        GoToXY(x3 * 10 + 15, i * 4 + 6);
                        putchar(191);


                        GoToXY(x4 * 10 + 15, i * 4 + 6);
                        putchar(192);
                    }

                    return;
                }
            }
        }
    }

    // 1__       and        __2
    //    |__2          1__|

    // Rechoose C(i, y1) and C'(i, y2)
    int y3 = y1;
    int y4 = y2;

    // Check for Z-shape with diagonal line going right - down - right (y1 < y2, else diagonal line going right - up - right)
    if (x1 < x2) {
        for (int i = x1 + 1; i < x2; i++) {
            if ((board[y3][i].isValid == 0) && (board[y4][i].isValid == 0)) { // Check if C and C' is inValid -> Check the line between 4 cells)

                // If it has a valid connection from (x1, y1) to (i, y3) and (i, y3) to (i, y4) and (i, y4) to (x2, y2)
                if (checkLineI(board, x1, y1, i, y3) && checkLineI(board, i, y3, i, y4) && checkLineI(board, i, y4, x2, y2))
                {
                    // Draw line from (x1, y1) to (i, y3) and (i, y3) to (i, y4) and (i, y4) to (x2, y2)
                    drawLineI(x1, y1, i, y3);
                    drawLineI(i, y3, i, y4);
                    drawLineI(i, y4, x2, y2);

                    // Draw the joint of vertical and horizontal line
                    if (y2 > y1)
                    {
                        GoToXY(i * 10 + 15, y3 * 4 + 6);
                        putchar(191);


                        GoToXY(i * 10 + 15, y4 * 4 + 6);
                        putchar(192);

                    }
                    else
                    {
                        GoToXY(i * 10 + 15, y3 * 4 + 6);
                        putchar(217);


                        GoToXY(i * 10 + 15, y4 * 4 + 6);
                        putchar(218);
                    }

                    return;
                }
            }
        }
    }
    else {
        // 2__       and        __1
        //    |__1          2__|

        // Check for Z-shape with diagonal line going right - up - right (y1 < y2, else diagonal line going right - down - right)
        for (int i = x2 + 1; i < x1; i++) {
            if ((board[y3][i].isValid == 0) && (board[y4][i].isValid == 0)) { // Check if C and C' is inValid -> Check the line between 4 cells)

                // If it has a valid connection from (x1, y1) to (i, y3) and (i, y3) to (i, y4) and (i, y4) to (x2, y2)
                if (checkLineI(board, x1, y1, i, y3) && checkLineI(board, i, y3, i, y4) && checkLineI(board, i, y4, x2, y2))
                {
                    // Draw line from (x1, y1) to (i, y3) and (i, y3) to (i, y4) and (i, y4) to (x2, y2)
                    drawLineI(x1, y1, i, y3);
                    drawLineI(i, y3, i, y4);
                    drawLineI(i, y4, x2, y2);

                    // Draw the joint of vertical and horizontal line
                    if (y2 > y1)
                    {
                        GoToXY(i * 10 + 15, y3 * 4 + 6);
                        putchar(218);

                        GoToXY(i * 10 + 15, y4 * 4 + 6);
                        putchar(217);

                    }
                    else
                    {
                        GoToXY(i * 10 + 15, y3 * 4 + 6);
                        putchar(192);

                        GoToXY(i * 10 + 15, y4 * 4 + 6);
                        putchar(191);
                    }

                    return;
                }
            }
        }
    }
}

// Draw the U line when matching U success - for Medium Mode
void drawLineU(cell** board, int x1, int y1, int x2, int y2) {

    // Handle cells on edges or corners (instant U-shapes):
    if (x1 == 0 && x2 == 0) {

        drawLineI(-1, y1, -1, y2);
        drawLineI(x1, y1, -1, y1);
        drawLineI(-1, y2, x2, y2);

        return;
    }

    if ((x1 == (BOARDWIDTH - 1)) && (x2 == (BOARDWIDTH - 1))) {

        drawLineI(BOARDWIDTH, y1, BOARDWIDTH, y2);
        drawLineI(x1, y1, BOARDWIDTH, y1);
        drawLineI(BOARDWIDTH, y2, x2, y2);

        return;
    }

    if (y1 == 0 && y2 == 0) {

        drawLineI(x1, -1, x2, -1);
        drawLineI(x1, y1, x1, -1);
        drawLineI(x2, -1, x2, y2);

        return;
    }

    if ((y1 == (BOARDHEIGHT - 1)) && (y2 == (BOARDHEIGHT - 1))) {

        drawLineI(x1, BOARDHEIGHT, x2, BOARDHEIGHT);
        drawLineI(x1, y1, x1, BOARDHEIGHT);
        drawLineI(x2, BOARDHEIGHT, x2, y2);

        return;
    }

    // Choose C(x1, i) and C'(x2, i)
    int x3 = x1;
    int x4 = x2;

    // upper U (line going up - right - up)
    if (y1 == 0 || y2 == 0) { 	// one of the two cells is on the first line
        if (y1 == 0 && (board[y1][x2].isValid == 0) && checkLineI(board, x2, y1, x2, y2)) {

            drawLineI(x1, -1, x2, -1);
            drawLineI(x1, y1, x1, -1);
            drawLineI(x2, -1, x2, y2);

            return;
        }
        if (y2 == 0 && (board[y2][x1].isValid == 0) && checkLineI(board, x1, 0, x1, y1)) {

            drawLineI(x2, -1, x1, -1);
            drawLineI(x2, y2, x2, -1);
            drawLineI(x1, -1, x1, y1);

            return;
        }
    }

    // The line start from the lower cell
    if (y1 <= y2) {
        for (int i = y1 - 1; i >= -1; i--) { // Check line from the lower line to the the highest line

            // If the line reached the two toppest cells
            if (i == -1) {
                if ((board[0][x3].isValid == 0) && (board[0][x4].isValid == 0)) {

                    // If it has a valid connection from (x1, y1) to (x3, i) and and (x4, i) to (x2, y2)
                    if (checkLineI(board, x1, y1, x3, 0) && checkLineI(board, x4, 0, x2, y2)) {

                        // Draw line from (x1, y1) to (x3, i) and (x3, i) to (x4, i) and (x4, i) to (x2, y2)
                        drawLineI(x1, y1, x3, i);
                        drawLineI(x2, y2, x4, i);
                        drawLineI(x3, i, x4, i);

                        return;
                    }
                }
                break;
            }
            if ((board[i][x3].isValid == 0) && (board[i][x4].isValid == 0)) {

                // If it has a valid connection from (x1, y1) to (x3, i) and (x3, i) to (x4, i) and (x4, i) to (x2, y2)
                if (checkLineI(board, x1, y1, x3, i) && checkLineI(board, x3, i, x4, i) && checkLineI(board, x4, i, x2, y2)) {

                    // Draw line from (x1, y1) to (x3, i) and (x3, i) to (x4, i) and (x4, i) to (x2, y2)
                    drawLineI(x1, y1, x3, i);
                    drawLineI(x2, y2, x4, i);
                    drawLineI(x3, i, x4, i);

                    return;
                }
            }
        }
    }
    else { // y1 > y2 // the same with the previous case
        for (int i = y2 - 1; i >= -1; i--) {
            if (i == -1) {
                if ((board[0][x3].isValid == 0) && (board[0][x4].isValid == 0)) {

                    // If it has a valid connection from (x1, y1) to (x3, i) and (x4, i) to (x2, y2)
                    if (checkLineI(board, x1, y1, x3, 0) && checkLineI(board, x4, 0, x2, y2)) {

                        // Draw line from (x1, y1) to (x3, i) and (x3, i) to (x4, i) and (x4, i) to (x2, y2)
                        drawLineI(x1, y1, x3, i);
                        drawLineI(x2, y2, x4, i);
                        drawLineI(x3, i, x4, i);

                        return;
                    }
                }
                break;
            }
            if ((board[i][x3].isValid == 0) && (board[i][x4].isValid == 0)) {

                // If it has a valid connection from (x1, y1) to (x3, i) and (x3, i) to (x4, i) and (x4, i) to (x2, y2)
                if (checkLineI(board, x1, y1, x3, i) && checkLineI(board, x3, i, x4, i) && checkLineI(board, x4, i, x2, y2)) {

                    // Draw line from (x1, y1) to (x3, i) and (x3, i) to (x4, i) and (x4, i) to (x2, y2)
                    drawLineI(x1, y1, x3, i);
                    drawLineI(x2, y2, x4, i);
                    drawLineI(x3, i, x4, i);

                    return;
                }
            }
        }
    }

    // Lower U (line going down - right - down)
    if ((y1 == BOARDHEIGHT - 1) || (y2 == BOARDHEIGHT - 1)) { // one of the two cells is on the last line
        if ((y1 == BOARDHEIGHT - 1) && (board[BOARDHEIGHT - 1][x2].isValid == 0) && checkLineI(board, x2, BOARDHEIGHT - 1, x2, y2)) {

            drawLineI(x1, BOARDHEIGHT, x2, BOARDHEIGHT);
            drawLineI(x1, y1, x1, BOARDHEIGHT);
            drawLineI(x2, BOARDHEIGHT, x2, y2);

            return;
        }
        if ((y2 == BOARDHEIGHT - 1) && (board[BOARDHEIGHT - 1][x1].isValid == 0) && checkLineI(board, x1, BOARDHEIGHT - 1, x1, y1)) {

            drawLineI(x1, BOARDHEIGHT, x2, BOARDHEIGHT);
            drawLineI(x1, y1, x1, BOARDHEIGHT);
            drawLineI(x2, BOARDHEIGHT, x2, y2);

            return;
        }
    }

    // The line start from the upper cell 
    // The code is almost the same at upper U, but in this case we check line from the upper line to the the lowest line
    if (y1 <= y2) {
        for (int i = y2 + 1; i <= BOARDHEIGHT; i++) { // Check line from the upper line to the the lowest line

            // If the line reached the lowest line
            if (i == BOARDHEIGHT) {
                if ((board[BOARDHEIGHT - 1][x3].isValid == 0) && (board[BOARDHEIGHT - 1][x4].isValid == 0)) {

                    // If it has a valid connection from (x1, y1) to (x3, i) and (x4, i) to (x2, y2)
                    if (checkLineI(board, x1, y1, x3, BOARDHEIGHT - 1) && checkLineI(board, x4, BOARDHEIGHT - 1, x2, y2)) {

                        // Draw line from (x1, y1) to (x3, i) and (x3, i) to (x4, i) and (x4, i) to (x2, y2)
                        drawLineI(x1, y1, x3, i);
                        drawLineI(x2, y2, x4, i);
                        drawLineI(x3, i, x4, i);

                        return;
                    }
                }
                break;
            }
            if ((board[i][x3].isValid == 0) && (board[i][x4].isValid == 0)) {

                // If it has a valid connection from (x1, y1) to (x3, i) and (x3, i) to (x4, i) and (x4, i) to (x2, y2)
                if (checkLineI(board, x1, y1, x3, i) && checkLineI(board, x3, i, x4, i) && checkLineI(board, x4, i, x2, y2)) {

                    // Draw line from (x1, y1) to (x3, i) and (x3, i) to (x4, i) and (x4, i) to (x2, y2)
                    drawLineI(x1, y1, x3, i);
                    drawLineI(x2, y2, x4, i);
                    drawLineI(x3, i, x4, i);

                    return;
                }
            }
        }
    }
    else { // y1 > y2 // the same with the previous case
        for (int i = y1 + 1; i <= BOARDHEIGHT; i++) {
            if (i == BOARDHEIGHT) {
                if ((board[BOARDHEIGHT - 1][x3].isValid == 0) && (board[BOARDHEIGHT - 1][x4].isValid == 0)) {

                    // If it has a valid connection from (x1, y1) to (x3, i) and (x4, i) to (x2, y2)
                    if (checkLineI(board, x1, y1, x3, BOARDHEIGHT - 1) && checkLineI(board, x4, BOARDHEIGHT - 1, x2, y2)) {

                        // Draw line from (x1, y1) to (x3, i) and (x3, i) to (x4, i) and (x4, i) to (x2, y2)
                        drawLineI(x1, y1, x3, i);
                        drawLineI(x2, y2, x4, i);
                        drawLineI(x3, i, x4, i);

                        return;
                    }
                }
                break;
            }
            if ((board[i][x3].isValid == 0) && (board[i][x4].isValid == 0)) {

                // If it has a valid connection from (x1, y1) to (x3, i) and (x3, i) to (x4, i) and (x4, i) to (x2, y2)
                if (checkLineI(board, x1, y1, x3, i) && checkLineI(board, x3, i, x4, i) && checkLineI(board, x4, i, x2, y2)) {

                    // Draw line from (x1, y1) to (x3, i) and (x3, i) to (x4, i) and (x4, i) to (x2, y2)
                    drawLineI(x1, y1, x3, i);
                    drawLineI(x2, y2, x4, i);
                    drawLineI(x3, i, x4, i);

                    return;
                }
            }
        }
    }


    // Rechoose C(i, y1) and C'(i, y2)
    int y3 = y1;
    int y4 = y2;

    // Left U (line going left - down - left)
    if (x1 == 0 || x2 == 0) { // one of the two cells is on the fisrt column
        if (x1 == 0 && (board[y2][0].isValid == 0) && checkLineI(board, 0, y2, x2, y2)) {

            drawLineI(x1, y1, -1, y1);
            drawLineI(-1, y2, x2, y2);
            drawLineI(-1, y1, -1, y2);

            return;
        }
        if (x2 == 0 && (board[y1][0].isValid == 0) && checkLineI(board, 0, y1, x1, y1)) {

            drawLineI(x1, y1, -1, y1);
            drawLineI(-1, y2, x2, y2);
            drawLineI(-1, y1, -1, y2);

            return;
        }
    }

    // The column start from more right cell
    if (x1 <= x2) {
        for (int i = x1 - 1; i >= -1; i--) { // Check column from the more right column to the the most left column

            // If the column reached the two most left cells
            if (i == -1) {
                if ((board[y3][0].isValid == 0) && (board[y4][0].isValid == 0)) {

                    // If it has a valid connection from (x1, y1) to (i, y3) and (i, y4) to (x2, y2)
                    if (checkLineI(board, x1, y1, 0, y3) && checkLineI(board, 0, y4, x2, y2)) {

                        // Draw line from (x1, y1) to (i, y3) and (i, y3) to (i, y4) and (i, y4) to (x2, y2)
                        drawLineI(x1, y1, i, y3);
                        drawLineI(i, y3, i, y4);
                        drawLineI(i, y4, x4, y4);

                        return;
                    }
                }
                break;
            }
            if ((board[y3][i].isValid == 0) && (board[y4][i].isValid == 0)) {

                // If it has a valid connection from (x1, y1) to (i, y3) and (i, y3) to (i, y4) and (i, y4) to (x2, y2)
                if (checkLineI(board, x1, y1, i, y3) && checkLineI(board, i, y3, i, y4) && checkLineI(board, i, y4, x2, y2)) {

                    // Draw line from (x1, y1) to (i, y3) and (i, y3) to (i, y4) and (i, y4) to (x2, y2)
                    drawLineI(x1, y1, i, y3);
                    drawLineI(i, y3, i, y4);
                    drawLineI(i, y4, x4, y4);

                    return;
                }
            }
        }
    }
    else { // x1 > x2
        for (int i = x2 - 1; i >= -1; i--) {

            // If the column reached the two most left cells
            if (i == -1) {

                if ((board[y3][0].isValid == 0) && (board[y4][0].isValid == 0)) {

                    // If it has a valid connection from (x1, y1) to (i, y3) and (i, y4) to (x2, y2)
                    if (checkLineI(board, x1, y1, 0, y3) && checkLineI(board, 0, y4, x2, y2)) {

                        // Draw line from (x1, y1) to (i, y3) and (i, y3) to (i, y4) and (i, y4) to (x2, y2)
                        drawLineI(x1, y1, i, y3);
                        drawLineI(i, y3, i, y4);
                        drawLineI(i, y4, x4, y4);

                        return;
                    }
                }
                break;
            }
            if ((board[y3][i].isValid == 0) && (board[y4][i].isValid == 0)) {

                // If it has a valid connection from (x1, y1) to (i, y3) and (i, y3) to (i, y4) and (i, y4) to (x2, y2)
                if (checkLineI(board, x1, y1, i, y3) && checkLineI(board, i, y3, i, y4) && checkLineI(board, i, y4, x2, y2)) {

                    // Draw line from (x1, y1) to (i, y3) and (i, y3) to (i, y4) and (i, y4) to (x2, y2)
                    drawLineI(x1, y1, i, y3);
                    drawLineI(i, y3, i, y4);
                    drawLineI(i, y4, x4, y4);

                    return;
                }
            }
        }
    }

    // Right U (line going right - down - right)
    if ((x1 == BOARDWIDTH - 1) || (x2 == BOARDWIDTH - 1)) { // one of the two cells is on the last column
        if ((x1 == BOARDWIDTH - 1) && (board[y2][BOARDWIDTH - 1].isValid == 0) && checkLineI(board, BOARDWIDTH - 1, y2, x2, y2)) {

            drawLineI(x1, y1, BOARDWIDTH, y1);
            drawLineI(BOARDWIDTH, y2, x2, y2);
            drawLineI(BOARDWIDTH, y1, BOARDWIDTH, y2);

            return;
        }
        if ((x2 == BOARDWIDTH - 1) && (board[y1][BOARDWIDTH - 1].isValid == 0) && checkLineI(board, BOARDWIDTH - 1, y1, x1, y1)) {

            drawLineI(x1, y1, BOARDWIDTH, y1);
            drawLineI(BOARDWIDTH, y2, x2, y2);
            drawLineI(BOARDWIDTH, y1, BOARDWIDTH, y2);

            return;
        }
    }

    // The column start from the more left cell 
    // The code is almost the same at left U, but in this case we check column from the more left column to the the most right column
    if (x1 <= x2) {
        for (int i = x2 + 1; i <= BOARDWIDTH; i++) { // Check column from the more left column to the the most right column

            // If the column reached the two most right cells
            if (i == BOARDWIDTH) {

                if ((board[y3][BOARDWIDTH - 1].isValid == 0) && (board[y4][BOARDWIDTH - 1].isValid == 0)) {

                    // If it has a valid connection from (x1, y1) to (i, y3) and (i, y4) to (x2, y2)
                    if (checkLineI(board, x1, y1, BOARDWIDTH - 1, y3) && checkLineI(board, BOARDWIDTH - 1, y4, x2, y2)) {

                        // Draw line from (x1, y1) to (i, y3) and (i, y3) to (i, y4) and (i, y4) to (x2, y2)
                        drawLineI(x1, y1, i, y1);
                        drawLineI(i, y2, x2, y2);
                        drawLineI(i, y1, i, y2);

                        return;
                    }
                }
                break;
            }
            if ((board[y3][i].isValid == 0) && (board[y4][i].isValid == 0)) {

                // If it has a valid connection from (x1, y1) to (i, y3) and (i, y3) to (i, y4) and (i, y4) to (x2, y2)
                if (checkLineI(board, x1, y1, i, y3) && checkLineI(board, i, y3, i, y4) && checkLineI(board, i, y4, x2, y2)) {

                    // Draw line from (x1, y1) to (i, y3) and (i, y3) to (i, y4) and (i, y4) to (x2, y2)
                    drawLineI(x1, y1, i, y1);
                    drawLineI(i, y2, x2, y2);
                    drawLineI(i, y1, i, y2);

                    return;
                }
            }
        }
    }
    else { // x1 > x2 // the same with the previous case
        for (int i = x1 + 1; i <= BOARDWIDTH; i++) {

            // If the column reached the two most right cells
            if (i == BOARDWIDTH) {
                if ((board[y3][BOARDWIDTH - 1].isValid == 0) && (board[y4][BOARDWIDTH - 1].isValid == 0)) {

                    // If it has a valid connection from (x1, y1) to (i, y3) and (i, y4) to (x2, y2)
                    if (checkLineI(board, x1, y1, BOARDWIDTH - 1, y3) && checkLineI(board, BOARDWIDTH - 1, y4, x2, y2)) {

                        // Draw line from (x1, y1) to (i, y3) and (i, y3) to (i, y4) and (i, y4) to (x2, y2)
                        drawLineI(x1, y1, i, y1);
                        drawLineI(i, y2, x2, y2);
                        drawLineI(i, y1, i, y2);

                        return;
                    }
                }
                break;
            }
            if ((board[y3][i].isValid == 0) && (board[y4][i].isValid == 0)) {

                // If it has a valid connection from (x1, y1) to (i, y3) and (i, y3) to (i, y4) and (i, y4) to (x2, y2)
                if (checkLineI(board, x1, y1, i, y3) && checkLineI(board, i, y3, i, y4) && checkLineI(board, i, y4, x2, y2)) {

                    // Draw line from (x1, y1) to (i, y3) and (i, y3) to (i, y4) and (i, y4) to (x2, y2)
                    drawLineI(x1, y1, i, y1);
                    drawLineI(i, y2, x2, y2);
                    drawLineI(i, y1, i, y2);

                    return;
                }
            }
        }
    }
}


// ======Hard mode=================================================================

// Draw the L line when matching L success - for Hard Mode
void drawLineL(cell2** board, int x1, int y1, int x2, int y2) {
    // this code is almost the same as drawLineL for medium mode
    // but instead of check if (board[y][i].isValid), we check if (findTheNode(board, i, y) != NULL)
    
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
        if (checkLineI(board, x1, y1, x3, y3) && checkLineI(board, x3, y3, x2, y2)) {
            drawLineI(x1, y1, x3, y3);

            drawLineI(x3, y3, x2, y2);

            GoToXY(x3 * 10 + 15, y3 * 4 + 6);

            if (y2 > y1)
            {
                putchar(192);
            }
            else
            {
                putchar(218);
            }

            return;

        }
    }
    x3 = x2;
    y3 = y1;

    //  A----C          |----B
    //  |    |    and   |    |
    //  |----B          A----C
    if (findTheNode(board, x3, y3) == NULL) {
        if (checkLineI(board, x1, y1, x3, y3) && checkLineI(board, x3, y3, x2, y2)) {
            drawLineI(x1, y1, x3, y3);

            drawLineI(x3, y3, x2, y2);

            GoToXY(x3 * 10 + 15, y3 * 4 + 6);

            if (y2 > y1)
            {
                putchar(191);
            }
            else
            {
                putchar(217);
            }

            return;

        }
    }
}

// Draw the Z line when matching Z success - for Hard Mode
void drawLineZ(cell2** board, int x1, int y1, int x2, int y2) {
    // This code is almost the same as drawLineZ for medium mode
    // But instead of check if (board[y][i].isValid), we check if (findTheNode(board, i, y) != NULL)

    // |__      and     __|
    //    |            |
    int x3 = x1;
    int x4 = x2;
    if (y1 < y2) {
        for (int i = y1 + 1; i < y2; i++) {
            if ((findTheNode(board, x3, i) == NULL) && (findTheNode(board, x4, i) == NULL)) {
                if (checkLineI(board, x1, y1, x3, i) && checkLineI(board, x3, i, x4, i) && checkLineI(board, x4, i, x2, y2))
                {
                    drawLineI(x1, y1, x3, i);

                    drawLineI(x3, i, x4, i);

                    drawLineI(x4, i, x2, y2);


                    if (x2 > x1)
                    {
                        GoToXY(x3 * 10 + 15, i * 4 + 6);
                        putchar(192);

                        GoToXY(x4 * 10 + 15, i * 4 + 6);
                        putchar(191);

                    }
                    else
                    {
                        GoToXY(x3 * 10 + 15, i * 4 + 6);
                        putchar(217);

                        GoToXY(x4 * 10 + 15, i * 4 + 6);
                        putchar(218);

                    }

                    return;
                }
            }
        }
    }
    else {
        for (int i = y2 + 1; i < y1; i++) {
            if ((findTheNode(board, x3, i) == NULL) && (findTheNode(board, x4, i) == NULL)) {
                if (checkLineI(board, x1, y1, x3, i) && checkLineI(board, x3, i, x4, i) && checkLineI(board, x4, i, x2, y2))
                {
                    drawLineI(x1, y1, x3, i);

                    drawLineI(x3, i, x4, i);

                    drawLineI(x4, i, x2, y2);

                    if (x2 > x1)
                    {
                        GoToXY(x3 * 10 + 15, i * 4 + 6);
                        putchar(218);


                        GoToXY(x4 * 10 + 15, i * 4 + 6);
                        putchar(217);
                    }
                    else
                    {
                        GoToXY(x3 * 10 + 15, i * 4 + 6);
                        putchar(191);


                        GoToXY(x4 * 10 + 15, i * 4 + 6);
                        putchar(192);
                    }

                    return;
                }
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
                if (checkLineI(board, x1, y1, i, y3) && checkLineI(board, i, y3, i, y4) && checkLineI(board, i, y4, x2, y2))
                {
                    drawLineI(x1, y1, i, y3);

                    drawLineI(i, y3, i, y4);

                    drawLineI(i, y4, x2, y2);

                    if (y2 > y1)
                    {
                        GoToXY(i * 10 + 15, y3 * 4 + 6);
                        putchar(191);


                        GoToXY(i * 10 + 15, y4 * 4 + 6);
                        putchar(192);

                    }
                    else
                    {
                        GoToXY(i * 10 + 15, y3 * 4 + 6);
                        putchar(217);


                        GoToXY(i * 10 + 15, y4 * 4 + 6);
                        putchar(218);
                    }

                    return;
                }
            }
        }
    }
    else {
        for (int i = x2 + 1; i < x1; i++) {
            if ((findTheNode(board, i, y3) == NULL) && (findTheNode(board, i, y4) == NULL)) {
                if (checkLineI(board, x1, y1, i, y3) && checkLineI(board, i, y3, i, y4) && checkLineI(board, i, y4, x2, y2))
                {
                    drawLineI(x1, y1, i, y3);

                    drawLineI(i, y3, i, y4);

                    drawLineI(i, y4, x2, y2);

                    if (y2 > y1)
                    {
                        GoToXY(i * 10 + 15, y3 * 4 + 6);
                        putchar(218);

                        GoToXY(i * 10 + 15, y4 * 4 + 6);
                        putchar(217);

                    }
                    else
                    {
                        GoToXY(i * 10 + 15, y3 * 4 + 6);
                        putchar(192);

                        GoToXY(i * 10 + 15, y4 * 4 + 6);
                        putchar(191);
                    }

                    return;
                }
            }
        }
    }
}

// Draw the U line when matching U success - for Hard Mode
void drawLineU(cell2** board, int x1, int y1, int x2, int y2) {
    // This code is almost the same as drawLineU for medium mode
    // But instead of check if (board[y][i].isValid), we check if (findTheNode(board, i, y) != NULL)
        
    if (x1 == 0 && x2 == 0) {

        drawLineI(-1, y1, -1, y2);
        drawLineI(x1, y1, -1, y1);
        drawLineI(-1, y2, x2, y2);

        return;
    }

    if ((x1 == (BOARDWIDTH - 1)) && (x2 == (BOARDWIDTH - 1))) {

        drawLineI(BOARDWIDTH, y1, BOARDWIDTH, y2);
        drawLineI(x1, y1, BOARDWIDTH, y1);
        drawLineI(BOARDWIDTH, y2, x2, y2);

        return;
    }

    if (y1 == 0 && y2 == 0) {

        drawLineI(x1, -1, x2, -1);
        drawLineI(x1, y1, x1, -1);
        drawLineI(x2, -1, x2, y2);

        return;
    }

    if ((y1 == (BOARDHEIGHT - 1)) && (y2 == (BOARDHEIGHT - 1))) {

        drawLineI(x1, BOARDHEIGHT, x2, BOARDHEIGHT);
        drawLineI(x1, y1, x1, BOARDHEIGHT);
        drawLineI(x2, BOARDHEIGHT, x2, y2);

        return;
    }


    // upper U
    if (y1 == 0 || y2 == 0) { // 1 trong 2 dang o bien tren
        if (y1 == 0 && (findTheNode(board, x2, 0) == NULL) && checkLineI(board, x2, 0, x2, y2)) {
            drawLineI(x1, -1, x2, -1);
            drawLineI(x1, y1, x1, -1);
            drawLineI(x2, -1, x2, y2);

            return;
        }
        if (y2 == 0 && (findTheNode(board, x1, 0) == NULL) && checkLineI(board, x1, 0, x1, y1)) {
            drawLineI(x2, -1, x1, -1);
            drawLineI(x2, y2, x2, -1);
            drawLineI(x1, -1, x1, y1);

            return;
        }
    }

    int x3 = x1;
    int x4 = x2;
    if (y1 <= y2) {
        for (int i = y1 - 1; i >= -1; i--) {
            if (i == -1) {
                if ((findTheNode(board, x3, 0) == NULL) && (findTheNode(board, x4, 0) == NULL)) {
                    if (checkLineI(board, x1, y1, x3, 0) && checkLineI(board, x4, 0, x2, y2)) {

                        drawLineI(x1, y1, x3, i);
                        drawLineI(x2, y2, x4, i);
                        drawLineI(x3, i, x4, i);

                        return;
                    }
                }
                break;
            }
            if ((findTheNode(board, x3, i) == NULL) && (findTheNode(board, x4, i) == NULL)) {
                if (checkLineI(board, x1, y1, x3, i) && checkLineI(board, x3, i, x4, i) && checkLineI(board, x4, i, x2, y2)) {

                    drawLineI(x1, y1, x3, i);
                    drawLineI(x2, y2, x4, i);
                    drawLineI(x3, i, x4, i);

                    return;
                }
            }
        }
    }
    else { // y1 > y2
        for (int i = y2 - 1; i >= -1; i--) {
            if (i == -1) {
                if ((findTheNode(board, x3, 0) == NULL) && (findTheNode(board, x4, 0) == NULL)) {
                    if (checkLineI(board, x1, y1, x3, 0) && checkLineI(board, x4, 0, x2, y2)) {

                        drawLineI(x1, y1, x3, i);
                        drawLineI(x2, y2, x4, i);
                        drawLineI(x3, i, x4, i);

                        return;
                    }
                }
                break;
            }
            if ((findTheNode(board, x3, i) == NULL) && (findTheNode(board, x4, i) == NULL)) {
                if (checkLineI(board, x1, y1, x3, i) && checkLineI(board, x3, i, x4, i) && checkLineI(board, x4, i, x2, y2)) {

                    drawLineI(x1, y1, x3, i);
                    drawLineI(x2, y2, x4, i);
                    drawLineI(x3, i, x4, i);

                    return;
                }
            }
        }
    }

    // lower U
    if ((y1 == BOARDHEIGHT - 1) || (y2 == BOARDHEIGHT - 1)) { // 1 trong 2 dang o bien duoi
        if ((y1 == BOARDHEIGHT - 1) && (findTheNode(board, x2, BOARDHEIGHT - 1) == NULL) && checkLineI(board, x2, BOARDHEIGHT - 1, x2, y2)) {
            drawLineI(x1, BOARDHEIGHT, x2, BOARDHEIGHT);
            drawLineI(x1, y1, x1, BOARDHEIGHT);
            drawLineI(x2, BOARDHEIGHT, x2, y2);

            return;
        }
        if ((y2 == BOARDHEIGHT - 1) && (findTheNode(board, x1, BOARDHEIGHT - 1) == NULL) && checkLineI(board, x1, BOARDHEIGHT - 1, x1, y1)) {

            drawLineI(x1, BOARDHEIGHT, x2, BOARDHEIGHT);
            drawLineI(x1, y1, x1, BOARDHEIGHT);
            drawLineI(x2, BOARDHEIGHT, x2, y2);

            return;
        }
    }

    if (y1 <= y2) {
        for (int i = y2 + 1; i <= BOARDHEIGHT; i++) {
            if (i == BOARDHEIGHT) {
                if ((findTheNode(board, x3, BOARDHEIGHT - 1) == NULL) && (findTheNode(board, x4, BOARDHEIGHT - 1) == NULL)) {
                    if (checkLineI(board, x1, y1, x3, BOARDHEIGHT - 1) && checkLineI(board, x4, BOARDHEIGHT - 1, x2, y2)) {

                        drawLineI(x1, y1, x3, i);
                        drawLineI(x2, y2, x4, i);
                        drawLineI(x3, i, x4, i);

                        return;
                    }
                }
                break;
            }
            if ((findTheNode(board, x3, i) == NULL) && (findTheNode(board, x4, i) == NULL)) {
                if (checkLineI(board, x1, y1, x3, i) && checkLineI(board, x3, i, x4, i) && checkLineI(board, x4, i, x2, y2)) {

                    drawLineI(x1, y1, x3, i);
                    drawLineI(x2, y2, x4, i);
                    drawLineI(x3, i, x4, i);

                    return;
                }
            }
        }
    }
    else { // y1 > y2
        for (int i = y1 + 1; i <= BOARDHEIGHT; i++) {
            if (i == BOARDHEIGHT) {
                if ((findTheNode(board, x3, BOARDHEIGHT - 1) == NULL) && (findTheNode(board, x4, BOARDHEIGHT - 1) == NULL)) {
                    if (checkLineI(board, x1, y1, x3, BOARDHEIGHT - 1) && checkLineI(board, x4, BOARDHEIGHT - 1, x2, y2)) {

                        drawLineI(x1, y1, x3, i);
                        drawLineI(x2, y2, x4, i);
                        drawLineI(x3, i, x4, i);

                        return;
                    }
                }
                break;
            }
            if ((findTheNode(board, x3, i) == NULL) && (findTheNode(board, x4, i) == NULL)) {
                if (checkLineI(board, x1, y1, x3, i) && checkLineI(board, x3, i, x4, i) && checkLineI(board, x4, i, x2, y2)) {

                    drawLineI(x1, y1, x3, i);
                    drawLineI(x2, y2, x4, i);
                    drawLineI(x3, i, x4, i);

                    return;
                }
            }
        }
    }

    // left U
    if (x1 == 0 || x2 == 0) { // 1 trong 2 dang o bien trai
        if (x1 == 0 && (findTheNode(board, 0, y2) == NULL) && checkLineI(board, 0, y2, x2, y2)) {

            drawLineI(x1, y1, -1, y1);
            drawLineI(-1, y2, x2, y2);
            drawLineI(-1, y1, -1, y2);

            return;
        }
        if (x2 == 0 && (findTheNode(board, 0, y1) == NULL) && checkLineI(board, 0, y1, x1, y1)) {

            drawLineI(x1, y1, -1, y1);
            drawLineI(-1, y2, x2, y2);
            drawLineI(-1, y1, -1, y2);

            return;
        }
    }

    int y3 = y1;
    int y4 = y2;
    if (x1 <= x2) {
        for (int i = x1 - 1; i >= -1; i--) {
            if (i == -1) {
                if ((findTheNode(board, 0, y3) == NULL) && (findTheNode(board, 0, y4) == NULL)) {
                    if (checkLineI(board, x1, y1, 0, y3) && checkLineI(board, 0, y4, x2, y2)) {

                        drawLineI(x1, y1, i, y3);
                        drawLineI(i, y3, i, y4);
                        drawLineI(i, y4, x4, y4);

                        return;
                    }
                }
                break;
            }
            if ((findTheNode(board, i, y3) == NULL) && (findTheNode(board, i, y4) == NULL)) {
                if (checkLineI(board, x1, y1, i, y3) && checkLineI(board, i, y3, i, y4) && checkLineI(board, i, y4, x2, y2)) {

                    drawLineI(x1, y1, i, y3);
                    drawLineI(i, y3, i, y4);
                    drawLineI(i, y4, x4, y4);

                    return;
                }
            }
        }
    }
    else { // x1 > x2
        for (int i = x2 - 1; i >= -1; i--) {
            if (i == -1) {
                if ((findTheNode(board, 0, y3) == NULL) && (findTheNode(board, 0, y4) == NULL)) {
                    if (checkLineI(board, x1, y1, 0, y3) && checkLineI(board, 0, y4, x2, y2)) {

                        drawLineI(x1, y1, i, y3);
                        drawLineI(i, y3, i, y4);
                        drawLineI(i, y4, x4, y4);

                        return;
                    }
                }
                break;
            }
            if ((findTheNode(board, i, y3) == NULL) && (findTheNode(board, i, y4) == NULL)) {
                if (checkLineI(board, x1, y1, i, y3) && checkLineI(board, i, y3, i, y4) && checkLineI(board, i, y4, x2, y2)) {

                    drawLineI(x1, y1, i, y3);
                    drawLineI(i, y3, i, y4);
                    drawLineI(i, y4, x4, y4);

                    return;
                }
            }
        }
    }

    // right U
    if ((x1 == BOARDWIDTH - 1) || (x2 == BOARDWIDTH - 1)) { // 1 trong 2 dang o bien phai
        if ((x1 == BOARDWIDTH - 1) && (findTheNode(board, BOARDWIDTH - 1, y2) == NULL) && checkLineI(board, BOARDWIDTH - 1, y2, x2, y2)) {

            drawLineI(x1, y1, BOARDWIDTH, y1);
            drawLineI(BOARDWIDTH, y2, x2, y2);
            drawLineI(BOARDWIDTH, y1, BOARDWIDTH, y2);

            return;
        }
        if ((x2 == BOARDWIDTH - 1) && (findTheNode(board, BOARDWIDTH - 1, y1) == NULL) && checkLineI(board, BOARDWIDTH - 1, y1, x1, y1)) {

            drawLineI(x1, y1, BOARDWIDTH, y1);
            drawLineI(BOARDWIDTH, y2, x2, y2);
            drawLineI(BOARDWIDTH, y1, BOARDWIDTH, y2);

            return;
        }
    }

    if (x1 <= x2) {
        for (int i = x2 + 1; i <= BOARDWIDTH; i++) {
            if (i == BOARDWIDTH) {
                if ((findTheNode(board, BOARDWIDTH - 1, y3) == NULL) && (findTheNode(board, BOARDWIDTH - 1, y4) == NULL)) {
                    if (checkLineI(board, x1, y1, BOARDWIDTH - 1, y3) && checkLineI(board, BOARDWIDTH - 1, y4, x2, y2)) {

                        drawLineI(x1, y1, i, y1);
                        drawLineI(i, y2, x2, y2);
                        drawLineI(i, y1, i, y2);

                        return;
                    }
                }
                break;
            }
            if ((findTheNode(board, i, y3) == NULL) && (findTheNode(board, i, y4) == NULL)) {
                if (checkLineI(board, x1, y1, i, y3) && checkLineI(board, i, y3, i, y4) && checkLineI(board, i, y4, x2, y2)) {

                    drawLineI(x1, y1, i, y1);
                    drawLineI(i, y2, x2, y2);
                    drawLineI(i, y1, i, y2);

                    return;
                }
            }
        }
    }
    else { // x1 > x2
        for (int i = x1 + 1; i <= BOARDWIDTH; i++) {
            if (i == BOARDWIDTH) {
                if ((findTheNode(board, BOARDWIDTH - 1, y3) == NULL) && (findTheNode(board, BOARDWIDTH - 1, y4) == NULL)) {
                    if (checkLineI(board, x1, y1, BOARDWIDTH - 1, y3) && checkLineI(board, BOARDWIDTH - 1, y4, x2, y2)) {

                        drawLineI(x1, y1, i, y1);
                        drawLineI(i, y2, x2, y2);
                        drawLineI(i, y1, i, y2);

                        return;
                    }
                }
                break;
            }
            if ((findTheNode(board, i, y3) == NULL) && (findTheNode(board, i, y4) == NULL)) {
                if (checkLineI(board, x1, y1, i, y3) && checkLineI(board, i, y3, i, y4) && checkLineI(board, i, y4, x2, y2)) {

                    drawLineI(x1, y1, i, y1);
                    drawLineI(i, y2, x2, y2);
                    drawLineI(i, y1, i, y2);

                    return;
                }
            }
        }
    }
}

