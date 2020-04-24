#include "opcje.h"

void _Graphics_Initialize(struct Graphics *self)
{
	_Ramka(self);
}
void _Ramka(struct Graphics *self)
{
	self->h = 205;
	self->v = 186;
	self->gl = 201;
	self->gp = 187;
	self->dl = 200;
	self->dp = 188;
}
void _Znaki(struct Graphics *self)
{
	self->lewy = 175;
	self->prawy = 174;
}
void _Plansza(struct Graphics *self)
{
	self->ramka = -78;
	self->tlo = -80;
	self->kursor = '@';
	self->ustawione = -79;
}

int absZnak(int a)
{
	return a < 0 ? 256 + a : a;
}

char *znakS(char lit, int p)
{
	static char przycisk[8] = { 0 };
	if (!p)
	{
		switch (lit)
		{
		case 8:
			strcpy(przycisk, "B.SPACE");
			return przycisk;

		case 13:
			strcpy(przycisk, "ENTER");
			return przycisk;

		case 27:
			strcpy(przycisk, "ESC");
			return przycisk;

		case 32:
			strcpy(przycisk, "SPACJA");
			return przycisk;
		}
		przycisk[0] = lit;
		przycisk[1] = 0;
		return przycisk;
	}

	switch (lit)
	{
	case 30:
		strcpy(przycisk, "ALT-A");
		break;

	case 48:
		strcpy(przycisk, "ALT-B");
		break;

	case 59:
		strcpy(przycisk, "F1");
		break;

	case 60:
		strcpy(przycisk, "F2");
		break;

	case 61:
		strcpy(przycisk, "F3");
		break;

	case 62:
		strcpy(przycisk, "F4");
		break;

	case 63:
		strcpy(przycisk, "F5");
		break;

	case 64:
		strcpy(przycisk, "F6");
		break;

	case 65:
		strcpy(przycisk, "F7");
		break;

	case 66:
		strcpy(przycisk, "F8");
		break;

	case 67:
		strcpy(przycisk, "F9");
		break;

	case 68:
		strcpy(przycisk, "F10");
		break;

	case -123:
		strcpy(przycisk, "F11");
		break;

	case -122:
		strcpy(przycisk, "F12");
		break;

	case 71:
		strcpy(przycisk, "Home");
		break;

	case 73:
		strcpy(przycisk, "PgDn");
		break;

	case 79:
		strcpy(przycisk, "End");
		break;

	case 81:
		strcpy(przycisk, "PgDn");
		break;

	case 82:
		strcpy(przycisk, "Insert");
		break;

	case 83:
		strcpy(przycisk, "Delete");
		break;

	case 72:
		strcpy(przycisk, "\30");
		break;

	case 80:
		strcpy(przycisk, "\31");
		break;

	case 75:
		strcpy(przycisk, "\33");
		break;

	case 77:
		strcpy(przycisk, "\32");
		break;

	}


	return przycisk;
}

char wyglad(char znak)
{
	COORD tmpsize = { 80, 300 };
	SMALL_RECT windowSize = { 0, 0, 33, 34 };
	COORD bufferSize = { 34, 35 };

	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), tmpsize);
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), 1, &windowSize);
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize);

	int x = absZnak(znak) % 16;
	int y = absZnak(znak) / 16;
	int sizeX;
	int sizeY;
	int element = 0;
	char plansza[1123];
	char tablica[1123];

	for (sizeY = 0; sizeY<16; sizeY++)
	{
		for (sizeX = 0; sizeX<33; sizeX++)
		{
			plansza[sizeY * 2 * 34 + sizeX] = ' ';
		}
		plansza[sizeY * 2 * 34 + sizeX] = '\n';
		for (sizeX = 0; sizeX<16; sizeX++, element++)
		{
			plansza[(sizeY * 2 + 1) * 34 + sizeX * 2] = ' ';
			switch (element)
			{
			default:
				plansza[(sizeY * 2 + 1) * 34 + sizeX * 2 + 1] = element;
				break;
			case 0:
			case 7:
			case 8:
			case 9:
			case 10:
			case 13:
				plansza[(sizeY * 2 + 1) * 34 + sizeX * 2 + 1] = ' ';
				break;
			}
		}
		plansza[(sizeY * 2 + 1) * 34 + sizeX * 2] = ' ';
		plansza[(sizeY * 2 + 1) * 34 + sizeX * 2 + 1] = '\n';
	}

	for (sizeX = 0; sizeX<33; sizeX++)
	{
		plansza[sizeY * 2 * 34 + sizeX] = ' ';
	}

	plansza[sizeY * 2 * 34 + sizeX] = '\n';
	plansza[sizeY * 2 * 34 + sizeX + 1] = '\0';
	system("cls");

	while (1)
	{

		strcpy(tablica, plansza);
		tablica[(y * 2) * 34 + x * 2] = 218;
		tablica[(y * 2) * 34 + x * 2 + 1] = 196;
		tablica[(y * 2) * 34 + x * 2 + 2] = 191;
		tablica[(y * 2 + 1) * 34 + x * 2] = 179;
		//tablica[(y * 2 + 1) * 34 + x * 2 + 1] = '@';
		tablica[(y * 2 + 1) * 34 + x * 2 + 2] = 179;
		tablica[(y * 2 + 2) * 34 + x * 2] = 192;
		tablica[(y * 2 + 2) * 34 + x * 2 + 1] = 196;
		tablica[(y * 2 + 2) * 34 + x * 2 + 2] = 217;

		COORD coord;
		coord.X = 0;
		coord.Y = 0;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		puts(tablica);
		char buf = _getch();

		switch (buf)
		{
		case KEY_INPUT:
			buf = _getch();
		default:
			if (buf == 77 && x < 15)
			{
				x++;
			}
			else if (buf == 75 && x > 0)
			{
				x--;
			}
			else if (buf == 72 && y > 0)
			{
				y--;
			}
			else if (buf == 80 && y < 15)
			{
				y++;
			}
			break;

		case 13:
			return x + (y * 16 + 1) - 1;
		case 27:
			return znak;
		}
	}
	return 0;
}

void sterDef(struct Sterowanie *ster)
{
	(*ster).wGore = 72;
	(*ster).wGorePair = 1;
	(*ster).wDol = 80;
	(*ster).wDolPair = 1;
	(*ster).wLewo = 75;
	(*ster).wLewoPair = 1;
	(*ster).wPrawo = 77;
	(*ster).wPrawoPair = 1;
	ster->zapis = 59;
	ster->zapisPair = 1;
	ster->wczytanie = 60;
	ster->wczytaniePair = 1;
	ster->pauza = ' ';
	ster->pauzaPair = 0;
	ster->nowy = 'n';
	ster->nowyPair = 0;
}

char przypisz(char *key)
{
	printf("Podaj nowy");
	*key = _getch();
	if (*key != KEY_INPUT && *key) return 0;
	*key = _getch();
	return 1;
}

void opcje(struct Sterowanie *ster, struct Graphics *graphics)
{
	COORD tmpsize = { 80, 300 };
	SMALL_RECT windowSize = { 0, 0, 40, 20 };
	COORD bufferSize = { 41, 21 };

	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), tmpsize);
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), 1, &windowSize);
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize);

	struct Kursor opcje;
	opcje.pozycja = 0;
	int num1 = 0;
	int ilosc = 0;
	while (1)
	{

		ilosc = 0;
		system("cls");
		printf("Sterowanie\n\n");
		printf("%cPrzesu\344 w g\242r\251  : %s%c\n", graphics->lewy * !(opcje.pozycja - ilosc), znakS(ster->wGore, ster->wGorePair), graphics->prawy * !(opcje.pozycja - ilosc));	ilosc++;
		printf("%cPrzesu\344 w d\242\210   : %s%c\n", graphics->lewy * !(opcje.pozycja - ilosc), znakS(ster->wDol, ster->wDolPair), graphics->prawy * !(opcje.pozycja - ilosc));	ilosc++;
		printf("%cPrzesu\344 w lewo  : %s%c\n", graphics->lewy * !(opcje.pozycja - ilosc), znakS(ster->wLewo, ster->wLewoPair), graphics->prawy * !(opcje.pozycja - ilosc));		ilosc++;
		printf("%cPrzesu\344 w prawo : %s%c\n", graphics->lewy * !(opcje.pozycja - ilosc), znakS(ster->wPrawo, ster->wPrawoPair), graphics->prawy * !(opcje.pozycja - ilosc));		ilosc++;
		printf("%cPauza		 : %s%c\n", graphics->lewy * !(opcje.pozycja - ilosc), znakS(ster->pauza, ster->pauzaPair), graphics->prawy * !(opcje.pozycja - ilosc));				ilosc++;
		printf("%cZapisz gr\251	 : %s%c\n", graphics->lewy * !(opcje.pozycja - ilosc), znakS(ster->zapis, ster->zapisPair), graphics->prawy * !(opcje.pozycja - ilosc));			ilosc++;
		printf("%cWczytaj gr\251	 : %s%c\n", graphics->lewy * !(opcje.pozycja - ilosc), znakS(ster->wczytanie, ster->wczytaniePair), graphics->prawy * !(opcje.pozycja - ilosc)); ilosc++;
		printf("%cNiestandardowa gra	 : %s%c\n", graphics->lewy * !(opcje.pozycja - ilosc), znakS(ster->nowy, ster->nowyPair), graphics->prawy * !(opcje.pozycja - ilosc)); ilosc++;
		printf("%cDomy\230lnie sterowanie%c\n", graphics->lewy * !(opcje.pozycja - ilosc), graphics->prawy * !(opcje.pozycja - ilosc));	ilosc++;
		for (num1 = 0; num1 < 41; num1++) printf("~");
		printf("\nWygl\245d\n\n");
		printf("%cRamka		 : %c%c\n", graphics->lewy * !(opcje.pozycja - ilosc), graphics->ramka, graphics->prawy * !(opcje.pozycja - ilosc));				ilosc++;
		printf("%cT\210o		 : %c%c\n", graphics->lewy * !(opcje.pozycja - ilosc), graphics->tlo, graphics->prawy * !(opcje.pozycja - ilosc));			ilosc++;
		printf("%cUstawione	 : %c%c\n", graphics->lewy * !(opcje.pozycja - ilosc), graphics->ustawione, graphics->prawy * !(opcje.pozycja - ilosc));			ilosc++;
		printf("%cKlocek		 : %c%c\n", graphics->lewy * !(opcje.pozycja - ilosc), graphics->kursor, graphics->prawy * !(opcje.pozycja - ilosc));			ilosc++;
		printf("%cDomy\230lnie%c\n", graphics->lewy * !(opcje.pozycja - ilosc), graphics->prawy * !(opcje.pozycja - ilosc));	ilosc++;
		printf("%cPowr\242t%c", graphics->lewy * !(opcje.pozycja - ilosc), graphics->prawy * !(opcje.pozycja - ilosc));			ilosc++;
		switch (_getch())
		{
		case 224:
			switch (_getch())
			{
			case 72:
				if (opcje.pozycja > 0)
				{
					opcje.pozycja--;
				}
				break;

			case 80:
				if (opcje.pozycja < ilosc - 1)
				{
					opcje.pozycja++;
				}
				break;
			}
			break;

		case 27:
			return;
			break;

		case '\r':
			switch (opcje.pozycja)
			{
			case 0:
				ster->wGorePair = przypisz(&ster->wGore);
				break;

			case 1:
				ster->wDolPair = przypisz(&ster->wDol);
				break;

			case 2:
				ster->wLewoPair = przypisz(&ster->wLewo);
				break;

			case 3:
				ster->wPrawoPair = przypisz(&ster->wPrawo);
				break;

			case 4:
				ster->pauzaPair = przypisz(&ster->pauza);
				break;

			case 5:
				ster->zapisPair = przypisz(&ster->zapis);
				break;

			case 6:
				ster->wczytaniePair = przypisz(&ster->wczytanie);
				break;

			case 7:
				ster->wczytaniePair = przypisz(&ster->wczytanie);
				break;

			case 8:
				sterDef(ster);
				break;

			case 9:
				graphics->ramka = wyglad(graphics->ramka);
				break;

			case 10:
				graphics->tlo = wyglad(graphics->tlo);
				break;

			case 11:
				graphics->ustawione = wyglad(graphics->ustawione);
				break;

			case 12:
				graphics->kursor = wyglad(graphics->kursor);
				break;

			case 13:
				_Plansza(graphics);
				break;

			case 14:
				return;
				break;
			}
			SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), tmpsize);
			SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), 1, &windowSize);
			SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize);
		}
	}
	return;
}
