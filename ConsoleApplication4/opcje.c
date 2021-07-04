#include "opcje.h"
#include <stdio.h>
#include <windows.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include "graphics/draw.h"
#include "input/keys.h"


void _Sterowanie_Default(struct Sterowanie *self)
{
    key_init(&self->zapis, VK_F1);
    key_init(&self->wczytanie, VK_F2);
    key_init(&self->pauza, VK_SPACE);
    key_init(&self->nowy, 'N');
    return;
}

void _Sterowanie_ProcessInput(struct Sterowanie *self)
{
    _Process_Key(&self->nowy);
    _Process_Key(&self->pauza);
    _Process_Key(&self->wczytanie);
    _Process_Key(&self->zapis);
    self->direction.Process_Input(&self->direction);
    self->utilities.Process_Input(&self->utilities);
    self->numbers.Process_Input(&self->numbers);
    return;
}

void _Sterowanie_Initialize(struct Sterowanie *self)
{
    self->Process_Input = &_Sterowanie_ProcessInput;
    self->Default = &_Sterowanie_Default;
     _Sterowanie_Default(self);
     _DirectionKeys_Initialize(&self->direction);
     _UtilityKeys_Initialize(&self->utilities);
     _NumKeys_Initialize(&self->numbers);
     return;
}

void _Graphics_Initialize(struct Graphics *self)
{
	_Ramka(&self->border);
	_Znaki(&self->chars);
	_Plansza(&self->board);
}

void _Ramka(struct Ramka *self)
{
	self->h = 205;
	self->v = 186;
	self->gl = 201;
	self->gp = 187;
	self->dl = 200;
	self->dp = 188;
}
void _Znaki(struct Znaki *self)
{
	self->lewy = 175;
	self->prawy = 174;
}
void _Plansza(struct Plansza *self)
{
	self->ramka = -78;
	self->background = -80;
	self->kursor = '@';
	self->ustawione = -79;
    return;
}

int absZnak(int a)
{
	return a < 0 ? 256 + a : a;
}

char *znakS(char lit)
{
    static char przycisk[8] = { 0 };
    switch (lit)
    {
    case VK_BACK:
        strcpy(przycisk, "B.SPACE");
        return przycisk;

    case VK_RETURN:
        strcpy(przycisk, "ENTER");
        return przycisk;

    case VK_ESCAPE:
        strcpy(przycisk, "ESC");
        return przycisk;

    case 30:
        strcpy(przycisk, "ALT-A");
        break;

    case VK_SPACE:
        strcpy(przycisk, "SPACJA");
        return przycisk;

    case 48:
        strcpy(przycisk, "ALT-B");
        break;

    case VK_F1:
        strcpy(przycisk, "F1");
        break;

    case VK_F2:
        strcpy(przycisk, "F2");
        break;

    case VK_F3:
        strcpy(przycisk, "F3");
        break;

    case VK_F4:
        strcpy(przycisk, "F4");
        break;

    case VK_F5:
        strcpy(przycisk, "F5");
        break;

    case  VK_F6:
        strcpy(przycisk, "F6");
        break;

    case  VK_F7:
        strcpy(przycisk, "F7");
        break;

    case  VK_F8:
        strcpy(przycisk, "F8");
        break;

    case  VK_F9:
        strcpy(przycisk, "F9");
        break;

    case  VK_F10:
        strcpy(przycisk, "F10");
        break;

    case  VK_F11:
        strcpy(przycisk, "F11");
        break;

    case  VK_F12:
        strcpy(przycisk, "F12");
        break;

    case VK_HOME:
        strcpy(przycisk, "Home");
        break;

    case 73:
        strcpy(przycisk, "PgDn");
        break;

    case VK_END:
        strcpy(przycisk, "End");
        break;

    case 81:
        strcpy(przycisk, "PgDn");
        break;

    case VK_INSERT:
        strcpy(przycisk, "Insert");
        break;

    case VK_DELETE:
        strcpy(przycisk, "Delete");
        break;

    case VK_UP:
        strcpy(przycisk, "\30");
        break;

    case VK_DOWN:
        strcpy(przycisk, "\31");
        break;

    case VK_LEFT:
        strcpy(przycisk, "\33");
        break;

    case VK_RIGHT:
        strcpy(przycisk, "\32");
        break;
    default:
        przycisk[0] = lit;
        przycisk[1] = 0;
    }


    return przycisk;
}

char wyglad(char znak)
{
    setConsoleSize(34, 35);

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
    clearConsole();

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
        char buf = getchar();

        switch (buf)
        {
        case KEY_INPUT:
            buf = getchar();
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

char przypisz(char *key)
{
	printf("Podaj nowy");
	*key = getchar();
	if (*key != KEY_INPUT && *key) return 0;
	*key = getchar();
	return 1;
}

void opcje(struct Sterowanie *ster, struct Graphics *graphics)
{
    setConsoleSize(41, 21);

    struct Kursor opcje;
    opcje.pozycja = 0;
    int num1 = 0;
    int ilosc = 0;
    while (1)
    {

        ilosc = 0;
        clearConsole();
        printf("Sterowanie\n\n");
        printf("%cPrzesu\344 w g\242r\251  : %s%c\n", graphics->chars.lewy * !(opcje.pozycja - ilosc), znakS(ster->direction.up.code), graphics->chars.prawy * !(opcje.pozycja - ilosc));	ilosc++;
        printf("%cPrzesu\344 w d\242\210   : %s%c\n", graphics->chars.lewy * !(opcje.pozycja - ilosc), znakS(ster->direction.down.code), graphics->chars.prawy * !(opcje.pozycja - ilosc));	ilosc++;
        printf("%cPrzesu\344 w lewo  : %s%c\n", graphics->chars.lewy * !(opcje.pozycja - ilosc), znakS(ster->direction.left.code), graphics->chars.prawy * !(opcje.pozycja - ilosc));		ilosc++;
        printf("%cPrzesu\344 w prawo : %s%c\n", graphics->chars.lewy * !(opcje.pozycja - ilosc), znakS(ster->direction.right.code), graphics->chars.prawy * !(opcje.pozycja - ilosc));		ilosc++;
        printf("%cPauza		 : %s%c\n", graphics->chars.lewy * !(opcje.pozycja - ilosc), znakS(ster->pauza.code), graphics->chars.prawy * !(opcje.pozycja - ilosc));				ilosc++;
        printf("%cZapisz gr\251	 : %s%c\n", graphics->chars.lewy * !(opcje.pozycja - ilosc), znakS(ster->zapis.code), graphics->chars.prawy * !(opcje.pozycja - ilosc));			ilosc++;
        printf("%cWczytaj gr\251	 : %s%c\n", graphics->chars.lewy * !(opcje.pozycja - ilosc), znakS(ster->wczytanie.code), graphics->chars.prawy * !(opcje.pozycja - ilosc)); ilosc++;
        printf("%cNiestandardowa gra	 : %s%c\n", graphics->chars.lewy * !(opcje.pozycja - ilosc), znakS(ster->nowy.code), graphics->chars.prawy * !(opcje.pozycja - ilosc)); ilosc++;
        printf("%cDomy\230lnie sterowanie%c\n", graphics->chars.lewy * !(opcje.pozycja - ilosc), graphics->chars.prawy * !(opcje.pozycja - ilosc));	ilosc++;
        for (num1 = 0; num1 < 41; num1++) printf("~");
        printf("\nWygl\245d\n\n");
        printf("%cRamka		 : %c%c\n", graphics->chars.lewy * !(opcje.pozycja - ilosc), graphics->board.ramka, graphics->chars.prawy * !(opcje.pozycja - ilosc));				ilosc++;
        printf("%cT\210o		 : %c%c\n", graphics->chars.lewy * !(opcje.pozycja - ilosc), graphics->board.background, graphics->chars.prawy * !(opcje.pozycja - ilosc));			ilosc++;
        printf("%cUstawione	 : %c%c\n", graphics->chars.lewy * !(opcje.pozycja - ilosc), graphics->board.ustawione, graphics->chars.prawy * !(opcje.pozycja - ilosc));			ilosc++;
        printf("%cKlocek		 : %c%c\n", graphics->chars.lewy * !(opcje.pozycja - ilosc), graphics->board.kursor, graphics->chars.prawy * !(opcje.pozycja - ilosc));			ilosc++;
        printf("%cDomy\230lnie%c\n", graphics->chars.lewy * !(opcje.pozycja - ilosc), graphics->chars.prawy * !(opcje.pozycja - ilosc));	ilosc++;
        printf("%cPowr\242t%c", graphics->chars.lewy * !(opcje.pozycja - ilosc), graphics->chars.prawy * !(opcje.pozycja - ilosc));			ilosc++;
        switch (getchar())
        {
        case KEY_INPUT:
            switch (getchar())
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
            
            case 8:
                ster->Default(ster);
                break;

            case 9:
                graphics->board.ramka = wyglad(graphics->board.ramka);
                break;

            case 10:
                graphics->board.background = wyglad(graphics->board.background);
                break;

            case 11:
                graphics->board.ustawione = wyglad(graphics->board.ustawione);
                break;

            case 12:
                graphics->board.kursor = wyglad(graphics->board.kursor);
                break;

            case 13:
                _Plansza(&graphics->board);
                break;

            case 14:
                return;
                break;
            }
            setConsoleSize(41, 21);
        }
    }
    return;
}

int kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF)
    {
    ungetc(ch, stdin);
    return 1;
    }

    return 0;
}