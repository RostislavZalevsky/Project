#include "AllegroView.h"

AllegroView::AllegroView()
{
	display = nullptr,	timer = nullptr, eventQueue = nullptr, backgroundImage = nullptr, mainFont = nullptr, lifeFont = nullptr, welFont = nullptr, wel1Font = nullptr;
	fpsTimeout = 200;

	draw = done = true;
	pos_x = pos_y = 338;
	Number = 0;
	life = 5;
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
	//////////////////////////////////////////////////////////////////////
	if (!al_install_keyboard()) {
		throw "Tnstall keyboard error!";
	}
	//////////////////////////////////////////////////////////////////////
	timer = al_create_timer(1.0 / fpsTimeout);
	if (timer == nullptr) {
		throw "Timer creation error!";
	}
	//////////////////////////////////////////////////////////////////////
	eventQueue = al_create_event_queue();
	if (eventQueue == nullptr) {
		throw "Event queue creation error!";
	}
	//////////////////////////////////////////////////////////////////////
	backgroundImage = al_load_bitmap("Resources/Images/Sud_img.jpg");
	if (backgroundImage == nullptr) {
		throw "Load image error!";
	}
	//////////////////////////////////////////////////////////////////////
	if (!al_init_font_addon()) {
		throw "Font init error!";
	}
	if (!al_init_ttf_addon()) {
		throw "TTF init error!";
	}

	mainFont = al_load_font("Resources/Fonts/AdobeFanHeitiStd-Bold.otf", 75, 0);
	lifeFont = al_load_font("Resources/Fonts/AdobeFanHeitiStd-Bold.otf", 18.75, 0);
	welFont = al_load_font("Resources/Fonts/HARLOWSI.ttf", 100, 0);
	wel1Font = al_load_font("Resources/Fonts/comicz.ttf", 50, 0);
	//al_set_target_bitmap(al_get_backbuffer(display));
	backgroundColor.r = r, backgroundColor.g = g, backgroundColor.b = b, backgroundColor.a = 0;
	//DrawSudoku();//eventQueue = al_create_event_queue();
	al_install_mouse();//mouse
	eventQueue = al_create_event_queue();

	al_register_event_source(eventQueue, al_get_timer_event_source(timer));	//timer		//al_clear_to_color(al_map_rgb(r, g, b));//al_flip_display();//al_rest(5);///// for( while )
	al_register_event_source(eventQueue, al_get_display_event_source(display));//display
	al_register_event_source(eventQueue, al_get_keyboard_event_source());//keyboard
	al_register_event_source(eventQueue, al_get_mouse_event_source());//mouse
}
void AllegroView::Welcome()
{
	ALLEGRO_EVENT ev;
	bool done1 = true, doneLevel = false;
	pos_x = pos_y = 0;
	while (done1) {
		al_wait_for_event(eventQueue, &ev);
		if (ev.type == ALLEGRO_EVENT_TIMER && al_is_event_queue_empty(eventQueue)) al_flip_display();
		switch (ev.keyboard.keycode) {
		case ALLEGRO_KEY_ESCAPE:
			done1 = false;
			done = false;
			break;
		}
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			done1 = false;
			done = false;
			break;
		}
		al_set_target_bitmap(al_get_backbuffer(display));
		al_draw_bitmap(backgroundImage, 0, 0, 0);

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
			pos_y -= keys[UP] * (600 / fpsTimeout);
			pos_y += keys[DOWN] * (600 / fpsTimeout);
			pos_x -= keys[LEFT] * (600 / fpsTimeout);
			pos_x += keys[RIGHT] * (600 / fpsTimeout);
		}

		if (ev.type == ALLEGRO_EVENT_MOUSE_AXES){
			pos_x = ev.mouse.x;
			pos_y = ev.mouse.y;
		}
		if (175 <= pos_x && 225 <= pos_y && 575 >= pos_x && 450 >= pos_y) {
			al_init_primitives_addon();
			if (175 <= pos_x && 225 <= pos_y && 575 >= pos_x && 300 >= pos_y) {
				al_draw_filled_rounded_rectangle(175, 225, 575, 300, 10, 10, al_map_rgba(100, 100, 100, 0));
			}
			else if (175 <= pos_x && 300 <= pos_y && 575 >= pos_x && 375 >= pos_y) {
				al_draw_filled_rounded_rectangle(175, 300, 575, 375, 10, 10, al_map_rgba(100, 100, 100, 0));
			}
			else if (175 <= pos_x && 375 <= pos_y && 575 >= pos_x && 450 >= pos_y) {
				al_draw_filled_rounded_rectangle(175, 375, 575, 450, 10, 10, al_map_rgba(100, 100, 100, 0));
			}			
		}
		switch (ev.mouse.button) {
		case 1:
			if (175 <= ev.mouse.x && 300 <= ev.mouse.y && 575 >= ev.mouse.x && 375 >= ev.mouse.y) {
				al_draw_filled_rounded_rectangle(175, 300, 575, 375, 10, 10, al_map_rgb(0, 128, 255));
				al_draw_text(welFont, al_map_rgb(255, 255, 255), 375, 75, ALLEGRO_ALIGN_CENTRE, "Welcome!");
				al_draw_text(wel1Font, al_map_rgb(255, 255, 255), 375, 225, ALLEGRO_ALIGN_CENTRE, "Resume Game");
				al_draw_text(wel1Font, al_map_rgb(255, 255, 255), 375, 300, ALLEGRO_ALIGN_CENTRE, "New Game");
				al_draw_text(wel1Font, al_map_rgb(255, 255, 255), 375, 375, ALLEGRO_ALIGN_CENTRE, "Exit Game");
				done1 = false;
				doneLevel = true;
				Sleep(500);
			}
			if (175 <= ev.mouse.x && 375 <= ev.mouse.y && 575 >= ev.mouse.x && 450 >= ev.mouse.y) {
				al_draw_filled_rounded_rectangle(175, 375, 575, 450, 10, 10, al_map_rgb(0, 128, 255));
				al_draw_text(welFont, al_map_rgb(255, 255, 255), 375, 75, ALLEGRO_ALIGN_CENTRE, "Welcome!");
				al_draw_text(wel1Font, al_map_rgb(255, 255, 255), 375, 225, ALLEGRO_ALIGN_CENTRE, "Resume Game");
				al_draw_text(wel1Font, al_map_rgb(255, 255, 255), 375, 300, ALLEGRO_ALIGN_CENTRE, "New Game");
				al_draw_text(wel1Font, al_map_rgb(255, 255, 255), 375, 375, ALLEGRO_ALIGN_CENTRE, "Exit Game");
				done1 = false;
				done = false;
				Sleep(500);
			}
			break;
		}
		al_draw_text(welFont, al_map_rgb(255, 255, 255), 375, 75, ALLEGRO_ALIGN_CENTRE, "Welcome!");
		al_draw_text(wel1Font, al_map_rgb(255, 255, 255), 375, 225, ALLEGRO_ALIGN_CENTRE, "Resume Game");
		al_draw_text(wel1Font, al_map_rgb(255, 255, 255), 375, 300, ALLEGRO_ALIGN_CENTRE, "New Game");
		al_draw_text(wel1Font, al_map_rgb(255, 255, 255), 375, 375, ALLEGRO_ALIGN_CENTRE, "Exit Game");
		al_flip_display();
	}



	/////////////////////////////////////////////////////////////////////////////
	if (doneLevel == true) {
		done1 = true;
		while (done1)
		{
			al_wait_for_event(eventQueue, &ev);
			if (ev.type == ALLEGRO_EVENT_TIMER && al_is_event_queue_empty(eventQueue)) al_flip_display();
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_ESCAPE:
				done1 = false;
				done = false;
				break;
			}
			if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				done1 = false;
				done = false;
				break;
			}
			al_set_target_bitmap(al_get_backbuffer(display));
			al_draw_bitmap(backgroundImage, 0, 0, 0);

			if (ev.type == ALLEGRO_EVENT_MOUSE_AXES) {
				pos_x = ev.mouse.x;
				pos_y = ev.mouse.y;
			}
			if (175 <= pos_x && 225 <= pos_y && 575 >= pos_x && 600 >= pos_y) {
				al_init_primitives_addon();
				if (175 <= pos_x && 225 <= pos_y && 575 >= pos_x && 300 >= pos_y) {
					al_draw_filled_rounded_rectangle(175, 225, 575, 300, 10, 10, al_map_rgba(100, 100, 100, 0));
				}
				else if (175 <= pos_x && 300 <= pos_y && 575 >= pos_x && 375 >= pos_y) {
					al_draw_filled_rounded_rectangle(175, 300, 575, 375, 10, 10, al_map_rgba(100, 100, 100, 0));
				}
				else if (175 <= pos_x && 375 <= pos_y && 575 >= pos_x && 450 >= pos_y) {
					al_draw_filled_rounded_rectangle(175, 375, 575, 450, 10, 10, al_map_rgba(100, 100, 100, 0));
				}
				else if (175 <= pos_x && 450 <= pos_y && 575 >= pos_x && 525 >= pos_y) {
					al_draw_filled_rounded_rectangle(175, 450, 575, 525, 10, 10, al_map_rgba(100, 100, 100, 0));
				}
				else if (175 <= pos_x && 525 <= pos_y && 575 >= pos_x && 600 >= pos_y) {
					al_draw_filled_rounded_rectangle(175, 525, 575, 600, 10, 10, al_map_rgba(100, 100, 100, 0));
				}
			}


			switch (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			case 1:
				if (175 <= ev.mouse.x && 225 <= ev.mouse.y && 575 >= ev.mouse.x && 300 >= ev.mouse.y) {
					al_draw_filled_rounded_rectangle(175, 225, 575, 300, 10, 10, al_map_rgb(0, 128, 255));
					al_draw_text(welFont, al_map_rgb(255, 255, 255), 375, 75, ALLEGRO_ALIGN_CENTRE, "Level");
					al_draw_text(wel1Font, al_map_rgb(255, 255, 255), 375, 225, ALLEGRO_ALIGN_CENTRE, "Basic");
					al_draw_text(wel1Font, al_map_rgb(255, 255, 255), 375, 300, ALLEGRO_ALIGN_CENTRE, "Easy");
					al_draw_text(wel1Font, al_map_rgb(255, 255, 255), 375, 375, ALLEGRO_ALIGN_CENTRE, "Medium");
					al_draw_text(wel1Font, al_map_rgb(255, 255, 255), 375, 450, ALLEGRO_ALIGN_CENTRE, "Hard");
					al_draw_text(wel1Font, al_map_rgb(255, 255, 255), 375, 525, ALLEGRO_ALIGN_CENTRE, "Evil");
					done1 = false;
					this->Level = 40;
					AddNum();
					Sleep(500);
					break;
				}
				if (175 <= ev.mouse.x && 300 <= ev.mouse.y && 575 >= ev.mouse.x && 375 >= ev.mouse.y) {
					al_draw_filled_rounded_rectangle(175, 300, 575, 375, 10, 10, al_map_rgb(0, 128, 255));
					al_draw_text(welFont, al_map_rgb(255, 255, 255), 375, 75, ALLEGRO_ALIGN_CENTRE, "Level");
					al_draw_text(wel1Font, al_map_rgb(255, 255, 255), 375, 225, ALLEGRO_ALIGN_CENTRE, "Basic");
					al_draw_text(wel1Font, al_map_rgb(255, 255, 255), 375, 300, ALLEGRO_ALIGN_CENTRE, "Easy");
					al_draw_text(wel1Font, al_map_rgb(255, 255, 255), 375, 375, ALLEGRO_ALIGN_CENTRE, "Medium");
					al_draw_text(wel1Font, al_map_rgb(255, 255, 255), 375, 450, ALLEGRO_ALIGN_CENTRE, "Hard");
					al_draw_text(wel1Font, al_map_rgb(255, 255, 255), 375, 525, ALLEGRO_ALIGN_CENTRE, "Evil");
					done1 = false;
					this->Level = 30;
					AddNum();
					Sleep(500);
				}
				if (175 <= ev.mouse.x && 375 <= ev.mouse.y && 575 >= ev.mouse.x && 450 >= ev.mouse.y) {
					al_draw_filled_rounded_rectangle(175, 375, 575, 450, 10, 10, al_map_rgb(0, 128, 255));
					al_draw_text(welFont, al_map_rgb(255, 255, 255), 375, 75, ALLEGRO_ALIGN_CENTRE, "Level");
					al_draw_text(wel1Font, al_map_rgb(255, 255, 255), 375, 225, ALLEGRO_ALIGN_CENTRE, "Basic");
					al_draw_text(wel1Font, al_map_rgb(255, 255, 255), 375, 300, ALLEGRO_ALIGN_CENTRE, "Easy");
					al_draw_text(wel1Font, al_map_rgb(255, 255, 255), 375, 375, ALLEGRO_ALIGN_CENTRE, "Medium");
					al_draw_text(wel1Font, al_map_rgb(255, 255, 255), 375, 450, ALLEGRO_ALIGN_CENTRE, "Hard");
					al_draw_text(wel1Font, al_map_rgb(255, 255, 255), 375, 525, ALLEGRO_ALIGN_CENTRE, "Evil");
					done1 = false;
					this->Level = 25;
					AddNum();
					Sleep(500);
				}
				if (175 <= ev.mouse.x && 450 <= ev.mouse.y && 575 >= ev.mouse.x && 525 >= ev.mouse.y) {
					al_draw_filled_rounded_rectangle(175, 450, 575, 525, 10, 10, al_map_rgb(0, 128, 255));
					al_draw_text(welFont, al_map_rgb(255, 255, 255), 375, 75, ALLEGRO_ALIGN_CENTRE, "Level");
					al_draw_text(wel1Font, al_map_rgb(255, 255, 255), 375, 225, ALLEGRO_ALIGN_CENTRE, "Basic");
					al_draw_text(wel1Font, al_map_rgb(255, 255, 255), 375, 300, ALLEGRO_ALIGN_CENTRE, "Easy");
					al_draw_text(wel1Font, al_map_rgb(255, 255, 255), 375, 375, ALLEGRO_ALIGN_CENTRE, "Medium");
					al_draw_text(wel1Font, al_map_rgb(255, 255, 255), 375, 450, ALLEGRO_ALIGN_CENTRE, "Hard");
					al_draw_text(wel1Font, al_map_rgb(255, 255, 255), 375, 525, ALLEGRO_ALIGN_CENTRE, "Evil");
					done1 = false;
					this->Level = 22;
					AddNum();
					Sleep(500);
				}
				if (175 <= ev.mouse.x && 525 <= ev.mouse.y && 575 >= ev.mouse.x && 600 >= ev.mouse.y) {
					al_draw_filled_rounded_rectangle(175, 525, 575, 600, 10, 10, al_map_rgb(0, 128, 255));
					al_draw_text(welFont, al_map_rgb(255, 255, 255), 375, 75, ALLEGRO_ALIGN_CENTRE, "Level");
					al_draw_text(wel1Font, al_map_rgb(255, 255, 255), 375, 225, ALLEGRO_ALIGN_CENTRE, "Basic");
					al_draw_text(wel1Font, al_map_rgb(255, 255, 255), 375, 300, ALLEGRO_ALIGN_CENTRE, "Easy");
					al_draw_text(wel1Font, al_map_rgb(255, 255, 255), 375, 375, ALLEGRO_ALIGN_CENTRE, "Medium");
					al_draw_text(wel1Font, al_map_rgb(255, 255, 255), 375, 450, ALLEGRO_ALIGN_CENTRE, "Hard");
					al_draw_text(wel1Font, al_map_rgb(255, 255, 255), 375, 525, ALLEGRO_ALIGN_CENTRE, "Evil");
					done1 = false;
					this->Level = 20;
					AddNum();
					Sleep(500);
				}
				break;
			}
			this->Level = Level;
			al_draw_text(welFont, al_map_rgb(255, 255, 255), 375, 75, ALLEGRO_ALIGN_CENTRE, "Level");
			al_draw_text(wel1Font, al_map_rgb(255, 255, 255), 375, 225, ALLEGRO_ALIGN_CENTRE, "Basic");
			al_draw_text(wel1Font, al_map_rgb(255, 255, 255), 375, 300, ALLEGRO_ALIGN_CENTRE, "Easy");
			al_draw_text(wel1Font, al_map_rgb(255, 255, 255), 375, 375, ALLEGRO_ALIGN_CENTRE, "Medium");
			al_draw_text(wel1Font, al_map_rgb(255, 255, 255), 375, 450, ALLEGRO_ALIGN_CENTRE, "Hard");
			al_draw_text(wel1Font, al_map_rgb(255, 255, 255), 375, 525, ALLEGRO_ALIGN_CENTRE, "Evil");
			/*Basic = 40;
			Easy = 30;
			Medium = 25;
			Hard = 22;
			Evil = 20;*/
			al_flip_display();
		}
		doneLevel = false;
	}
}
void AllegroView::CoreWelcome()
{
	
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
	Welcome();																									////////////////////
	while (done) {																								////////////////////
		al_wait_for_event(eventQueue, &ev);																		////////////////////
																												////////////////////
		if (ev.type == ALLEGRO_EVENT_TIMER && al_is_event_queue_empty(eventQueue)) al_flip_display();			////////////////////
																												////////////////////
		switch (ev.keyboard.keycode) {																			////////////////////
		case ALLEGRO_KEY_ESCAPE:																				////////////////////
			done = false;																						////////////////////
			break;																								////////////////////
		}																										////////////////////
																												////////////////////
		directionKey(ev), directionMouse(ev), directionNKey(ev);												////////////////////
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
		al_draw_line(36, line, 714, line, al_map_rgb(0, 128, 255), 2);
		al_draw_line(line, 36, line, 714, al_map_rgb(0,128, 255), 2);
	}
	for (double line = 37.5; line <= 712.5; line += 225) {
		al_draw_line(35, line, 715, line, al_map_rgb(255, 0, 128), 5);
		al_draw_line(line, 35, line, 715, al_map_rgb(255, 0, 128), 5);
	}
	DrawLife();
	drawText();
}

void AllegroView::DrawRectangle()
{
	Console _console;
	for (double i = 37.5; i < height - 37.5; i += 75)
		for (double j = 37.5; j < width - 37.5; j += 75)
		{
			if (pos_x >= j && pos_x <= j + 75 && pos_y >= i && pos_y <= i + 75) {
				int x1 = pos_x, y1 = pos_y;
				pos_x = j, pos_y = i;
				int x = (pos_x + 37.5) / 75, y = (pos_y + 37.5) / 75;
				_console.GotoXY(0, 14);cout << "[" << x << "]" << " " << "[" << y << "]";
				DrawSudoku(); //al_hide_mouse_cursor(display);
				for (double i = 37.5; i < height - 37.5; i += 75) {
					for (double j = 37.5; j < width - 37.5; j += 75) {
						int x2 = (j - 37.5) / 75, y2 = (i - 37.5) / 75;
						if ((Sudoku_Num1[x][y] == Sudoku_table[x][y] || Sudoku_Num[x][y] == Sudoku_table[x][y]) && (Sudoku_Num1[x2][y2] != 0 || Sudoku_Num[x2][y2] != 0) && (Sudoku_Num1[x2][y2] == Sudoku_table[x][y] || Sudoku_Num[x2][y2] == Sudoku_table[x][y])) {
							al_draw_filled_rectangle(j, i, j + 75, i + 75, al_map_rgba(100, 100, 100, 0));
						}
					}
				}
				if ((Sudoku_Num1[x][y] == 0 && Sudoku_Num[x][y] == 0) || (Sudoku_Num1[x][y] != Sudoku_table[x][y] && Sudoku_Num[x][y] == 0)) {
					al_draw_filled_rectangle(j, i, j + 75, i + 75, al_map_rgba(100, 100, 100, 0));
				}
				_console.GotoXY(0, 13), _console.SetColor(Color::Black, Color::White);
				cout << "pos_x: " << x1 << "  " << "pos_y: " << y1 << "  " << endl;
				pos_x = x1, pos_y = y1;
				drawText();
			}
		}
}

void AllegroView::SetNum()
{
	for (double i = 37.5; i <= height - 75; i += 75) 
		for (double j = 37.5; j <= width - 75; j += 75)
		{
			if (pos_x >= j && pos_x <= j + 75 && pos_y >= i && pos_y <= i + 75) {
				int x1 = pos_x, y1 = pos_y;
				pos_x = j, pos_y = i;
				int x = pos_x / 75, y = pos_y / 75;
				if (Sudoku_Num[x][y] == 0 && Sudoku_Num1[x][y] != Sudoku_table[x][y]) {
					Sudoku_Num1[x][y] = Number;
					if (Sudoku_Num1[x][y] != Sudoku_table[x][y]) {
					//	life--;
					//	break;
					}
				}
				
				pos_x = x1, pos_y = y1;
				DrawRectangle();
			}
		}
}

void AllegroView::drawText()
{
	for (int h_t = 1;h_t <= 9;h_t++) {
		for (int w_t = 1;w_t <= 9;w_t++) {
			if (0 != Sudoku_Num[w_t - 1][h_t - 1]) {//yellow_TEXT
				char str[2];
				_itoa_s(Sudoku_Num[w_t - 1][h_t - 1], str, 10);
				al_draw_text(mainFont, al_map_rgb(255, 255, 255), w_t * 75 - 18.75, h_t * 75 - 37.5, 0, str);
			}
			if (0 != Sudoku_Num1[w_t - 1][h_t - 1] && Sudoku_Num1[w_t - 1][h_t - 1] == Sudoku_table[w_t - 1][h_t - 1]) {//green_TEXT
				char str[2];
				_itoa_s(Sudoku_Num1[w_t - 1][h_t - 1], str, 10);
				al_draw_text(mainFont, al_map_rgb(0, 255, 0), w_t * 75 - 18.75, h_t * 75 - 37.5, 0, str);
			}
			if (0 != Sudoku_Num1[w_t - 1][h_t - 1] && Sudoku_Num1[w_t - 1][h_t - 1] != Sudoku_table[w_t - 1][h_t - 1]) {//red_TEXT
				char str[2];
				_itoa_s(Sudoku_Num1[w_t - 1][h_t - 1], str, 10);
				al_draw_text(mainFont, al_map_rgb(255, 0, 0), w_t * 75 - 18.75, h_t * 75 - 37.5, 0, str);
			}
		}
	}
}

void AllegroView::DrawLife()
{
	al_draw_filled_ellipse(721.875, 9.375, 9.375, 9.375, al_map_rgb(255, 0, 0));
	al_draw_filled_ellipse(740.625, 9.375, 9.375, 9.375, al_map_rgb(255, 0, 0));
	al_draw_filled_triangle(712.5, 9.375, 750, 9.375, 731.25, 37.5, al_map_rgb(255, 0, 0));
	//if (life >= 0) {
	//	GameSudoku s;
	//	s.Game();//
	//	s.Show();
	//	Initialize(750, 750, 255, 255, 0, s.Sudoku_table);
	//}
	char str[2];
	_itoa_s(life, str, 10);
	al_draw_text(lifeFont, al_map_rgb(255, 255, 0), 726.75, 10, 0, str);
}

void AllegroView::AddNum()
{
	srand(time(NULL));//number
	for (int x = 0; x < 9; x++)
		for (int y = 0; y < 9; y++) {
			Sudoku_Num[x][y] = 0;
			Sudoku_Num1[x][y] = 0;
		}
	int i = 0; 
	while (i < Level) {
		int x, y;
		x = rand() % 9, y = rand() % 9;
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
		if (37.5 <= ev.mouse.x && 37.5 <= ev.mouse.y && 712.5 >= ev.mouse.x && 712.5 >= ev.mouse.y && ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			pos_x = ev.mouse.x,	pos_y = ev.mouse.y;
			DrawRectangle();
		}
		break;
	case 2:
		if (ev.mouse.button & 2 && ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
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
		pos_y -= keys[UP] * (600 / fpsTimeout);
		pos_y += keys[DOWN] * (600 / fpsTimeout);
		pos_x -= keys[LEFT] * (600 / fpsTimeout);
		pos_x += keys[RIGHT] * (600 / fpsTimeout);
		if (37.5 < pos_x && 37.5 < pos_y && 712.5 > pos_x && 712.5 > pos_y) {
			DrawRectangle();
		}
		else {
			if (37.5 > pos_y) pos_y = 712.5;
			if (712.5 < pos_y) pos_y = 37.5;
			if (38 > pos_x) pos_x = 711;
			if (711 < pos_x) pos_x = 38;
			DrawRectangle();
		}
	}
}
void AllegroView::directionNKey(ALLEGRO_EVENT & ev)
{
	switch (ev.keyboard.keycode) {
	case ALLEGRO_KEY_DELETE:
	case ALLEGRO_KEY_PAD_0:
	case ALLEGRO_KEY_0:	Number = 0, SetNum();
		break;
	case ALLEGRO_KEY_PAD_1:
	case ALLEGRO_KEY_1:	Number = 1,	SetNum();
		break;
	case ALLEGRO_KEY_PAD_2:
	case ALLEGRO_KEY_2:Number = 2, SetNum();
		break;
	case ALLEGRO_KEY_PAD_3:
	case ALLEGRO_KEY_3:Number = 3, SetNum();
		break;
	case ALLEGRO_KEY_PAD_4:
	case ALLEGRO_KEY_4:Number = 4, SetNum();
		break;
	case ALLEGRO_KEY_PAD_5:
	case ALLEGRO_KEY_5:Number = 5, SetNum();
		break;
	case ALLEGRO_KEY_PAD_6:
	case ALLEGRO_KEY_6:Number = 6, SetNum();
		break;
	case ALLEGRO_KEY_PAD_7:
	case ALLEGRO_KEY_7:Number = 7, SetNum();
		break;
	case ALLEGRO_KEY_PAD_8:
	case ALLEGRO_KEY_8:Number = 8, SetNum();
		break;
	case ALLEGRO_KEY_PAD_9:
	case ALLEGRO_KEY_9:Number = 9, SetNum();
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