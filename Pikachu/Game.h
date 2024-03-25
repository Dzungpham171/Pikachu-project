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
	static bool exitGame;									//Cờ thoát game
	static int current_option;								//Lựa chọn hiện tại
	const static string options[8];							//Tên các lựa chọn
	static void mainScreen();								//Màn hình chính
	static void mainMenu();									//Menu
	static void playMenu();									//Menu play
	static void leaderBoard();								//Màn hình load file leaderboard
	static void helpScreen();								//Màn hình hướng dẫn
	static void exitScreen();								//Màn hình thoát
	static void playEasy();									//Chế độ easy
	static void playMedium();								//Chế độ medium
	static void printLogo();								//In ra logo
	static void goBack() {}									//Trở về menu
	static void printOptionsBoard();						//In ra các bảng lựa chọn
	static void printAnimation();							//In hiệu ứng mở đầu
	static void printRectangle(int, int, int, int);			//Vẽ hình chữ nhật
	static void changeOption(bool, bool);					//Thay đổi lựa chọn
};

struct Player {
	string playerName;
	string playerID;
	string className;
	int score;
	string mode;
};

int Menu::current_option;
const string Menu::options[8] = { "Play", "LeaderBoard", "Help", "Exit", "Easy", "  Medium   ", "Back", "Exit"};

void Menu::mainScreen()
{
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
	Controller::playSound(BACKGROUND_SOUND);
	printAnimation();
	bool loadMenu = 1;
	while (true)
	{
		if (loadMenu)
			mainMenu();
		switch (Controller::getConsoleInput())
		{
		case 2:
			changeOption(0, 1);
			loadMenu = 0;
			break;
		case 5:
			changeOption(1, 1);
			loadMenu = 0;
			break;
		case 6:
			if (current_option == 0)
				loadMenu = 0;
			else
				loadMenu = 1;
			function_map[options[current_option]]();
			break;
		default:
			Controller::playSound(ERROR_SOUND);
			loadMenu = 0;
		}
	}

	Controller::clearConsole();
}

void Menu::printLogo()
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
	cout << logo;
	Controller::gotoXY(38, 0);
	Controller::setConsoleColor(BRIGHT_WHITE, BLUE);
	cout << "Tran Tung Lam - Le Minh";
	Controller::gotoXY(40, 1);
	cout << "21127337 - 21127165";
	Controller::gotoXY(38, 8);
	Controller::setConsoleColor(BRIGHT_WHITE, GREEN);
	cout << R"(
  _____  _  _  ___   __  __    _  _____  ___  _  _  ___  _  _   ___    ___    _    __  __  ___ 
 |_   _|| || || __| |  \/  |  /_\|_   _|/ __|| || ||_ _|| \| | / __|  / __|  /_\  |  \/  || __|
   | |  | __ || _|  | |\/| | / _ \ | | | (__ | __ | | | | .` || (_ | | (_ | / _ \ | |\/| || _| 
   |_|  |_||_||___| |_|  |_|/_/ \_\|_|  \___||_||_||___||_|\_| \___|  \___|/_/ \_\|_|  |_||___|
	)";
}

void Menu::printOptionsBoard()
{
	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	int left = 44; //48
	int top = 20;
	Controller::gotoXY(left, top);
	putchar(201);
	for (int i = 1; i < 12; i++)
	{
		putchar(205);
	}
	putchar(187);


	for (int i = 1; i < 8; i++)
	{
		Controller::gotoXY(left, top + i);
		if (i % 2 != 0)
		{
			putchar(186);
			Controller::gotoXY(left + 12, top + i);
			putchar(186);
		}
		else
		{
			putchar(199);
			for (int i = 1; i < 12; i++)
			{
				putchar(196);
			}
			putchar(182);
		}
	}
	Controller::gotoXY(left, top + 8);
	putchar(200);
	for (int i = 1; i < 12; i++)
	{
		putchar(205);
	}
	putchar(188);
}

void Menu::printAnimation()
{
	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	Controller::clearConsole();
	char symbolpos[] = { 5,0,19,0,33,0,47,0,61,0,75,0,89,0,0,103,5,13,19,
							   13,33,13,47,13,61,13,75,13,89,13,13,103,13,18,26,18,40,18,
							   54,18,68,18,82,18,18,96,5,24,19,24,33,24,47,24,61,24,75,24,
							   89,24,24,103,12,30,26,30,40,30,54,30,68,30,82,30,96,30 };
	int n = (sizeof(symbolpos) / sizeof(symbolpos[0])) / 2;
	bool turn = 0;
	unsigned char symbol[] = { 4,15 };

	int color[] = { LIGHT_AQUA, AQUA, LIGHT_BLUE, BLUE, LIGHT_PURPLE, PURPLE };
	int colorcount = 0;
	int loop = 10;
	while (loop--)
	{
		for (int i = 0; i < n; i += 2)
		{
			Controller::setConsoleColor(BRIGHT_WHITE, getRandomInt(0, 15));
			Controller::gotoXY(symbolpos[i * 2], symbolpos[i * 2 + 1]);
			putchar(symbol[turn]);
		}
		for (int i = 1; i < n; i += 2)
		{
			Controller::setConsoleColor(BRIGHT_WHITE, getRandomInt(0, 15));
			Controller::gotoXY(symbolpos[i * 2], symbolpos[i * 2 + 1]);
			putchar(symbol[!turn]);
		}
		Controller::gotoXY(0, 0);
		printLogo();
		colorcount++;
		turn = !turn;
		Sleep(250);
	}
}

void Menu::changeOption(bool direction, bool flag) //0: lên, 1: xuống
{
	int top = 21;
	if ((direction == 0 && (current_option == 4 || current_option == 0))
		|| (direction == 1 && (current_option == 3 || current_option == 7)))
	{
		Controller::playSound(ERROR_SOUND);
		return;
	}
	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	Controller::gotoXY(50 - (int)options[current_option].length() / 2, top + current_option % 4 * 2);
	cout << options[current_option];
	if (flag)
	{
		Controller::gotoXY(40, top + current_option % 4 * 2);
		putchar(32);
		Controller::gotoXY(60, top + current_option % 4 * 2);
		putchar(32);
	}
	(direction == 1) ? current_option++ : current_option--;
	if (flag)
	{
		Controller::playSound(MOVE_SOUND);
		Controller::setConsoleColor(BRIGHT_WHITE, RED);
		Controller::gotoXY(40, top + current_option % 4 * 2);
		putchar(175);
		Controller::gotoXY(50 - (int)options[current_option].length() / 2, top + current_option % 4 * 2);
		cout << options[current_option];
		Controller::gotoXY(60, top + current_option % 4 * 2);
		putchar(174);
	}
}

void Menu::mainMenu()
{
	Controller::setConsoleColor(BRIGHT_WHITE, RED);
	Controller::clearConsole();
	printLogo();
	printOptionsBoard();
	current_option = 3;
	changeOption(0, 0);
	changeOption(0, 0);
	changeOption(0, 1);
}

void Menu::playMenu()
{
	current_option = 7;
	changeOption(0, 0);
	changeOption(0, 0);
	changeOption(0, 1);
}

void Menu::helpScreen()
{
	Controller::showCursor(false);
	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	Controller::clearConsole();
	int left = 5, top = 2, width = 85, height = 23;
	int line1 = 6, line2 = 19, line3 = 20, line4 = 15;
	printRectangle(left, top, width, height);
	Controller::gotoXY(left + 1, line1);
	for (int i = 0; i < width; i++)
	{
		putchar(196);
	}
	Controller::gotoXY(left + 1, line2);
	for (int i = 0; i < width; i++)
	{
		putchar(196);
	}
	Controller::gotoXY(left + 1, line4);
	for (int i = 0; i < width; i++)
	{
		putchar(196);
	}
	for (int i = 1; i < height; i++)
	{
		Controller::gotoXY(line3, top + i);
		putchar(179);
	}
	Controller::gotoXY(line3, line1);
	putchar(197);
	Controller::gotoXY(line3, line2);
	putchar(197);

	Controller::setConsoleColor(BRIGHT_WHITE, BLUE);
	Controller::gotoXY(left + 3, top + 2);
	cout << "Moves:";
	Controller::gotoXY(left + 20, top + 1);
	putchar(249); cout << "Up:    W, up arrow";
	Controller::gotoXY(left + 52, top + 1);
	putchar(249); cout << "Down:  S, down arrow";
	Controller::gotoXY(left + 20, top + 3);
	putchar(249); cout << "Left:  A, left arrow";
	Controller::gotoXY(left + 52, top + 3);
	putchar(249); cout << "Right: D, right arrow";


	Controller::gotoXY(left + 3, top + 8);
	cout << "Rules:";
	Controller::gotoXY(left + 17, top + 5);
	int left1 = left + 17;
	putchar(249); cout << " The Matching Game (commonly known as the Pikachu Puzzle Game)";
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

	Controller::gotoXY(left + 3, top + 15);
	cout << "Scoring:";
	Controller::setConsoleColor(BRIGHT_WHITE, GREEN);
	Controller::gotoXY(left1 + 10, top + 14);
	putchar(249); cout << " I Matching: +1 BTC";
	Controller::setConsoleColor(BRIGHT_WHITE, GREEN);
	Controller::gotoXY(left1 + 40, top + 14);
	putchar(249); cout << " L Matching: +2 BTC";
	Controller::setConsoleColor(BRIGHT_WHITE, GREEN);
	Controller::gotoXY(left1 + 10, top + 15);
	putchar(249); cout << " Z Matching: +3 BTC";
	Controller::gotoXY(left1 + 40, top + 15);
	putchar(249); cout << " U Matching: +4 BTC";
	Controller::setConsoleColor(BRIGHT_WHITE, RED);
	Controller::gotoXY(left1 + 10, top + 16);
	putchar(249); cout << " Not Matched: -2 BTC";
	Controller::setConsoleColor(BRIGHT_WHITE, RED);
	Controller::gotoXY(left1 + 40, top + 16);
	putchar(249); cout << " Move suggestion: -2 BTC";

	Controller::setConsoleColor(BRIGHT_WHITE, BLUE);
	Controller::gotoXY(left + 3, top + 20);
	cout << "Developers:";
	Controller::gotoXY(left + 31, top + 19);
	cout << "Dev 1: Tran Tung Lam (21127337)";
	Controller::gotoXY(left + 31, top + 21);
	cout << "Dev 2: Le Minh (21127645)";

	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	printRectangle(45, 27, 8, 2);
	Controller::setConsoleColor(BRIGHT_WHITE, RED);
	Controller::gotoXY(43, 28);
	putchar(175);
	Controller::gotoXY(48, 28);
	cout << "Back";
	Controller::gotoXY(56, 28);
	putchar(174);
	while (Controller::getConsoleInput() != 6)
	{
		Controller::playSound(ERROR_SOUND);
	}
}

void Menu::printRectangle(int left, int top, int width, int height)
{
	Controller::gotoXY(left, top);
	putchar(218);
	for (int i = 0; i < width; i++)
		putchar(196);
	putchar(191);

	int i = 0;
	for (; i < height; i++)
	{
		Controller::gotoXY(left, top + i + 1);
		putchar(179);
		Controller::gotoXY(left + width + 1, top + i + 1);
		putchar(179);
	}

	Controller::gotoXY(left, top + i);
	putchar(192);
	for (i = 0; i < width; i++)
		putchar(196);
	putchar(217);
}

void Menu::exitScreen()
{
	Controller::showCursor(false);
	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	Controller::clearConsole();
	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	Menu::printRectangle(34, 13, 35, 8);
	Menu::printRectangle(37, 18, 7, 2);
	Menu::printRectangle(60, 18, 6, 2);
	Controller::setConsoleColor(BRIGHT_WHITE, RED);
	Controller::gotoXY(0, 0);
	printLogo();
	Controller::gotoXY(42, 16);
	cout << "Do you want to exit?";
	string str[2] = { "Yes", "No" };
	int left[] = { 35,40,47,58,63,69 }, word[] = { 32,32,175,174 }, color[] = { BLACK, RED }, top = 19;
	bool choice = 0;
	bool loop = 1;
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
	while (loop)
	{
		int key = Controller::getConsoleInput();
		if ((key == 3 && choice == 1) || (key == 4 && choice == 0))
		{
			print1();
		}
		else if (key == 6)
		{
			if (!choice)
			{
				Controller::setConsoleColor(BLACK, BRIGHT_WHITE);
				Controller::clearConsole();
				exit(0);
			}
			return;
		}
		else
		{
			Controller::playSound(ERROR_SOUND);
		}
	}
}


void Menu::leaderBoard()
{
	current_option = 0;
	Controller::clearConsole();
	Player p[100];
	Controller::setConsoleColor(BRIGHT_WHITE, RED);
	cout << R"(
	  _      ______          _____  ______ _____  ____   ____          _____  _____  
	 | |    |  ____|   /\   |  __ \|  ____|  __ \|  _ \ / __ \   /\   |  __ \|  __ \ 
	 | |    | |__     /  \  | |  | | |__  | |__) | |_) | |  | | /  \  | |__) | |  | |
	 | |    |  __|   / /\ \ | |  | |  __| |  _  /|  _ <| |  | |/ /\ \ |  _  /| |  | |
	 | |____| |____ / ____ \| |__| | |____| | \ \| |_) | |__| / ____ \| | \ \| |__| |
	 |______|______/_/    \_\_____/|______|_|  \_\____/ \____/_/    \_\_|  \_\_____/                                                                 
	)";
	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	printRectangle(5, 8, 85, 17);

	Controller::setConsoleColor(BRIGHT_WHITE, BLUE);
	Controller::gotoXY(8, 9);
	cout << "STT";
	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	for (int i = 1; i < 17; i++)
	{
		Controller::gotoXY(13, 8 + i);
		putchar(179);
	}
	for (int i = 6; i < 13; i++)
	{
		Controller::gotoXY(i, 10);
		putchar(196);
	}
	Controller::setConsoleColor(BRIGHT_WHITE, BLUE);
	Controller::gotoXY(18, 9);
	cout << "Name";
	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	for (int i = 1; i < 17; i++)
	{
		Controller::gotoXY(30, 8 + i);
		putchar(179);
	}
	for (int i = 14; i < 30; i++)
	{
		Controller::gotoXY(i, 10);
		putchar(196);
	}
	Controller::setConsoleColor(BRIGHT_WHITE, BLUE);
	Controller::gotoXY(36, 9);
	cout << "ID";
	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	for (int i = 1; i < 17; i++)
	{
		Controller::gotoXY(45, 8 + i);
		putchar(179);
	}
	for (int i = 31; i < 45; i++)
	{
		Controller::gotoXY(i, 10);
		putchar(196);
	}
	Controller::setConsoleColor(BRIGHT_WHITE, BLUE);
	Controller::gotoXY(52, 9);
	cout << "Class";
	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	for (int i = 1; i < 17; i++)
	{
		Controller::gotoXY(62, 8 + i);
		putchar(179);
	}
	for (int i = 46; i < 62; i++)
	{
		Controller::gotoXY(i, 10);
		putchar(196);
	}
	Controller::setConsoleColor(BRIGHT_WHITE, BLUE);
	Controller::gotoXY(68, 9);
	cout << "Mode";
	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	for (int i = 1; i < 17; i++)
	{
		Controller::gotoXY(78, 8 + i);
		putchar(179);
	}
	for (int i = 63; i < 78; i++)
	{
		Controller::gotoXY(i, 10);
		putchar(196);
	}

	Controller::setConsoleColor(BRIGHT_WHITE, BLUE);
	Controller::gotoXY(82, 9);
	cout << "Score";
	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	for (int i = 79; i < 91; i++)
	{
		Controller::gotoXY(i, 10);
		putchar(196);
	}
	int y = 11;
	int lines = 8;
	int n = 0;
	string tmp;
	fstream fs("rank\\leaderboard.txt", ios::in);

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
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (p[j].score > p[i].score) {
				swap(p[i], p[j]);
			}
		}
	}
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

	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	printRectangle(45, 27, 8, 2);
	Controller::setConsoleColor(BRIGHT_WHITE, RED);
	Controller::gotoXY(43, 28);
	putchar(175);
	Controller::gotoXY(48, 28);
	cout << "Back";
	Controller::gotoXY(56, 28);
	putchar(174);
	while (Controller::getConsoleInput() != 6)
	{
		Controller::playSound(ERROR_SOUND);
	}
}

struct Game {
	BoardView* board;				// Create new board
	char playerName[15] = "", playerID[9] = "", className[8] = "", mode[8] = "";
	int _mode;
	int _x, _y;
	bool isPlaying;
	int _lockedBlock;
	int _remainBlocks;
	int score;

	vector<pair<int, int>> _lockedBlockPair; //First: row - Second: column

	bool checkMatchedPokemons(pair<int, int>, pair<int, int>);
	int checkIMatching(pair<int, int>, pair<int, int>, bool);
	bool checkLMatching(pair<int, int>, pair<int, int>, bool);
	bool checkZMatching(pair<int, int>, pair<int, int>, bool);
	bool checkUMatching(pair<int, int>, pair<int, int>, bool);
	bool checkMatching(pair<int, int>, pair<int, int>, bool);

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
	void deleteBlock();
	bool isAvailableBlock(bool);

	void askContinue();
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
				cout << score << " BTC ";
			}
			else {
				Controller::gotoXY(80, 17);
				cout << score << " BTC";
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
				cout << score << " BTC ";
			}
			else {
				Controller::gotoXY(80, 17);
				cout << score << " BTC";
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
				cout << score << " BTC ";
			}
			else {
				Controller::gotoXY(80, 17);
				cout << score << " BTC";
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
				cout << score << " BTC ";
			}
			else {
				Controller::gotoXY(80, 17);
				cout << score << " BTC";
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
				cout << score << " BTC ";
			}
			else {
				Controller::gotoXY(80, 17);
				cout << score << " BTC";
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
								cout << score << " BTC ";
							}
							else {
								Controller::gotoXY(80, 17);
								cout << score << " BTC";
							}
							return;
						}
					}
				}
			}
		}
	}
}