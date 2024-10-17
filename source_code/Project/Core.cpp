#include <iostream>
#include <iomanip>
#include <conio.h>
#include <math.h>
#include <Windows.h>
#include <string>
#include <mmsystem.h>

#include "Check.h"
#include "Core.h"
#include "Struct.h"
#include "Menu.h"
#include "Visual.h"

using namespace std;

// ======Utility=================================================================

// Setting the color of background and font on the console window
void setColor(int background, int font)
{
    int color = background * 16 + font;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


// https://codelearn.io/sharing/windowsh-ham-dinh-dang-noi-dung-console
// Go to the position X, Y on the console window
void GoToXY(int posX, int posY)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Position;
    Position.X = posX;
    Position.Y = posY;

    SetConsoleCursorPosition(hStdout, Position);
}

// Play the sound effect
void playSound(int t)
{
    LPCWSTR soundFile[] = { L"Data//Sound Effect//MenuMove.wav", L"Data//Sound Effect//EnterMenu.wav",
                            L"Data//Sound Effect//BoardMove.wav",
                            L"Data//Sound Effect//SelectDeselect.wav", L"Data//Sound Effect//Matching.wav",
                            L"Data//Sound Effect//Winning.wav", L"Data//Sound Effect//Losing.wav",
                            L"Data//Sound Effect//Error.wav", L"Data//Sound Effect//Notification.wav" };

    PlaySound(soundFile[t], NULL, SND_FILENAME | SND_ASYNC);
}

// Compare two player's record - Helping saveLeaderboard() function work
bool compareP(player p1, player p2)
{
    // Compare who has more point
    if (p1.point > p2.point)
    {
        return true;
    }
    else if (p1.point < p2.point)
    {
        return false;
    }

    // Compare who has the minimum stages
    if (p1.stages < p2.stages)
    {
        return true;
    }
    else if (p1.stages > p2.stages)
    {
        return false;
    }

    // Compare which player's record has the higher difficulty
    if (p1.mode > p2.mode)
    {
        return true;
    }
    else if (p1.mode < p2.mode)
    {
        return false;
    }

    // If point, stages and difficulty are equal, then return true (The lastest record, the better)
    return true;
}


// Save the new player's record to the Leaderboard
int posInLeaderboard(player p, lst& list) {

    // New player's record position
    int index = 11;
    
    // list.player always have 10 records p[0],... p[9]
    // Compare to each player's records on the leaderboard

    while (compareP(p, list.Player[index - 2]))
    {
        index--;

        if (index == 1)
        {
            break;
        }
    }
    
    // If the new player is inside top 10 player have the best performance, cout the line :"You are the NO. ... the Leaderboard"
    if (index != 11)
    {
        GoToXY(59, 17);

        setColor(BLACK, BRIGHT_WHITE);
        cout << "You are the ";

        if (index == 1)
        {
            setColor(BLACK, LIGHT_RED);
            cout << "NO. " << index;
        }
        else
        {
            setColor(BLACK, YELLOW);
            cout << "NO. " << index;
        }

        setColor(BLACK, BRIGHT_WHITE);
        cout << " of the Leaderboard!";
    }

    // Return the new player's record's position in Leaderboard
    return index;
}

// Play on the console window after the game ended (Ask if the player want to continue to the next stage or not)
void aftermathAction(player p, lst& list, int status, int index)
{
    // If player still have atleast 1 life and the game has ended
    if (p.life && (status == 1 || status == 2)) {

        // Display "YOU WON"
        displayStatus(true);

        // If the player won because of there is no more valid pair to match (The board still has cells)
        if (status == 2) {
            setColor(BLACK, AQUA);
            GoToXY(28, 9);
            cout << "THERE IS NO MORE MOVE, THEREFORE ";
        }

        playSound(WINNING);

        setColor(BLACK, BRIGHT_WHITE);
        GoToXY(50, 19);
        cout << "Do you want to continue next game? (Y/N): ";

        while (true)
        {
            GoToXY(95, 19);
            char c;
            c = _getch();

            if (c == 'y' || c == 'Y') {
                p.stages++;

                if (p.mode == 1)
                {
                    mediumMode(p, list);
                }
                else
                {
                    hardMode(p, list);
                }

                break;
            }
            else if (c == 'n' || c == 'N')
            {
                list.Player.insert(list.Player.begin() + (index - 1), p);

                break;
            }
        }
    }
    else if (p.life == 0) {

        displayStatus(0);
        playSound(LOSING);

        list.Player.insert(list.Player.begin() + (index - 1), p);

        Sleep(2000);
    }
    else if (status == 3)
    {
        list.Player.insert(list.Player.begin() + (index - 1), p);
    }
}

// win = true: Winn
// win = false: Lose
// See if you win or lose, then and print out on the console window
void displayStatus(bool win) {

    HANDLE Controller = GetStdHandle(STD_OUTPUT_HANDLE);


    if (win) {

        SetConsoleTextAttribute(Controller, 3);
        GoToXY(50, 10);
        cout << R"(
                |||   |||   |||||||||   |||   |||       |||   |||    |||   |||||||||   ||||   |||
                 ||| |||    |||   |||   |||   |||       |||  |||||   |||   |||   |||   |||||  |||
                  |||||     |||   |||   |||   |||       ||| ||| |||  |||   |||   |||   ||| || |||
                   |||      |||   |||   |||   |||        |||||    |||||    |||   |||   |||  |||||
                   |||      |||||||||   |||||||||         |||      |||     |||||||||   |||   |||| 
        )";

        SetConsoleTextAttribute(Controller, 7);
    }
    else {

        SetConsoleTextAttribute(Controller, 4);
        GoToXY(50, 10);
        cout << R"(
                |||   |||   |||||||||   |||   |||       |||         |||||||||   |||||||||   |||||||||
                 ||| |||    |||   |||   |||   |||       |||         |||   |||   |||         |||      
                  |||||     |||   |||   |||   |||       |||         |||   |||   |||||||||   |||||||||
                   |||      |||   |||   |||   |||       |||         |||   |||         |||   |||      
                   |||      |||||||||   |||||||||       |||||||||   |||||||||   |||||||||   ||||||||| 
        )";
        SetConsoleTextAttribute(Controller, 7);
    }

    return;
}


// Make W, A, S, D work as arrow keys and turn B -> b
int returnKey(int t)
{
    // If t = 'W' or t = 'w'
    if (t == 87 || t == 119)
    {
        return (KEY_UP);
    }

    // If t = 'S' or t = 's'
    if (t == 83 || t == 115)
    {
        return (KEY_DOWN);
    }

    // If t = 'A' or t = 'a'
    if (t == 65 || t == 97)
    {
        return (KEY_LEFT);
    }

    // If t = 'D' or t = 'd'
    if (t == 68 || t == 100)
    {
        return (KEY_RIGHT);
    }

    // If t = 'B' return 'b'
    if (t == 66)
    {
        return (98);
    }

    // Return the t in the end (no change)
    return t;
}

// Setting player's status at the begining of the game, and let the player enter their name
void getPlayerPlayingInfo(player& p)
{
    system("CLS");

    // Setting player's status
    p.life = 3;
    p.point = 0;
    p.stages = 1;

    char temp[21];

    setColor(BLACK, BRIGHT_WHITE);

    // Receive the input name
    GoToXY(58, 18);
    cout << "Please enter your name (only 20 characters):";
    setColor(BLACK, BRIGHT_WHITE);
    GoToXY(74, 20);
    cin.getline(temp, 20); 

    p.name = temp;

    // If player just enter, the player's name is "UNKNOWN"
    if (p.name.length() == 0)
    {
        p.name = "UNKNOWN";
    }
}

// ======Medium mode=================================================================

// Basic Move on console window at game display time - for Medium mode
// KEY_UP, KEY_DOWN, KEY LEFT, KEY RIGHT, ENTER_KEY, ESC KEY
// B, b , W, w, A, a, S, s, D, s
void move(cell** board, position& pos, int& status, player& p, position selectedPos[], background bg, int& couple) {
    int temp;

    temp = returnKey(_getch());

    if (temp == ESC_KEY || temp == ENTER_KEY || temp == 98) {
        if (temp == ESC_KEY) { // If player press ESC
            //3: Exit game
            status = 3;
        }
        else if (temp == ENTER_KEY) { // If player press ENTER
            
            // If player match the same cell - Deselect it
            if (pos.x == selectedPos[0].x && pos.y == selectedPos[0].y) {

                playSound(DSELECT);

                // Highlight the cell that player deselect by gray color
                board[selectedPos[0].y][selectedPos[0].x].drawBox(GRAY * 16);
                Sleep(200);
                board[selectedPos[0].y][selectedPos[0].x].isSelected = 0;

                couple = 2;
                selectedPos[0] = { -1, -1 };
            } 
            else {
                // Store the cell(s) that player choose
                selectedPos[2 - couple].x = pos.x;
                selectedPos[2 - couple].y = pos.y;
                board[pos.y][pos.x].isSelected = 1;
                couple--;

                if (couple == 0) { // If player have match a pair cells
                    
                    if (board[selectedPos[0].y][selectedPos[0].x].val == board[selectedPos[1].y][selectedPos[1].x].val) {  // If these cells have a same character
                        // x1, y1, x2, y2

                        playSound(MATCHING);

                        // flag = 0: Wrong pattern
                        // flag = 2: I pattern
                        // flag = 3: L pattern
                        // flag = 4: Z pattern
                        // flag = 5: U pattern
                        int flag = allCheck(board, selectedPos[0].x, selectedPos[0].y, selectedPos[1].x, selectedPos[1].y);

                        if (flag) {
                            // Pattern I, L
                            if (flag <= 3)
                            {
                                setColor(BLACK, LIGHT_GREEN);
                                GoToXY(87, 11);
                                cout << "+20";

                                p.point += 20;
                            }
                            // Pattern Z, U
                            else
                            {
                                setColor(BLACK, LIGHT_GREEN);
                                GoToXY(87, 11);
                                cout << "+25";

                                p.point += 25;
                            }

                            setColor(BLACK, WHITE);

                            // Hightlight the matching cells by green color (Green background with different font's color)
                            board[selectedPos[0].y][selectedPos[0].x].drawBox(40);
                            board[selectedPos[1].y][selectedPos[1].x].drawBox(40);
                            
                            // Showing the pattern that player choose and the plus point at the player's info board
                            if (flag == 2)
                            {
                                setColor(GREEN, WHITE);
                                drawLineI(selectedPos[0].x, selectedPos[0].y, selectedPos[1].x, selectedPos[1].y);
                                setColor(BLACK, LIGHT_GREEN);
                                GoToXY(80, 13);
                                cout << "FOUND MATCHING PATTERN I!";
                            }
                            else if (flag == 3)
                            {
                                setColor(GREEN, WHITE);
                                drawLineL(board, selectedPos[0].x, selectedPos[0].y, selectedPos[1].x, selectedPos[1].y);
                                setColor(BLACK, LIGHT_GREEN);
                                GoToXY(80, 13);
                                cout << "FOUND MATCHING PATTERN L!";
                            }
                            else if (flag == 4)
                            {
                                setColor(GREEN, WHITE);
                                drawLineZ(board, selectedPos[0].x, selectedPos[0].y, selectedPos[1].x, selectedPos[1].y);
                                setColor(BLACK, LIGHT_GREEN);
                                GoToXY(80, 13);
                                cout << "FOUND MATCHING PATTERN Z!";
                            }
                            else if (flag == 5)
                            {
                                setColor(GREEN, WHITE);
                                drawLineU(board, selectedPos[0].x, selectedPos[0].y, selectedPos[1].x, selectedPos[1].y);
                                setColor(BLACK, LIGHT_GREEN);
                                GoToXY(80, 13);
                                cout << "FOUND MATCHING PATTERN U!";
                            }
       
                            Sleep(500);

                            setColor(BLACK, WHITE);

                            // Clear all the unnecessary space on the player's info board
                            GoToXY(80, 13);
                            cout << "                         ";
                            GoToXY(88, 10);
                            cout << p.point << "            ";
                            GoToXY(87, 11);
                            cout << "   ";

                            setColor(BLACK, WHITE);
                            // Delete that 2 cells
                            board[selectedPos[0].y][selectedPos[0].x].isValid = 0;
                            board[selectedPos[0].y][selectedPos[0].x].deleteBox();
                            board[selectedPos[1].y][selectedPos[1].x].isValid = 0;
                            board[selectedPos[1].y][selectedPos[1].x].deleteBox();

                            // Render the board but only print the background
                            renderBoard(board, bg, 1);
                        }
                        else {
                            // Hightlight the matching cells by red color and different font's color because it is wrong pattern
                            board[selectedPos[0].y][selectedPos[0].x].drawBox(RED * 16 + 6);
                            board[selectedPos[1].y][selectedPos[1].x].drawBox(RED * 16 + 6);
                            playSound(S_ERROR);

                            p.life--;
                            p.point -= 10;

                            // Showing the pattern that player choose is wrong and the subtract point and subtract life at the player's info board
                            setColor(BLACK, LIGHT_RED);
                            GoToXY(80, 13);
                            cout << "WRONG PATTERN!";
                            GoToXY(87, 11);
                            cout << "-10";
                            if (p.life == 2)
                            {
                                GoToXY(92, 6);
                            }
                            else if (p.life == 1)
                            {
                                GoToXY(90, 6);
                            }
                            else
                            {
                                GoToXY(88, 6);
                            }
                            cout << "* ";

                            Sleep(500);

                            // Clear all the unnecessary space on the player's info board
                            GoToXY(87, 11);
                            cout << "   ";
                            if (p.life == 2)
                            {
                                GoToXY(92, 6);
                            }
                            else if (p.life == 1)
                            {
                                GoToXY(90, 6);
                            }
                            else
                            {
                                GoToXY(88, 6);
                            }
                            cout << "  ";
                            setColor(BLACK, WHITE);
                            GoToXY(88, 10);
                            cout << p.point << "            ";
                            GoToXY(80, 13);
                            cout << "               ";
                        }
                    }
                    else {
                        // Hightlight the matching cells by red color and different font's color because it is wrong pattern
                        board[selectedPos[0].y][selectedPos[0].x].drawBox(RED * 16 + 6);
                        board[selectedPos[1].y][selectedPos[1].x].drawBox(RED * 16 + 6);

                        playSound(S_ERROR);

                        p.life--;
                        p.point -= 10;

                        // Showing the pattern that player choose is wrong and the subtract point and subtract life at the player's info board
                        setColor(BLACK, LIGHT_RED);
                        GoToXY(80, 13);
                        cout << "WRONG PATTERN!";
                        GoToXY(87, 11);
                        cout << "-10";
                        if (p.life == 2)
                        {
                            GoToXY(92, 6);
                        }
                        else if (p.life == 1)
                        {
                            GoToXY(90, 6);
                        }
                        else
                        {
                            GoToXY(88, 6);
                        }
                        cout << "* ";

                        Sleep(500);

                        // Clear all the unnecessary space on the player's info board
                        GoToXY(87, 11);
                        cout << "   ";
                        if (p.life == 2)
                        {
                            GoToXY(92, 6);
                        }
                        else if (p.life == 1)
                        {
                            GoToXY(90, 6);
                        }
                        else
                        {
                            GoToXY(88, 6);
                        }
                        cout << "  ";
                        setColor(BLACK, WHITE);
                        GoToXY(88, 10);
                        cout << p.point << "            ";
                        GoToXY(80, 13);
                        cout << "               ";
                    }
                    // Return back to the status of choose none cell
                    board[selectedPos[0].y][selectedPos[0].x].isSelected = 0;
                    board[selectedPos[1].y][selectedPos[1].x].isSelected = 0;
                    couple = 2;
                    selectedPos[0] = { -1, -1 };
                    selectedPos[1] = { -1, -1 };

                    // Find a new valid cell to show the current cell player at
                    for (int i = pos.y; i < BOARDHEIGHT; i++) {
                        for (int j = pos.x; j < BOARDWIDTH; j++) {
                            if (board[i][j].isValid == 1) {
                                pos.x = j;
                                pos.y = i;
                                return;
                            }
                        }
                    }

                    for (int i = pos.y; i >= 0; i--) {
                        for (int j = pos.x; j >= 0; j--) {
                            if (board[i][j].isValid == 1) {
                                pos.x = j;
                                pos.y = i;
                                return;
                            }
                        }
                    }

                    for (int i = 0; i < BOARDHEIGHT; i++) { 
                        for (int j = 0; j < BOARDWIDTH; j++) {
                            if (board[i][j].isValid == 1) {
                                pos.x = j;
                                pos.y = i;
                                return;
                            }
                        }
                    }
                }
                else
                {
                    // If player have only choose a cell
                    playSound(DSELECT);
                }
            }
        } else if (temp == 98) {

            // If player's point is not negative then give player suggestion move
            if (p.point >= 0)
            {
                playSound(NOTIFICATION);

                suggestMove(board);

                p.point -= 30;

                setColor(BLACK, LIGHT_RED);
                GoToXY(87, 11);
                cout << "-30";
            }
            else
            {
                playSound(S_ERROR);

                setColor(BLACK, LIGHT_RED);
                GoToXY(80, 13);
                cout << "YOUR POINT IS NEGATIVE!";
            }

            Sleep(400);

            // Clear all the unnecessary space on the player's info board
            setColor(BLACK, WHITE);
            GoToXY(88, 10);
            cout << p.point << "            ";
            GoToXY(87, 11);
            cout << "   ";
            GoToXY(80, 13);
            cout << "                       ";
        }
    }
    else // If player enter W/ w/ up arrow, S/ s/ down arrow, D/ d/ left arrow, A/ a/ right arrow or any other keys
    {

        // Check if this cell is selected or not
        if ((pos.y != selectedPos[0].y || pos.x != selectedPos[0].x) && (pos.y != selectedPos[1].y || pos.x != selectedPos[1].x)) 
            board[pos.y][pos.x].isSelected = 0;

        // Check which direction player choose
        switch (temp)
        {
            // For each direction, find a new valid cell from the previous cell's position to put player's cursor on
            // Find from column ... to ..., row ... to .... If there is any cell valid turn the player's cursor to it

            //If player enter W / w / up arrow
            case KEY_UP:

                playSound(MOVE);

                for (int i = pos.x; i < BOARDWIDTH; i++) {
                    for (int j = pos.y - 1; j >= 0; j--) {
                        if (board[j][i].isValid) {
                            pos.x = i;
                            pos.y = j;
                            return;
                        }
                    }
                }

                for (int i = pos.x - 1; i >= 0; i--) {
                    for (int j = pos.y - 1; j >= 0; j--) {
                        if (board[j][i].isValid) {
                            pos.x = i;
                            pos.y = j;
                            return;
                        }
                    }
                }

                for (int i = pos.x; i < BOARDWIDTH; i++) {
                    for (int j = BOARDHEIGHT - 1; j > pos.y; j--) {
                        if (board[j][i].isValid) {
                            pos.x = i;
                            pos.y = j;
                            return;
                        }
                    }
                }

                for (int i = pos.x; i >= 0; i--) {
                    for (int j = BOARDHEIGHT - 1; j > pos.y; j--) {
                        if (board[j][i].isValid) {
                            pos.x = i;
                            pos.y = j;
                            return;
                        }
                    }
                }

                break;

            //If player enter S / s / down arrow
            case KEY_DOWN:

                playSound(MOVE);

                for (int i = pos.x; i < BOARDWIDTH; i++) {
                    for (int j = pos.y + 1; j < BOARDHEIGHT; j++) {
                        if (board[j][i].isValid) {
                            pos.x = i;
                            pos.y = j;
                            return;
                        }
                    }
                }

                for (int i = pos.x - 1; i >= 0; i--) {
                    for (int j = pos.y + 1; j < BOARDHEIGHT; j++) {
                        if (board[j][i].isValid) {
                            pos.x = i;
                            pos.y = j;
                            return;
                        }
                    }
                }

                for (int i = pos.x; i < BOARDWIDTH; i++) {
                    for (int j = 0; j < pos.y; j++) {
                        if (board[j][i].isValid) {
                            pos.x = i;
                            pos.y = j;
                            return;
                        }
                    }
                }

                for (int i = pos.x - 1; i >= 0; i--) {
                    for (int j = 0; j < pos.y; j++) {
                        if (board[j][i].isValid) {
                            pos.x = i;
                            pos.y = j;
                            return;
                        }
                    }
                }

                break;

            //If player enter A / a / left arrow
            case KEY_LEFT:

                playSound(MOVE);

                for (int i = pos.y; i >= 0; i--) {
                    for (int j = pos.x - 1; j >= 0; j--) {
                        if (board[i][j].isValid) {
                            pos.x = j;
                            pos.y = i;
                            return;
                        }
                    }
                }

                for (int i = pos.y + 1; i < BOARDHEIGHT; i++) {
                    for (int j = pos.x - 1; j >= 0; j--) {
                        if (board[i][j].isValid) {
                            pos.x = j;
                            pos.y = i;
                            return;
                        }
                    }
                }

                for (int i = pos.y; i >= 0; i--) {
                    for (int j = BOARDWIDTH - 1; j > pos.x; j--) {
                        if (board[i][j].isValid) {
                            pos.x = j;
                            pos.y = i;
                            return;
                        }
                    }
                }

                for (int i = pos.y + 1; i < BOARDHEIGHT; i++) {
                    for (int j = BOARDWIDTH - 1; j > pos.x; j--) {
                        if (board[i][j].isValid) {
                            pos.x = j;
                            pos.y = i;
                            return;
                        }
                    }
                }
                break;

            //If player enter D / d / right arrow
            case KEY_RIGHT:

                playSound(MOVE);

                for (int i = pos.y; i >= 0; i--) {
                    for (int j = pos.x + 1; j < BOARDWIDTH; j++) {
                        if (board[i][j].isValid) {
                            pos.x = j;
                            pos.y = i;
                            return;
                        }
                    }
                }

                for (int i = pos.y + 1; i < BOARDHEIGHT; i++) {
                    for (int j = pos.x + 1; j < BOARDWIDTH; j++) {
                        if (board[i][j].isValid) {
                            pos.x = j;
                            pos.y = i;
                            return;
                        }
                    }
                }

                for (int i = pos.y; i >= 0; i--) {
                    for (int j = 0; j < pos.x; j++) {
                        if (board[i][j].isValid) {
                            pos.x = j;
                            pos.y = i;
                            return;
                        }
                    }
                }

                for (int i = pos.y + 1; i < BOARDHEIGHT; i++) {
                    for (int j = 0; j < pos.x; j++) {
                        if (board[i][j].isValid) {
                            pos.x = j;
                            pos.y = i;
                            return;
                        }
                    }
                }

            // If any other key is pressed
            default:
                break;
        }
    }
}

// Suggest two cells that can be matched in legal pattern (I, L, Z, U) - for Medium Mode
void suggestMove(cell** board) {

    // Check any pair cells on the board that can be matched
    for (int i = 0; i < BOARDHEIGHT; i++) {
        for (int j = 0; j < BOARDWIDTH; j++) {

            // If that cell is not a blank space
            if (board[i][j].isValid != 0) {
                for (int x = 0; x < BOARDHEIGHT; x++) {
                    for (int y = 0; y < BOARDWIDTH; y++) {
                        // If two cells is not the same cell
                        if (x != i || y != j) {

                            // If two cells have a legal pattern and the 2nd cell is not a blank space
                            if (allCheck(board, j, i, y, x) && board[x][y].isValid != 0) {

                                // Highlight that two cells with light yellow background
                                board[i][j].isSelected = 1;
                                board[x][y].isSelected = 1;
                                board[i][j].drawBox(LIGHT_YELLOW * 16);
                                board[x][y].drawBox(LIGHT_YELLOW * 16);
                                board[i][j].isSelected = 0;
                                board[x][y].isSelected = 0;

                                return;
                            }
                        }
                    }
                }
            }
        }
    }
}


// Creating the board to contain all essential data to help the game works - for Medium Mode
void initBoard(cell** board) {

    // Attach the position on each cell
    for (int i = 0; i < BOARDHEIGHT; i++) { 
        board[i] = new cell[BOARDWIDTH];
        for (int j = 0; j < BOARDWIDTH; j++) {
            board[i][j].pos.x = j;
            board[i][j].pos.y = i;
        }
    }

    int flagNum = (BOARDWIDTH * BOARDHEIGHT) / 2;

    // Attach a character to each cell
    while (flagNum) {  

        int index, time = 2;
        // Random a character from A to Z
        int num = rand() % (90 - 65) + 65;

        // Attach that character to 2 random cells
        while (time) { 

            index = rand() % (BOARDWIDTH * BOARDHEIGHT);
            if (board[index % BOARDHEIGHT][index / BOARDHEIGHT].val == ' ') {

                board[index % BOARDHEIGHT][index / BOARDHEIGHT].val = char(num);
                time--;
            }
        }

        flagNum--;
    }
}

// flag = 0: There is no new matching cells
// flag > 0: There is A NEW matching cells
// Print out the backgound and all the cells of the board on the console window - for Medium Mode
void renderBoard(cell** board, background bg, int flag) {
    // If there is a new matching cells
    if (flag > 0)
    {
        // Clear all the space beyond the board
        setColor(BLACK, WHITE);

        for (int i = 0; i < 61; i++) {

            GoToXY(5 + i, 2);
            cout << ' ';
            GoToXY(5 + i, 3);
            cout << ' ';
            GoToXY(5 + i, 37);
            cout << ' ';
            GoToXY(5 + i, 38);
            cout << ' ';
        }

        for (int i = 0; i < 35; i++) {

            GoToXY(5, 3 + i);
            cout << ' ';
            GoToXY(6, 3 + i);
            cout << ' ';
            GoToXY(7, 3 + i);
            cout << ' ';
            GoToXY(8, 3 + i);
            cout << ' ';
            GoToXY(9, 3 + i);
            cout << ' ';
            GoToXY(61, 3 + i);
            cout << ' ';
            GoToXY(62, 3 + i);
            cout << ' ';
            GoToXY(63, 3 + i);
            cout << ' ';
            GoToXY(64, 3 + i);
            cout << ' ';
            GoToXY(65, 3 + i);
            cout << ' ';
        }

        // Print out the all background to delete the matching line
        for (int i = 0; i < BOARDHEIGHT; i++) {
            for (int j = 0; j < BOARDWIDTH; j++) {
                if (!board[i][j].isValid) {

                    bg.displayBackground(j, i);

                    if (i != 0)
                    {
                        board[i - 1][j].drawBox(112);
                    }
                    if (i != BOARDHEIGHT - 1)
                    {
                        board[i + 1][j].drawBox(112);
                    }
                    if (j != 0)
                    {
                        board[i][j - 1].drawBox(112);
                    }
                    if (j != BOARDWIDTH - 1)
                    {
                        board[i][j + 1].drawBox(112);
                    }
                }
            }
        }

        return;
    }

    // If there is no new matching cells, draw a box of all cells like normally
    for (int i = 0; i < BOARDHEIGHT; i++) {
        for (int j = 0; j < BOARDWIDTH; j++) {
            if (board[i][j].isValid)
            {
                board[i][j].drawBox(WHITE * 16);
            }
        }
    }
}

// Delete dynamic memory of the board
void deleteBoard(cell** &board) {
    for (int i = 0; i < BOARDHEIGHT; i++) {
        delete[] board[i];
    }
    delete[] board;
    board = NULL;
}

// Print out the box that cover the cell board - for Medium Mode
void drawRectangle(cell** board, int left, int top) {

    if (board == NULL) return;

    setColor(BLACK, BRIGHT_WHITE);

    // Draw top line
    GoToXY(left + 1, top);
    putchar(201);
    for (int i = 1; i < (BOARDWIDTH + 2) * 10 - 2; i++)
    {
        Sleep(1);
        putchar(205);
    }
    putchar(187);

    // Draw right line
    for (int i = 1; i < (BOARDHEIGHT + 2) * 4; i++)
    {
        Sleep(1);
        GoToXY((BOARDWIDTH + 2) * 10 + left - 1, i + top);
        putchar(186);
    }
    GoToXY((BOARDWIDTH + 2) * 10 + left - 1, (BOARDHEIGHT + 2) * 4 + top);
    putchar(188);

    // Draw bottom line
    for (int i = 1; i < (BOARDWIDTH + 2) * 10 - 2; i++)
    {
        GoToXY((BOARDWIDTH + 2) * 10 + left - i - 1, (BOARDHEIGHT + 2) * 4 + top);
        Sleep(1);
        putchar(205);
    }

    GoToXY(left + 1, (BOARDHEIGHT + 2) * 4 + top);
    putchar(200);

    // Draw left line
    for (int i = 1; i < (BOARDHEIGHT + 2) * 4; i++)
    {
        Sleep(1);
        GoToXY(left + 1, (BOARDHEIGHT + 2) * 4 + top - i);
        putchar(186);
    }
}



// ======Hard mode=================================================================

// Delete one cell of the line
void deleteNode(cell2*& pLine, int x) {

    if (x < 0) return;

    if (pLine == NULL) return;

    cell2* pTemp = pLine;
    cell2* pPrev = NULL;

    // If the cell is the first cell of that line
    if (pLine->pos.x == x) {
        if (pTemp->pNext == NULL) {
            delete pTemp;
            pTemp = NULL;
            pLine = NULL;

            return;
        }
        pLine = pTemp->pNext;
        delete pTemp;

        return;
    }
    else {
        pPrev = pTemp;
        pTemp = pTemp->pNext;

        for (int i = 1; i < getLineLength(pLine); i++) {
            if (pTemp->pos.x == x) {
                pPrev->pNext = pTemp->pNext;
                delete pTemp;
                return;
            }
            pPrev = pTemp;
            pTemp = pTemp->pNext;
        }
    }
}

// Rearrange the positions of all the cells on one line
void resetBoard(cell2**& board, int x1, int y1, int x2, int y2) {

    // If the cells are in the same row
    if (y1 == y2) {

        deleteNode(board[y1], x1);
        deleteNode(board[y1], x2);

        cell2* pTemp = board[y1];

        if (pTemp != NULL) {
            for (int i = 0; i < getLineLength(board[y1]); i++) {
                pTemp->pos.x = i;
                pTemp = pTemp->pNext;
            }
        }
    }
    else {

        deleteNode(board[y1], x1);
        deleteNode(board[y2], x2);

        cell2* pTemp1 = board[y1];
        cell2* pTemp2 = board[y2];

        // Rearrange the positions of all the cells on y1 row
        if (pTemp1 != NULL)
        {
            for (int i = 0; i < getLineLength(board[y1]); i++) {
                pTemp1->pos.x = i;
                pTemp1 = pTemp1->pNext;
            }
        }

        // Rearrange the positions of all the cells on y2 row
        if (pTemp2 != NULL)
        {
            for (int i = 0; i < getLineLength(board[y2]); i++) {
                pTemp2->pos.x = i;
                pTemp2 = pTemp2->pNext;
            }
        }
    }
}

// Return the length of one row
int getLineLength(cell2* pHead) {

    // The row is empty
    if (pHead == NULL)
    {
        return 0;
    }
    else {

        int cnt = 1;

        cell2* pCurr = pHead;
        while (pCurr->pNext != NULL) {
            pCurr = pCurr->pNext;
            cnt++;
        }

        return cnt;
    }
}

// Push information of one cell into board
void push(cell2*& board, cell2* pAdd) {
    if (board == NULL) {
        board = pAdd;
    }
    else {
        cell2* pTemp = board;
        while (pTemp->pNext != NULL)
        {
            pTemp = pTemp->pNext;
        }
        pTemp->pNext = pAdd;
    }
}

// Find one cell in the board with position x, y
cell2* findTheNode(cell2** board, int x, int y) {
    // If the cell is out of board (out of bound)
    if (x < 0 || (x > BOARDWIDTH) || y < 0 || (y > BOARDHEIGHT)) return NULL;

    cell2* pTemp = board[y];
    while (pTemp != NULL) {
        if (pTemp->pos.x == x) {
            return pTemp;
        }
        pTemp = pTemp->pNext;
    }

    return NULL;
}

// Basic Move on console window at game display time - for Hard mode
// KEY_UP, KEY_DOWN, KEY LEFT, KEY RIGHT, ENTER_KEY, ESC KEY
// B, b , W, w, A, a, S, s, D, s
void move2(cell2** board, position& pos, int& status, player& p, position selectedPos[], background bg, int& couple) {
    int temp;

    temp = returnKey(_getch());

    if (temp == ESC_KEY || temp == ENTER_KEY || temp == 98) {
        if (temp == ESC_KEY) { // If player press ESC
            //3: Exit game
            status = 3;
        }
        else if (temp == ENTER_KEY) { // If player press ENTER

            // If player match the same cell
            if (pos.x == selectedPos[0].x && pos.y == selectedPos[0].y) {
                cell2* pTemp = findTheNode(board, pos.x, pos.y);
                playSound(DSELECT);

                // Highlight the cell that player deselect by gray color
                pTemp->drawBox(GRAY * 16);
                Sleep(200);

                pTemp->isSelected = 0;
                couple = 2;
                selectedPos[0] = { -1, -1 };

            }
            else {
                // Store the cell(s) that player choose
                selectedPos[2 - couple].x = pos.x;
                selectedPos[2 - couple].y = pos.y;
                findTheNode(board, pos.x, pos.y)->isSelected = 1; // 
                couple--;

                if (couple == 0) { // If player have match a couple cells
                    cell2* p1;
                    cell2* p2;
                    p1 = findTheNode(board, selectedPos[0].x, selectedPos[0].y);
                    p2 = findTheNode(board, selectedPos[1].x, selectedPos[1].y);

                    if ((p1->val == p2->val) && (p1 != NULL) && (p2 != NULL)) {  // If these cells have a same character
                        // x1, y1, x2, y2
                        playSound(MATCHING);

                        // flag = 0: Wrong pattern
                        // flag = 2: I pattern
                        // flag = 3: L pattern
                        // flag = 4: Z pattern
                        // flag = 5: U patter
                        int flag = allCheck(board, selectedPos[0].x, selectedPos[0].y, selectedPos[1].x, selectedPos[1].y);

                        if (flag) {
                            // Pattern I, L
                            if (flag <= 3)
                            {
                                setColor(BLACK, LIGHT_GREEN);
                                GoToXY(87, 11);
                                cout << "+28";

                                p.point += 28;
                            }
                            else
                            // Pattern Z, U
                            {
                                setColor(BLACK, LIGHT_GREEN);
                                GoToXY(87, 11);
                                cout << "+30";

                                p.point += 30;
                            }

                            setColor(BLACK, WHITE);

                            // Hightlight the matching cells by green color (Green background with different font's color)
                            p1->drawBox(GREEN * 16 + 8);
                            p2->drawBox(GREEN * 16 + 8);

                            // Showing the pattern that player choose and the plus point at the player's info board
                            if (flag == 2)
                            {
                                setColor(GREEN, WHITE);
                                drawLineI(selectedPos[0].x, selectedPos[0].y, selectedPos[1].x, selectedPos[1].y);
                                setColor(BLACK, LIGHT_GREEN);
                                GoToXY(80, 13);
                                cout << "FOUND MATCHING PATTERN I!";
                            }
                            else if (flag == 3)
                            {
                                setColor(GREEN, WHITE);
                                drawLineL(board, selectedPos[0].x, selectedPos[0].y, selectedPos[1].x, selectedPos[1].y);
                                setColor(BLACK, LIGHT_GREEN);
                                GoToXY(80, 13);
                                cout << "FOUND MATCHING PATTERN L!";
                            }
                            else if (flag == 4)
                            {
                                setColor(GREEN, WHITE);
                                drawLineZ(board, selectedPos[0].x, selectedPos[0].y, selectedPos[1].x, selectedPos[1].y);
                                setColor(BLACK, LIGHT_GREEN);
                                GoToXY(80, 13);
                                cout << "FOUND MATCHING PATTERN Z!";
                            }
                            else if (flag == 5)
                            {
                                setColor(GREEN, WHITE);
                                drawLineU(board, selectedPos[0].x, selectedPos[0].y, selectedPos[1].x, selectedPos[1].y);
                                setColor(BLACK, LIGHT_GREEN);
                                GoToXY(80, 13);
                                cout << "FOUND MATCHING PATTERN U!";
                            }


                            Sleep(500);

                            setColor(BLACK, WHITE);

                            // Clear all the unnecessary space on the player's info board
                            GoToXY(80, 13);
                            cout << "                         ";
                            GoToXY(88, 10);
                            cout << p.point << "            ";
                            GoToXY(87, 11);
                            cout << "   ";
                            // 


                            setColor(BLACK, WHITE);

                            // Deselected that 2 cells
                            p1->isSelected = 0;
                            p2->isSelected = 0; 

                            // Delete that 2 cells
                            resetBoard(board, selectedPos[0].x, selectedPos[0].y, selectedPos[1].x, selectedPos[1].y);

                            // Render the board but only print the background
                            renderBoard(board, bg, flag);
                        }
                        else {
                            // Hightlight the matching cells by red color and different font's color because it is wrong pattern
                            p1->drawBox(RED * 16 + 6);
                            p2->drawBox(RED * 16 + 6);
                            playSound(S_ERROR);

                            p.life--;
                            p.point -= 10;

                            // Showing the pattern that player choose is wrong and the subtract point and subtract life at the player's info board
                            setColor(BLACK, LIGHT_RED);
                            GoToXY(80, 13);
                            cout << "WRONG PATTERN!";
                            GoToXY(87, 11);
                            cout << "-10";
                            if (p.life == 2)
                            {
                                GoToXY(92, 6);
                            }
                            else if (p.life == 1)
                            {
                                GoToXY(90, 6);
                            }
                            else
                            {
                                GoToXY(88, 6);
                            }
                            cout << "* ";

                            Sleep(500);

                            // Clear all the unnecessary space on the player's info board
                            GoToXY(87, 11);
                            cout << "   ";
                            if (p.life == 2)
                            {
                                GoToXY(92, 6);
                            }
                            else if (p.life == 1)
                            {
                                GoToXY(90, 6);
                            }
                            else
                            {
                                GoToXY(88, 6);
                            }
                            cout << "  ";
                            setColor(BLACK, WHITE);
                            GoToXY(88, 10);
                            cout << p.point << "            ";
                            GoToXY(80, 13);
                            cout << "               ";
                            p1->isSelected = 0;
                            p2->isSelected = 0;
                        }
                    }
                    else {
                        // Hightlight the matching cells by red color and different font's color because it is wrong pattern
                        p1->drawBox(RED * 16 + 6);
                        p2->drawBox(RED * 16 + 6);

                        playSound(S_ERROR);

                        p.life--;
                        p.point -= 10;

                        // Showing the pattern that player choose is wrong and the subtract point and subtract life at the player's info board
                        setColor(BLACK, LIGHT_RED);
                        GoToXY(80, 13);
                        cout << "WRONG PATTERN!";
                        GoToXY(87, 11);
                        cout << "-10";
                        if (p.life == 2)
                        {
                            GoToXY(92, 6);
                        }
                        else if (p.life == 1)
                        {
                            GoToXY(90, 6);
                        }
                        else
                        {
                            GoToXY(88, 6);
                        }
                        cout << "* ";

                        Sleep(500);

                        // Clear all the unnecessary space on the player's info board
                        GoToXY(87, 11);
                        cout << "   ";
                        if (p.life == 2)
                        {
                            GoToXY(92, 6);
                        }
                        else if (p.life == 1)
                        {
                            GoToXY(90, 6);
                        }
                        else
                        {
                            GoToXY(88, 6);
                        }
                        cout << "  ";
                        setColor(BLACK, WHITE);
                        GoToXY(88, 10);
                        cout << p.point << "            ";
                        GoToXY(80, 13);
                        cout << "               ";

                        p1->isSelected = 0;
                        p2->isSelected = 0;
                    }

                    // Return back to the status of choose none cell
                    p1 = NULL;
                    p2 = NULL;
                    couple = 2;
                    selectedPos[0] = { -1, -1 };
                    selectedPos[1] = { -1, -1 };

                    // Find a new valid cell to show the current cell player at
                    for (int i = pos.y; i < BOARDHEIGHT; i++) {
                        for (int j = pos.x; j < getLineLength(board[i]); j++) {
                            if (findTheNode(board, j, i) != NULL) {
                                pos.x = j;
                                pos.y = i;
                                return;
                            }
                        }
                    }

                    for (int i = 0; i < BOARDHEIGHT; i++) { 
                        for (int j = 0; j < getLineLength(board[i]); j++) {
                            if (findTheNode(board, j, i) != NULL) {
                                pos.x = j;
                                pos.y = i;
                                return;
                            }
                        }
                    }
                }
                else
                {
                    // If player have only choose a cell
                    playSound(DSELECT);
                }
            }
        }
        else if (temp == 98) {

            // If player's point is not negative then give player suggestion move
            if (p.point >= 0)
            {
                playSound(NOTIFICATION);

                suggestMove(board);

                p.point -= 30;

                setColor(BLACK, LIGHT_RED);
                GoToXY(87, 11);
                cout << "-30";
            }
            else
            {
                playSound(S_ERROR);

                setColor(BLACK, LIGHT_RED);
                GoToXY(80, 13);
                cout << "YOUR POINT IS NEGATIVE!";
            }

            Sleep(400);

            // Clear all the unnecessary space on the player's info board
            setColor(BLACK, WHITE);
            GoToXY(88, 10);
            cout << p.point << "            ";
            GoToXY(87, 11);
            cout << "   ";
            GoToXY(80, 13);
            cout << "                       ";
        }
    }
    else // If player enter W/ w/ up arrow, S/ s/ down arrow, D/ d/ left arrow, A/ a/ right arrow or any other keys
    {

        // Check if this cell is selected or not
        if ((pos.y != selectedPos[0].y || pos.x != selectedPos[0].x) && (pos.y != selectedPos[1].y || pos.x != selectedPos[1].x)) // ktra xem o nay co dang duoc chon hay khong
            findTheNode(board, pos.x, pos.y)->isSelected = 0;

        switch (temp)
        {
            // For each direction, find a new valid cell from the previous cell's position to put player's cursor on
            // Find from column ... to ..., row ... to .... If there is any cell valid turn the player's cursor to it

            //If player enter W / w / up arrow
            case KEY_UP:

                playSound(MOVE);

                for (int i = pos.x; i < BOARDWIDTH; i++) {
                    for (int j = pos.y - 1; j >= 0; j--) {
                        if (findTheNode(board, i, j) != NULL) {
                            pos.x = i;
                            pos.y = j;
                            return;
                        }
                    }
                }

                for (int i = pos.x - 1; i >= 0; i--) {
                    for (int j = pos.y - 1; j >= 0; j--) {
                        if (findTheNode(board, i, j) != NULL) {
                            pos.x = i;
                            pos.y = j;
                            return;
                        }
                    }
                }

                for (int i = pos.x; i < BOARDWIDTH; i++) {
                    for (int j = BOARDHEIGHT - 1; j > pos.y; j--) {
                        if (findTheNode(board, i, j) != NULL) {
                            pos.x = i;
                            pos.y = j;
                            return;
                        }
                    }
                }

                for (int i = pos.x; i >= 0; i--) {
                    for (int j = BOARDHEIGHT - 1; j > pos.y; j--) {
                        if (findTheNode(board, i, j) != NULL) {
                            pos.x = i;
                            pos.y = j;
                            return;
                        }
                    }
                }

                break;

            //If player enter S / s / down arrow
            case KEY_DOWN:

                playSound(MOVE);

                for (int i = pos.x; i < BOARDWIDTH; i++) {
                    for (int j = pos.y + 1; j < BOARDHEIGHT; j++) {
                        if (findTheNode(board, i, j) != NULL) {
                            pos.x = i;
                            pos.y = j;
                            return;
                        }
                    }
                }

                for (int i = pos.x - 1; i >= 0; i--) {
                    for (int j = pos.y + 1; j < BOARDHEIGHT; j++) {
                        if (findTheNode(board, i, j) != NULL) {
                            pos.x = i;
                            pos.y = j;
                            return;
                        }
                    }
                }

                for (int i = pos.x; i < BOARDWIDTH; i++) {
                    for (int j = 0; j < pos.y; j++) {
                        if (findTheNode(board, i, j) != NULL) {
                            pos.x = i;
                            pos.y = j;
                            return;
                        }
                    }
                }

                for (int i = pos.x - 1; i >= 0; i--) {
                    for (int j = 0; j < pos.y; j++) {
                        if (findTheNode(board, i, j) != NULL) {
                            pos.x = i;
                            pos.y = j;
                            return;
                        }
                    }
                }

                break;

            //If player enter A / a / left arrow
            case KEY_LEFT:

                playSound(MOVE);

                for (int i = pos.y; i >= 0; i--) {
                    for (int j = pos.x - 1; j >= 0; j--) {
                        if (findTheNode(board, j, i) != NULL) {
                            pos.x = j;
                            pos.y = i;
                            return;
                        }
                    }
                }

                for (int i = pos.y + 1; i < BOARDHEIGHT; i++) {
                    for (int j = pos.x - 1; j >= 0; j--) {
                        if (findTheNode(board, j, i) != NULL) {
                            pos.x = j;
                            pos.y = i;
                            return;
                        }
                    }
                }

                for (int i = pos.y; i >= 0; i--) {
                    for (int j = BOARDWIDTH - 1; j > pos.x; j--) {
                        if (findTheNode(board, j, i) != NULL) {
                            pos.x = j;
                            pos.y = i;
                            return;
                        }
                    }
                }

                for (int i = pos.y + 1; i < BOARDHEIGHT; i++) {
                    for (int j = BOARDWIDTH - 1; j > pos.x; j--) {
                        if (findTheNode(board, j, i) != NULL) {
                            pos.x = j;
                            pos.y = i;
                            return;
                        }
                    }
                }
                break;

            //If player enter D / d / right arrow
            case KEY_RIGHT:

                playSound(MOVE);

                for (int i = pos.y; i >= 0; i--) {
                    for (int j = pos.x + 1; j < BOARDWIDTH; j++) {
                        if (findTheNode(board, j, i) != NULL) {
                            pos.x = j;
                            pos.y = i;
                            return;
                        }
                    }
                }

                for (int i = pos.y + 1; i < BOARDHEIGHT; i++) {
                    for (int j = pos.x + 1; j < BOARDWIDTH; j++) {
                        if (findTheNode(board, j, i) != NULL) {
                            pos.x = j;
                            pos.y = i;
                            return;
                        }
                    }
                }

                for (int i = pos.y; i >= 0; i--) {
                    for (int j = 0; j < pos.x; j++) {
                        if (findTheNode(board, j, i) != NULL) {
                            pos.x = j;
                            pos.y = i;
                            return;
                        }
                    }
                }

                for (int i = pos.y + 1; i < BOARDHEIGHT; i++) {
                    for (int j = 0; j < pos.x; j++) {
                        if (findTheNode(board, j, i) != NULL) {
                            pos.x = j;
                            pos.y = i;
                            return;
                        }
                    }
                }

            // If any other key is pressed
            default:
                break;
            }
    }
}

// Suggest two cells that can be matched in legal pattern (I, L, Z, U) - for Hard Mode
void suggestMove(cell2** board) {

    // Check any pair cells on the board that can be matched
    for (int i = 0; i < BOARDHEIGHT; i++) {
        for (int j = 0; j < getLineLength(board[i]); j++) {

            cell2* tmp1 = findTheNode(board, j, i);

            // If that cell is not a blank space
            if (tmp1 != NULL) {
                for (int x = 0; x < BOARDHEIGHT; x++) {
                    for (int y = 0; y < getLineLength(board[x]); y++) {
                        // If two cells is not the same cell
                        if (x != i || y != j) {

                            cell2* tmp2 = findTheNode(board, y, x);

                            // If two cells have a legal pattern and the 2nd cell is not a blank space
                            if (allCheck(board, j, i, y, x) && (tmp2 != NULL)) {


                                // Highlight that pair of cells with light yellow
                                tmp1->isSelected = 1;
                                tmp2->isSelected = 1;
                                tmp1->drawBox(LIGHT_YELLOW * 16);
                                tmp2->drawBox(LIGHT_YELLOW * 16);
                                tmp1->isSelected = 0;
                                tmp2->isSelected = 0;

                                return;
                            }
                        }
                    }
                }
            }
        }
    }
}

// Creating the board to contain all essential data to help the game works - for Hard Mode
void initBoard2(cell2**& board) {

    // Attach the position on each cell
    for (int i = 0; i < BOARDHEIGHT; i++) {

        board[i] = NULL;
        for (int j = 0; j < BOARDWIDTH; j++) {

            cell2* pHead = new cell2;
            pHead->pos.y = i;
            pHead->pos.x = j;
            pHead->pNext = NULL;
            push(board[i], pHead);
        }
    }

    int flagNum = (BOARDHEIGHT * BOARDWIDTH) / 2;

    // Attach a character to each cell
    while (flagNum) {

        int y, time = 2;
        // Random a character from A to Z
        int num = rand() % (90 - 65) + 65;

        // Attach that character to 2 random cells
        while (time) {

            y = rand() % BOARDHEIGHT; // 8
            int x = rand() % BOARDWIDTH; // 5
            cell2* pTemp = findTheNode(board, x, y);
            if (pTemp->val == ' ') {

                pTemp->val = char(num);
                time--;
            }
        }

        flagNum--;
    }
}

// Print out the box that cover the cell board - for Hard Mode
void drawRectangle(cell2** board, int left, int top) {
    if (board == NULL) return;
    HANDLE Controller = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(Controller, BRIGHT_WHITE);
    // Draw top line
    GoToXY(left + 1, top);
    putchar(201);
    for (int i = 1; i < (BOARDWIDTH + 2) * 10 - 2; i++)
    {
        Sleep(1);
        putchar(205);
    }
    putchar(187);

    left--;
    // Draw right line
    for (int i = 1; i < (BOARDHEIGHT + 2) * 4; i++)
    {
        Sleep(1);
        GoToXY((BOARDWIDTH + 2) * 10 + left, i + top);
        putchar(186);
    }
    GoToXY((BOARDWIDTH + 2) * 10 + left, (BOARDHEIGHT + 2) * 4 + top);
    putchar(188);

    // Draw bottom line
    for (int i = 1; i < (BOARDWIDTH + 2) * 10 - 2; i++)
    {
        GoToXY((BOARDWIDTH + 2) * 10 + left - i, (BOARDHEIGHT + 2) * 4 + top);
        Sleep(1);
        putchar(205);
    }

    left++;

    GoToXY(left + 1, (BOARDHEIGHT + 2) * 4 + top);
    putchar(200);

    // Draw left line
    for (int i = 1; i < (BOARDHEIGHT + 2) * 4; i++)
    {
        Sleep(1);
        GoToXY(left + 1, (BOARDHEIGHT + 2) * 4 + top - i);
        putchar(186);
    }

}

// Delete all the cells of the board after game ended
void deleteBoard(cell2** board, background bg) {
    for (int i = 0; i < BOARDHEIGHT; i++) {
        cell2* pTemp;

        while (board[i] != NULL)
        {
            pTemp = board[i];

            board[i] = board[i]->pNext;

            delete pTemp;
        }
    }
    delete[]board;
}


// flag = 0: There is no new matching cells
// flag > 0: There is A NEW matching cells
// Print out the backgound and all the cells of the board on the console window - for Hard Mode
void renderBoard(cell2** board, background bg, int flag) {
    int* line_length = new int[BOARDHEIGHT];
    for (int i = 0; i < BOARDHEIGHT; i++) {
        line_length[i] = getLineLength(board[i]);
    }

    // If there is a new matching cells
    if (flag > 0)
    {
        // Clear all the space beyond the board
        setColor(BLACK, WHITE);

        for (int i = 0; i < 61; i++) {

            GoToXY(5 + i, 2);
            cout << ' ';
            GoToXY(5 + i, 3);
            cout << ' ';
            GoToXY(5 + i, 37);
            cout << ' ';
            GoToXY(5 + i, 38);
            cout << ' ';
        }

        for (int i = 0; i < 35; i++) {

            GoToXY(5, 3 + i);
            cout << ' ';
            GoToXY(6, 3 + i);
            cout << ' ';
            GoToXY(7, 3 + i);
            cout << ' ';
            GoToXY(8, 3 + i);
            cout << ' ';
            GoToXY(9, 3 + i);
            cout << ' ';
            GoToXY(61, 3 + i);
            cout << ' ';
            GoToXY(62, 3 + i);
            cout << ' ';
            GoToXY(63, 3 + i);
            cout << ' ';
            GoToXY(64, 3 + i);
            cout << ' ';
            GoToXY(65, 3 + i);
            cout << ' ';
        }

        // Print out the all background to delete the matching line


        for (int i = 0; i < BOARDHEIGHT; i++) {
            for (int j = line_length[i]; j < BOARDWIDTH; j++) {
                bg.displayBackground(j, i);
            }
        }

        return;
    }

    // If there is no new matching cells, drawbox of all cells 
    for (int i = 0; i < BOARDHEIGHT; i++) {
        for (int j = 0; j < line_length[i]; j++) {
            if (findTheNode(board, j, i) != NULL)
            {
                findTheNode(board, j, i)->drawBox(112);

            }
        }
    }
}








