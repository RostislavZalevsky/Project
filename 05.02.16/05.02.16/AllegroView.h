#pragma once
#include "Header.h"

class AllegroView
{
	ALLEGRO_DISPLAY *display;
	ALLEGRO_TIMER *timer;
	ALLEGRO_EVENT_QUEUE *eventQueue;
	ALLEGRO_COLOR backgroundColor;

	ALLEGRO_BITMAP *backgroundImage;
	ALLEGRO_BITMAP *mainAtlas;

	int width;
	int height;

	int fpsTimeout;

public:
	AllegroView();

	void Initialize(int width, int height, int r, int g, int b);

	~AllegroView();
};