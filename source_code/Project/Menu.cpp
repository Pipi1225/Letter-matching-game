#include <conio.h>
#include <math.h>
#include <iomanip>
#include <cwchar>
#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <cmath>
#include <ctime>

#include "Check.h"
#include "Core.h"
#include "Visual.h"
#include "Menu.h"
#include "Struct.h"

#pragma comment(lib, "Winmm.lib")

using namespace std;


// https://stackoverflow.com/questions/71731641/how-to-make-console-automatically-zoom-to-full-screen-when-running-in-c
// Answer 1
// Make console window have the resolution of the game
void makeFullScreen(){
    HWND Hwnd = GetForegroundWindow();

    // Resolution of the game
    int x = 1536;
    int y = 864;

    // Make the console get to the center of the screen
    int pos_x = abs(GetSystemMetrics(SM_CXSCREEN) - x) / 2;
    int pos_y = abs(GetSystemMetrics(SM_CYSCREEN) - y) / 2;

    // Avoid resize the wrong console
    UpdateWindow(GetParent(Hwnd));

    // Setting the console to the appropriate resolution
    LONG winstyle = GetWindowLong(Hwnd, GWL_STYLE);
    MoveWindow(Hwnd, pos_x, pos_y, x, y, TRUE);

    //SetWindowLong(Hwnd, GWL_STYLE, (winstyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);
}


// https://codelearn.io/codecamp.blog/sharing/detail/windowsh-va-ham-dinh-dang-console-p1
// Disable user resizing console window
void disableResizeWindow(){
    HWND hWnd = GetConsoleWindow();
    SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_SIZEBOX);
}


// https://codelearn.io/codecamp.blog/sharing/detail/windowsh-va-ham-dinh-dang-console-p1
// Disable user using buttons: Minimize, Maximize
void disableCtrButton()
{
    HWND hWnd = GetConsoleWindow();
    HMENU hMenu = GetSystemMenu(hWnd, false);

    DeleteMenu(hMenu, SC_MINIMIZE, MF_BYCOMMAND);
    DeleteMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);

    SetWindowLong(hWnd, GWL_STYLE,
    GetWindowLong(hWnd, GWL_STYLE) & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME));

}



// https://codelearn.io/codecamp.blog/sharing/detail/windowsh-va-ham-dinh-dang-console-p1
// Hide the scrollbar
void hideScrollbar(bool status)
{
    HWND hWnd = GetConsoleWindow();
    ShowScrollBar(hWnd, SB_BOTH, status);
}


// https://stackoverflow.com/questions/18028808/remove-blinking-underscore-on-console-cmd-prompt
// Hide the console cursor
void hideConsoleCursor(bool status)
{
    HANDLE Controller = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    cursorInfo.dwSize = 1;

    cursorInfo.bVisible = status; // set the cursor visibility
    SetConsoleCursorInfo(Controller, &cursorInfo);
}

// Setup the console window when run code
void setupConsole() {
    makeFullScreen();
    disableResizeWindow();
    disableCtrButton();
    hideScrollbar(false);
    hideConsoleCursor(false);

    // Make the console use the code page 437 (Extended ASCII Table)
    SetConsoleOutputCP(437);
}

// Starting menu when run code
void startingMenu() {

    srand(time(NULL));

    // Declared a list to store top 10 players
    lst list;
    list.readRanked();

    setupConsole();   
    Sleep(300);

    // chose = 0: New game
    // chose = 1: Showing the Leaderboard of ten players have the best performance
    // chose = 2: Showing information about this game and developers
    // chose = 3: Exit game (Exit program)
    int chose = 0;
    setColor(BLACK, GRAY);

    while (true) {
        // Print the logo of the game
        GoToXY(0, 0);
        printLogo();

        setColor(BLACK, GRAY);
        if (chose == 0) {
            // Highlight the NEW GAME button
            setColor(BLACK, BRIGHT_WHITE);
            GoToXY(73, 23);
            cout << "> NEW GAME <";
            setColor(BLACK, GRAY);
            GoToXY(71, 26);
            cout << "  LEADER BOARD  ";
            GoToXY(75, 29);
            cout << "  INFO  ";
            GoToXY(75, 32);
            cout << "  EXIT  ";
        }
        else if (chose == 1) {
            // Highlight the LEADER BOARD button
            GoToXY(73, 23);
            cout << "  NEW GAME  ";
            setColor(BLACK, BRIGHT_WHITE);
            GoToXY(71, 26);
            cout << "> LEADER BOARD <";
            setColor(BLACK, GRAY);
            GoToXY(75, 29);
            cout << "  INFO  ";
            GoToXY(75, 32);
            cout << "  EXIT  ";
        }
        else if (chose == 2) {
            // Highlight the INFO button
            GoToXY(73, 23);
            cout << "  NEW GAME  ";
            GoToXY(71, 26);
            cout << "  LEADER BOARD  ";
            setColor(BLACK, BRIGHT_WHITE);
            GoToXY(75, 29);
            cout << "> INFO <";
            setColor(BLACK, GRAY);
            GoToXY(75, 32);
            cout << "  EXIT  ";
        }
        else {
            // Highlight the EXIT button
            GoToXY(73, 23);
            cout << "  NEW GAME  ";
            GoToXY(71, 26);
            cout << "  LEADER BOARD  ";
            GoToXY(75, 29);
            cout << "  INFO  ";
            setColor(BLACK, BRIGHT_WHITE);
            GoToXY(75, 32);
            cout << "> EXIT <";
            setColor(BLACK, GRAY);
        }

        GoToXY(73, 38);
        setColor(BLACK, GRAY);
        cout << "DEVELOPED BY";
        setColor(BLACK, LIGHT_GREEN);
        GoToXY(63, 40);
        cout << "DUONG GIA HUY - NGUYEN HIEU THUAN";
        setColor(BLACK, GRAY);

        // Case for each key player's press (switch button)
        switch (returnKey(_getch())) {
            // If player press W, w or up arrow
            case KEY_UP:
            {
                playSound(MOVE_MENU);

                chose--;
                // Switch to the EXIT button if the player is already at NEW GAME button
                if (chose < 0){
                    chose = 3;
                    break;
                }
                break;
            }

            // If player press S, s or down arrow
            case KEY_DOWN:
            {
                playSound(MOVE_MENU);
                chose++;
                // Switch to the NEW GAME button if the player is already at EXIT button
                if (chose > 3){
                    chose = 0;
                    break;
                }
                break;
            }

            // If player press Enter
            case ENTER_KEY:
            {
                playSound(ENTER_MENU);

                if (chose == 0){
                    // New game
                    NewGameMenu(list);
                    printLogo();
                    break;
                }
                else if (chose == 1) {
                    // Leaderboard
                    LeaderBoardMenu(list);
                    printLogo();
                    break;
                }
                else if (chose == 2) {
                    // Information
                    InformationMenu();
                    printLogo();
                    break;
                }
                else {
                    // Exit the program
                    system("CLS");

                    // Save the top 10 player's record
                    list.writeRanked();

                    return;
                }
            }
        }
        setColor(BLACK, GRAY);
    }
}

// Print out the leader board on the console window (Top 10 player's record)
void LeaderBoardMenu(lst list) {
    system("CLS");

    unsigned char logo2[] = R"(

                                                                                      _________________________________  
                                                                                      7  _  77     77  _  77  _  77    \ 
                                                                                      |   __||  7  ||  _  ||    _||  7  |
                                                                                      |  _  ||  |  ||  7  ||  _ \ |  |  |
                                                                                      |  7  ||  !  ||  |  ||  7  ||  !  |
                                                                                      !_____!!_____!!__!__!!__!__!!_____! 
                                                                             
                                                                                                                        
    )";

    unsigned char logo1[] = R"(

                                          ____   ___________________  ______________ 
                                          7  7   7     77  _  77    \ 7     77  _  7 
                                          |  |   |  ___!|  _  ||  7  ||  ___!|    _| 
                                          |  !___|  __|_|  7  ||  |  ||  __|_|  _ \  
                                          |     7|     7|  |  ||  !  ||     7|  7  | 
                                          !_____!!_____!!__!__!!_____!!_____!!__!__! 
                                                                                      
    )";

    setColor(BLACK, LIGHT_YELLOW);
    cout << logo2;

    GoToXY(0, 0);
    setColor(BLACK, YELLOW);
    cout << logo1;

    setColor(BLACK, GRAY);

    // X = 30: Left line
    // X = 133: Right line
    // Y = 10 : Top line
    // Y = 35 : Bottom line

    // Drawing box
    // Drawing the top line and the bottom line
    for (int i = 1; i <= 103; i++)
    {
         GoToXY(30 + i, 10);
         putchar(196);

         GoToXY(30 + i, 12);
         putchar(196);

         GoToXY(30 + i, 35);
         putchar(196);
    }
    
    // Drawing the vertical line
    for (int i = 1; i < 25; i++)
    {
        // The left line
        GoToXY(30, 10 + i);
        putchar(179);

        // The right line
        GoToXY(133, 10 + i);
        putchar(179);

        GoToXY(42, 10 + i);
        putchar(179);

        GoToXY(70, 10 + i);
        putchar(179);

        GoToXY(87, 10 + i);
        putchar(179);

        GoToXY(106, 10 + i);
        putchar(179);
    }


    // Draw the chain that "connect" Leaderboard and the border console
    for (int i = 0; i < 10; i++)
    {
        GoToXY(30, i);
        cout << '8';

        GoToXY(133, i);
        cout << '8';
    }

    // Draw the joints of vertical and horizontal lines
    GoToXY(133, 35);
    putchar(217);

    GoToXY(30, 35);
    putchar(192);

    GoToXY(42, 10);
    putchar(194);

    GoToXY(42, 35);
    putchar(193);

    GoToXY(70, 10);
    putchar(194);

    GoToXY(70, 35);
    putchar(193);

    GoToXY(87, 10);
    putchar(194);

    GoToXY(87, 35);
    putchar(193);

    GoToXY(106, 10);
    putchar(194);

    GoToXY(106, 35);
    putchar(193);

    GoToXY(42, 12);
    putchar(197);

    GoToXY(70, 12);
    putchar(197);

    GoToXY(87, 12);
    putchar(197);

    GoToXY(106, 12);
    putchar(197);

    GoToXY(30, 12);
    putchar(195);

    GoToXY(133, 12);
    putchar(180);

    setColor(BLACK, BRIGHT_WHITE);
    GoToXY(30, 10);
    cout << '0';
    GoToXY(133, 10);
    cout << '0';

    // Print out all the title
    // Y = 11: Title line
    setColor(BLACK, YELLOW);
    GoToXY(35, 11);
    cout << "No.";

    setColor(BLACK, LIGHT_YELLOW);
    GoToXY(47, 11);
    cout << " NAME";
    GoToXY(77, 11);
    cout << "MODE";
    GoToXY(94, 11);
    cout << "STAGES";
    GoToXY(116, 11);
    cout << "POINTS";

    setColor(BLACK, WHITE);

    // Print out the data of the no. i player
    for (int i = 0; i < 10; i++)
    {
        if (i == 0)
        {
            setColor(BLACK, LIGHT_RED);
            GoToXY(36, 14 + i * 2);

            cout << (i + 1);
        }
        else
        {
            if (i == 10)
            {
                GoToXY(35, 15 + i * 2);
            }
            else
            {
                GoToXY(36, 15 + i * 2);
            }

            setColor(BLACK, WHITE);

            cout << (i + 1);
        }

        // Print out the name of the no. i player
        if (i == 0)
        {
            GoToXY(46, 14 + i * 2);
        }
        else
        {
            GoToXY(46, 15 + i * 2);
        }

        cout << list.Player[i].name;

        // Print out the mode of the no. i player
        if (i == 0)
        {
            GoToXY(76, 14 + i * 2);
        }
        else
        {
            GoToXY(76, 15 + i * 2);
        }

        if (list.Player[i].mode == 1)
        {
            cout << "MEDIUM";
        }
        else
        {
            cout << " HARD";
        }

        if (i == 0)
        {
            GoToXY(96, 14 + i * 2);
        }
        else
        {
            GoToXY(96, 15 + i * 2);

            setColor(BLACK, BRIGHT_WHITE);
        }

        cout << setw(2) << list.Player[i].stages;

        // Print out the points of the no. i player
        if (i == 0)
        {
            GoToXY(117, 14 + i * 2);
        }
        else
        {
            GoToXY(117, 15 + i * 2);

            setColor(BLACK, WHITE);
        }

        cout << list.Player[i].point;
    }

    setColor(BLACK, BRIGHT_WHITE);

    GoToXY(76, 39);
    cout << "> BACK <";

    while (true)
    {   
        // If player press Enter -> Go back to Main Menu
        if (_getch() == ENTER_KEY)
        {
            playSound(ENTER_MENU);

            setColor(BLACK, GRAY);

            break;
        }
    }

    system("CLS");
}

// Print out the Information menu on the console window
void InformationMenu() {
    
    system("CLS");

    setColor(BLACK, GRAY);

    // X = 30: Left line
    // X = 133: Right line
    // 
    // Y = 2 : Top line
    // Y = 35 : Bottom line

    for (int i = 1; i <= 102; i++)
    {
        // The Top line
        GoToXY(30 + i, 2);
        putchar(196);

        // The horizontal line seperate the Info and the Rule of the game
        GoToXY(30 + i, 10);
        putchar(196);

        // The Bottom line
        GoToXY(30 + i, 36);
        putchar(196);
    }

    for (int i = 1; i <= 35; i++)
    {
        // The left line
        GoToXY(30, 1 + i);
        putchar(179);

        // The right line
        GoToXY(133, 1 + i);
        putchar(179);
    }

    // Draw the joints of vertical and horizontal lines
    GoToXY(30, 2);
    putchar(218);

    GoToXY(30, 10);
    putchar(195);

    GoToXY(30, 36);
    putchar(192);

    GoToXY(133, 2);
    putchar(191);

    GoToXY(133, 10);
    putchar(180);

    GoToXY(133, 36);
    putchar(217);


    setColor(BLACK, YELLOW);

    // Print out the general info of the game
    GoToXY(35, 4);
    cout << "The Matching Game ";

    setColor(BLACK, WHITE);

    cout << "(commonly known as Pikachu Puzzle Game) includes a board of multiple cells,";
    GoToXY(35, 5);

    cout << "each of which presents a figure, but here it presents a character.";

    GoToXY(35, 7);
    cout << "The player finds, selects and matches a pair of ";
    setColor(BLACK, LIGHT_YELLOW);
    cout << "cells";
    setColor(BLACK, WHITE);
    cout << " that contain the same character and";

    GoToXY(35, 8);
    cout << "connect each other in some ";
    setColor(BLACK, LIGHT_AQUA);
    cout << "particular pattern";
    setColor(BLACK, WHITE);
    cout << ". And there is two modes: ";
    setColor(BLACK, AQUA);
    cout << "MEDIUM";
    setColor(BLACK, WHITE);
    cout << " and ";
    setColor(BLACK, LIGHT_BLUE);
    cout << "HARD.";

    // Print out rule of how to count points (wrong pattern, I, L, Z, U for medium/hard mode)
    setColor(BLACK, WHITE);
    GoToXY(35, 12);
    cout << "A ";
    setColor(BLACK, LIGHT_AQUA);
    cout << "legal match";
    setColor(BLACK, WHITE);
    cout << " will make the two ";
    setColor(BLACK, LIGHT_YELLOW);
    cout << "cells";
    setColor(BLACK, WHITE);
    cout << " disappear:";

    GoToXY(35, 23);
    cout << "A ";
    setColor(BLACK, LIGHT_PURPLE);
    cout << "illegal match";
    setColor(BLACK, WHITE);
    cout << " will make you lose points and a life,";

    GoToXY(35, 24);
    cout << "in the game you only have ";
    setColor(BLACK, YELLOW);
    cout << "three lifes:";

    setColor(BLACK, BRIGHT_WHITE);
    GoToXY(35, 31);
    cout << "You win the game if you have cleared all the ";
    setColor(BLACK, LIGHT_YELLOW);
    cout << "cells";
    setColor(BLACK, BRIGHT_WHITE);
    GoToXY(35, 32);
    cout << "or if there are no possible ways to match.";
    GoToXY(35, 34);
    cout << "Otherwise, you lose the game if you have ";
    setColor(BLACK, YELLOW);
    cout << "no life left.";

    setColor(BLACK, BRIGHT_WHITE);
    GoToXY(99, 13);
    cout << "Select/Deselect:";
    GoToXY(99, 15);
    cout << "Up:";
    GoToXY(99, 17);
    cout << "Down:";
    GoToXY(99, 19);
    cout << "Left:";
    GoToXY(99, 21);
    cout << "Right:";
    GoToXY(99, 23);
    cout << "Move suggestion:";

    GoToXY(35, 14);
    cout << "I pattern matching:";
    GoToXY(35, 16);
    cout << "L pattern matching:";
    GoToXY(35, 18);
    cout << "Z pattern matching:";
    GoToXY(35, 20);
    cout << "U pattern matching:";
    GoToXY(35, 26);
    cout << "Wrong pattern matching:";
    GoToXY(35, 28);
    cout << "Ask for a move suggestion:";

    setColor(BLACK, WHITE);
    GoToXY(116, 13);
    cout << "Enter";
    GoToXY(106, 15);
    cout << "W / up arrow";
    GoToXY(106, 17);
    cout << "S / down arrow";
    GoToXY(106, 19);
    cout << "A / left arrow";
    GoToXY(106, 21);
    cout << "D / right arrow";
    GoToXY(116, 23);
    cout << "B";

    // Point for medium mode
    setColor(BLACK, AQUA);
    GoToXY(62, 14);
    cout << "+20 points";
    GoToXY(62, 16);
    cout << "+20 points";
    GoToXY(62, 18);
    cout << "+25 points";
    GoToXY(62, 20);
    cout << "+25 points";
    setColor(BLACK, LIGHT_BLUE);
    GoToXY(78, 14);

    // Point for hard mode
    cout << "+28 points";
    GoToXY(78, 16);
    cout << "+28 points";
    GoToXY(78, 18);
    cout << "+30 points";
    GoToXY(78, 20);
    cout << "+30 points";

    setColor(BLACK, LIGHT_RED);
    GoToXY(62, 26);
    cout << "-10 points";
    GoToXY(62, 28);
    cout << "-30 points";

    setColor(BLACK, GRAY);
    GoToXY(98, 30);
    cout << "Developers:";

    // Print out Credit
    setColor(BLACK, LIGHT_GREEN);
    GoToXY(98, 32);
    cout << "Duong Gia Huy     - 23127052";
    GoToXY(98, 34);
    cout << "Nguyen Hieu Thuan - 23127125";

    setColor(BLACK, BRIGHT_WHITE);

    GoToXY(76, 39);
    cout << "> BACK <";

    while (true)
    {
        // If player press Enter -> Go back to Main Menu
        if (_getch() == ENTER_KEY)
        {
            playSound(ENTER_MENU);

            setColor(BLACK, GRAY);

            break;
        }
    }

    system("CLS");
}

// Print out the New Game menu on the console window
void NewGameMenu(lst& list) {
    system("CLS");

    setColor(BLACK, BRIGHT_WHITE);
    // chose = 0: Medium mode
    // chose = 1: Hard mode (Linked list, Advanced Feature)
    // chose = 2: Back
    int chose = 0;
    
    while (true) {
        // Highlight the MEDIUM button
        if (chose == 0) {

            GoToXY(74, 17);
            setColor(BLACK, BRIGHT_WHITE);
            cout << "> MEDIUM <";
            setColor(BLACK, GRAY);
            GoToXY(75, 20);
            cout << "  HARD  ";
            GoToXY(75, 23);
            cout << "  BACK  ";
        }

        // Highlight the HARD button
        else if (chose == 1) {

            GoToXY(74, 17);
            setColor(BLACK, GRAY);
            cout << "  MEDIUM  ";
            setColor(BLACK, BRIGHT_WHITE);
            GoToXY(75, 20);
            cout << "> HARD <";
            setColor(BLACK, GRAY);
            GoToXY(75, 23);
            cout << "  BACK  ";
        }

        // Highlight the BACK button
        else if (chose == 2) {

            GoToXY(74, 17);
            setColor(BLACK, GRAY);
            cout << "  MEDIUM  ";
            GoToXY(75, 20);
            cout << "  HARD  ";
            setColor(BLACK, BRIGHT_WHITE);
            GoToXY(75, 23);
            cout << "> BACK <";
        }

        // Case for each key player's press (switch button)
        switch (returnKey(_getch())) {

            // If player press W, w or up arrow
            case KEY_UP:
            {
                playSound(MOVE_MENU);

                chose--;

                // Switch to the MEDIUM button if the player is already at BACK button
                if (chose < 0) {
                    chose = 2;
                    break;
                }
                break;
            }

            // If player press S, s or down arrow
            case KEY_DOWN:
            {
                playSound(MOVE_MENU);

                chose++;

                // Switch to the BACK button if the player is already at MEDIUM button
                if (chose > 2) {
                    chose = 0;
                    break;
                }
                break;
            }

            // If player press Enter
            case ENTER_KEY:
            {
                playSound(ENTER_MENU);

                if (chose == 0) {

                    player p;
                    p.mode = 1;
                    getPlayerPlayingInfo(p);

                    mediumMode(p, list);

                    break;
                }
                else if (chose == 1) {

                    player p;
                    p.mode = 2;

                    getPlayerPlayingInfo(p);

                    hardMode(p, list);

                    break;
                }
                else if (chose == 2) {

                    // Return back to Main Menu
                    system("CLS");
                    return;
                }
            }
        }
    }
}

// Display Medium mode on the console window
void mediumMode(player& p, lst& list) {
    system("CLS");

    cell** board = new cell * [BOARDHEIGHT];
    background bg;

    bg.getBackground();
    
    initBoard(board);
    drawRectangle(board, 0, 0);
    setupPlayInfo(p);

    setColor(BLACK, WHITE);

    position selectedPos[] = { {-1, -1}, {-1, -1} };
    int couple = 2;
    position curPosition{ 0, 0 };

    //0. Are playing
    //1. End game
    //2. End game because out of moves
    //3. Player choose exit game
    int status = 0; 

    renderBoard(board, bg, 0);

    // In case the board have no move at the beginning
    // If there is any valid pair
    if (!(checkValidPair(board)))
    {
        // If there is any cell on the board
        if (checkCellExist(board)) {

            status = 2;
        }
        else {

            status = 1;
        }
    }

    while (!status && p.life) {
        board[curPosition.y][curPosition.x].isSelected = 1;

        // Print out all the cells
        renderBoard(board, bg, 0);

        move(board, curPosition, status, p, selectedPos, bg, couple);

        // If there is any valid pair
        if (!(checkValidPair(board)))
        {
            // If there is any cell on the board
            if (checkCellExist(board)) {

                status = 2;
            }
            else {

                status = 1;
            }
        }
    }

    renderBoard(board, bg, 0);
    deleteBoard(board);
    Sleep(1500);

    system("CLS");

    aftermathAction(p, list, status, posInLeaderboard(p, list));

    system("CLS");
}

// Display Hard mode on the console window
void hardMode(player& p, lst& list) {
    system("CLS");

    background bg;
    bg.getBackground();

    cell2** board = new cell2 * [BOARDHEIGHT];
    initBoard2(board);
    drawRectangle(board, 0, 0);
    setupPlayInfo(p);
    setColor(BLACK, WHITE);

    position selectedPos[] = { {-1, -1}, {-1, -1} };
    int couple = 2;
    position curPosition{ 0, 0 };

    //0. Are playing
    //1. End game
    //2. End game because there is no move
    //3. Player choose exit game
    int status = 0;

    renderBoard(board, bg, 0);

    // In case the board have no move at the beginning
    // If there is any valid pair
    if (!(checkValidPair(board)))
    {
        // If there is any cell on the board
        if (checkCellExist(board)) {

            status = 2;
        }
        else {

            status = 1;
        }
    }

    while (!status && p.life) {
        findTheNode(board, curPosition.x, curPosition.y)->isSelected = 1;

        renderBoard(board, bg, 0);

        move2(board, curPosition, status, p, selectedPos, bg, couple);

        // If there is any valid pair
        if (!(checkValidPair(board)))
        {
            // If there is any cell on the board
            if (checkCellExist(board)) {

                status = 2;
            }
            else {

                status = 1;
            }
        }
    }

    renderBoard(board, bg, 0);
    deleteBoard(board, bg);
    Sleep(1500);

    system("CLS");

    aftermathAction(p, list, status, posInLeaderboard(p, list));

    system("CLS");
}
