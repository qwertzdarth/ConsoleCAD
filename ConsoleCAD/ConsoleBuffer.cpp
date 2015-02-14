#include "ConsoleBuffer.h"
#include <vector>
#include <Windows.h>
#include <iostream>

using namespace std;

ConsoleBuffer::ConsoleBuffer(unsigned int x, unsigned int y) {
	ColorChar standard;
	x += 2;
	standard.c = ' ';
	standard.color = WHITE;
	this->matrix = new vector<vector<ColorChar>>(y, vector<ColorChar>(x, standard));
	//this->setSize(x+1, y+1);
	this->setSize(x, y);
	size_x = x;
	size_y = y;
}

ConsoleBuffer::~ConsoleBuffer() {
	this->matrix->clear();
}

void ConsoleBuffer::clrscr() {
	system("cls");
}

void ConsoleBuffer::setcolor(unsigned short color)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon, color);
}

void ConsoleBuffer::set(unsigned int x, unsigned int y, ColorChar c) {
	this->get(x,y) = c;
}

ColorChar& ConsoleBuffer::get(unsigned int x,unsigned int y) {
	if (x < this->size_x && y < this->size_y) {
		return (*this->matrix)[y][x];
	}
	else
	{
		ColorChar c;
		return c;
	}
}

void ConsoleBuffer::draw() {
	//this->clrscr();
	/*vector<vector<ColorChar>>* _matrix = this->matrix;
	for (unsigned int _y = 0; _y < this->sizeY(); _y++) {
		for (unsigned int _x = 0; _x < this->sizeX(); _x++) {
			ColorChar& cc = this->get(_x,_y);
			this->setcolor(cc.color);
			printf("%c", cc.c);
		}
		cout << endl;
	}*/
	//this->setcurpos(0, 0);


	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);

	CHAR_INFO* screenBuffer = new CHAR_INFO[sizeX()*sizeY()];
	int i = 0;
	for (unsigned int _y = 0; _y < size_y; _y++) {
		for (unsigned int _x = 0; _x < size_x; _x++) {
			ColorChar& cc = this->get(_x, _y);
			CHAR_INFO temp;
			temp.Attributes = cc.color;
			temp.Char.UnicodeChar = cc.c;
			screenBuffer[i] = temp;
			i++;
		}
	}

	COORD dwBufferSize = { sizeX(), sizeY() };
	COORD dwBufferCoord = { 0, 0 };
	SMALL_RECT rcRegion = { 0, 0, sizeX() - 1, sizeY() - 1 };

	WriteConsoleOutput(hCon, screenBuffer, dwBufferSize, dwBufferCoord, &rcRegion);

	//this->setcurpos(0, 0);
}

unsigned int ConsoleBuffer::sizeY() {
	//return this->matrix->size();
	return size_y;
}

unsigned int ConsoleBuffer::sizeX() {
	//unsigned int minSize = MAXUINT;
	//for (vector<vector<ColorChar>>::size_type _y = 0; _y < this->matrix->size(); _y++) {
	//	unsigned int size = this->matrix->at(_y).size();
	//	minSize = size < minSize ? size : minSize;
	//}
	//return minSize;
	return size_x;
}

void ConsoleBuffer::setcurpos(unsigned int x, unsigned int y) {
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD co;
	co.X = x;
	co.Y = y;
	SetConsoleCursorPosition(hCon, co);
}

void ConsoleBuffer::setSize(unsigned int width, unsigned int height) {
	SMALL_RECT r;
	COORD      c;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE hConOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!GetConsoleScreenBufferInfo(hConOut, &csbi))
		throw runtime_error("You must be attached to a human.");

	r.Left =
		r.Top = 0;
	r.Right = width - 1;
	r.Bottom = height - 1;
	SetConsoleWindowInfo(hConOut, TRUE, &r);

	c.X = width;
	c.Y = height;
	SetConsoleScreenBufferSize(hConOut, c);
}

void ConsoleBuffer::clearbuf() {
	ColorChar c;
	c.c = ' ';
	c.color = WHITE;
	for (unsigned int i = 0; i < this->sizeY(); i++) {
		this->matrix->at(i).assign(this->sizeX(), c);
	}
}