#pragma once
#include <stdbool.h>
#define KEY_INPUT 224
#define KEY_STATE(key_code) GetAsyncKeyState(key_code) & 0x8000

typedef struct Key
{
    bool isDown;
    bool isFalling;
    bool isRising;
    char code;
    void(*ProcessKey)(struct Key *self);
}Key;

void _Process_Key(struct Key *self);
void _Key_Initialize(struct Key *self, char code);

typedef struct NumKeys
{
    Key num0;
    Key num1;
    Key num2;
    Key num3;
    Key num4;
    Key num5;
    Key num6;
    Key num7;
    Key num8;
    Key num9;

    void(*Process_Input)(struct NumKeys *self);
    void(*Default)(struct NumKeys *self);
}NumKeys;

void _NumKeys_Default(struct NumKeys *self);
void _NumKeys_ProcessInput(struct NumKeys *self);
void _NumKeys_Initialize(struct NumKeys *self);

typedef struct DirectionKeys
{
    Key up;
    Key down;
    Key left;
    Key right;
    void(*Process_Input)(struct DirectionKeys *self);
    void(*Default)(struct DirectionKeys *self);
}DirectionKeys;

void _DirectionKeys_Default(struct DirectionKeys *self);
void _DirectionKeys_ProcessInput(struct DirectionKeys *self);
void _DirectionKeys_Initialize(struct DirectionKeys *self);

typedef struct UtilityKeys
{
    Key esc;
    Key enter;
    Key backspace;
    void(*Process_Input)(struct UtilityKeys *self);
    void(*Default)(struct UtilityKeys *self);
}UtilityKeys;

void _UtilityKeys_Default(struct UtilityKeys *self);
void _UtilityKeys_ProcessInput(struct UtilityKeys *self);
void _UtilityKeys_Initialize(struct UtilityKeys *self);

typedef struct Sterowanie
{
    struct DirectionKeys direction;
    struct NumKeys numbers;
    struct UtilityKeys utilities;
    Key zapis;
    Key wczytanie;
    Key pauza;
    Key nowy;
    

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

