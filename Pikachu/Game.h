#pragma once
#include "BoardView.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>
#include <random>

#define LEFT 5
#define TOP 1

using namespace std;


#define _EASY 4
#define _MEDIUM 6

struct Menu
{
	static bool exitGame;									// exit game flag
	static int current_option;								// current option (0-7)
	const static string options[8];								// array of options' name
	static void mainScreen();								// main screen
	static void mainMenu();									// Menu
	static void playMenu();									// Menu play
	static void leaderBoard();								// leaderboard screen
	static void helpScreen();								// instruction screen
	static void exitScreen();								// exit screen
	static void playEasy();									// play easy game
	static void playMedium();								// play medium game
	static void printLogo();								// print logo
	static void goBack() {}									// an empty function to keep the order of unordered_map options
	static void printOptionsBoard();							// print options board
	static void printAnimation();								// starting animation effect 
	static void printRectangle(int, int, int, int);						// print rectangle
	static void changeOption(bool, bool);							// change option
};

struct Player {
	string playerName;
	string playerID;
	string className;
	int score;
	string mode;
}; //to save players

int Menu::current_option;
const string Menu::options[8] = { "Play", "LeaderBoard", "Help", "Exit", "Easy", "  Medium   ", "Back", "Exit"}; // 8 options in the game

void Menu::mainScreen()
{	//maps strings to function pointers
	unordered_map<string, void(*)()> function_map = {
		{options[0], playMenu},
		{options[1], leaderBoard},
		{options[2], helpScreen},
		{options[3], exitScreen},
		{options[4], playEasy},
		{options[5], playMedium},
		{options[6], goBack},
		{options[7], exitScreen}
	};
	Controller::playSound(BACKGROUND_SOUND); // play background sound
	printAnimation();
	bool loadMenu = 1; // to decide if print the main menu
	while (true)
	{
		if (loadMenu)
			mainMenu();
		switch (Controller::getConsoleInput()) // get input from console
		{
		case 2: // KEY_UP
			changeOption(0, 1); // decrease current_option and change the interface (if possible)
			loadMenu = 0;
			break;
		case 5: // KEY_DOWN
			changeOption(1, 1); // increase current_option and change the interface (if possible)
			loadMenu = 0;
			break;
		case 6: // enter
			if (current_option == 0) // enter "Play" key will not load menu next loop
				loadMenu = 0;
			else
				loadMenu = 1;
			function_map[options[current_option]](); // run the function of current option
			break;
		default: // other characters will lead to error sound, do not load menu next loop
			Controller::playSound(ERROR_SOUND);
			loadMenu = 0;
		}
	}

	Controller::clearConsole(); // clear console
}

void Menu::printLogo() //print logo, title, students' name and ID
{
	unsigned char logo[] = R"(

		 ________  ___  ___  __    ________  ________  ___  ___  ___  ___     
		|\   __  \|\  \|\  \|\  \ |\   __  \|\   ____\|\  \|\  \|\  \|\  \    
		\ \  \|\  \ \  \ \  \/  /|\ \  \|\  \ \  \___|\ \  \\\  \ \  \\\  \   
		 \ \   ____\ \  \ \   __\_ \ \   __  \ \  \    \ \   __  \ \  \\\  \  
		  \ \  \___|\ \  \ \  \\ \  \ \  \ \  \ \  \____\ \  \ \  \ \  \\\  \ 
		   \ \__\    \ \__\ \__\\ \__\ \__\ \__\ \_______\ \__\ \__\ \_______\
		    \|__|     \|__|\|__| \|__|\|__|\|__|\|_______|\|__|\|__|\|_______|                                                                   
	)"; 
	cout << logo;	//Define and print the logo
	Controller::gotoXY(38, 0); //moving cursor to (38,0)
	Controller::setConsoleColor(BRIGHT_WHITE, BLUE); // setting color
	cout << "Pham Ngoc Dung - Nguyen Anh Kiet "; // student's name
	Controller::gotoXY(40, 1); //moving cursor to (40,1)
	cout << "    23127003 - 23127005"; //student's ID
	Controller::gotoXY(38, 8); //moving cursor to (38,8)
	Controller::setConsoleColor(BRIGHT_WHITE, GREEN); //setting color
	cout << R"(
  _____  _  _  ___   __  __    _  _____  ___  _  _  ___  _  _   ___    ___    _    __  __  ___ 
 |_   _|| || || __| |  \/  |  /_\|_   _|/ __|| || ||_ _|| \| | / __|  / __|  /_\  |  \/  || __|
   | |  | __ || _|  | |\/| | / _ \ | | | (__ | __ | | | | .` || (_ | | (_ | / _ \ | |\/| || _| 
   |_|  |_||_||___| |_|  |_|/_/ \_\|_|  \___||_||_||___||_|\_| \___|  \___|/_/ \_\|_|  |_||___|
	)";
}

void Menu::printOptionsBoard()
{
	Controller::setConsoleColor(BRIGHT_WHITE, BLACK); // Set console color
	int left = 44;
	int top = 20;
	Controller::gotoXY(left, top); // Move cursor to specified position
	putchar(201); // Print top left corner of the frame (╔)
	for (int i = 1; i < 12; i++)
	{
		putchar(205); // Print horizontal line character (═)
	}
	putchar(187); // Print top right corner of the frame (╗)

	// Print the vertical lines and T intersections for the sides of the frame
	for (int i = 1; i < 8; i++)
	{
		Controller::gotoXY(left, top + i);
		if (i % 2 != 0)
		{
			putchar(186); // Print vertical line character (║)
			Controller::gotoXY(left + 12, top + i);
			putchar(186); // Print vertical line character (║)
		}
		else
		{
			putchar(199); // Print T intersection character (╣)
			for (int i = 1; i < 12; i++)
			{
				putchar(196); // Print horizontal line character (─)
			}
			putchar(182); // Print T intersection character (╠)
		}
	}
	Controller::gotoXY(left, top + 8); // Move cursor to bottom left position
	putchar(200); // Print bottom left corner of the frame (╚)
	for (int i = 1; i < 12; i++)
	{
		putchar(205); // Print horizontal line character (═)
	}
	putchar(188); // Print bottom right corner of the frame (╝)
}

void Menu::printAnimation() //Capcut animation :)))
{
	Controller::setConsoleColor(BRIGHT_WHITE, BLACK); //Set console color
	Controller::clearConsole(); // Clear the console screen
	// Array of random symbol positions
	char symbolpos[] = { 5,0,19,0,33,0,47,0,61,0,75,0,89,0,0,103,5,13,19,
							   13,33,13,47,13,61,13,75,13,89,13,13,103,13,18,26,18,40,18,
							   54,18,68,18,82,18,18,96,5,24,19,24,33,24,47,24,61,24,75,24,
							   89,24,24,103,12,30,26,30,40,30,54,30,68,30,82,30,96,30 };
	int n = (sizeof(symbolpos) / sizeof(symbolpos[0])) / 2; // Calculate the number of symbol positions
	bool turn = 0; // Flag to determine which symbol to print
	unsigned char symbol[] = { 4,15 }; // ♦ ☼

	int color[] = { LIGHT_AQUA, AQUA, LIGHT_BLUE, BLUE, LIGHT_PURPLE, PURPLE };
	int colorcount = 0; // Counter for colors
	int loop = 10; // Number of animation loops
	while (loop--) 
	{
		for (int i = 0; i < n; i += 2) // Print symbols at even positions
		{
			Controller::setConsoleColor(BRIGHT_WHITE, getRandomInt(0, 15)); // Set random console color
			Controller::gotoXY(symbolpos[i * 2], symbolpos[i * 2 + 1]); // Move cursor to symbol position
			putchar(symbol[turn]); //print ♦
		}
		for (int i = 1; i < n; i += 2)  // Print symbols at odd positions
		{
			Controller::setConsoleColor(BRIGHT_WHITE, getRandomInt(0, 15)); // Set random console color
			Controller::gotoXY(symbolpos[i * 2], symbolpos[i * 2 + 1]); // Move cursor to symbol position
			putchar(symbol[!turn]); //print ☼
		}
		Controller::gotoXY(0, 0); // Move cursor to top-left corner
		printLogo(); 
		colorcount++; // Increment color counter
		turn = !turn; // turn flag
		Sleep(250); // Sleep for 250 milliseconds
	}
}

void Menu::changeOption(bool direction, bool flag) // direction: 0 is up, 1 is down, this is not a completed function; flag = 1 will change the interface
{
	int top = 21; // Vertical position offset for displaying options

	// Check if the current option is at the top or bottom and the direction is invalid
	if ((direction == 0 && (current_option == 4 || current_option == 0)) // "easy" or "play option can't go up
		|| (direction == 1 && (current_option == 3 || current_option == 7))) //"exit" option can't go down
	{
		Controller::playSound(ERROR_SOUND); // Play an error sound
		return; 
	}

	Controller::setConsoleColor(BRIGHT_WHITE, BLACK); // Set console color
	Controller::gotoXY(50 - (int)options[current_option].length() / 2, top + current_option % 4 * 2); // Move cursor to the current option
	cout << options[current_option]; // Output the current option

	if (flag)
	{
		// Clear the left and right indicator spaces if flag is true
		Controller::gotoXY(40, top + current_option % 4 * 2);
		putchar(32); // space character
		Controller::gotoXY(60, top + current_option % 4 * 2);
		putchar(32); // space character
	}

	(direction == 1) ? current_option++ : current_option--; // Increment or decrement the current option

	if (flag)
	{
		Controller::playSound(MOVE_SOUND); // Play a move sound
		Controller::setConsoleColor(BRIGHT_WHITE, RED); // Current option is red and have » « point to
		Controller::gotoXY(40, top + current_option % 4 * 2);
		putchar(175); // Output »
		Controller::gotoXY(50 - (int)options[current_option].length() / 2, top + current_option % 4 * 2);
		cout << options[current_option]; // Output the updated option text
		Controller::gotoXY(60, top + current_option % 4 * 2);
		putchar(174); // Output «
	}
}

void Menu::mainMenu()
{
	Controller::setConsoleColor(BRIGHT_WHITE, RED); // Set console color
	Controller::clearConsole(); // clear console screen
	//print logo and options board
	printLogo();
	printOptionsBoard();
	// move current_option to 0 ("play") and print option 0-3 ("play" - "exit)
	current_option = 3;
	changeOption(0, 0);
	changeOption(0, 0);
	changeOption(0, 1); 
}

void Menu::playMenu()
{
	// move current_option to 4 ("easy") and print option 4-7 ("easy" - "exit")
	current_option = 7;
	changeOption(0, 0);
	changeOption(0, 0);
	changeOption(0, 1);
}

void Menu::helpScreen()
{
	Controller::showCursor(false); //hide the console cursor
	Controller::setConsoleColor(BRIGHT_WHITE, BLACK); //set color
	Controller::clearConsole(); // clear console
	// set value of position of the rectangle, 1 vertical and 3 horizontal lines to categorize the in4
	int left = 5, top = 2, width = 85, height = 23;
	int line1 = 6, line2 = 19, line3 = 20, line4 = 15;
	printRectangle(left, top, width, height); //print rectangle
	// print 3 horizontal lines
	Controller::gotoXY(left + 1, line1);
	for (int i = 0; i < width; i++)
	{
		putchar(196); // "─"
	}
	Controller::gotoXY(left + 1, line2);
	for (int i = 0; i < width; i++)
	{
		putchar(196); // "─"
	}
	Controller::gotoXY(left + 1, line4);
	for (int i = 0; i < width; i++)
	{
		putchar(196); // "─"
	}
	for (int i = 1; i < height; i++) // print vertical line
	{
		Controller::gotoXY(line3, top + i);
		putchar(179);
	}
	Controller::gotoXY(line3, line1);
	putchar(197); // "┼"
	Controller::gotoXY(line3, line2);
	putchar(197); // "┼"
	// Moves instruction
	Controller::setConsoleColor(BRIGHT_WHITE, BLUE);
	Controller::gotoXY(left + 3, top + 2);
	cout << "Moves:";
	Controller::gotoXY(left + 20, top + 1);
	putchar(249); cout << "Up:    W, up arrow"; // 249: character ∙
	Controller::gotoXY(left + 52, top + 1);
	putchar(249); cout << "Down:  S, down arrow";
	Controller::gotoXY(left + 20, top + 3);
	putchar(249); cout << "Left:  A, left arrow";
	Controller::gotoXY(left + 52, top + 3);
	putchar(249); cout << "Right: D, right arrow";
	// Rules instruction 	
	Controller::gotoXY(left + 3, top + 8);
	cout << "Rules:";
	Controller::gotoXY(left + 17, top + 5);
	int left1 = left + 17;
	putchar(249); cout << " The Matching Game (commonly known as the Pikachu Puzzle Game)"; // 249: character ∙
	Controller::gotoXY(left1, top + 6);
	cout << " includes a board of multiple cells, each of which presents a figure.";
	Controller::gotoXY(left1, top + 8);
	putchar(249); cout << " The player finds and matches a pair of cells that contain the same";
	Controller::gotoXY(left1, top + 9);
	cout << " figure and connect each other in some particular pattern.";
	Controller::gotoXY(left1, top + 11);
	putchar(249); cout << " A legal match will make the two cells disappear. The game ends when";
	Controller::gotoXY(left1, top + 12);
	cout << " all matching pairs are found.";
	// score instruction
	Controller::gotoXY(left + 3, top + 15);
	cout << "Scoring:";
	Controller::setConsoleColor(BRIGHT_WHITE, GREEN);
	Controller::gotoXY(left1 + 10, top + 14);
	putchar(249); cout << " I Matching: +1 Point";
	Controller::setConsoleColor(BRIGHT_WHITE, GREEN);
	Controller::gotoXY(left1 + 40, top + 14);
	putchar(249); cout << " L Matching: +2 Point";
	Controller::setConsoleColor(BRIGHT_WHITE, GREEN);
	Controller::gotoXY(left1 + 10, top + 15);
	putchar(249); cout << " Z Matching: +3 Point";
	Controller::gotoXY(left1 + 40, top + 15);
	putchar(249); cout << " U Matching: +4 Point";
	Controller::setConsoleColor(BRIGHT_WHITE, RED);
	Controller::gotoXY(left1 + 10, top + 16);
	putchar(249); cout << " Not Matched: -2 Point";
	Controller::setConsoleColor(BRIGHT_WHITE, RED);
	Controller::gotoXY(left1 + 40, top + 16);
	putchar(249); cout << " Move suggestion: -2 Point";
	// Developers' in4
	Controller::setConsoleColor(BRIGHT_WHITE, BLUE);
	Controller::gotoXY(left + 3, top + 20);
	cout << "Developers:";
	Controller::gotoXY(left + 31, top + 19);
	cout << "Dev 1: Nguyen Anh Kiet (23127005)";
	Controller::gotoXY(left + 31, top + 21);
	cout << "Dev 2: Pham Ngoc Dung (23127003)";
	// Back key
	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	printRectangle(45, 27, 8, 2);
	Controller::setConsoleColor(BRIGHT_WHITE, RED);
	Controller::gotoXY(43, 28);
	putchar(175); // »
	Controller::gotoXY(48, 28);
	cout << "Back";
	Controller::gotoXY(56, 28);
	putchar(174); // «
	while (Controller::getConsoleInput() != 6) // players have to press "enter" to go back
	{
		Controller::playSound(ERROR_SOUND);
	}
}

void Menu::printRectangle(int left, int top, int width, int height)
{	// print the top line
	Controller::gotoXY(left, top);
	putchar(218); // ┌
	for (int i = 0; i < width; i++)
		putchar(196); // ─
	putchar(191); // ┐
	// print 2 vertical lines
	int i = 0;
	for (; i < height; i++)
	{
		Controller::gotoXY(left, top + i + 1);
		putchar(179); // │
		Controller::gotoXY(left + width + 1, top + i + 1);
		putchar(179); // │
	}
	// print the bottom line
	Controller::gotoXY(left, top + i);
	putchar(192); // └
	for (i = 0; i < width; i++)
		putchar(196); // ─
	putchar(217); // ┘
}

void Menu::exitScreen()
{
	Controller::showCursor(false); // hide cursor
	Controller::setConsoleColor(BRIGHT_WHITE, BLACK); // set color
	Controller::clearConsole(); // clear console
	Controller::setConsoleColor(BRIGHT_WHITE, BLACK); // set color
	// 3 rectangle for "Do you want to exit?", "Yes", "No"
	Menu::printRectangle(34, 13, 35, 8);
	Menu::printRectangle(37, 18, 7, 2);
	Menu::printRectangle(60, 18, 6, 2);
	Controller::setConsoleColor(BRIGHT_WHITE, RED);
	Controller::gotoXY(0, 0);
	printLogo(); // print the logo like the main screen
	Controller::gotoXY(42, 16);
	cout << "Do you want to exit?";
	string str[2] = { "Yes", "No" };
	int left[] = { 35,40,47,58,63,69 }, // position of "Yes","NO", », «
	word[] = { 32,32,175,174 }, // spacebar for not current option; », « for current option
	color[] = { BLACK, RED }, // black for not current option; red for current option
	top = 19; // position y of "Yes", "No"
	bool choice = 0; // 0 for "yes", 1 for "no"
	bool loop = 1;
	auto print1 = [&]() // print the frame, the current choice; change the choice
	{
		int i = 0;
		while (i < 2)
		{
			Controller::playSound(MOVE_SOUND);
			Controller::setConsoleColor(BRIGHT_WHITE, color[i]);
			Controller::gotoXY(left[choice * 3], top);        putchar(word[i * 2]);  // spacebar for not current option; » for current option
			Controller::gotoXY(left[choice * 3 + 1], top);    cout << str[choice]; // "yes"/"no"
			Controller::gotoXY(left[choice * 3 + 2], top);    putchar(word[i * 2 + 1]); // spacebar for not current option; « for current option
			if (!i++)
				choice = !choice; // "yes" -> no, "no" -> "yes"
		}
	};
	print1(); // print exit screen
	while (loop)
	{
		int key = Controller::getConsoleInput(); // get input from console
		if ((key == 3 && choice == 1) || (key == 4 && choice == 0)) // KEY_LEFT for "no" or KEY_RIGHT for "yes"
		{
			print1();
		}
		else if (key == 6) // enter
		{
			if (!choice) // "yes" will exit the program
			{
				Controller::setConsoleColor(BLACK, BRIGHT_WHITE);
				Controller::clearConsole();
				exit(0);
			}
			return;
		}
		else // other characters will play error sound
		{
			Controller::playSound(ERROR_SOUND);
		}
	}
}


void Menu::leaderBoard()
{
	current_option = 0; // set current_option to 0
	Controller::clearConsole();
	Player p[100]; // save 100 players
	Controller::setConsoleColor(BRIGHT_WHITE, RED);
	cout << R"(
	  _      ______          _____  ______ _____  ____   ____          _____  _____  
	 | |    |  ____|   /\   |  __ \|  ____|  __ \|  _ \ / __ \   /\   |  __ \|  __ \ 
	 | |    | |__     /  \  | |  | | |__  | |__) | |_) | |  | | /  \  | |__) | |  | |
	 | |    |  __|   / /\ \ | |  | |  __| |  _  /|  _ <| |  | |/ /\ \ |  _  /| |  | |
	 | |____| |____ / ____ \| |__| | |____| | \ \| |_) | |__| / ____ \| | \ \| |__| |
	 |______|______/_/    \_\_____/|______|_|  \_\____/ \____/_/    \_\_|  \_\_____/                                                                 
	)";
	// set the frame with a rectangle and lines, categorize the board into STT, Name, ID, Class, Mode, Score.
	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	printRectangle(5, 8, 85, 17);
	Controller::setConsoleColor(BRIGHT_WHITE, BLUE);
	Controller::gotoXY(8, 9);
	cout << "STT";
	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	for (int i = 1; i < 17; i++)
	{
		Controller::gotoXY(13, 8 + i);
		putchar(179); // │
	}
	for (int i = 6; i < 13; i++)
	{
		Controller::gotoXY(i, 10);
		putchar(196); // ─
	}
	Controller::setConsoleColor(BRIGHT_WHITE, BLUE);
	Controller::gotoXY(18, 9);
	cout << "Name";
	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	for (int i = 1; i < 17; i++)
	{
		Controller::gotoXY(30, 8 + i);
		putchar(179); // │
	}
	for (int i = 14; i < 30; i++)
	{
		Controller::gotoXY(i, 10);
		putchar(196); // ─
	}
	Controller::setConsoleColor(BRIGHT_WHITE, BLUE);
	Controller::gotoXY(36, 9);
	cout << "ID";
	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	for (int i = 1; i < 17; i++)
	{
		Controller::gotoXY(45, 8 + i);
		putchar(179); // │
	}
	for (int i = 31; i < 45; i++)
	{
		Controller::gotoXY(i, 10);
		putchar(196); // ─
	}
	Controller::setConsoleColor(BRIGHT_WHITE, BLUE);
	Controller::gotoXY(52, 9);
	cout << "Class";
	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	for (int i = 1; i < 17; i++)
	{
		Controller::gotoXY(62, 8 + i);
		putchar(179); // │
	}
	for (int i = 46; i < 62; i++)
	{
		Controller::gotoXY(i, 10);
		putchar(196); // ─
	}
	Controller::setConsoleColor(BRIGHT_WHITE, BLUE);
	Controller::gotoXY(68, 9);
	cout << "Mode";
	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	for (int i = 1; i < 17; i++)
	{
		Controller::gotoXY(78, 8 + i);
		putchar(179); // │
	}
	for (int i = 63; i < 78; i++)
	{
		Controller::gotoXY(i, 10);
		putchar(196); // ─
	}

	Controller::setConsoleColor(BRIGHT_WHITE, BLUE);
	Controller::gotoXY(82, 9);
	cout << "Score";
	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	for (int i = 79; i < 91; i++)
	{
		Controller::gotoXY(i, 10);
		putchar(196); // ─
	}
	int y = 11; // position sign
	int lines = 8; // print top 7 players
	int n = 0; // number of players
	string tmp;
	fstream fs("rank\\leaderboard.txt", ios::in); // get file from rank\leaderboard text file
	// read and save players' in4 to p array
	while (!fs.eof()) {
		getline(fs, p[n].playerName);
		getline(fs, p[n].playerID);
		getline(fs, p[n].className);
		getline(fs, p[n].mode);
		fs >> p[n].score;
		fs.ignore();
		n++;
	}
	fs.close();
	// sort the scores of players
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (p[j].score > p[i].score) {
				swap(p[i], p[j]);
			}
		}
	}
	// print top 7 players
	for (int i = 1; i < lines; i++) {
		Controller::gotoXY(9, y);
		cout << i;
		Controller::gotoXY(16, y);
		cout << p[i - 1].playerName;
		Controller::gotoXY(33, y);
		cout << p[i - 1].playerID;
		Controller::gotoXY(50, y);
		cout << p[i - 1].className;
		Controller::gotoXY(68, y);
		cout << p[i - 1].mode;
		Controller::gotoXY(84, y);
		cout << p[i - 1].score;
		y += 2;
	}
	// Back key
	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	printRectangle(45, 27, 8, 2);
	Controller::setConsoleColor(BRIGHT_WHITE, RED);
	Controller::gotoXY(43, 28);
	putchar(175); // »
	Controller::gotoXY(48, 28);
	cout << "Back";
	Controller::gotoXY(56, 28);
	putchar(174); // «
	while (Controller::getConsoleInput() != 6) // players have to press "enter" to go back
	{
		Controller::playSound(ERROR_SOUND);
	}
}

struct Game {
	BoardView* board;				// Create new board
	char playerName[15] = "", playerID[9] = "", className[8] = "", mode[8] = "";  // player's in4
	int _mode; // easy or normal game
	int _x, _y; 
	bool isPlaying; // check if in game screen
	int _lockedBlock; // number of locked block: 0 if there's no locked block, 1 if there is 1 locked block, 2 wil delete blocks if matching
	int _remainBlocks; // number of remain blocks, 0 wil end game
	int score; // current score

	vector<pair<int, int>> _lockedBlockPair; // position of locked block(s) First: row - Second: column

	bool checkMatchedPokemons(pair<int, int>, pair<int, int>); // 1 if 2 pokemons is the same
	int checkIMatching(pair<int, int>, pair<int, int>, bool); 
	bool checkLMatching(pair<int, int>, pair<int, int>, bool);
	bool checkZMatching(pair<int, int>, pair<int, int>, bool);
	bool checkUMatching(pair<int, int>, pair<int, int>, bool);
	bool checkMatching(pair<int, int>, pair<int, int>, bool); // check I,L,Z,U matching in order, then change and print the score

	Game(int);
	~Game();

	void setupGame();
	void startGame();
	void printInterface();
	void saveData();

	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();

	char getPokemons(int x, int y);

	void lockBlock();
	void deleteBlock(); // delete blocks if matching, then print announcement if end game or no more matching blocks
	bool isAvailableBlock(bool); // check if there are any possible matching blocks

	void askContinue(); // ask to continue in end ame
	void moveSuggestion();
};

Game::Game(int mode)
{
	_mode = mode;
	_x = LEFT, _y = TOP;
	board = new BoardView(_mode, LEFT, TOP);
	isPlaying = true;
	_lockedBlock = 0;
	_lockedBlockPair.clear();
	_remainBlocks = _mode * _mode;
	score = 0;
}

Game::~Game() {
	delete board;
	board = nullptr;
}

void Game::startGame() 
{
	Controller::clearConsole();
	while (isPlaying) {
		_remainBlocks = _mode * _mode;
		score = 0;
		bool isPause = false;
		printInterface();
		_x = board->getXAt(0, 0);
		_y = board->getYAt(0, 0);
		Controller::gotoXY(_x, _y);
		board->selectedBlock(_x, _y, GREEN);
		putchar(board->getPokemons(_x, _y));
		Controller::gotoXY(_x, _y);
		if (!isAvailableBlock(true)) {
			Controller::setConsoleColor(BRIGHT_WHITE, RED);
			Controller::gotoXY(69, 18);
			cout << "Game Announcement";
			Controller::gotoXY(64, 19);
			cout << "There are no more ways left!";
			Sleep(800);
			Controller::gotoXY(62, 21);
			cout << "Auto reset the board. Have fun!";
			Sleep(1000);
			startGame();
		}
		while (_remainBlocks && !isPause) {
			switch (Controller::getConsoleInput())
			{
			case 0:
				Controller::playSound(ERROR_SOUND);
				break;
			case 1:
				saveData();
				Menu::exitScreen();
				return;
			case 2:
				moveUp();
				break;
			case 3:
				moveLeft();
				break;
			case 4:
				moveRight();
				break;
			case 5:
				moveDown();
				break;
			case 6:
				lockBlock();
				break;
			case 7:
				isPause = true;
				Menu::helpScreen();
				break;
			case 8:
				moveSuggestion();
				break;
			}
		}
		if (isPause)
			continue;
		askContinue();
	}

	saveData();
}

void Menu::playEasy()
{
	Game g(_EASY);
	g.setupGame();
	g.startGame();
}

void Menu::playMedium()
{
	Game g(_MEDIUM);
	g.setupGame();
	g.startGame();
}

void Game::setupGame() {
	Controller::setConsoleColor(BRIGHT_WHITE, YELLOW);
	Controller::clearConsole();
	Controller::gotoXY(0, 0);
	Menu::printLogo();	
	Controller::showCursor(true);
	Controller::setConsoleColor(BRIGHT_WHITE, RED);
	Controller::gotoXY(25, 15);
	cout << "Please enter your name shortly, under 10 characters!";

	Controller::setConsoleColor(BRIGHT_WHITE, LIGHT_BLUE);
	Controller::gotoXY(35, 18);
	cout << "Enter your name:  ";
	cin.getline(playerName, 15);
	Controller::gotoXY(35, 20);
	cout << "Enter your ID:  ";
	cin.getline(playerID, 9);
	Controller::gotoXY(35, 22);
	cout << "Enter your class's name:  ";
	cin.getline(className, 8);
	if (_mode == 4)
		strcpy_s(mode, "EASY");
	else 
		strcpy_s(mode, "MEDIUM");
	Controller::showCursor(false);
}

void Game::saveData() {
	fstream fs("rank\\leaderboard.txt", ios::app);
	fs << playerName << '\n' << playerID << '\n' << className << '\n' << mode << '\n' << score << '\n';
	fs.close();
}

void Game::moveRight()
{
	if (_x < board->getXAt(board->getSize() - 1, board->getSize() - 1))
	{
		Controller::playSound(MOVE_SOUND);
		if (board->getCheck(_x, _y) != _LOCK) {
			board->unselectedBlock(_x, _y);
		}

		if (board->getCheckAtXY(_x, _y) == 0)
		{
			Controller::gotoXY(_x, _y);
		}
		_x += 8;

		if (board->getCheck(_x, _y) != _LOCK) {
			board->selectedBlock(_x, _y, GREEN);
		}
	}
	else
		Controller::playSound(ERROR_SOUND);
	
}

void Game::moveLeft()
{
	if (_x > board->getXAt(0, 0))
	{
		Controller::playSound(MOVE_SOUND);
		if (board->getCheck(_x, _y) != _LOCK) {
			board->unselectedBlock(_x, _y);
		}

		if (board->getCheckAtXY(_x, _y) == 0)
		{
			Controller::gotoXY(_x, _y);
		}
		_x -= 8;

		if (board->getCheck(_x, _y) != _LOCK) {
			board->selectedBlock(_x, _y, GREEN);
		}
	}
	else
		Controller::playSound(ERROR_SOUND);
}

void Game::moveDown()
{
	if (_y < board->getYAt(board->getSize() - 1, board->getSize() - 1))
	{
		Controller::playSound(MOVE_SOUND);
		if (board->getCheck(_x, _y) != _LOCK) {
			board->unselectedBlock(_x, _y);
		}

		if (board->getCheckAtXY(_x, _y) == 0)
		{
			Controller::gotoXY(_x, _y);
		}
		_y += 4;

		if (board->getCheck(_x, _y) != _LOCK) {
			board->selectedBlock(_x, _y, GREEN);
		}
	}
	else
		Controller::playSound(ERROR_SOUND);
}

void Game::moveUp()
{
	if (_y > board->getYAt(0, 0))
	{
		Controller::playSound(MOVE_SOUND);
		if (board->getCheck(_x, _y) != _LOCK) {
			board->unselectedBlock(_x, _y);
		}

		if (board->getCheckAtXY(_x, _y) == 0)
		{
			Controller::gotoXY(_x, _y);
		}
		_y -= 4;

		if (board->getCheck(_x, _y) != _LOCK) {
			board->selectedBlock(_x, _y, GREEN);
		}
	}
	else
		Controller::playSound(ERROR_SOUND);
}

void Game::printInterface()
{
	board->createBackground();
	board->showBoard();
	board->buildBoardData();
	board->renderBoard();

	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	Menu::printRectangle(59, 1, 33, 10);
	Menu::printRectangle(59, 12, 33, 10);

	Menu::printRectangle(60, 2, 31, 2);
	Controller::setConsoleColor(BRIGHT_WHITE, RED);
	Controller::gotoXY(67, 3);
	cout << "PLAYER'S INFORMATION";

	Controller::setConsoleColor(BRIGHT_WHITE, BLUE);
	Controller::gotoXY(65, 5);
	if(strlen(playerName) != 0)
		cout << "Player's name: " << playerName;
	else {
		strcpy_s(playerName, "unknown");
		cout << "Player's name: " << playerName;
	}
	Controller::gotoXY(65, 7);
	if(strlen(playerID) != 0)
		cout << "Student's ID: " << playerID;
	else {
		strcpy_s(playerID, "unknown");
		cout << "Student's ID: " << playerID;
	}
	Controller::gotoXY(65, 9);
	if(strlen(className) != 0)
		cout << "Class: " << className;
	else {
		strcpy_s(className, "unknown");
		cout << "Class: " << className;
	}
	
	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	Menu::printRectangle(60, 13, 31, 2);
	Controller::setConsoleColor(BRIGHT_WHITE, RED);
	Controller::gotoXY(69, 14);
	cout << "GAME INFORMATION";
	Controller::setConsoleColor(BRIGHT_WHITE, BLUE);
	Controller::gotoXY(65, 16);
	cout << "Moves:";
	Controller::gotoXY(65, 17);
	cout << "Current score:";
	Controller::gotoXY(80, 17);
	cout << score;

	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	Menu::printRectangle(59, 24, 33, 2);
	Menu::printRectangle(59, 27, 14, 2);
	Menu::printRectangle(78, 27, 14, 2);

	Controller::setConsoleColor(BRIGHT_WHITE, PURPLE);
	Controller::gotoXY(67, 25);
	cout << "M : Move suggestion";
	Controller::setConsoleColor(BRIGHT_WHITE, GREEN);
	Controller::gotoXY(63, 28);
	cout << "H : Help";
	Controller::setConsoleColor(BRIGHT_WHITE, YELLOW);
	Controller::gotoXY(81, 28);
	cout << "Esc : Exit";
}

char Game::getPokemons(int x, int y)
{
	return board->getPokemons(x, y);
}

void Game::lockBlock()
{
	Controller::playSound(ENTER_SOUND);
	if (board->getCheck(_x, _y) == _LOCK || board->getCheck(_x, _y) == _DELETE) {
		return;
	}
	board->lockBlock(_x, _y);
	
	_lockedBlockPair.push_back(pair<int, int>(_x, _y));
	_lockedBlock++;

	if (_lockedBlock == 2) {
		deleteBlock();
	}
}

bool Game::checkMatchedPokemons(pair<int, int> firstBlock, pair<int, int> secondBlock)
{
	return (board->getPokemons(firstBlock.first, firstBlock.second) == board->getPokemons(secondBlock.first, secondBlock.second));
}

int Game::checkIMatching(pair<int, int> firstBlock, pair<int, int> secondBlock, bool isChecking)
{
	if (firstBlock.first == secondBlock.first && firstBlock.second == secondBlock.second) {
		return 2;
	}
	// check line y -> check value of x
	if (firstBlock.second == secondBlock.second) {
		if (firstBlock.first > secondBlock.first)
			swap(firstBlock, secondBlock);

		for (int i = firstBlock.first; i <= secondBlock.first; i += 8) {
			if (i == firstBlock.first || i == secondBlock.first)
				continue;
			if (board->getCheck(i, firstBlock.second) != _DELETE) {
				return 0;
			}
		}
		if (board->getCheck(firstBlock.first, firstBlock.second) == _DELETE
			|| board->getCheck(secondBlock.first, secondBlock.second) == _DELETE) {
			return 2;
		}

		if (checkMatchedPokemons(firstBlock,secondBlock))  {
			if (isChecking == false) {
				board->drawLineI(firstBlock, secondBlock);
				Sleep(200);
				board->deleteLineI(firstBlock, secondBlock);
			}
			return 1;
		}
	}
	// check line x -> check value of y
	if (firstBlock.first == secondBlock.first) {
		if (firstBlock.second > secondBlock.second)
			swap(firstBlock, secondBlock);

		for (int i = firstBlock.second; i <= secondBlock.second; i += 4) {
			if (i == firstBlock.second || i == secondBlock.second)
				continue;
			if (board->getCheck(firstBlock.first, i) != _DELETE) {
				return 0;
			}
		}
		if (board->getCheck(firstBlock.first, firstBlock.second) == _DELETE
			|| board->getCheck(secondBlock.first, secondBlock.second) == _DELETE) {
			return 2;
		}

		if (checkMatchedPokemons(firstBlock, secondBlock)) {
			if (isChecking == false) {
				board->drawLineI(firstBlock, secondBlock);
				Sleep(200);
				board->deleteLineI(firstBlock, secondBlock);
			}
			return 1;
		}
	}
	return 0;
}
bool Game::checkLMatching(pair<int, int> firstBlock, pair<int, int> secondBlock, bool isChecking)
{
	if (firstBlock.first > secondBlock.first)
		swap(firstBlock, secondBlock);

	pair<int, int> Lcorner;
	Lcorner.first = firstBlock.first;
	Lcorner.second = secondBlock.second;
	if (board->getCheck(Lcorner.first, Lcorner.second) == _DELETE) {
		if (checkIMatching(Lcorner, firstBlock, isChecking) && checkIMatching(Lcorner, secondBlock, isChecking)) {
			if (isChecking == false) {
				board->drawLineL(firstBlock, secondBlock, Lcorner);
				Sleep(200);
				board->deleteLineL(firstBlock, secondBlock, Lcorner);
			}
			return 1;
		}
	}

	Lcorner.first = secondBlock.first;
	Lcorner.second = firstBlock.second;
	if (board->getCheck(Lcorner.first, Lcorner.second) == _DELETE) {
		if (checkIMatching(Lcorner, secondBlock, isChecking) && checkIMatching(Lcorner, firstBlock, isChecking)) {
			if (isChecking == false) {
				board->drawLineL(firstBlock, secondBlock, Lcorner);
				Sleep(200);
				board->deleteLineL(firstBlock, secondBlock, Lcorner);
			}
			return 1;
		}	
	}
	return 0;
}
bool Game::checkZMatching(pair<int, int> firstBlock, pair<int, int> secondBlock, bool isChecking)
{
	if (firstBlock.first > secondBlock.first)
		swap(firstBlock, secondBlock);

	pair<int, int> Zcorner1;
	pair<int, int> Zcorner2;
	
	for (int i = firstBlock.first + 8; i < secondBlock.first; i += 8) {
		if (board->getCheck(i, firstBlock.second) == _DELETE) {
			if (board->getCheck(i, secondBlock.second) == _DELETE) {
				Zcorner1.first = i;	
				Zcorner1.second = firstBlock.second;
				Zcorner2.first = i;
				Zcorner2.second = secondBlock.second;
				if (checkIMatching(Zcorner1, Zcorner2, isChecking) &&
					checkIMatching(Zcorner2, secondBlock, isChecking)) {
					if (isChecking == false) {
						board->drawLineZ(firstBlock, secondBlock, Zcorner1, Zcorner2);
						Sleep(200);
						board->deleteLineZ(firstBlock, secondBlock, Zcorner1, Zcorner2);
					}
					return 1;
				}
			}
		}
		else break;
	}

	if (firstBlock.second > secondBlock.second)
		swap(firstBlock, secondBlock);
	for (int i = firstBlock.second + 4; i < secondBlock.second; i += 4) {
		if (board->getCheck(firstBlock.first, i) == _DELETE) {
			if (board->getCheck(secondBlock.first, i) == _DELETE) {
				Zcorner1.first = firstBlock.first;	
				Zcorner1.second = i;
				Zcorner2.first = secondBlock.first;
				Zcorner2.second = i;
				if (checkIMatching(Zcorner1, Zcorner2, isChecking) &&
					checkIMatching(Zcorner2, secondBlock, isChecking)) {
					if (isChecking == false) {
						board->drawLineZ(firstBlock, secondBlock, Zcorner1, Zcorner2);
						Sleep(200);
						board->deleteLineZ(firstBlock, secondBlock, Zcorner1, Zcorner2);
					}
					return 1;
				}
			}
		}
		else break;
	}
	return 0;
}
bool Game::checkUMatching(pair<int, int> firstBlock, pair<int, int> secondBlock, bool isChecking)
{
	pair<int, int> Ucorner1;
	pair<int, int> Ucorner2;
	const int size = board->getSize();
	const int x = board->getXAt(0, 0);
	const int y = board->getYAt(0, 0);
	
	if (firstBlock.first == secondBlock.first)
		if (firstBlock.second > secondBlock.second)
			swap(firstBlock, secondBlock);

	// U ngang trai
	if (firstBlock.first > secondBlock.first)
		swap(firstBlock, secondBlock);
	for (int i = firstBlock.first - 8; i >= x - 8; i -= 8) {
		Ucorner1.first = i;
		Ucorner1.second = firstBlock.second;
		Ucorner2.first = i;
		Ucorner2.second = secondBlock.second;

		if (i == x - 8) {
			Ucorner1.first = x;
			Ucorner1.second = firstBlock.second;
			Ucorner2.first = x;
			Ucorner2.second = secondBlock.second;
			if (Ucorner1.first == firstBlock.first && Ucorner2.first == secondBlock.first)
				return 1;
			if ((board->getCheck(Ucorner1.first, Ucorner1.second) == _DELETE ||
				(Ucorner1.first == firstBlock.first && Ucorner1.second == firstBlock.second))
				&& board->getCheck(Ucorner2.first, Ucorner2.second) == _DELETE) {
				if (checkIMatching(firstBlock, Ucorner1, isChecking) == 2 && checkIMatching(secondBlock, Ucorner2, isChecking) == 2)
					return 1;
			}
			else break;
		}
		if (board->getCheck(Ucorner1.first, Ucorner1.second) == _DELETE
			&& board->getCheck(Ucorner2.first, Ucorner2.second) == _DELETE) {
			if (checkIMatching(Ucorner1, firstBlock, isChecking) == 2 && checkIMatching(Ucorner2, secondBlock, isChecking) == 2
				&& checkIMatching(Ucorner1, Ucorner2, isChecking) == 2) {
				if (isChecking == false) {
					board->drawLineU(firstBlock, secondBlock, Ucorner1, Ucorner2);
					Sleep(200);
					board->deleteLineU(firstBlock, secondBlock, Ucorner1, Ucorner2);
				}
				return 1;
			}
		}
		else break;
	}
	// U ngang phai
	if (firstBlock.first < secondBlock.first)
		swap(firstBlock, secondBlock);
	for (int i = firstBlock.first + 8; i <= x + size * 8; i += 8) {
		Ucorner1.first = i;
		Ucorner1.second = firstBlock.second;
		Ucorner2.first = i;
		Ucorner2.second = secondBlock.second;
		
		if (i == x + size * 8) {
			Ucorner1.first = x + size * 8 - 8;
			Ucorner1.second = firstBlock.second;
			Ucorner2.first = x + size * 8 - 8;
			Ucorner2.second = secondBlock.second;

			if (Ucorner1.first == firstBlock.first && Ucorner2.first == secondBlock.first)
				return 1;
			if ((board->getCheck(Ucorner1.first, Ucorner1.second) == _DELETE ||
				(Ucorner1.first == firstBlock.first && Ucorner1.second == firstBlock.second))
				&& board->getCheck(Ucorner2.first, Ucorner2.second) == _DELETE) {
				if (checkIMatching(firstBlock, Ucorner1, isChecking) == 2 && checkIMatching(secondBlock, Ucorner2, isChecking) == 2)
					return 1;
			}
			else break;
		}

		if (board->getCheck(Ucorner1.first, Ucorner1.second) == _DELETE
			&& board->getCheck(Ucorner2.first, Ucorner2.second) == _DELETE) {
			if (checkIMatching(Ucorner1, firstBlock, isChecking) == 2 && checkIMatching(Ucorner2, secondBlock, isChecking) == 2
				&& checkIMatching(Ucorner1, Ucorner2, isChecking) == 2) {
				if (isChecking == false) {
					board->drawLineU(firstBlock, secondBlock, Ucorner1, Ucorner2);
					Sleep(1200);
					board->deleteLineU(firstBlock, secondBlock, Ucorner1, Ucorner2);
				}
				return 1;
			}
		}
		else break;
	}
	if (firstBlock.second == secondBlock.second)
		if (firstBlock.first > secondBlock.first)
			swap(firstBlock, secondBlock);	

	// U doc tren
	if (firstBlock.second > secondBlock.second)
		swap(firstBlock, secondBlock);
	for (int i = firstBlock.second - 4; i >= y - 4; i -= 4) {
		Ucorner1.first = firstBlock.first;
		Ucorner1.second = i;
		Ucorner2.first = secondBlock.first;
		Ucorner2.second = i;

		if (i == y - 4) {
			Ucorner2.first = secondBlock.first;
			Ucorner2.second = y;
			Ucorner1.first = firstBlock.first;
			Ucorner1.second = y;

			if (Ucorner1.second == firstBlock.second && Ucorner2.second == secondBlock.second)
				return 1;
			if ((board->getCheck(Ucorner1.first, Ucorner1.second) == _DELETE || 
				(Ucorner1.first == firstBlock.first && Ucorner1.second == firstBlock.second))
				&& board->getCheck(Ucorner2.first, Ucorner2.second) == _DELETE) {
				if (checkIMatching(firstBlock, Ucorner1, isChecking) == 2 && checkIMatching(secondBlock, Ucorner2, isChecking) == 2)
					return 1;
			}
			else break;
		}

		if (board->getCheck(Ucorner1.first, Ucorner1.second) == _DELETE
			&& board->getCheck(Ucorner2.first, Ucorner2.second) == _DELETE) {
			if (checkIMatching(Ucorner1, firstBlock, isChecking) == 2 && checkIMatching(Ucorner2, secondBlock, isChecking) == 2
				&& checkIMatching(Ucorner1, Ucorner2, isChecking) == 2) {
				if (isChecking == false) {
					board->drawLineU(firstBlock, secondBlock, Ucorner1, Ucorner2);
					Sleep(200);
					board->deleteLineU(firstBlock, secondBlock, Ucorner1, Ucorner2);
				}
				return 1;
			}
		}
		else break;
	}
	// U doc duoi
	if (firstBlock.second < secondBlock.second)
		swap(firstBlock, secondBlock);
	for (int i = firstBlock.second + 4; i <= y + size * 4; i += 4) {
		Ucorner1.first = firstBlock.first;
		Ucorner1.second = i;
		Ucorner2.first = secondBlock.first;
		Ucorner2.second = i;

		if (i == y + size * 4) {
			Ucorner2.first = secondBlock.first;
			Ucorner2.second = y + size * 4 - 4;
			Ucorner1.first = firstBlock.first;
			Ucorner1.second = y + size * 4 - 4;

			if (Ucorner1.second == firstBlock.second && Ucorner2.second == secondBlock.second)
				return 1;
			if ((board->getCheck(Ucorner1.first, Ucorner1.second) == _DELETE ||
				(Ucorner1.first == firstBlock.first && Ucorner1.second == firstBlock.second))
				&& board->getCheck(Ucorner2.first, Ucorner2.second) == _DELETE) {
				if (checkIMatching(firstBlock, Ucorner1, isChecking) == 2 && checkIMatching(secondBlock, Ucorner2, isChecking) == 2)
					return 1;
			}
			else break;
		}

		if (board->getCheck(Ucorner1.first, Ucorner1.second) == _DELETE
			&& board->getCheck(Ucorner2.first, Ucorner2.second) == _DELETE) {
			if (checkIMatching(Ucorner1, firstBlock, isChecking) == 2 && checkIMatching(Ucorner2, secondBlock, isChecking) == 2
				&& checkIMatching(Ucorner1, Ucorner2, isChecking) == 2) {
				if (isChecking == false) {
					board->drawLineU(firstBlock, secondBlock, Ucorner1, Ucorner2);
					Sleep(200);
					board->deleteLineU(firstBlock, secondBlock, Ucorner1, Ucorner2);
				}
				return 1;
			}
		}
		else break;
	}
	return 0;
}
bool Game::checkMatching(pair<int, int> firstBlock, pair<int, int> secondBlock, bool isChecking)
{
	if (!checkMatchedPokemons(firstBlock, secondBlock)) {
		if (isChecking == false) {
			Controller::setConsoleColor(BRIGHT_WHITE, BLUE);
			Controller::gotoXY(72, 16);
			cout << "Not Matched";
			score -= 2;
			Controller::setConsoleColor(BRIGHT_WHITE, RED);
			if (score >= 0) {
				Controller::gotoXY(80, 17);
				cout << score << " Point";
			}
			else {
				Controller::gotoXY(80, 17);
				cout << score << " Point";
			}
		}
		return 0;
	}
	if (checkIMatching(firstBlock, secondBlock, isChecking)) {
		if (isChecking == false) {
			Controller::setConsoleColor(BRIGHT_WHITE, BLUE);
			Controller::gotoXY(72, 16);
			cout << "I Matching.";
			score += 1;
			Controller::setConsoleColor(BRIGHT_WHITE, GREEN);
			if (score >= 0) {
				Controller::gotoXY(80, 17);
				cout << score << " Point";
			}
			else {
				Controller::gotoXY(80, 17);
				cout << score << " Point";
			}
		}
		return 1;
	}
	if (checkLMatching(firstBlock, secondBlock, isChecking)) {
		if (isChecking == false) {
			Controller::setConsoleColor(BRIGHT_WHITE, BLUE);
			Controller::gotoXY(72, 16);
			cout << "L Matching.";
			score += 2;
			Controller::setConsoleColor(BRIGHT_WHITE, GREEN);
			if (score >= 0) {
				Controller::gotoXY(80, 17);
				cout << score << " Point";
			}
			else {
				Controller::gotoXY(80, 17);
				cout << score << " Point";
			}
		}
		return 1;
	}
	if (checkZMatching(firstBlock, secondBlock, isChecking)) {
		if (isChecking == false) {
			Controller::setConsoleColor(BRIGHT_WHITE, BLUE);
			Controller::gotoXY(72, 16);
			cout << "Z Matching.";
			score += 3;
			Controller::setConsoleColor(BRIGHT_WHITE, GREEN);
			if (score >= 0) {
				Controller::gotoXY(80, 17);
				cout << score << " Point";
			}
			else {
				Controller::gotoXY(80, 17);
				cout << score << " Point";
			}
		}
		return 1;
	}
	if (checkUMatching(firstBlock, secondBlock, isChecking)) {
		if (isChecking == false) {
			Controller::setConsoleColor(BRIGHT_WHITE, BLUE);
			Controller::gotoXY(72, 16);
			cout << "U Matching.";
			score += 4;
			Controller::setConsoleColor(BRIGHT_WHITE, GREEN);
			if (score >= 0) {
				Controller::gotoXY(80, 17);
				cout << score << " Point";
			}
			else {
				Controller::gotoXY(80, 17);
				cout << score << " Point";
			}
		}
		return 1;
	}
	return 0;
}

void Game::deleteBlock() {
	_lockedBlock = 0;
	bool isChecking = false;
	if (!checkMatching(_lockedBlockPair[0], _lockedBlockPair[1], isChecking)) {
		for (auto block : _lockedBlockPair)
			board->unselectedBlock(block.first, block.second);
		_lockedBlockPair.clear();
		board->selectedBlock(_x, _y, GREEN);
		return;
	}
	for (auto block : _lockedBlockPair)
		board->deleteBlock(block.first, block.second);
	_lockedBlockPair.clear();
	board->selectedBlock(_x, _y, GREEN);
	_remainBlocks -= 2;
	if (_remainBlocks == 0) {
		Controller::setConsoleColor(BRIGHT_WHITE, RED);
		Controller::gotoXY(69, 18);
		cout << "Game Announcement";
		Controller::setConsoleColor(BRIGHT_WHITE, BLUE);
		Controller::gotoXY(67, 19);
		cout << "You have won the game.";
		Controller::setConsoleColor(BRIGHT_WHITE, BLUE);
		Controller::gotoXY(69, 20);
		cout << "CONGRATULATIONS!";
		Controller::gotoXY(70, 21);
		cout << "Your score: " << score;
		Controller::playSound(WIN_SOUND);
		board->unselectedBlock(_x, _y);
		_x = board->getXAt(0, 0);
		_y = board->getYAt(0, 0);
		Controller::gotoXY(_x, _y);
		board->selectedBlock(_x, _y, BRIGHT_WHITE);
		Sleep(7000);
		return;
	}
	isChecking = true;
	if (!isAvailableBlock(isChecking)) {
		Controller::setConsoleColor(BRIGHT_WHITE, RED);
		Controller::gotoXY(69, 18);
		cout << "Game Announcement";
		Controller::gotoXY(64, 19);
		cout << "There are no more ways left!";
		Controller::playSound(EFFECT_SOUND);
		Sleep(1000);
		Controller::gotoXY(62, 21);
		cout << "Auto reset the board. Have fun!";
		Sleep(4000);
		startGame();
	}		
}

bool Game::isAvailableBlock(bool isChecking) {
	int size = board->getSize();
	pair<int, int> firstBlock;
	pair<int, int> secondBlock;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			firstBlock.first = board->getXAt(i, j);
			firstBlock.second = board->getYAt(i, j);
			if (board->getCheck(firstBlock.first, firstBlock.second) == _DELETE) {
				continue;
			}
			for (int m =  i ; m < size; m++) {
				for (int n = 0; n < size; n++) {
					if (i == m && n <= j) continue;
					secondBlock.first = board->getXAt(m, n);
					secondBlock.second = board->getYAt(m, n);
					if(board->getCheck(secondBlock.first, secondBlock.second) == _DELETE)
						continue;
					if (checkMatching(firstBlock, secondBlock, isChecking)) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

void Game::askContinue()
{
	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	Controller::clearConsole();
	Controller::gotoXY(0, 0);
	Controller::setConsoleColor(BRIGHT_WHITE, RED);
	Menu::printLogo();
	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	Menu::printRectangle(34, 13, 35, 8);
	Menu::printRectangle(37, 18, 7, 2);
	Menu::printRectangle(60, 18, 6, 2);
	Controller::gotoXY(36, 16);
	Controller::setConsoleColor(BRIGHT_WHITE, GREEN);
	cout << "Do you want to play another round?";
	string str[2] = { "Yes", "No" };
	int left[] = { 35,40,47,58,63,69 }, word[] = { 32,32,175,174 }, color[] = { BLACK, GREEN }, top = 19;
	bool choice = 1;
	auto print1 = [&]()
	{
		int i = 0;
		while (i < 2)
		{
			Controller::playSound(MOVE_SOUND);
			Controller::setConsoleColor(BRIGHT_WHITE, color[i]);
			Controller::gotoXY(left[choice * 3], top);        putchar(word[i * 2]);
			Controller::gotoXY(left[choice * 3 + 1], top);    cout << str[choice];
			Controller::gotoXY(left[choice * 3 + 2], top);    putchar(word[i * 2 + 1]);
			if (!i++)
				choice = !choice;
		}
	};
	print1();
	while (true)
	{
		int key = Controller::getConsoleInput();
		if ((key == 3 && choice == 1) || (key == 4 && choice == 0))
			print1();
		else if (key == 6)
		{
			if (!choice)
				isPlaying = true;
			else
				isPlaying = false;
			return;
		}
		else
			Controller::playSound(ERROR_SOUND);
	}
}

void Game::moveSuggestion() {
	bool isHelp = true;
	int size = board->getSize();
	pair<int, int> firstBlock;
	pair<int, int> secondBlock;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			firstBlock.first = board->getXAt(i, j);
			firstBlock.second = board->getYAt(i, j);
			if (board->getCheck(firstBlock.first, firstBlock.second) == _DELETE) {
				continue;
			}
			for (int m = i; m < size; m++) {
				for (int n = 0; n < size; n++) {
					if (i == m && n <= j) continue;
					secondBlock.first = board->getXAt(m, n);
					secondBlock.second = board->getYAt(m, n);
					if (board->getCheck(secondBlock.first, secondBlock.second) == _DELETE)
						continue;
					if (checkMatching(firstBlock, secondBlock, isHelp)) {
						if(isHelp) {
							board->selectedBlock(firstBlock.first, firstBlock.second, PURPLE);
							board->selectedBlock(secondBlock.first, secondBlock.second, PURPLE);
							Sleep(200);
							board->unselectedBlock(firstBlock.first, firstBlock.second);
							board->unselectedBlock(secondBlock.first, secondBlock.second);
							score -= 2;
							Controller::setConsoleColor(BRIGHT_WHITE, RED);
							if (score >= 0) {
								Controller::gotoXY(80, 17);
								cout << score << " Point";
							}
							else {
								Controller::gotoXY(80, 17);
								cout << score << " Point";
							}
							return;
						}
					}
				}
			}
		}
	}
}
