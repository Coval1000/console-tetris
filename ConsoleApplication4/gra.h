#pragma once
#include "biblioteki.h"

typedef struct Player
{
	POINT poss;
	POINT shape[4];
	float speed;
	float points;
	int time;
} Player;

void _Player_Default(struct Player *self, POINT frame)
{
	self->poss.x = frame.x / 2 - 2;
	self->poss.y = 2;
	self->speed = 1;
	self->points = 0;
	self->time = 0;
	return;
}

typedef struct Board
{
	POINT frame;
	char *map;
	char *mapB;
	int level;
	int cycle;
	int custom;
	
	BOOL(*CreateMap)(struct Board *self, Graphics_t *graphics);
	BOOL(*CustomMap)(struct Board *self, struct Player *player, Graphics_t *graphics);
	void(*Shutdown)(struct Board *self);
	void(*Print)(struct Board *self, struct Player *player, Graphics_t *graphics);
} Board_t;

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void draw(char *d)
{	
	gotoxy(0, 0);
	puts(d);
	return;
}

void _Board_Print(Board_t *self, struct Player *player, Graphics_t *graphics)
{
	strcpy(self->map, self->mapB);
	self->map[(player->poss.y + player->shape[0].y) * (self->frame.x + 1) + player->poss.x + player->shape[0].x] = graphics->board.kursor;
	self->map[(player->poss.y + player->shape[1].y) * (self->frame.x + 1) + player->poss.x + player->shape[1].x] = graphics->board.kursor;
	self->map[(player->poss.y + player->shape[2].y) * (self->frame.x + 1) + player->poss.x + player->shape[2].x] = graphics->board.kursor;
	self->map[(player->poss.y + player->shape[3].y) * (self->frame.x + 1) + player->poss.x + player->shape[3].x] = graphics->board.kursor;
	draw(self->map);
	return;
}

void _Board_Shutdown(Board_t *self)
{
	free(self->mapB);
	free(self->map);
	self->map = NULL;
	self->mapB = NULL;
}

BOOL _Board_CreateMap(Board_t *self, Graphics_t *graphics)
{
	void *tmp = NULL;
	if (self->frame.x * self->frame.y == 0) return FALSE;

	if(self->map) tmp = realloc(self->map, ((self->frame.x + 1)*self->frame.y + 1) * sizeof(char));
	else tmp = malloc(((self->frame.x + 1)*self->frame.y + 1) * sizeof(char));

	if (tmp)
	{
		self->map = (char*)tmp;
		COORD tmpsize = { 260, 300 };
		SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), tmpsize);
		COORD bufferSize = { self->frame.x + 2, self->frame.y + 6 };
		SMALL_RECT konsola = { 0, 0, self->frame.x + 1, self->frame.y + 5 };
		SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), 1, &konsola);
		SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize);
		int i = 0;
		int w = 0;
		for (; i < self->frame.x; ++i)
		{
			self->map[i] = graphics->board.ramka;
		}
		for (self->map[i] = '\n', ++i; i < (((self->frame.x + 1)*self->frame.y) - (self->frame.x + 1)); ++i)
		{
			self->map[i] = graphics->board.ramka;
			for (w = 0, ++i; w < self->frame.x - 2; w++, ++i)
			{
				self->map[i] = graphics->board.background;
			}
			self->map[i] = graphics->board.ramka;
			self->map[++i] = '\n';
		}
		for (; i < ((self->frame.x + 1)*self->frame.y) - 1; ++i)
		{
			self->map[i] = graphics->board.ramka;
		}
		self->map[i] = '\n';
		self->map[++i] = '\0';
		system("cls");
		self->mapB = (char*)malloc(strlen(self->map) + 1);
		strcpy(self->mapB, self->map);
		return TRUE;
	}
	putchar(8);
	return FALSE;
}

BOOL _Board_CustomMap(Board_t *self, struct Player *player, Graphics_t *graphics)
{
	struct Kursor kursor;
	struct Sterowanie controls;
	_Sterowanie_Initialize(&controls);
	kursor.pozycja = 0;
	unsigned char x = 0;
	unsigned char y = 0;
	int ilosc;
	int value;
	COORD tmpsize = { 260, 300 };
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), tmpsize);
	COORD bufferSize = { 35, 21 };
	SMALL_RECT konsola = { 0, 0, 34 , 20 };
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), 1, &konsola);
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize);
	for (; !controls.utilities.enter.isDown; controls.Process_Input(&controls))
	{

		system("cls");
		printf("Wynik gry niestandardowej nie jest zapisywany na tablicy wynik\242w.\n UWAGA! okno konsoli nie mo\276e by\206 \nwi\251ksze ni\276 ekran. Powoduje to \nb\210\251de wy\230wietlanie zbyt du\276ych map\n\n");
		ilosc = 0;
		printf("%cX: %d\n", graphics->chars.lewy * !(kursor.pozycja - ilosc), x); ilosc++;
		printf("%cY: %d\n", graphics->chars.lewy * !(kursor.pozycja - ilosc), y); ilosc++;
		if (controls.utilities.esc.isDown)
		{
			self->Shutdown(self);
			return FALSE;
		}
		value = controls.numbers.num0.isRising |
			controls.numbers.num1.isRising << 1 |
			controls.numbers.num2.isRising << 2 |
			controls.numbers.num3.isRising << 3 |
			controls.numbers.num4.isRising << 4 |
			controls.numbers.num5.isRising << 5 |
			controls.numbers.num6.isRising << 6 |
			controls.numbers.num7.isRising << 7 |
			controls.numbers.num8.isRising << 8 |
			controls.numbers.num9.isRising << 9;
		if (value)
		{
			switch (value)
			{
			case 1:
				value = 0;
				break;
			case 2:
				value = 1;
				break;
			case 4:
				value = 2;
				break;
			case 8:
				value = 3;
				break;
			case 16:
				value = 4;
				break;
			case 32:
				value = 5;
				break;
			case 64:
				value = 6;
				break;
			case 128:
				value = 7;
				break;
			case 256:
				value = 8;
				break;
			case 512:
				value = 9;
				break;
			}
			if (!kursor.pozycja)
			{
				if (value + x * 10 > 255) x = 255;
				else x = value + x * 10;
			}
			else
			{
				if (value + y * 10 > 255) y = 255;
				else y = value + y * 10;
			}
		}
		if (controls.utilities.backspace.isRising)
		{
			if (!kursor.pozycja && x > 0) x = x / 10;
			else if (y > 0) y = y / 10;
		}
		if (controls.direction.up.isRising && kursor.pozycja > 0) kursor.pozycja--;
		if (controls.direction.down.isRising && kursor.pozycja < ilosc - 1) kursor.pozycja++;
	}	
	if (!x || !y)
	{
		self->Shutdown(self);
		return FALSE;
	}
	self->frame.x = x + 2;
	self->frame.y = y + 2;
	self->CreateMap(self, graphics);
	_Player_Default(player, self->frame);
	self->level = 1;
	self->custom = 1;
	return TRUE;
}

void _Board_Initilaze(Board_t *self)
{
	self->frame.x = 0;
	self->frame.y = 0;
	self->level = 1;
	self->cycle = 0;
	self->custom = 0;
	self->map = NULL;
	self->mapB = NULL;
	self->CreateMap = &_Board_CreateMap;
	self->CustomMap = &_Board_CustomMap;
	self->Shutdown = &_Board_Shutdown;
	self->Print = &_Board_Print;
	return;
}


int ptg(int a, int b)
{
	if (b == 1) return a;
	else if (b == 0) return 1;
	return a*ptg(a, b - 1);
}

int sumaC(int a, int b)
{
	if (b == 1) return a;
	else if (b == 0) return 0;
	return a + sumaC(a + a, b - 1);
}

void zapis(char *w, Player *player, POINT frame, Graphics_t *graphics)
{
	int i = 0;
	char trans = 0;
	FILE *zapisz;
	zapisz = fopen("zapis1.txt", "wb");
	fprintf(zapisz, "%d", strlen(w));
	putc(0, zapisz);

	for (i = 0; *(w + i); i++)
	{
		if (*(w + i) == graphics->board.background) trans = 't';
		else if (*(w + i) == graphics->board.ustawione) trans = 'u';
		else if (*(w + i) == graphics->board.ramka) trans = 'r';
		else trans = *(w + i);
		fprintf(zapisz, "%c", trans);
	}
	putc(0, zapisz);

	putc(player->poss.x, zapisz);
	putc(player->poss.y, zapisz);
	for (i = 0; i < 4; i++) 
	{ 
		putc(player->shape[i].x, zapisz); 
		putc(player->shape[i].y, zapisz);
	}

	putc(frame.x, zapisz);
	putc(frame.y, zapisz);

	putc(0, zapisz);
	fprintf(zapisz, "%d", player->time);
	putc(0, zapisz);
	fprintf(zapisz, "%g", player->points);
	putc(0, zapisz);
	fprintf(zapisz, "%g", player->speed);
	putc(0, zapisz);
	putc(0, zapisz);
	fclose(zapisz);
	return;
}

char *wczyt(char *w, Player *player, POINT frame, Graphics_t *graphics)
{
	FILE *wczytaj;
	wczytaj = fopen("zapis1.txt", "rb");
	if (wczytaj)
	{
		int i = 0;
		char trans = 1;

		for (trans = getc(wczytaj); trans; trans = getc(wczytaj)) i = (trans - '0') + i * 10;

		void *tmp = w;
		if (tmp = realloc(w, i * sizeof(char) + 1))
		{
			w = tmp;
		}
		else
		{
			system("cls");
			printf("\aB\210ad pami\251ci");
			return w;
		}

		player->points = 0;
		player->time = 0;
		player->speed = 0;

		i = 0;
		do
		{

			fscanf(wczytaj, "%c", &trans);
			switch (trans)
			{
			case 't':
				*(w + i) = graphics->board.background;
				break;
			case 'u':
				*(w + i) = graphics->board.ustawione;
				break;
			case 'r':
				*(w + i) = graphics->board.ramka;
				break;
			default:
				*(w + i)= trans;
			}
			i++;
		} while (*(w + i - 1));

		player->poss.x = getc(wczytaj);
		player->poss.y = getc(wczytaj);

		for (i = 0; i < 4; i++)
		{
			player->shape[i].x = getc(wczytaj);
			player->shape[i].y = getc(wczytaj);
		}

		frame.x = getc(wczytaj);
		frame.y = getc(wczytaj);

		getc(wczytaj);

		for (trans = getc(wczytaj); trans; trans = getc(wczytaj)) player->time = (trans - 48) + player->time * 10;
		player->time = (clock() / CLOCKS_PER_SEC) - player->time;

		i = 0;
		while (trans = getc(wczytaj))
		{
			if (!i && trans != '.')
			{
				player->points = (trans - 48) + player->points * 10;
			}
			else if (i && trans != '.')
			{
				player->points = (trans - 48)*(1. / (float)ptg(10, i)) + player->points;
				i++;
			}
			else i++;
		}

		i = 0;
		while (trans = getc(wczytaj))
		{
			if (!i && trans != '.')
			{
				player->speed = (trans - 48) + player->speed * 10;
			}
			else if (i && trans != '.')
			{
				player->speed = (trans - 48)*(1. / (float)ptg(10, i)) + player->speed;
				i++;
			}
			else i++;
		}
		SMALL_RECT windowSize = { 0, 0, frame.x + 1, frame.y + 5 };
		SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), 1, &windowSize);
		COORD bufferSize = { frame.x + 1 + 1, frame.y + 5 + 1 };
		SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize);
		fclose(wczytaj);
	}
	else
	{
		SMALL_RECT windowSize1 = { 0, 0, 45, 20 };
		SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), 1, &windowSize1);
		COORD bufferSize1 = { 46, 21 };
		SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize1);
		system("cls");
		printf("\aNie uda\210o si\251 za\210adowa\206 stanu gry!\nNacisnij dowolny klawisz, \276eby kontynuowa\206");
		getchar();
		SMALL_RECT windowSize2 = { 0, 0, frame.x + 1, frame.y + 5 };
		SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), 1, &windowSize2);
		COORD bufferSize2 = { frame.x + 1 + 1, frame.y + 5 + 1 };
		SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize2);
	}
	return w;
}

int collision_check(char *map, Player *player, POINT frame, char object, char kierunek)
{
	switch (kierunek)
	{
	case 'P':
		if (*(map + (player->poss.y + player->shape[0].y) * (frame.x + 1) + player->poss.x + player->shape[0].x + 1) == object &&
			*(map + (player->poss.y + player->shape[1].y) * (frame.x + 1) + player->poss.x + player->shape[1].x + 1) == object &&
			*(map + (player->poss.y + player->shape[2].y) * (frame.x + 1) + player->poss.x + player->shape[2].x + 1) == object &&
			*(map + (player->poss.y + player->shape[3].y) * (frame.x + 1) + player->poss.x + player->shape[3].x + 1) == object) return 1;
		return 0;
	case 'L':
		if (*(map + (player->poss.y + player->shape[0].y) * (frame.x + 1) + player->poss.x + player->shape[0].x - 1) == object &&
			*(map + (player->poss.y + player->shape[1].y) * (frame.x + 1) + player->poss.x + player->shape[1].x - 1) == object &&
			*(map + (player->poss.y + player->shape[2].y) * (frame.x + 1) + player->poss.x + player->shape[2].x - 1) == object &&
			*(map + (player->poss.y + player->shape[3].y) * (frame.x + 1) + player->poss.x + player->shape[3].x - 1) == object) return 1;
		return 0;
	case 'G':
		if (*(map + (player->poss.y + player->shape[0].y - 1) * (frame.x + 1) + player->poss.x + player->shape[0].x) == object &&
			*(map + (player->poss.y + player->shape[1].y - 1) * (frame.x + 1) + player->poss.x + player->shape[1].x) == object &&
			*(map + (player->poss.y + player->shape[2].y - 1) * (frame.x + 1) + player->poss.x + player->shape[2].x) == object &&
			*(map + (player->poss.y + player->shape[3].y - 1) * (frame.x + 1) + player->poss.x + player->shape[3].x) == object) return 1;
		return 0;
	case 'D':
		if (*(map + (player->poss.y + player->shape[0].y + 1) * (frame.x + 1) + player->poss.x + player->shape[0].x) == object &&
			*(map + (player->poss.y + player->shape[1].y + 1) * (frame.x + 1) + player->poss.x + player->shape[1].x) == object &&
			*(map + (player->poss.y + player->shape[2].y + 1) * (frame.x + 1) + player->poss.x + player->shape[2].x) == object &&
			*(map + (player->poss.y + player->shape[3].y + 1) * (frame.x + 1) + player->poss.x + player->shape[3].x) == object) return 1;
		return 0;
	case 'R':
		if (*(map + (player->poss.y - player->shape[0].x) * (frame.x + 1) + player->poss.x + player->shape[0].y) == object &&
			*(map + (player->poss.y - player->shape[1].x) * (frame.x + 1) + player->poss.x + player->shape[1].y) == object &&
			*(map + (player->poss.y - player->shape[2].x) * (frame.x + 1) + player->poss.x + player->shape[2].y) == object &&
			*(map + (player->poss.y - player->shape[3].x) * (frame.x + 1) + player->poss.x + player->shape[3].y) == object) return 1;
		return 0;
	case 'O':
		if (*(map + player->poss.y * (frame.x + 1) + player->poss.x) == object &&
			*(map + player->poss.y * (frame.x + 1) + player->poss.x) == object &&
			*(map + player->poss.y * (frame.x + 1) + player->poss.x) == object &&
			*(map + player->poss.y * (frame.x + 1) + player->poss.x) == object) return 1;
		return 0;
	}
	return -1;
}

void random_Block(Player *player)
{
	srand(time(NULL));
	switch (rand() % 7)
	{
	case 0: //kwadrat
		player->shape[0].x = 0;
		player->shape[0].y = 0;
		player->shape[1].x = 1;
		player->shape[1].y = 0;
		player->shape[2].x = 0;
		player->shape[2].y = 1;
		player->shape[3].x = 1;
		player->shape[3].y = 1;
		return;
	case 1: //Z
		player->shape[0].x = -1;
		player->shape[0].y = 0;
		player->shape[1].x = 0;
		player->shape[1].y = 0;
		player->shape[2].x = 0;
		player->shape[2].y = 1;
		player->shape[3].x = 1;
		player->shape[3].y = 1;
		return;
	case 2: //!Z
		player->shape[0].x = 0;
		player->shape[0].y = 0;
		player->shape[1].x = 1;
		player->shape[1].y = 0;
		player->shape[2].x = -1;
		player->shape[2].y = 1;
		player->shape[3].x = 0;
		player->shape[3].y = 1;
		return;
	case 3: //L
		player->shape[0].x = 0;
		player->shape[0].y = -1;
		player->shape[1].x = 0;
		player->shape[1].y = 0;
		player->shape[2].x = 0;
		player->shape[2].y = 1;
		player->shape[3].x = 1;
		player->shape[3].y = 1;
		return;
	case 4: //!L
		player->shape[0].x = 0;
		player->shape[0].y = -1;
		player->shape[1].x = 0;
		player->shape[1].y = 0;
		player->shape[2].x = 0;
		player->shape[2].y = 1;
		player->shape[3].x = -1;
		player->shape[3].y = 1;
		return;
	case 5: //T
		player->shape[0].x = 0;
		player->shape[0].y = -1;
		player->shape[1].x = -1;
		player->shape[1].y = 0;
		player->shape[2].x = 0;
		player->shape[2].y = 0;
		player->shape[3].x = 1;
		player->shape[3].y = 0;
		return;
	case 6: //|
		player->shape[0].x = 0;
		player->shape[0].y = -1;
		player->shape[1].x = 0;
		player->shape[1].y = 0;
		player->shape[2].x = 0;
		player->shape[2].y = 1;
		player->shape[3].x = 0;
		player->shape[3].y = 2;
		return;
	}
}

void rotate(Player *player)
{
	int i, a;
	for (i = 0; i < 4; ++i)
	{
		a = player->shape[i].x;
		player->shape[i].x = -player->shape[i].y;
		player->shape[i].y = a;
	}
	return;
}

void komunikat(char *background, POINT	frame, char *tekst, int pX, int pY, char w, int ramka, Graphics_t *graphics)
{
	int iX = 0;
	int iY = 0;
	int t;
	int m = 0;
	if (frame.x < strlen(tekst))return;
	switch (w)
	{
	case 'L':
		for (t=-1;t<2;t++)
		{
			for (m=0;;m++)
			{
				*(background + ((frame.y / 2) + pY + t) * (frame.x + 1) + m + pX) = graphics->border.h;
			}
		}
		for (m = 0; tekst[m]; m++)
		{
			*(background + ((frame.y / 2) + pY) * (frame.x + 1) + m + pX) = tekst[m];
		}
		break;
	

	case 'P':
		for (m = 0; tekst[m]; m++)
		{
			*(background + ((frame.y / 2) + pY) * (frame.x + 1) + frame.x - strlen(tekst) + m + pX) = tekst[m];
		}
		break;

	case 'S':
		if (ramka)
		{
			for (t = -1; t < 2; t++)
			{
				switch (t)
				{
				case -1:
					*(background + ((frame.y / 2) + pY + t) * (frame.x + 1) + (frame.x / 2) - strlen(tekst) / 2 + pX - 1) = graphics->border.gl;
					break;
				case 0:
					*(background + ((frame.y / 2) + pY + t) * (frame.x + 1) + (frame.x / 2) - strlen(tekst) / 2  + pX - 1) = graphics->border.v;
					break;
				case 1:
					*(background + ((frame.y / 2) + pY + t) * (frame.x + 1) + (frame.x / 2) - strlen(tekst) / 2  + pX - 1) = graphics->border.dl;
					break;
				}
				for (m = 0; tekst[m]; m++)
				{
					*(background + ((frame.y / 2) + pY + t) * (frame.x + 1) + (frame.x / 2) - strlen(tekst) / 2 + m + pX) = graphics->border.h;
				}
				switch (t)
				{
				case -1:
					*(background + ((frame.y / 2) + pY + t) * (frame.x + 1) + (frame.x / 2) - strlen(tekst) / 2 + m + pX ) = graphics->border.gp;
					break;
				case 0:
					*(background + ((frame.y / 2) + pY + t) * (frame.x + 1) + (frame.x / 2) - strlen(tekst) / 2 + m + pX ) = graphics->border.v;
					break;
				case 1:
					*(background + ((frame.y / 2) + pY + t) * (frame.x + 1) + (frame.x / 2) - strlen(tekst) / 2 + m + pX ) = graphics->border.dp;
					break;
				}
			}
		}
		for (m = 0; tekst[m]; m++)
		{
			*(background + ((frame.y / 2)+pY) * (frame.x + 1) + (frame.x / 2) - strlen(tekst) / 2 + m + pX) = tekst[m];
		}
		break;
	}
}

int down(Board_t *board, Player *player, int timePopr, Wynik **tWynikow, Graphics_t *graphics)
{
	if (collision_check(board->mapB, player, board->frame, graphics->board.background, 'D')) player->poss.y++;
	else
	{
		int stack = 0;
		int t = 1;
		char m = 1;
		board->mapB[(player->poss.y + player->shape[0].y) * (board->frame.x + 1) + player->poss.x + player->shape[0].x] = graphics->board.ustawione;
		board->mapB[(player->poss.y + player->shape[1].y) * (board->frame.x + 1) + player->poss.x + player->shape[1].x] = graphics->board.ustawione;
		board->mapB[(player->poss.y + player->shape[2].y) * (board->frame.x + 1) + player->poss.x + player->shape[2].x] = graphics->board.ustawione;
		board->mapB[(player->poss.y + player->shape[3].y) * (board->frame.x + 1) + player->poss.x + player->shape[3].x] = graphics->board.ustawione;
		POINT primary;
		int xc;
		int yc;
		for (primary.y = 1; primary.y<board->frame.y - 1; ++primary.y)
		{
			for (primary.x = 1; primary.x <= board->frame.y - 1; ++primary.x)
			{
				if (board->mapB[primary.y * (board->frame.x + 1) + primary.x] == graphics->board.background) break;
				else if (primary.x == board->frame.x - 1)
				{
					for (xc = 1; xc <= board->frame.x - 2; ++xc)
					{
						board->mapB[primary.y * (board->frame.x + 1) + xc] = graphics->board.background;
					}
					for (yc = primary.y; yc>0; --yc)
					{
						for (xc = 1; xc <= board->frame.x - 2; ++xc)
						{
							if (yc>1) board->mapB[yc * (board->frame.x + 1) + xc] = board->mapB[(yc - 1) * (board->frame.x + 1) + xc];
							else board->mapB[yc * (board->frame.x + 1) + xc] = graphics->board.background;
						}
					}
					stack++;
				}
			}
		}
		if (stack != 0) player->points += sumaC(5, stack) * player->speed;
		else player->points += player->speed * 1;
		player->poss.x = board->frame.x / 2;
		player->poss.y = 2;
		random_Block(player);
		if (!collision_check(board->mapB, player, board->frame, graphics->board.background, 'O'))
		{
			Wynik wynik;
			wynik.wynik = player->points;
			wynik.czasGry = (clock() / (CLOCKS_PER_SEC)) - timePopr;
			char *tekst = { "Koniec gry!" };
			komunikat(board->mapB, board->frame, "Koniec gry!", 0, 0, 'S',1, graphics);
			system("cls");
			draw(board->mapB);
			if(!board->custom)wynikiPrownaj(&wynik, tWynikow);
			printf("\nWci\230nij Enter aby wr\242ci\206 do menu...");
			char znak;
			do { znak = getchar(); } while (znak != 13);
			return 0;
		}

	}
	return 1;
}

void gra(Wynik **tWynikow, struct Sterowanie *ster, Graphics_t *graphics)
{	
	Board_t board;
	_Board_Initilaze(&board);
	board.frame.x = 16;
	board.frame.y = 18;
	board.CreateMap(&board, graphics);
	Player player;
	_Player_Default(&player, board.frame);
	random_Block(&player);
	int timePopr = clock() / (CLOCKS_PER_SEC);
	while (1)
	{
		if (player.speed > board.level + 1) ++board.level;
		if (50 < board.cycle*player.speed)
		{
			board.cycle = 0;
			if (!down(&board, &player, timePopr, tWynikow, graphics))
			{
				board.Shutdown(&board);
				return;
			}
		}
		ster->Process_Input(ster);
		if (ster->direction.right.isRising && collision_check(board.mapB, &player, board.frame, graphics->board.background, 'P'))
		{
			player.poss.x++;
		}
		if (ster->direction.left.isRising && collision_check(board.mapB, &player, board.frame, graphics->board.background, 'L'))
		{
			player.poss.x--;
		}
		if (ster->direction.up.isRising && collision_check(board.mapB, &player, board.frame, graphics->board.background, 'R'))
		{
			//player.poss[1]--;
			rotate(&player);
		}
		if (ster->direction.down.isDown)
		{
			if (!down(&board, &player, timePopr, tWynikow, graphics))
			{
				board.Shutdown(&board);
				return;
			}
		}
		if (ster->zapis.isRising)
		{
			zapis(board.mapB, &player, board.frame, graphics);
		}
		if (ster->wczytanie.isRising)
		{
			board.mapB = wczyt(board.mapB, &player, board.frame, graphics);
			board.map = realloc(board.map, strlen(board.mapB) + 1);
			strcpy(board.map, board.mapB);
		}
		if (ster->pauza.isRising)
		{
			int pauza = 0;
			pauza = (clock() / (CLOCKS_PER_SEC));
			komunikat(board.map, board.frame, "Pauza", 0, 0, 'S', 1, graphics);
			draw(board.map);
			getchar();
			timePopr += (clock() / (CLOCKS_PER_SEC)) - pauza;
		}
		if (ster->nowy.isRising)
		{
			if (!board.CustomMap(&board, &player, graphics))return;
			timePopr = clock() / CLOCKS_PER_SEC;
		}
		if (ster->utilities.esc.isRising)
		{
			int pauza = 0;
			pauza = (clock() / (CLOCKS_PER_SEC));
			komunikat(board.map, board.frame, "Na pewno? T/N", 0, 0, 'S', 1, graphics);
			draw(board.map);
			char key = 0;
			do
			{
				if (key == 't')
				{
					board.Shutdown(&board);
					return;
				}
				key = getchar();
			} while (key != 'n');
			timePopr += (clock() / (CLOCKS_PER_SEC)) - pauza;
		}

		board.Print(&board, &player, graphics);
		player.time = (clock() / (CLOCKS_PER_SEC)) - timePopr;
		printf("Wynik: %.f\n", player.points);
		player.time >= 60 ? printf("Czas: %dmin %ds\n", player.time / 60, player.time % 60) : printf("Czas: %ds\n", player.time);
		printf("ESC aby wyjsc\n");
		board.cycle++;
		player.speed += 0.00017 * board.level;
		Sleep(20);
	}
	return;
}
