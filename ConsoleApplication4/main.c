#include <stdio.h>
#include "gra.h"
#include "wynik.h"
#include "graphics/draw.h"

#define WINDOW_DEFAULT_WIDTH 	(21)
#define WINDOW_DEFAULT_HEIGHT	(21)

int main()
{
    SetConsoleTitle(TEXT("Projekt Tetris"));
    
    struct Sterowanie controls;
    _Sterowanie_Initialize(&controls);

    struct Graphics graphics;
    _Graphics_Initialize(&graphics);

    Wynik_t *tWynikow;
    tWynikow = malloc(sizeof(Wynik_t));
    tWynikow = wynikiWczyt(tWynikow);

    struct Kursor kursor;
    kursor.pozycja = 0;

    int ilosc = 0;

    setConsoleSize(WINDOW_DEFAULT_WIDTH, WINDOW_DEFAULT_HEIGHT);
    while (1)
    {
        ilosc = 0;
        clearConsole();
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
            setConsoleSize(WINDOW_DEFAULT_WIDTH, WINDOW_DEFAULT_HEIGHT);
            break;

        case '2':
            opcje(&controls, &graphics);
            setConsoleSize(WINDOW_DEFAULT_WIDTH, WINDOW_DEFAULT_HEIGHT);
            break;

        case '3':
            wyniki(tWynikow);
            setConsoleSize(WINDOW_DEFAULT_WIDTH, WINDOW_DEFAULT_HEIGHT);
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
            setConsoleSize(WINDOW_DEFAULT_WIDTH, WINDOW_DEFAULT_HEIGHT);
        }

    }
    return 0;
}
