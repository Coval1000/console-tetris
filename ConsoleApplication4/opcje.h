#pragma once
#include <stdbool.h>
#include "input/keys.h"

typedef struct Sterowanie
{
    struct DirectionKeys direction;
    struct NumKeys numbers;
    struct UtilityKeys utilities;
    Key_t zapis;
    Key_t wczytanie;
    Key_t pauza;
    Key_t nowy;
    

    void(*Process_Input)(struct Sterowanie *self);
    void(*Default)(struct Sterowanie *self);
}Sterowanie;

void _Sterowanie_Default(struct Sterowanie *self);
void _Sterowanie_ProcessInput(struct Sterowanie *self);
void _Sterowanie_Initialize(struct Sterowanie *self);

struct Kursor
{
    char aktywny[10];
    char pozycja;
};

struct Plansza
{
    char ramka;
    char background;
    char kursor;
    char ustawione;
};
struct Ramka
{
    char h;
    char v;
    char gl;
    char gp;
    char dl;
    char dp;
};
struct Znaki
{
    char lewy;
    char prawy;
};

typedef struct Graphics
{
    struct Znaki chars;
    struct Ramka border;
    struct Plansza board;
} Graphics_t;


void _Ramka(struct Ramka *self);
void _Znaki(struct Znaki *self);
void _Plansza(struct Plansza *self);
void _Graphics_Initialize(Graphics_t *self);

int absZnak(int a);

char *znakS(char lit);

char wyglad(char znak);

char przypisz(char *key);

void opcje(struct Sterowanie *ster, Graphics_t *graphics);

int kbhit(void);