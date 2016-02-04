#include "Header.h"
#include "AllegroView.h"

void main()
{
	try
	{
		AllegroView all;
		all.Initialize(600, 400, 40, 30, 155);
		al_rest(5.0);
	}
	catch (char *message)
	{
		cout << message << endl;
	}
	catch (int code)
	{
		if (code == 1) cout << "Display creation error!\n";
	}
	catch (...)
	{
		cout << "Unknow exception!" << endl;
	}
	//_getch();
}