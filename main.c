#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "gamelib.h"

int main()
{	
	time_t t;
	srand((unsigned) time(&t)); //inizializzo generatore di numeri casuali

	tutorial();
	
	puts("\n********************************\nBenvenuto a Lake Trasymeno, eheh\n********************************\n\n************************************************************************************************************************************************************************\nE' venerdì 13 giugno 1980 ed un gruppo di studenti universitari del Corso di Laurea in Informatica si trasferisce in vacanza al 'Campeggio Lake Trasymeno', che sta \nper riaprire. Ventitre anni prima, infatti, nello stesso campeggio, un ragazzino di nome Gieson era annegato per colpa della negligenza di un programmatore: a causa di un segmentation fault nel suo programma di noleggio delle barche, alla famiglia di Gieson era stata affidata una barca con un motore difettoso. Gieson però infesta \nancora il campeggio, e nutre vendetta nei confronti degli informatici poco attenti che hanno seguito il corso di Programmazione I giocando a League of Legends... \nGiacomo e Marzia, entrambi studenti del primo anno, rimangono isolati dagli altri quando...\n\n************************************************************************************************************************************************************************\n\n");
	int a;
	
	do 
	{
		printf("1) Crea mappa\n\n2) Gioca\n\n3) Termina gioco\n\n\n");
		scanf("%d", &a);

		switch (a)
		{
		case 1 :
		crea_mappa();
		break;

		case 2 :
		gioca();
		break;

		case 3:
		puts("\nSei sicuro?\n\n1) Sì\n\n2) No\n\n");
			scanf("%1d", &a);
			switch(a)
			{
				case 1:
				puts("\n***********\n*Game Over*\n***********\n");
				dealloca();
				exit(1);
				break;

				case 2:
				main();
				break;

				default:
				printf("\n****************************\nScelta non valida, riprovare\n****************************\n\n");
				break;	
			}

		default:
		printf("\n****************************\nScelta non valida, riprovare\n****************************\n\n");
		break;
		}
	}

	while (a != 3);

	return 0;
}