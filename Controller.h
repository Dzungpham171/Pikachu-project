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
	static HWND consoleWindow;    //Con trỏ xử lí cửa sổ console
	static HANDLE consoleOutput;  //Con trỏ xử lí output console
	static void setUpConsole();               //Thiết lập cửa sổ console
	static void gotoXY(int, int);			  //Di chuyển con trỏ đến vị trí x,y
	static void setAndCenterWindow();         //Căn giữa và thiết lập độ phân giải màn hình console
	static void setConsoleColor(int, int);    //Thiết lập màu chữ và và màu nền
	static void hideScrollBars();             //Ẩn thanh cuộn
	static void setConsoleTitle();            //Cài đặt tiêu đề console
	static void disableMaximize();            //Vô hiệu hóa phóng to màn hình
	static void showCursor(bool);             //Ẩn hoặc hiện con trỏ
	static void setFontInfo();                //Cài đặt font chữ
	static void clearConsole();               //Xóa màn hình console
	static void disableMouseInput();          //Vô hiệu hóa chuột trong console
	static int getConsoleInput();             //Lấy lệnh từ bàn phím
	static void playSound(int);               //Phát âm thanh
}; 

int getRandomInt(int begin, int end);         //Hàm lấy số nguyên ngẫu nhiên

HWND Controller::consoleWindow = GetConsoleWindow();
HANDLE Controller::consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

void Controller::setUpConsole()
{
	setFontInfo();
	setAndCenterWindow();
	disableMaximize();
	setConsoleTitle();
	hideScrollBars();
	showCursor(false);
	disableMouseInput();
}

void Controller::gotoXY(int pX, int pY)
{
	SetConsoleCursorPosition(consoleOutput, COORD{ (short)pX, (short)pY });
}

void Controller::setAndCenterWindow()
{
	RECT rectClient, rectWindow;
	GetClientRect(consoleWindow, &rectClient), GetWindowRect(consoleWindow, &rectWindow);
	int width = 1100;
	int height = 768;
	int posX = (GetSystemMetrics(SM_CXSCREEN) - width) / 2,
		posY = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;
	MoveWindow(consoleWindow, posX, posY, width, height, TRUE);
}

void Controller::setConsoleColor(int background, int text)
{
	SetConsoleTextAttribute(consoleOutput, background * 16 + text);
}

void Controller::hideScrollBars()
{
	ShowScrollBar(consoleWindow, SB_BOTH, 0);
}

int wchar_to_char(const wchar_t* wstr, char* buffer, int buf_size) 
{
    return WideCharToMultiByte(CP_ACP, 0, wstr, -1, buffer, buf_size, NULL, NULL);
}

void Controller::setConsoleTitle()
{

	SetConsoleTitleW(L"\u0050\u0049\u004b\u0041\u0043\u0048\u0055"); // PIKACHU
}

void Controller::disableMaximize()
{
	SetWindowLong(consoleWindow, GWL_STYLE,
		GetWindowLong(consoleWindow, GWL_STYLE) & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME));
}

void Controller::showCursor(bool show)
{
	CONSOLE_CURSOR_INFO info = { 1, show };
	SetConsoleCursorInfo(consoleOutput, &info);
}

void Controller::setFontInfo()
{
	// 12 - 24
	CONSOLE_FONT_INFOEX info;
	info.cbSize = sizeof(info);
	GetCurrentConsoleFontEx(consoleOutput, FALSE, &info);
	info.dwFontSize.X = 12;
	info.dwFontSize.Y = 24;
	wcscpy_s(info.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(consoleOutput, FALSE, &info);
}

void Controller::clearConsole()
{
	system("cls");
}

void Controller::disableMouseInput()
{
	DWORD prev_mode;
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(hInput, &prev_mode);
	SetConsoleMode(hInput, prev_mode & ~ENABLE_QUICK_EDIT_MODE);
}

int Controller::getConsoleInput()
{
	int c = _getch();
	// Arrow key
	if (c == 0 || c == 224)
	{
		switch (_getch())
		{
		case KEY_UP:				//lên
			return 2;
		case KEY_LEFT:				//trái
			return 3;
		case KEY_RIGHT:				//phải
			return 4;
		case KEY_DOWN:				//xuống
			return 5;
		default:				//nút khác
			return 0;
		}
	}
	else
	{
		if (c == KEY_ESC)                  //esc
			return 1;
		else if (c == 87 || c == 119) //W, w
			return 2;
		else if (c == 65 || c == 97)  //A, a
			return 3;
		else if (c == 68 || c == 100) //D, d
			return 4;
		else if (c == 83 || c == 115) //S, s
			return 5;
		else if (c == 13)             //Enter
			return 6;
		else if (c == 72 || c == 104) //H, h
			return 7;
		else if (c == 77 || c == 109) // M, m
			return 8;
		else
			return 0;                 //nút khác
	}
}

void Controller::playSound(int i)
{
	static vector<const wchar_t*> soundFile{L"move.wav", L"enter.wav", L"error.wav", L"placed.wav", L"win.wav",  L"background.wav", L"effect.wav" };
	PlaySoundW(soundFile[i], NULL, SND_FILENAME | SND_ASYNC);
}

int getRandomInt(int begin, int end)
{
	static random_device rd;
	static mt19937 mt(rd());
	uniform_int_distribution<int> dist(0, end);
	return dist(mt);
}