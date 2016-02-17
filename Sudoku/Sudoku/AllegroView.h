#pragma once
#include "AllegroHeader.h"
#include "Header.h"
#include "GameSudoku.h"

class AllegroView
{
	ALLEGRO_DISPLAY *display;
	ALLEGRO_TIMER *timer;
	ALLEGRO_EVENT_QUEUE *eventQueue;
	ALLEGRO_COLOR backgroundColor;
	ALLEGRO_BITMAP *backgroundImage;
	ALLEGRO_FONT *mainFont;
	bool done;//while

	int width;//screen
	int height;
	int fpsTimeout;

	bool draw;//mouse
	int pos_x;
	int pos_y;

	bool keys[4] = { false, false, false, false };//keyboard

	int Sudoku_table[9][9];
	int Sudoku_Num[9][9];

	int Basic;
	int	Easy;
	int	Medium;
	int	Hard;
	int	Evil;
public:
	AllegroView();
	void Initialize(int width, int height, int r, int g, int b, int Sudoku_table[9][9]);
	void Game(AllegroView *Sudoku);


	void DrawSudoku();
	void DrawRectangle();
	void SetNum();

	void AddNum();
	void directionMouse(ALLEGRO_EVENT& ev);
	void directionKey(ALLEGRO_EVENT& ev);
	void directionNKey(ALLEGRO_EVENT& ev);


	~AllegroView();
};

