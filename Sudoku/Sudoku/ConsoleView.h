#pragma once
#include "Header.h"

class Console {
	HANDLE hConsole;
	HANDLE hStdOut;
public:
	Console();
	void SetColor(int text, int background);
	void GotoXY(int X, int Y);
	~Console();
};
