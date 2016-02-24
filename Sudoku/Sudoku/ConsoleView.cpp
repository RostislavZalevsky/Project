#include "ConsoleView.h"

////void main() {
////	SetColor(1, 3);
////	GotoXY(5, 5);
////	cout << "*";
////	_getch();
////}

Console::Console()
{
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Console::SetColor(int text, int background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

void Console::GotoXY(int X, int Y)
{
	COORD coord = { X, Y };
	SetConsoleCursorPosition(hStdOut, coord);
}

Console::~Console()
{
}
