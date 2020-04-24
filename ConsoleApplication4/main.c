#include "biblioteki.h"


typedef struct Wynik Wynik;

int main()
{
	SetConsoleTitle(TEXT("Projekt Tetris"));
	
	SMALL_RECT windowSize = { 0, 0, 20, 20 };
	COORD bufferSize = { 21, 21 };
	COORD tmpsize = { 260, 300 };
	
	
	struct Sterowanie controls;
	_Sterowanie_Initialize(&controls);

	struct Graphics graphics;
	_Graphics_Initialize(&graphics);

	struct Wynik *tWynikow;
	tWynikow = malloc(sizeof(Wynik));
	tWynikow = wynikiWczyt(tWynikow);

	struct Kursor kursor;
	kursor.pozycja = 0;

	int ilosc = 0;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), tmpsize);
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), 1, &windowSize);
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize);
	while (1)
	{
		ilosc = 0;
		system("cls");
		printf("%c%d.Gra%c\n", graphics.lewy * !(kursor.pozycja - ilosc), ilosc + 1, graphics.prawy * !(kursor.pozycja - ilosc)); ilosc++;
		printf("%c%d.Opcje%c\n", graphics.lewy * !(kursor.pozycja - ilosc), ilosc + 1, graphics.prawy * !(kursor.pozycja - ilosc)); ilosc++;
		printf("%c%d.Wyniki%c\n", graphics.lewy * !(kursor.pozycja - ilosc), ilosc + 1, graphics.prawy * !(kursor.pozycja - ilosc)); ilosc++;
		switch (_getch())
		{
		case 27:
			exit(0);
			break;

		case KEY_INPUT:

			switch (_getch())
			{
			case 72:
				if (kursor.pozycja > 0)
				{
					kursor.pozycja--;
				}
				break;

			case 80:
				if (kursor.pozycja < ilosc-1)
				{
					kursor.pozycja++;
				}
				break;
			}
			break;

		case '1':
			gra(&tWynikow, &controls, &graphics);
			SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), tmpsize);
			SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), 1, &windowSize);
			SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize);
			break;

		case '2':
			opcje(&controls, &graphics);
			SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), tmpsize);
			SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), 1, &windowSize);
			SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize);
			break;

		case '3':
			wyniki(tWynikow);
			SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), tmpsize);
			SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), 1, &windowSize);
			SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize);
			break;

		case '\r':
			switch (kursor.pozycja)
			{
			case 0:
				gra(&tWynikow, &controls, &graphics);
				break;
			case 1:
				opcje(&controls, &graphics);
				break;
			case 2:
				wyniki(tWynikow);
				break;
			}
			SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), tmpsize);
			SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), 1, &windowSize);
			SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize);
		}

	}
	return 0;
}

//polskie znaki
/*
206 - æ c
210 - ³ l
230 - œ s
242 - ó o
245 - ¹ a 
251 - ê e
253 - Ÿ z'
276 - ¿ z
344 - ñ n
*/

//kopia zapasowa void gra()
/*
void gra()
{
	struct Player player;
	player.poss[0] = 1;
	player.poss[1] = 1;

	int xy[2] = { 12, 12 };
	char *mapB;
	char *map;
	map = createMap(xy[0], xy[1], xy, &player);
	mapB = malloc(strlen(map));
	strcpy(mapB, map);
	int time = 0;

	while (1)
	{
		if (_kbhit())
		{
			char buf = _getch();
			switch (buf)
			{
			case 224:
				buf = _getch();
			default:
				if (buf == controls.wPrawo &&		map[player.poss[1] * (xy[1] + 1) + player.poss[0] + 1] != sciana)
				{
					player.poss[0]++;
				}
				else if (buf == controls.wLewo &&	map[player.poss[1] * (xy[1] + 1) + player.poss[0] - 1] != sciana)
				{
					player.poss[0]--;
				}
				else if (buf == controls.wGore &&	map[(player.poss[1] - 1) * (xy[1] + 1) + player.poss[0]] != sciana)
				{
					player.poss[1]--;
				}
				else if (buf == controls.wDol &&	map[(player.poss[1] + 1) * (xy[1] + 1) + player.poss[0]] != sciana)
				{
					player.poss[1]++;
				}
				break;

			case 27:
				return;

			case 'z':
				zapis(map, &player, xy);
				break;

			case 'w':
				map = wczyt(map, &player, xy);
				break;

			case 'n':

				map = createMap(10, 10, xy, &player);
				break;
			}
		}
		strcpy(map, mapB);
		*(map + player.poss[1] * (xy[0] + 1) + player.poss[0]) = '@';
		draw(map);
		time = clock() / (CLOCKS_PER_SEC);
		printf("Czas: %ds\nESC aby wyjsc", time, xy[0], xy[1]);
		Sleep(50);
	}
	return;
}*/
