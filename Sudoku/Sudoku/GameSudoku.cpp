#include "GameSudoku.h"


GameSudoku::GameSudoku()
{
	for (int x1 = 0; x1 < 9; x1++)
		for (int y1 = 0; y1 < 9; y1++)
			Sudoku_table[x1][y1] = 0;
}

void GameSudoku::Game()
{
	for (int x1 = 0; x1 < 9; x1++)
		for (int y1 = 0; y1 < 9; y1++)
			Sudoku_table[x1][y1] = 0;

	srand(time(NULL));
	const int k = 3, Form_XY = k*k;
	int w = 1, w1 = 1, w2 = 1, rand1;

	for (int xy = 0; xy < Form_XY; xy++) {
		w2 = 0;
		for (int i = 1;i <= Form_XY;i++) {
			w = 0;
			do {
				w1 = 0;
				rand1 = rand() % 9;
				for (int j1 = 0; j1 < k;j1++)
					for (int j = 0;j < k;j++)
					{
						if (j1*k <= xy && xy < (j1*k) + k /**/&&/**/ j*k <= rand1 && rand1 < (j*k) + k) {
							for (int _y = j1*k;_y < (j1*k) + k;_y++)
								for (int _x = j*k;_x < (j*k) + k;_x++)
								{
									if (Sudoku_table[_y][_x] == i) w1++;
								}
						}
					}
				if (Sudoku_table[xy][rand1] == 0 && w1 == 0)
				{
					Sudoku_table[xy][rand1] = i;
					for (int j = 0;j < Form_XY;j++)
					{
						if (j != xy && Sudoku_table[j][rand1] == Sudoku_table[xy][rand1])
							w1++;// y
					}
					if (w1 > 0) Sudoku_table[xy][rand1] = 0;
				}
				else w1++;
				w++;
				if (w >= 1000)
				{
					for (int j = 0;j < Form_XY;j++)
					{
						Sudoku_table[xy][j] = 0;
						i = 0;
						w1 = 0;
						w = 0;
					}
				}
			} while (w1 != 0);
			w2++;
			if (w2 >= 100)
			{
				for (int x1 = 0; x1 < Form_XY; x1++)
					for (int y1 = 0; y1 < Form_XY; y1++)
						Sudoku_table[x1][y1] = 0;
				xy = 0;
				i = 0;
				w2 = 0;
			}
		}
	}
	for (int x1 = 0; x1 < 9; x1++)
		for (int y1 = 0; y1 < 9; y1++) 
			this->Sudoku_table[x1][y1] = Sudoku_table[x1][y1];
}


void GameSudoku::Show()
{
	const int k = 3, Form_XY = k*k;
	int i = 0, j = 0;
	for (int y = 0; y < Form_XY; y++)
	{
		if (j % 3 == 0)cout << "\n";
		for (int x = 0; x < Form_XY; x++)
		{
			if (x == 0)cout << " ";
			cout << Sudoku_table[x][y] << " ";
			i = x;
			i++;
			if (i % 3 == 0)cout << " ";
		}
		j = y;
		j++;
		cout << endl;
	}
}