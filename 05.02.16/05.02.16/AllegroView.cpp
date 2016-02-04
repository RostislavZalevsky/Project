#include "AllegroView.h"

AllegroView::AllegroView()
{
	display = nullptr;
	timer = nullptr;
	eventQueue = nullptr;
	backgroundImage = nullptr;

	fpsTimeout = 60;
}

void AllegroView::Initialize(int width, int height, int r, int g, int b)
{
	if (!al_init())
	{
		throw "Allegro initialize error!";
	}

	/*al_init_image_addon();*/

	this->width = width;
	this->height = height;

	display = al_create_display(width, height);

	if (display == nullptr)
	{
		throw "Display creation error!";//throw 1;
	}

	if (!al_install_keyboard())
	{
		throw "Tnstall keyboard error!";
	}

	timer = al_create_timer(1.0 / fpsTimeout);

	if (timer == nullptr)
	{
		throw "Timer creation error!";
	}

	eventQueue = al_create_event_queue();

	if (eventQueue == nullptr)
	{
		throw "Event queue creation error!";
	}

	//backgroundImage = al_load_bitmap("Resources/Images/space.jpg");
	//mainAtlas = al_load_bitmap("Resources/Images/mainAtlas.png");

	/*if (backgroundImage == nullptr || mainAtlas == nullptr)
	{
		throw "Load image error!";
	}*/

	al_set_target_bitmap(al_get_backbuffer(display));

	backgroundColor.r = r;
	backgroundColor.g = g;
	backgroundColor.b = b;
	backgroundColor.a = 0;

	al_register_event_source(eventQueue, al_get_timer_event_source(timer));	//al_clear_to_color(al_map_rgb(r, g, b));//al_flip_display();//al_rest(5);
	al_register_event_source(eventQueue, al_get_display_event_source(display));
	al_register_event_source(eventQueue, al_get_keyboard_event_source());

}

AllegroView::~AllegroView()
{
	if (display != nullptr)
	{
		al_destroy_display(display);
	}

	if (display != nullptr)
	{
		al_destroy_timer(timer);
	}

	if (eventQueue != nullptr)
	{
		al_destroy_event_queue(eventQueue);
	}
}
