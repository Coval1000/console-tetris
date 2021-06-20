#include "biblioteki.h"
#include "gra.h"

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
		system("clear");
		printf("%c%d.Gra%c\n", graphics.chars.lewy * !(kursor.pozycja - ilosc), ilosc + 1, graphics.chars.prawy * !(kursor.pozycja - ilosc)); ilosc++;
		printf("%c%d.Opcje%c\n", graphics.chars.lewy * !(kursor.pozycja - ilosc), ilosc + 1, graphics.chars.prawy * !(kursor.pozycja - ilosc)); ilosc++;
		printf("%c%d.Wyniki%c\n", graphics.chars.lewy * !(kursor.pozycja - ilosc), ilosc + 1, graphics.chars.prawy * !(kursor.pozycja - ilosc)); ilosc++;
		switch (getchar())
		{
		case 27:
			exit(0);
			break;

		case KEY_INPUT:

			switch (getchar())
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
