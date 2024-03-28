#pragma once
#pragma comment(lib, "Winmm.lib")

#include <windows.h>
#include <conio.h>
#include <vector>
#include <Random>
#include <string>
#include <Mmsystem.h>

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

// MOVEMENT
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESC 27

// SOUNDTRACK
#define MOVE_SOUND 0
#define ENTER_SOUND 1
#define ERROR_SOUND 2
#define WIN_SOUND 4
#define BACKGROUND_SOUND 5
#define EFFECT_SOUND 6
using namespace std;

struct Controller {
	Controller() {};
	~Controller() {};
	static HWND consoleWindow;    //Handle the console window
	static HANDLE consoleOutput;  //Handle the console output
	static void setUpConsole();               //Set up the console window.
	static void gotoXY(int, int);			  //Move the cursor to the specified position (x, y) on the console
	static void setAndCenterWindow();         //Centers and sets the console window's resolution.
	static void setConsoleColor(int, int);    //Sets the console's text and background colors.
	static void hideScrollBars();             //Hide the console's scroll bars.
	static void setConsoleTitle();            //Set the console window's title.
	static void disableMaximize();            //Disable maximizing the console window
	static void showCursor(bool);             //Show or hide the console cursor
	static void setFontInfo();                //Set the console's font information.
	static void clearConsole();               //Clear the console screen.
	static void disableMouseInput();          //Disable mouse
	static int getConsoleInput();             //Get input from keyboard
	static void playSound(int);               //Play sound based on the provided parameter.
}; 

int getRandomInt(int begin, int end);         //Get random interger (to print animation)

HWND Controller::consoleWindow = GetConsoleWindow(); //https://learn.microsoft.com/en-us/windows/console/getconsolewindow
HANDLE Controller::consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE); //https://learn.microsoft.com/en-us/windows/console/getstdhandle

void Controller::setUpConsole()
{
	setFontInfo();
	setAndCenterWindow();
	disableMaximize();
	setConsoleTitle();
	hideScrollBars();
	showCursor(false); //hide the console cursor
	disableMouseInput();
}

void Controller::gotoXY(int pX, int pY) //setting the cursor position to the coordinates specified by pX and pY
{
	SetConsoleCursorPosition(consoleOutput, COORD{ (short)pX, (short)pY }); //https://stackoverflow.com/questions/53560743/c-only-last-call-of-setconsolecursorposition-is-working
}

void Controller::setAndCenterWindow()
{
	RECT rectClient, rectWindow; //store the dimensions of the console window
	GetClientRect(consoleWindow, &rectClient), ////retrieve the dimensions https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getclientrect
		GetWindowRect(consoleWindow, &rectWindow); //https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getwindowrect
	int width = 1100;
	int height = 768;
	int posX = (GetSystemMetrics(SM_CXSCREEN) - width) / 2, //https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getsystemmetrics
		posY = (GetSystemMetrics(SM_CYSCREEN) - height) / 2; //Calculates the desired window position
	MoveWindow(consoleWindow, posX, posY, width, height, TRUE); //move and resize the console window to the specified position and dimensions https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-movewindow
}

void Controller::setConsoleColor(int background, int text) 
{
	SetConsoleTextAttribute(consoleOutput, background * 16 + text); //https://cplusplus.com/forum/beginner/58920/
}

void Controller::hideScrollBars() 
{
	ShowScrollBar(consoleWindow, SB_BOTH, 0); //https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-showscrollbar
}

int wchar_to_char(const wchar_t* wstr, char* buffer, int buf_size) //convert wide character strings to multibyte character strings
{
    return WideCharToMultiByte(CP_ACP, 0, wstr, -1, buffer, buf_size, NULL, NULL); //https://learn.microsoft.com/en-us/windows/win32/api/stringapiset/nf-stringapiset-widechartomultibyte
}

void Controller::setConsoleTitle()
{

	char title[20];
	wchar_to_char(L"\u0050\u0049\u004b\u0041\u0043\u0048\u0055", title, sizeof(title)); //PIKACHU
	SetConsoleTitle(title); //https://learn.microsoft.com/vi-vn/windows/console/setconsoletitle
}

void Controller::disableMaximize()
{
	SetWindowLong(consoleWindow, GWL_STYLE,
		GetWindowLong(consoleWindow, GWL_STYLE) & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME)); //https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setwindowlonga
}

void Controller::showCursor(bool show) // show = 0 in this project
{
	CONSOLE_CURSOR_INFO info = { 1, show };
	SetConsoleCursorInfo(consoleOutput, &info); //https://learn.microsoft.com/en-us/windows/console/setconsolecursorinfo
}

void Controller::setFontInfo()
{
	CONSOLE_FONT_INFOEX info;	//Declare a variable info of type CONSOLE_FONT_INFOEX.
	info.cbSize = sizeof(info);		//Set the cbSize member of info to the size of the structure info
	GetCurrentConsoleFontEx(consoleOutput, FALSE, &info);	//Retrieve the current font information of the console window and store in "info"
	info.dwFontSize.X = 12;		//Set the width of the font size to 12 pixels.
	info.dwFontSize.Y = 24;		//Set the height of the font size to 24 pixels.
	wcscpy_s(info.FaceName, L"Consolas"); //Copy the string "Consolas" to the FaceName member of the info structure
	SetCurrentConsoleFontEx(consoleOutput, FALSE, &info); //https://learn.microsoft.com/en-us/windows/console/setcurrentconsolefontex
}

void Controller::clearConsole()
{
	system("cls"); //https://cplusplus.com/forum/beginner/46492/
}

void Controller::disableMouseInput()
{
	DWORD prev_mode; // store the previous console input mode in "prev_mode
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE); //Retrieve the handle to the standard input device 
	GetConsoleMode(hInput, &prev_mode); // retrieve the current console input mode and stores it in prev_mode
	SetConsoleMode(hInput, prev_mode & ~ENABLE_QUICK_EDIT_MODE); //disable the quick edit mode for the console input mode stored in prev_mode
}

int Controller::getConsoleInput()
{
	int c = _getch(); //  read a single character from the console https://learn.microsoft.com/vi-vn/cpp/c-runtime-library/reference/getch-getwch?view=msvc-150
	if (c == 0 || c == 224)
	{
		switch (_getch())
		{
		case KEY_UP:				
			return 2;
		case KEY_LEFT:				
			return 3;
		case KEY_RIGHT:				
			return 4;
		case KEY_DOWN:				
			return 5;
		default:		// other character
			return 0;
		}
	}
	else
	{
		if (c == KEY_ESC)                  //esc
			return 1;
		else if (c == 87 || c == 119) //W, w
			return 2; // same as KEY_UP
		else if (c == 65 || c == 97)  //A, a
			return 3; // same as KEY_LEFT
		else if (c == 68 || c == 100) //D, d
			return 4; // same as KEY_RIGHT
		else if (c == 83 || c == 115) //S, s
			return 5; // same as KEY_DOWN
		else if (c == 13)             //Enter
			return 6;
		else if (c == 72 || c == 104) //H, h
			return 7;
		else if (c == 77 || c == 109) // M, m
			return 8;
		else
			return 0;             // other character
	}
}

void Controller::playSound(int i)
{
	static vector<const wchar_t*> soundFile{L"move.wav", L"enter.wav", L"error.wav", L"placed.wav", L"win.wav",  L"background.wav", L"effect.wav" }; // vector store names of the sound files
	PlaySoundW(soundFile[i], NULL, SND_FILENAME | SND_ASYNC); //play the sound with index i, allow the program to continue execution without waiting for the sound to finish playing
}

int getRandomInt(int begin, int end)
{
	static random_device rd;
	static mt19937 mt(rd()); //random number engine based on the Mersenne Twister algorithm https://www.geeksforgeeks.org/stdmt19937-class-in-cpp/
	uniform_int_distribution<int> dist(begin, end); //generates random integers in the range [begin, end]
	return dist(mt);
}
