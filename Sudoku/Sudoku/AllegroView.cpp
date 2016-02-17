#include "AllegroView.h"

AllegroView::AllegroView()
{
	display = nullptr;
	timer = nullptr;
	eventQueue = nullptr;
	backgroundImage = nullptr;
	mainFont = nullptr;
	fpsTimeout = 180;

	done = true;
	draw = true;

	pos_x = 338;
	pos_y = 338;

	Basic = 40;
	Easy = 30;
	Medium = 25;
	Hard = 22;
	Evil = 20;
}

void AllegroView::Initialize(int width, int height, int r, int g, int b, int Sudoku_table[9][9])
{
	if (!al_init()) {
		throw "Allegro initialize error!";
	}

	al_init_image_addon();

	this->width = width;
	this->height = height;

	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++) this->Sudoku_table[j][i] = Sudoku_table[j][i];

	display = al_create_display(width, height);
	if (display == nullptr) {
		throw "Display creation error!";//throw 1;
	}

	if (!al_install_keyboard()) {
		throw "Tnstall keyboard error!";
	}

	timer = al_create_timer(1.0 / fpsTimeout);
	if (timer == nullptr) {
		throw "Timer creation error!";
	}

	eventQueue = al_create_event_queue();
	if (eventQueue == nullptr) {
		throw "Event queue creation error!";
	}

	backgroundImage = al_load_bitmap("Resources/Images/Sud_img.jpg");
	if (backgroundImage == nullptr) {
		throw "Load image error!";
	}

	if (!al_init_font_addon()) {
		throw "Font init error!";
	}
	if (!al_init_ttf_addon()) {
		throw "TTF init error!";
	}

	AddNum();

	mainFont = al_load_font("Resources/Fonts/AdobeFanHeitiStd-Bold.otf", 75, 0);
	//al_set_target_bitmap(al_get_backbuffer(display));
	backgroundColor.r = r;
	backgroundColor.g = g;
	backgroundColor.b = b;
	backgroundColor.a = 0;

	DrawSudoku();//eventQueue = al_create_event_queue();

	al_install_mouse();//mouse
	eventQueue = al_create_event_queue();

	al_register_event_source(eventQueue, al_get_timer_event_source(timer));	//timer		//al_clear_to_color(al_map_rgb(r, g, b));//al_flip_display();//al_rest(5);
	al_register_event_source(eventQueue, al_get_display_event_source(display));//display

	al_register_event_source(eventQueue, al_get_keyboard_event_source());//keyboard
	al_register_event_source(eventQueue, al_get_mouse_event_source());//mouse
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AllegroView::Game(AllegroView * Sudoku)																	////////////////////
{																												////////////////////
	al_start_timer(timer);																						////////////////////
	ALLEGRO_EVENT ev;																							////////////////////
																												////////////////////
	while (done) {																								////////////////////
		al_wait_for_event(eventQueue, &ev);																		////////////////////
																												////////////////////
		if (ev.type == ALLEGRO_EVENT_TIMER && al_is_event_queue_empty(eventQueue)) {							////////////////////
			al_flip_display();																					////////////////////
		}																										////////////////////
		switch (ev.keyboard.keycode) {																			////////////////////
		case ALLEGRO_KEY_ESCAPE:																				////////////////////
			done = false;																						////////////////////
			break;																								////////////////////
		}																										////////////////////
																												////////////////////
		directionKey(ev);																						////////////////////
		directionMouse(ev);																						////////////////////
		directionNKey(ev);																						////////////////////
																												////////////////////
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {															////////////////////
			done = false;																						////////////////////
			break;																								////////////////////
		}																										////////////////////
	}																											////////////////////
}																												////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AllegroView::DrawSudoku()
{
	al_set_target_bitmap(al_get_backbuffer(display));

	al_draw_bitmap(backgroundImage, 0, 0, 0);

	al_init_primitives_addon();//|

	al_draw_filled_rectangle(262.5, 37.5, 487.5, 262.5, al_map_rgba(45, 45, 45, 90));
	al_draw_filled_rectangle(262.5, 487.5, 487.5, 712.5, al_map_rgba(45, 45, 45, 0));
	al_draw_filled_rectangle(37.5, 262.5, 262.5, 487.5, al_map_rgba(45, 45, 45, 0));
	al_draw_filled_rectangle(487.5, 262.5, 712.5, 487.5, al_map_rgba(45, 45, 45, 0));

	for (double line = 37.5; line <= 712.5; line += 75) {
		al_draw_line(36.25, line, 713.75, line, al_map_rgb(0, 128, 255), 2.5);
		al_draw_line(line, 36.25, line, 713.75, al_map_rgb(0, 128, 255), 2.5);
	}
	for (double line = 37.5; line <= 712.5; line += 225) {
		al_draw_line(35, line, 715, line, al_map_rgb(255, 0, 0), 5);
		al_draw_line(line, 35, line, 715, al_map_rgb(255, 0, 0), 5);
	}
	for (int h_t = 1;h_t <= 9;h_t++) {
		for (int w_t = 1;w_t <= 9;w_t++) {
			if (0 != Sudoku_Num[w_t - 1][h_t - 1]) {
				char str[2];
				_itoa_s(Sudoku_Num[w_t - 1][h_t - 1], str, 10);
				al_draw_text(mainFont, al_map_rgb(0, 255, 128), w_t * 75 - 18.75, h_t * 75 - 37.5, 0, str);
			}
		}
	}
}

void AllegroView::DrawRectangle()
{
	for (double i = 37.5; i <= height - 75; i += 75) {
		for (double j = 37.5; j < width - 75; j += 75)
		{
			if (pos_x >= j && pos_x <= j + 75 && pos_y >= i && pos_y <= i + 75) {
				int x1 = pos_x, y1 = pos_y;
				pos_x = j;
				pos_y = i;
				DrawSudoku();	//al_hide_mouse_cursor(display);
				cout << x1 << " " << y1 << endl;
				al_draw_filled_rectangle(pos_x, pos_y, pos_x + 75, pos_y + 75, al_map_rgba(103, 103, 103, 0));
				pos_x = x1;
				pos_y = y1;
				for (int h_t = 1;h_t <= 9;h_t++) {
					for (int w_t = 1;w_t <= 9;w_t++) {
						if (0 != Sudoku_Num[w_t - 1][h_t - 1]) {
							char str[2];
							_itoa_s(Sudoku_Num[w_t - 1][h_t - 1], str, 10);
							al_draw_text(mainFont, al_map_rgb(0, 255, 128), w_t * 75 - 18.75, h_t * 75 - 37.5, 0, str);
						}
					}
				}
			}
		}
	}
}

void AllegroView::SetNum()
{
}

void AllegroView::AddNum()
{
	srand(time(NULL));//number
	for (int x = 0; x < 9; x++)
		for (int y = 0; y < 9; y++)
			Sudoku_Num[x][y] = 0;
	int i = 0; 
	while (i < Basic) {
		int x, y;
		x = rand() % 9;
		y = rand() % 9;
		if (0 == Sudoku_Num[x][y]) {
			Sudoku_Num[x][y] = Sudoku_table[x][y];
			i++;
		}
	}
}

void AllegroView::directionMouse(ALLEGRO_EVENT& ev)
{
	switch (ev.mouse.button) {
	case 1:
		if (37.5 <= ev.mouse.x && 37.5 <= ev.mouse.y && 712.5 >= ev.mouse.x && 712.5 >= ev.mouse.y) {
			pos_x = ev.mouse.x;
			pos_y = ev.mouse.y;
			DrawRectangle();
		}
		break;
	case 2:
		if (ev.mouse.button & 2) {
			DrawSudoku();
			al_flip_display();
		}
		break;
	}
}

void AllegroView::directionKey(ALLEGRO_EVENT& ev)
{
	if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {//key
		switch (ev.keyboard.keycode) {
		case ALLEGRO_KEY_W:
		case ALLEGRO_KEY_UP:
			keys[UP] = true;
			break;
		case ALLEGRO_KEY_S:
		case ALLEGRO_KEY_DOWN:
			keys[DOWN] = true;
			break;
		case ALLEGRO_KEY_D:
		case ALLEGRO_KEY_RIGHT:
			keys[RIGHT] = true;
			break;
		case ALLEGRO_KEY_A:
		case ALLEGRO_KEY_LEFT:
			keys[LEFT] = true;
			break;
		}
	}
	else if (ev.type == ALLEGRO_EVENT_KEY_UP)
	{
		switch (ev.keyboard.keycode)
		{
		case ALLEGRO_KEY_W:
		case ALLEGRO_KEY_UP:
			keys[UP] = false;
			break;
		case ALLEGRO_KEY_S:
		case ALLEGRO_KEY_DOWN:
			keys[DOWN] = false;
			break;
		case ALLEGRO_KEY_D:
		case ALLEGRO_KEY_RIGHT:
			keys[RIGHT] = false;
			break;
		case ALLEGRO_KEY_A:
		case ALLEGRO_KEY_LEFT:
			keys[LEFT] = false;
			break;
		case ALLEGRO_KEY_ESCAPE:
			done = true;
			break;
		}
	}
	else if (ev.type == ALLEGRO_EVENT_TIMER)
	{
		pos_y -= keys[UP] * (540 / fpsTimeout);
		pos_y += keys[DOWN] * (540 / fpsTimeout);
		pos_x -= keys[LEFT] * (540 / fpsTimeout);
		pos_x += keys[RIGHT] * (540 / fpsTimeout);
		if (37.5 < pos_x && 37.5 < pos_y && 712.5 > pos_x && 712.5 > pos_y) {
			DrawSudoku();
			DrawRectangle();
		}
		else {
			if (37.5 > pos_y) pos_y = 712.5;
			if (712.5 < pos_y) pos_y = 37.5;
			if (112.5 > pos_y) pos_x = 637.5;
			if (637.5 < pos_y) pos_x = 112.5;
			DrawSudoku();
			DrawRectangle();
		}
	}
}
void AllegroView::directionNKey(ALLEGRO_EVENT & ev)
{
	switch (ev.keyboard.keycode) {
	case ALLEGRO_KEY_PAD_1:
	case ALLEGRO_KEY_1:
		
		break;
	case ALLEGRO_KEY_PAD_2:
	case ALLEGRO_KEY_2:

		break;
	case ALLEGRO_KEY_PAD_3:
	case ALLEGRO_KEY_3:

		break;
	case ALLEGRO_KEY_PAD_4:
	case ALLEGRO_KEY_4:

		break;
	case ALLEGRO_KEY_PAD_5:
	case ALLEGRO_KEY_5:

		break;
	case ALLEGRO_KEY_PAD_6:
	case ALLEGRO_KEY_6:

		break;
	case ALLEGRO_KEY_PAD_7:
	case ALLEGRO_KEY_7:

		break;
	case ALLEGRO_KEY_PAD_8:
	case ALLEGRO_KEY_8:

		break;
	case ALLEGRO_KEY_PAD_9:
	case ALLEGRO_KEY_9:
		
		break;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AllegroView::~AllegroView()
{
	if (display != nullptr) {
		al_destroy_display(display);
	}

	if (display != nullptr) {
		al_destroy_timer(timer);
	}

	if (eventQueue != nullptr) {
		al_destroy_event_queue(eventQueue);
	}
}