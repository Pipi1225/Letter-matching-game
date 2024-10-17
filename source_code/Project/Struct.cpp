#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <fstream>
#include <string>
#include <time.h>
#include <cstdlib>

#include "Menu.h"
#include "Check.h"
#include "Core.h"
#include "Struct.h"

using namespace std;

// Setup one box of the cell on the console window
char box[5][30]{
			{32, 196, 196, 196, 196, 196, 196, 196, 196, 196, 32},
			{179, 32, 32, 32, 32, 32, 32, 32, 32, 32, 179},
			{179, 32, 32, 32, 32, 32, 32, 32, 32, 32, 179},
			{179, 32, 32, 32, 32, 32, 32, 32, 32, 32, 179},
			{32, 196, 196, 196, 196, 196, 196, 196, 196, 196, 32}
};


// Read the rank data from file text
void lst :: readRanked()
{
	// Store the random number plus/substract to int (ASCII) of char of that player
	int random[10];

	// Declare a temp to store player's info
	player temp;

	ifstream fin;
	fin.open("Data//rank.txt");

	for (int i = 0; i < 10; i++)
	{
		// Declare string to store point of player in type string
		string tmp;

		// Get the essential data from file
		fin >> random[i];
		fin.ignore(10, '.');

		getline(fin, temp.name, '.');

		fin >> temp.mode;
		fin.ignore(10, 'p');

		getline(fin, tmp, ',');
		fin >> temp.stages;

		fin.ignore(100, '\n');


		// Decode the data from file
		// 
		// i % 2 == 0: Random is negative;
		// i % 2 != 0: Random is position;
		if (i % 2 == 0)
		{
			random[i] = (-1) * random[i];
		}

		int len1 = temp.name.length();

		for (int l = 0; l < len1; l++)
		{
			temp.name[l] = char(int(temp.name[l]) - 30 + random[i]);
		}

		temp.point = 0;

		int len2 = tmp.length();

		for (int l = len2 - 1; l >= 0; l--)
		{
			temp.point *= 10;

			temp.point += (int(tmp[l]) - 78 + random[i]);
		}

		Player.push_back(temp);
	}

	fin.close();
}

// Write the rank data to file
void lst :: writeRanked() {

	ofstream fout;
	fout.open("Data//rank.txt");

	for (int i = 0; i < 10; i++)
	{
		int random = rand() % 9 + 1;
		int len1 = Player[i].name.length();
		int tmp = Player[i].point;


		// i % 2 == 0: Random is negative;
		// i % 2 != 0: Ramdon is positive;
		if (i % 2 == 0)
		{
			random = (-1) * random;
		}

		// Print out the data from NO. i player's record
		if (random < 0)
		{
			fout << (-1) * random;
		}
		else
		{
			fout << random;
		}

		fout << '.';

		for (int l = 0; l < len1; l++)
		{
			fout << char(int(Player[i].name[l]) + 30 - random);
		}

		fout << '.' << Player[i].mode << 'p';

		// Print out the point from NO. i player's record in char
		while (tmp != 0)
		{
			fout << char((tmp % 10) + 78 - random);

			tmp /= 10;
		}

		fout << ',';

		fout << Player[i].stages << '.';

		// Garbage characters (Nothing valuable here)
		for (int i = 0; i < 70; i++)
		{
			if (i == 5 || i == 6)
			{
				fout << '.';
			}
			else
			{
				fout << char((rand() % 40) + 48);
			}
		}

		fout << endl;
	}

	fout.close();
}

// Read the background data from file text
void background::getBackground() {

	ifstream fin;

	string random[5] = { "Data//Background//background1.txt", "Data//Background//background2.txt", "Data//Background//background3.txt",
						 "Data//Background//background4.txt", "Data//Background//background5.txt"};

	// Get a random background from 5 background
	fin.open(random[rand() % 5].c_str());

	for (int i = 0; i < 33; i++) {
		for (int j = 0; j < 52; j++)
		{
			// Initialize the bg at i column, j row with blank space ' ' 
			// So if the fin.get doesn't return anything, the bg[i][j] will always have a character ' ' in it
			bg[i][j] = ' ';
			fin.get(bg[i][j]);
		}
	}

	//system("pause");

	fin.close();
}

// Print the background on the console window
void background :: displayBackground(int x, int y) {
	
	int min_x = max(x * 10, 0);
	int min_y = max(y * 4, 0);

	int max_x = (x + 1) * 10 + 1;
	int max_y = (y + 1) * 4;

	// Print out all the correspond character of background on that column x, row y cell on the console window
	for (int i = min_x; i <= max_x; i++)
	{
		for (int j = min_y; j <= max_y; j++)
		{
			GoToXY(i + 10, j + 4);
			cout << bg[j][i];
		}
	}
}


// ======Medium mode=================================================================

// Draw box cell on the console window with different colors - for Medium Mode
void cell::drawBox(int color) {

	// If it is a blank space
	if (!isValid) return;

	int x = pos.x + 1, y = pos.y + 1;

	// Print out the box cover the character
	for (int i = 0; i < 5; i++) {
		GoToXY(x * 10, y * 4 + i);
		cout << box[i];
	}

	// If that cell is selected by player
	if (isSelected) {
		// Make it have a color background
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color + (int(val) % 6 + 1)); // White background
		for (int i = 1; i < 4; i++) {
			GoToXY(x * 10 + 1, y * 4 + i);
			cout << "         ";
		}
		GoToXY(x * 10 + 5, y * 4 + 2);
		cout << val;

		setColor(BLACK, WHITE);
	}
	else {
		// Print out without background color
		GoToXY(x * 10 + 5, y * 4 + 2);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), int(val) % 6 + 1);
		cout << val;

		setColor(BLACK, WHITE);
	}
}

// Delete box cell on the console window - for Medium Mode
void cell::deleteBox() {

	int x = pos.x + 1, y = pos.y + 1;

	for (int i = 0; i < 5; i++) {
		GoToXY(x * 10, y * 4 + i);
		cout << "           ";
	}
}


// ======Hard mode=================================================================

// Draw box cell on the console window with different colors - for Hard Mode
void cell2::drawBox(int color) {
	int x = pos.x + 1, y = pos.y + 1;

	for (int i = 0; i < 5; i++) {
		GoToXY(x * 10, y * 4 + i);
		cout << box[i];
	}

	if (isSelected) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color + (int(val) % 6 + 1)); // white background
		for (int i = 1; i < 4; i++) {
			GoToXY(x * 10 + 1, y * 4 + i);
			cout << "         ";
		}

		GoToXY(x * 10 + 5, y * 4 + 2);
		cout << val;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
	else {
		GoToXY(x * 10 + 5, y * 4 + 2);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), int(val) % 6 + 1);
		cout << val;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
}

// Delete box cell on the console window - for Hard Mode
void cell2::deleteBox() {
	int x = pos.x + 1, y = pos.y + 1;
	for (int i = 0; i < 5; i++) {
		GoToXY(x * 10, y * 4 + i);
		cout << "           ";
	}
}