#pragma once

#define _NORMAL 0
#define _LOCK 1
#define _DELETE -1

struct Point
{
	int _x = 0;					//Vị trí x
	int _y = 0;					//Vị trí y
	int _check = 0;			//1: LOCK, 0: NORMAL, -1: DELETE
	char _pokemon = ' ';
	Point();			//Phương thức tạo lập
	Point(int, int, int, char);	//Phương thức tạo lập

	int getX();			//Lấy vị trí x
	int getY();			//Lấy vị trí y
	int getCheck();		//Lấy quân cờ

	void setX(int);		//Gán vị trí x
	void setY(int);		//Gán vị trí y
	void setCheck(int);	//Gán quân cờ

	char getPokemons();
	void setPokemons(char);

};

Point::Point()
{
	_x = _y = _check = 0;
}

Point::Point(int x, int y, int check, char pokemon)
{
	_x = x; _y = y;
	_check = check;
	_pokemon = pokemon;
}

int Point::getX()
{
	return _x;
}

int Point::getY()
{
	return _y;
}

int Point::getCheck()
{
	return _check;
}

void Point::setX(int x)
{
	_x = x;
}

void Point::setY(int y)
{
	_y = y;
}

void Point::setCheck(int check)
{
	_check = check;
}

char Point::getPokemons()
{
	return _pokemon;
}

void Point::setPokemons(char pokemon)
{
	_pokemon = pokemon;
}