#include "opcje.h"
#include <stdio.h>
#include <windows.h>

void _Process_Key(struct Key *self)
{
    BOOL result = GetAsyncKeyState(self->code) & 0x8000;
    if (result)
    {		
        if (self->isDown) self->isRising = FALSE;
        else self->isRising = TRUE;
        self->isFalling = FALSE;
        self->isDown = TRUE;
    }
    else
    {
        if (self->isDown) self->isFalling = TRUE;
        else self->isFalling = FALSE;
        self->isRising = FALSE;
        self->isDown = FALSE;
    }
    return;
}

void _Key_Initialize(struct Key *self, char code)
{
    self->code = code;
    self->isDown = FALSE;
    self->isFalling = FALSE;
    self->isRising = FALSE;
    self->ProcessKey = &_Process_Key;
}

void _NumKeys_Default(struct NumKeys *self)
{
    _Key_Initialize(&self->num0, '0');
    _Key_Initialize(&self->num1, '1');
    _Key_Initialize(&self->num2, '2');
    _Key_Initialize(&self->num3, '3');
    _Key_Initialize(&self->num4, '4');
    _Key_Initialize(&self->num5, '5');
    _Key_Initialize(&self->num6, '6');
    _Key_Initialize(&self->num7, '7');
    _Key_Initialize(&self->num8, '8');
    _Key_Initialize(&self->num9, '9');
    return;
}

void _NumKeys_ProcessInput(struct NumKeys *self)
{
    _Process_Key(&self->num0);
    _Process_Key(&self->num1);
    _Process_Key(&self->num2);
    _Process_Key(&self->num3);
    _Process_Key(&self->num4);
    _Process_Key(&self->num5);
    _Process_Key(&self->num6);
    _Process_Key(&self->num7);
    _Process_Key(&self->num8);
    _Process_Key(&self->num9);
    return;
}

void _NumKeys_Initialize(struct NumKeys *self)
{
    self->Process_Input = &_NumKeys_ProcessInput;
    self->Default = &_NumKeys_Default;
    _NumKeys_Default(self);
    return;
}

void _DirectionKeys_Default(struct DirectionKeys *self)
{
    _Key_Initialize(&self->up, VK_UP);
    _Key_Initialize(&self->down, VK_DOWN);
    _Key_Initialize(&self->left, VK_LEFT);
    _Key_Initialize(&self->right, VK_RIGHT);
    return;
}

void _DirectionKeys_ProcessInput(struct DirectionKeys *self)
{
    _Process_Key(&self->down);
    _Process_Key(&self->up);
    _Process_Key(&self->left);
    _Process_Key(&self->right);
    return;
}

void _DirectionKeys_Initialize(struct DirectionKeys *self)
{
    self->Process_Input = &_DirectionKeys_ProcessInput;
    self->Default = &_DirectionKeys_Default;
    _DirectionKeys_Default(self);
    return;
}

void _UtilityKeys_Default(struct UtilityKeys *self)
{
    _Key_Initialize(&self->esc, VK_ESCAPE);
    _Key_Initialize(&self->enter, VK_RETURN);
    _Key_Initialize(&self->backspace, VK_BACK);
    return;
}

void _UtilityKeys_ProcessInput(struct UtilityKeys *self)
{
    _Process_Key(&self->esc);
    _Process_Key(&self->enter);
    _Process_Key(&self->backspace);
    return;
}

void _UtilityKeys_Initialize(struct UtilityKeys *self)
{
    self->Process_Input = &_UtilityKeys_ProcessInput;
    self->Default = &_UtilityKeys_Default;
    _UtilityKeys_Default(self);
    return;
}

void _Sterowanie_Default(struct Sterowanie *self)
{
    _Key_Initialize(&self->zapis, VK_F1);
    _Key_Initialize(&self->wczytanie, VK_F2);
    _Key_Initialize(&self->pauza, VK_SPACE);
    _Key_Initialize(&self->nowy, 'N');
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
    system("clear");

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
        system("clear");
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
            SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), tmpsize);
            SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), 1, &windowSize);
            SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize);
        }
    }
    return;
}
