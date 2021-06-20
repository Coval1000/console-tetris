#include "../draw.h"
#include <windows.h>
#include <stdio.h>

///////////////
//Public Code//
///////////////

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    return;
}

void draw(char *d)
{
    gotoxy(0, 0);
    puts(d);
    return;
}

void setConsoleSize(int width, int height)
{
    COORD tmpsize = { 260, 300 };
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), tmpsize);
    COORD bufferSize = { width, height };
    SMALL_RECT konsola = { 0, 0, width - 1 , height - 1 };
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), 1, &konsola);
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize);
    return;
}

void clearConsole(void)
{
    system("clear");
    return;
}