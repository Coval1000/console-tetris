#pragma once

typedef struct Wynik
{
    float wynik;
    int czasGry;
    char imie[15];
} Wynik_t;

int logT(int a);
void imie(Wynik_t *wynik);
Wynik_t *wynikiDodaj(Wynik_t *tWynikow);
void wynikiZapis(Wynik_t *tWynikow);
Wynik_t *wynikiWczyt(Wynik_t *tWynikow);
int wynikiPrownaj(Wynik_t *wynik, Wynik_t **tWynikow);
void wyniki(Wynik_t *tWynikow);
