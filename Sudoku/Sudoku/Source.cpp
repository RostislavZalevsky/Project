#include "Header.h"
#include "AllegroView.h"
#include "GameSudoku.h"

void main()
{
	GameSudoku s;
	s.Game();//
	s.Show();
	try {
		AllegroView Table;
		Table.Initialize(750, 750, 255, 255, 0, s.Sudoku_table);
		Table.Game(&Table);
	}
	catch (char *messenge) {
		//al_show_native_message_box(NULL, NULL, NULL, messenge, NULL, NULL);
		cout << messenge << endl;
	}
	catch (...)	{
		//al_show_native_message_box(NULL, NULL, NULL, "Unknow exception!", NULL, NULL);
		cout << "Unknow exception!" << endl;
	}
	//_getch();
}