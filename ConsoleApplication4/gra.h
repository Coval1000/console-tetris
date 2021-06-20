#pragma once
#include <stdbool.h>
#include "opcje.h"
#include "wynik.h"
#include <stdlib.h>
#include <windows.h>

typedef struct Player
{
    POINT poss;
    POINT shape[4];
    float speed;
    float points;
    int time;
} Player_t;

void _Player_Default(Player_t *self, POINT frame);
typedef struct Board
{
    POINT frame;
    char *map;
    char *mapB;
    int level;
    int cycle;
    int custom;
    
    bool(*CreateMap)(struct Board *self, Graphics_t *graphics);
    bool(*CustomMap)(struct Board *self, Player_t *player, Graphics_t *graphics);
    void(*Shutdown)(struct Board *self);
    void(*Print)(struct Board *self, Player_t *player, Graphics_t *graphics);
} Board_t;

void _Board_Print(Board_t *self, Player_t *player, Graphics_t *graphics);
void _Board_Shutdown(Board_t *self);
bool _Board_CreateMap(Board_t *self, Graphics_t *graphics);
bool _Board_CustomMap(Board_t *self, Player_t *player, Graphics_t *graphics);
void _Board_Initilaze(Board_t *self);
int ptg(int a, int b);
int sumaC(int a, int b);
void zapis(char *w, Player_t *player, POINT frame, Graphics_t *graphics);
char *wczyt(char *w, Player_t *player, POINT frame, Graphics_t *graphics);
int collision_check(char *map, Player_t *player, POINT frame, char object, char kierunek);
void random_Block(Player_t *player);
void rotate(Player_t *player);
void komunikat(char *background, POINT	frame, char *tekst, int pX, int pY, char w, int ramka, Graphics_t *graphics);
int down(Board_t *board, Player_t *player, int timePopr, Wynik_t **tWynikow, Graphics_t *graphics);
void gra(Wynik_t **tWynikow, struct Sterowanie *ster, Graphics_t *graphics);
