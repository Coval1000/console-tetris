#pragma once
#include "biblioteki.h"

	struct Wynik
	{
		float wynik;
		int czasGry;
		char imie[15];
	};
	typedef struct Wynik Wynik;

	int lWynikow = 0;

	int logT(int a)
	{
		if (!(a /= 10))	return 1;
		return 1 + logT(a);
	}

	void imie(Wynik *wynik)
	{
		int i = 0;
		char b = 8;
		(*wynik).imie[i] = 0;
		do
		{
			if (b == 8 && i>0)
			{
				(*wynik).imie[i] = 0;
				i--;
				putchar(8);
				putchar(' ');
				putchar(8);
			}
			else if (b != 8 && i < 14)
			{
				(*wynik).imie[i] = b;
				i++;
				(*wynik).imie[i] = 0;
				putchar((*wynik).imie[i - 1]);
			}
		} while ((b = getchar()) != 13);
	}

	Wynik *wynikiDodaj(Wynik *tWynikow)
	{

		void *tmp = tWynikow;
		if (tmp = realloc(tWynikow, sizeof(Wynik)*(lWynikow + 1)))
		{
			tWynikow = tmp;
		}
		else
		{
			system("cls");
			printf("\aB\210ad pami\251ci");
			exit(10);
		}
		tWynikow[lWynikow].wynik = 0;
		tWynikow[lWynikow].czasGry = 0;
		tWynikow[lWynikow].imie[0] = 0;
		lWynikow++;
		return tWynikow;
	}

	void wynikiZapis(Wynik *tWynikow)
	{
		int i = 0;
		int j = 0;
		FILE *zapisz;
		zapisz = fopen("wyniki.txt", "wb");
		fprintf(zapisz, "%d", lWynikow);
		putc(0, zapisz);

		for (i = 0; i<lWynikow; i++)
		{
			fprintf(zapisz, "%g", (*(tWynikow + i)).wynik);
			putc(0, zapisz);
			fprintf(zapisz, "%d", (*(tWynikow + i)).czasGry);
			putc(0, zapisz);
			for (j = 0; (*(tWynikow + i)).imie[j]; j++)
			{
				fprintf(zapisz, "%c", (*(tWynikow + i)).imie[j]);
			}
			putc(0, zapisz);
		}
		fclose(zapisz);
		return;
	}

	Wynik *wynikiWczyt(Wynik *tWynikow)
	{
		FILE *wczytaj;
		wczytaj = fopen("wyniki.txt", "rb");
		if (wczytaj)
		{
			int i = 0;
			int j = 0;
			int b = 0;
			char trans = 1;

			for (trans = getc(wczytaj); trans; trans = getc(wczytaj)) i = (trans - 48) + i * 10;

			while (lWynikow<i)
			{
				tWynikow = wynikiDodaj(tWynikow);
				j = 0;
				(*(tWynikow + lWynikow - 1)).wynik = 0;
				(*(tWynikow + lWynikow - 1)).czasGry = 0;
				while (trans = getc(wczytaj))
				{
					if (!j && trans != '.')
					{
						(*(tWynikow + lWynikow - 1)).wynik = (trans - 48) + ((*(tWynikow + lWynikow - 1)).wynik) * 10;
					}
					else if (j && trans != '.')
					{
						(*(tWynikow + lWynikow - 1)).wynik = (trans - 48)*(1. / (float)ptg(10, j)) + (*(tWynikow + lWynikow - 1)).wynik;
						j++;
					}
					else j++;
				}

				for (trans = getc(wczytaj); trans; trans = getc(wczytaj)) (*(tWynikow + lWynikow - 1)).czasGry = (trans - 48) + (*(tWynikow + lWynikow - 1)).czasGry * 10;
				j = 0;
				do
				{
					fscanf(wczytaj, "%c", tWynikow[lWynikow - 1].imie + j);
					j++;
				} while (tWynikow[lWynikow - 1].imie[j - 1]);
			}
			fclose(wczytaj);
		}
		return tWynikow;
	}

	int wynikiPrownaj(Wynik *wynik, Wynik **tWynikow)
	{

		if ((*wynik).wynik > (*tWynikow)[lWynikow - 1].wynik)
		{
			if (!*tWynikow || lWynikow < 10) *tWynikow = wynikiDodaj(*tWynikow);
			int p = lWynikow - 1;//NIE U�YWA� FOR(;;) - siedlisko patologii!!!
			while (p >= 0 && (*wynik).wynik >(*tWynikow)[p].wynik)
			{
				if (p < lWynikow - 1)
				{
					(*tWynikow)[p + 1].czasGry = (*tWynikow)[p].czasGry;
					(*tWynikow)[p + 1].wynik = (*tWynikow)[p].wynik;
					strcpy((*tWynikow)[p + 1].imie, (*tWynikow)[p].imie);
				}
				if (p == 0 || (*wynik).wynik < (*tWynikow)[p - 1].wynik)
				{
					(*tWynikow)[p].czasGry = (*wynik).czasGry;
					(*tWynikow)[p].wynik = (*wynik).wynik;
					printf("%d. Miejsce!\nPodaj imie:\n", p + 1);
					imie(wynik);
					strcpy((*tWynikow)[p].imie, (*wynik).imie);
					wynikiZapis((*tWynikow));
					return p + 1;
				}
				p--;
			}//siedlisko patologii!!!
		}
		return 0;
	}

	void wyniki(Wynik *tWynikow)
	{
		SMALL_RECT windowSize = { 0, 0, 50, 20 };
		COORD bufferSize = { 51, 21 };
		COORD tmpsize = { 80, 300 };
		SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), tmpsize);
		SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), 1, &windowSize);
		SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize);

		int pozycja = 0;
		int l;
		int b = logT((int)tWynikow[pozycja].wynik);
		system("cls");
		printf("Wyniki\n\n");
		for (pozycja = 0; pozycja<lWynikow; pozycja++)
		{
			printf("%d.", pozycja + 1);
			for (l = 2 - logT(pozycja+1); l >= 0; l--)putchar(' ');
			printf("%s", tWynikow[pozycja].imie);
			for (l = 15 - strlen(tWynikow[pozycja].imie) + b - logT((int)tWynikow[pozycja].wynik); l >= 0; l--)putchar('.');
			printf("%.fp", tWynikow[pozycja].wynik);			
			for (l = 10 - b - logT(tWynikow[pozycja].czasGry / 60); l >= 0; l--)putchar(' ');
			printf("%dmin %s%ds\n",tWynikow[pozycja].czasGry / 60, (tWynikow[pozycja].czasGry % 60) < 10 ? "0" : "" , tWynikow[pozycja].czasGry % 60);
		}
		getchar();
	}



