#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "gamelib.h"

static Zona *prima_zona = NULL;
static Zona *ultima_zona = NULL;
static Zona *temp = NULL;
static Giocatore *Giocatori[2];
static int turno = 0, player = 0, mossa = 1; //player da mettere static per evitare problemi con i turni e con l'alternarsi dei giocatori, mossa serve principalmente per la funzione adrenalina;
static int CountZone = 0; //numero di zone presenti

void termina_gioco()
{
	puts("\n***********\n*Game Over*\n***********\n");
	for(int i = 0; i < 2; i++)
	{
		free(Giocatori[i]);
	}

	for (int i = 0; i < CountZone; i++)
	{
		if (ultima_zona == prima_zona)
		{
			free(ultima_zona);
			prima_zona = NULL;
			ultima_zona = NULL;
		}
		
		else
		{
			Zona * point = prima_zona;
			temp = point;

			while (point-> zona_successiva != NULL)
			{
				temp = point;						//temp punta alla penultima zona
				point = point -> zona_successiva;	//point è il valore dell'ultima zona
			}

			free(ultima_zona);
			ultima_zona = temp;
			ultima_zona -> zona_successiva = NULL;
		}
	}
	exit(1);
}

static void avanza(Giocatore *Giocatori)
{
	if(Giocatori -> posizione -> zona != USCITA_CAMPEGGIO)
	{
		Zona *temp = Giocatori -> posizione;
		temp = temp -> zona_successiva;
		Giocatori -> posizione = temp;
		printf("\n\nSei arrivato nella zona: ");
		switch (temp -> zona)
		{
			case 1:
			printf("Cucina\n\n");
			break;

			case 2:
			printf("Soggiorno\n\n");
			break;

			case 3:
			printf("Rimessa\n\n");
			break;

			case 4:
			printf("Strada\n\n");
			break;

			case 5:
			printf("Lungo Lago\n\n");
			break;

			case 6:
			printf("Uscita del campeggio\n\n");
			break;
		}
		mossa--;
	}

	else if (Giocatori -> posizione -> zona == USCITA_CAMPEGGIO)
	{
		printf("\n\n*************************************************************************\nSegmentation Fault 11: Gieson non può seguirti fin qui, %s\n*************************************************************************\n\n", player == 0 ? "Giacomo sei salvo!" : "Marzia sei salva!");
		Giocatori -> stato_giocatore = 1;
		mossa--;
	}
}

static void mostra_oggetto(Giocatore *Giocatori)
{
	switch(Giocatori -> posizione -> oggetto)
		{
			case 0:
			printf("\n\n*************************************************\nL'oggetto presente nella zona è una Cianfrusaglia\n*************************************************\n\n");
			break;

			case 1:
			printf("\n\n************************************************\nGli oggetti presenti nella zona sono delle Bende\n************************************************\n\n");
			break;

			case 2:
			printf("\n\n*******************************************\nL'oggetto presente nella zona è un Coltello\n*******************************************\n\n");
			break;

			case 3:
			printf("\n\n*******************************************\nL'oggetto presente nella zona è una Pistola\n*******************************************\n\n");
			break;

			case 4:
			printf("\n\n*********************************************\nL'OGGETTO PRESENTE NELLA ZONA E' DELLA BENZINAAAAAA\n*********************************************\n\n");
			break;

			case 5:
			printf("\n\n*****************************************\nL'oggetto presente nella zona è dell'Adrenalina\n*****************************************\n\n");
			break;
		}
	
	mossa--;
}

static void prendi_oggetto(Giocatore *Giocatori)
{
	int o = Giocatori -> posizione -> oggetto;
	int a;
	Giocatori -> zaino[o] ++;
	if (o != CIANFRUSAGLIA)
	{
		int o = Giocatori -> posizione -> oggetto;
		Giocatori -> zaino[o] ++;
		switch(o)
		{
			case 0:
			printf("\n\n******************************\nHai raccolto una Cianfrusaglia\n******************************\n\n");
			break;

			case 1:
			printf("\n\n************************\nHai raccolto delle Bende\n************************\n\n");
			break;

			case 2:
			printf("\n\n************************\nHai raccolto un Coltello\n************************\n\n");
			break;

			case 3:
			printf("\n\n************************\nHai raccolto una Pistola\n************************\n\n");
			break;

			case 4:
			printf("\n\n*******************************\nHAI RACCOLTO DELLA BENZINAAAAAA\n*******************************\n\n");
			break;

			case 5:
			printf("\n\n****************************\nHai raccolto dell'Adrenalina\n****************************\n\n");
			break;
		}
		Giocatori -> posizione -> oggetto = CIANFRUSAGLIA;
		mossa--;
	}

	else if (o == CIANFRUSAGLIA)
	{
		printf("\n\n******************************************************\nVuoi davvero raccogliere una Cianfrusaglia? Sul serio?\n******************************************************\n\n1) Sì\n\n2) No\n\n");
		scanf("%d", &a);
		if(player == 1)
		{
			switch(a)
			{
				case 1:
				printf("\n\n********************************************\nSCORDATELO, COL CAVOLO CHE TOCCO QUELLA ROBA\n********************************************\n\n");
				break;

				case 2:
				printf("\n\n***************************************\nGrazie al cielo, un po'di buon senso...\n***************************************\n\n");
				break;
			}
		}
		else if (player == 0)
		{
			switch(a)
			{
				case 1:
				printf("\n\n*****************************************************************************************************\nNon credo sia il caso di mettersi a raccogliere certe cavolate, non vedo come potrebbe tornarci utile\n*****************************************************************************************************\n\n");
				break;

				case 2:
				printf("\n\n****************************************\nMeglio così, andiamo avanti che è meglio\n****************************************\n\n");
				break;
			}
		}
	}	
}

static void cura(Giocatore *Giocatori)
{
	int a;
	if (Giocatori -> stato_giocatore == 3)
	{
		puts("\n*******************************************\nNon è necessario curarsi: hai tutta la vita\n\nVuoi farlo lo stesso? \n\n1) Sì\n\n2) No\n\nTe lo sconsiglio vivamente: non ha senso!\n*******************************************\n");
		scanf("%d", &a);

		switch(a)
		{
			case 1:
			Giocatori -> zaino[BENDE] --;
			Giocatori -> stato_giocatore = 3;
			puts("\n*********************************************************************************************\nTi sei curato nonostante avessi tutta la vita e hai pure perso un turno... Bravo il salame...\n*********************************************************************************************\n");
			break;

			case 2:
			mossa++;
			break;

			default:
			printf("\n****************************\nScelta non valida, riprovare\n****************************\n\n");
			break;
		}
	}

	else if (Giocatori -> zaino[BENDE] == 0)
	{
		puts("Non hai Bende per curarti, mi dispiace per te");
	}

	else if (Giocatori -> stato_giocatore == 2 && Giocatori -> zaino[BENDE] > 0)
	{
		Giocatori -> zaino[BENDE] --;
		Giocatori -> stato_giocatore = 3;
		puts("Bravissimo, ti sei curato :D");
	}
	mossa--;
}

static void usa_adrenalina(Giocatore *Giocatori)
{
	if(Giocatori -> zaino[ADRENALINA] > 0)
	{
		Giocatori -> zaino[ADRENALINA]--;
		mossa ++;
	}

	else
		puts("Non hai nessuna Adrenalina");
}

static void zaino(Giocatore *Giocatori)
{
	printf("\n\n****************************\nLo zaino di %s contiene\n\n", player == 0 ? "Giacomo" : "Marzia");

	for (int i = 0; i < 6; i++)
	{
		switch(i)
		{
			case 0:
			printf("\nCianfrusaglia: %d\n\n", Giocatori -> zaino[i]);
			break;

			case 1:
			printf("Bende: %d\n\n", Giocatori -> zaino[i]);
			break;

			case 2:
			printf("Coltello: %d\n\n", Giocatori -> zaino[i]);
			break;

			case 3:
			printf("Pistola: %d\n\n", Giocatori -> zaino[i]);
			break;

			case 4:
			printf("Benzina: %d\n\n", Giocatori -> zaino[i]);
			break;

			case 5:
			printf("Adrenalina: %d\n\n", Giocatori -> zaino[i]);
			break;
		}
	}
	puts("****************************");
}

static void inizializza()
{
	for (int i = 0; i < 2; i++)
	{
		Giocatori[i] = (Giocatore*) malloc(sizeof(Giocatore));
		Giocatori[i] -> stato_giocatore = 3;
		Giocatori[i] -> posizione = prima_zona;
	}

	Giocatori[0] -> zaino[COLTELLO] = 1;
	Giocatori[1] -> zaino[ADRENALINA] = 2;
	turno++;
}

static void random_map()
{
	printf("\n\nSelezionare livello di difficoltà:\n\n1) Facile\n\n2) Medio\n\n3) Difficile\n\n4) Folle\n\n");
	int a, numero_mappe, zone, oggetto;
	scanf("%d", &a);
	switch(a)
	{
		case 1:
		numero_mappe = rand() % (10 + 1 - 8) + 8;
		break;

		case 2:
		numero_mappe = rand() % (25 + 1 - 10) + 10;
		break;

		case 3:
		numero_mappe = rand() % (50 + 1 - 25) + 25;
		break;

		case 4:
		numero_mappe = rand() % (100 + 1 - 50) + 50;
		break;

		default:
		printf("\n****************************\nScelta non valida, riprovare\n****************************\n\n");
		break;
	}

	for (int i = 0; i < numero_mappe; i++)
	{
		if (prima_zona == NULL)
		{
			prima_zona = (Zona *) malloc(sizeof(Zona));
			ultima_zona = (Zona *) malloc(sizeof(Zona));
			ultima_zona = prima_zona;
		}

		else
		{
			ultima_zona -> zona_successiva = (Zona *) malloc(sizeof(Zona));
			ultima_zona = ultima_zona -> zona_successiva;						//Si alloca memoria per l'area successiva
			ultima_zona -> zona_successiva = NULL;
		}

		zone = rand()%5 + 1;
		oggetto = rand()%10;

		switch (zone)
		{	
			case 1:
			ultima_zona -> zona = CUCINA;

			switch(oggetto)
			{
				case 0 ... 2 :
				ultima_zona -> oggetto = CIANFRUSAGLIA;
				break;

				case 3 ... 4 :
				ultima_zona -> oggetto = BENDE;
				break;

				case 5 ... 8 :
				ultima_zona -> oggetto = COLTELLO;
				break;

				case 9:
				ultima_zona -> oggetto = ADRENALINA;
				break;
			}
			break;

			case 2:
			ultima_zona -> zona = SOGGIORNO;

			switch(oggetto)
			{
				case 0 ... 1 :
				ultima_zona -> oggetto = CIANFRUSAGLIA;
				break;

				case 2 :
				ultima_zona -> oggetto = BENDE;
				break;

				case 3 :
				ultima_zona -> oggetto = COLTELLO;
				break;

				case 4 ... 6 :
				ultima_zona -> oggetto = PISTOLA;
				break;

				case 7 ... 9:
				ultima_zona -> oggetto = ADRENALINA;
				break;
			}
			break;

			case 3:
			ultima_zona -> zona = RIMESSA;

			switch(oggetto)
			{
				case 0 ... 1 :
				ultima_zona -> oggetto = CIANFRUSAGLIA;
				break;

				case 2 :
				ultima_zona -> oggetto = BENDE;
				break;

				case 3 ... 5 :
				ultima_zona -> oggetto = COLTELLO;
				break;

				case 6 ... 8 :
				ultima_zona -> oggetto = BENZINA;
				break;

				case 9:
				ultima_zona -> oggetto = ADRENALINA;
				break;
			}				
			break;

			case 4:
			ultima_zona -> zona = STRADA;

			switch(oggetto)
			{
				case 0 ... 7 :
				ultima_zona -> oggetto = CIANFRUSAGLIA;
				break;

				case 8 :
				ultima_zona -> oggetto = COLTELLO;
				break;

				case 9:
				ultima_zona -> oggetto = BENZINA;
				break;
			}				
			break;

			case 5:
			ultima_zona -> zona = LUNGO_LAGO;

			switch(oggetto)
			{
				case 0 ... 6 :
				ultima_zona -> oggetto = CIANFRUSAGLIA;
				break;

				case 7 :
				ultima_zona -> oggetto = COLTELLO;
				break;

				case 8 ... 9:
				ultima_zona -> oggetto = BENZINA;
				break;
			}			
			break;
		}
	}

	ultima_zona -> zona_successiva = (Zona *) malloc(sizeof(Zona));
	ultima_zona = ultima_zona -> zona_successiva;
	ultima_zona -> zona_successiva = NULL;
	ultima_zona -> zona = USCITA_CAMPEGGIO;
	oggetto = rand()%10;

	switch(oggetto)
	{
		case 0 ... 8 :
		ultima_zona -> oggetto = CIANFRUSAGLIA;
		break;

		case 9 :
		ultima_zona -> oggetto = COLTELLO;
		break;
	}
}

static void ins_zona()
{	
	int b, oggetto; // b = parametro di scelta nella funzione ins_zona(), o = parametro per la generazione di oggetti nelle mappe
	if (prima_zona == NULL)
	{
	prima_zona = (Zona *) malloc(sizeof(Zona));
	ultima_zona = (Zona *) malloc(sizeof(Zona));
	ultima_zona = prima_zona;
	}

	else if (ultima_zona -> zona == 6)
	{
		printf("\n****************************************************************\nL'ultima zona deve essere necessariamente l'Uscita del Campeggio\n****************************************************************\n\n");
		crea_mappa();
	}

	else
	{
	ultima_zona -> zona_successiva = (Zona *) malloc(sizeof(Zona));
	ultima_zona = ultima_zona -> zona_successiva;						//Si alloca memoria per l'area successiva
	ultima_zona -> zona_successiva = NULL;
	}

	puts("\n\n**********************************************************************\nScegliere le aree della mappa (verranno inserite nell'ordine digitato):\n**********************************************************************\n\n1) Cucina\n\n2) Soggiorno\n\n3) Rimessa\n\n4) Strada\n\n5) Lungo Lago\n\n6) Uscita Campeggio\n\n");
	oggetto = rand() % 10;
	scanf("%d", &b);

	switch (b) //assegna un valore da 1 a 6 all'ultima zona
	{	
		case 1:
			ultima_zona -> zona = CUCINA;

			switch(oggetto)
			{
				case 0 ... 2 :
				ultima_zona -> oggetto = CIANFRUSAGLIA;
				break;

				case 3 ... 4 :
				ultima_zona -> oggetto = BENDE;
				break;

				case 5 ... 8 :
				ultima_zona -> oggetto = COLTELLO;
				break;

				case 9:
				ultima_zona -> oggetto = ADRENALINA;
				break;
			}

		break;

		case 2:
			ultima_zona -> zona = SOGGIORNO;

			switch(oggetto)
			{
				case 0 ... 1 :
				ultima_zona -> oggetto = CIANFRUSAGLIA;
				break;

				case 2 :
				ultima_zona -> oggetto = BENDE;
				break;

				case 3 :
				ultima_zona -> oggetto = COLTELLO;
				break;

				case 4 ... 6 :
				ultima_zona -> oggetto = PISTOLA;
				break;

				case 7 ... 9:
				ultima_zona -> oggetto = ADRENALINA;
				break;
			}

		break;

		case 3:
			ultima_zona -> zona = RIMESSA;

			switch(oggetto)
			{
				case 0 ... 1 :
				ultima_zona -> oggetto = CIANFRUSAGLIA;
				break;

				case 2 :
				ultima_zona -> oggetto = BENDE;
				break;

				case 3 ... 5 :
				ultima_zona -> oggetto = COLTELLO;
				break;

				case 6 ... 8 :
				ultima_zona -> oggetto = BENZINA;
				break;

				case 9:
				ultima_zona -> oggetto = ADRENALINA;
				break;
			}
			
		break;

		case 4:
			ultima_zona -> zona = STRADA;

			switch(oggetto)
			{
				case 0 ... 7 :
				ultima_zona -> oggetto = CIANFRUSAGLIA;
				break;

				case 8 :
				ultima_zona -> oggetto = COLTELLO;
				break;

				case 9:
				ultima_zona -> oggetto = BENZINA;
				break;
			}
			
		break;

		case 5:
			ultima_zona -> zona = LUNGO_LAGO;

			switch(oggetto)
			{
				case 0 ... 6 :
				ultima_zona -> oggetto = CIANFRUSAGLIA;
				break;

				case 7 :
				ultima_zona -> oggetto = COLTELLO;
				break;

				case 8 ... 9:
				ultima_zona -> oggetto = BENZINA;
				break;
			}
			
		break;

		case 6:
			ultima_zona -> zona = USCITA_CAMPEGGIO;

			switch(oggetto)
			{
				case 0 ... 8 :
				ultima_zona -> oggetto = CIANFRUSAGLIA;
				break;

				case 9 :
				ultima_zona -> oggetto = COLTELLO;
				break;
			}
			
		break;

		default:
			printf("\n\n****************************\nScelta non valida, riprovare\n****************************\n\n");
		break;
		}
		CountZone ++;
}

static void stampa_mappa()
{
	Zona * temp = prima_zona;

	puts("****************");
	int c = 1;

	while (temp != NULL)
	{
		printf("%d^ zona: ", c);
		switch (temp -> zona)
		{
		case 1:
		printf("Cucina\n");
		break;

		case 2:
		printf("Soggiorno\n");
		break;

		case 3:
		printf("Rimessa\n");
		break;

		case 4:
		printf("Strada\n");
		break;

		case 5:
		printf("Lungo Lago\n");
		break;

		case 6:
		printf("Uscita del Campeggio\n");
		break;
		}
		printf("L'indirizzo di memoria della zona successiva è %p\n\n", temp -> zona_successiva);
		/*switch (temp -> oggetto)
		{
		case 0:
		printf("Cianfrusaglia\n\n");
		break;

		case 1:
		printf("Bende\n\n");
		break;

		case 2:
		printf("Coltello\n\n");
		break;

		case 3:
		printf("Pistola\n\n");
		break;

		case 4:
		printf("Benzina\n\n");
		break;

		case 5:
		printf("Adrenalina\n\n");
		break;
		}*/
		temp = temp -> zona_successiva;
		c++;
	}
	puts("****************");
}

static void chiudi_mappa()
{
	main();
}


static void canc_zona()
{
	if (ultima_zona == NULL)
	{
		puts("\nBisogna aggiungere almeno una zona per poterla eliminare");
	}

	else if (ultima_zona == prima_zona)
	{
		free(ultima_zona);
		prima_zona = NULL;
		ultima_zona = NULL;
	}

	else
	{
		Zona * point = prima_zona;
		temp = point;

		while (point-> zona_successiva != NULL)
		{
			temp = point;						//temp punta alla penultima zona
			point = point -> zona_successiva;	//point è il valore dell'ultima zona
		}

		free(ultima_zona);
		ultima_zona = temp;
		ultima_zona -> zona_successiva = NULL;
	}
	CountZone --;
}


void crea_mappa()
{
	static int a; // a = parametro di scelta nella funzione crea_mappa()

	do 
	{
		printf("\n\n*************************************\nScegliere un'azione da intraprendere:\n*************************************\n\n\n1) Aggiungi zona\n\n2) Cancella zona\n\n3) Stampa mappa\n\n4) Mappa Random\n\n5) Chiudi mappa\n\n\n");
		scanf("%d", &a);
		puts("");

		switch (a)
		{

		case 1:
		ins_zona();
		break;

		case 2:
		canc_zona();
		break;

		case 3:
		stampa_mappa();
		break;

		case 4:
		random_map();
		break;

		case 5:
		chiudi_mappa();
		break;

		default:
		printf("\n********************************************\nScelta non valida, digitare un numero valido\n********************************************\n\n");
		break;
		}
	}
	while (a != 4);
}

void gioca()
{

	if (CountZone < 8) //prima verifica (servono almeno 8 zone per giocare)
	{
		puts("\n********************************************\n* Poche zone per giocare: aggiungine altre *\n********************************************\n\n");
		ins_zona();
	}

	else if (ultima_zona -> zona != 6) //seconda verifica (ultima zona per forza l'uscita del campeggio)
	{
		puts("\n********************************************************************************\n* L'ultima zona dev'essere per forza l'Uscita del Campeggio. Modifica la mappa *\n********************************************************************************\n\n");
		crea_mappa();
	}

	else
	{
		int a;
		Zona * temp = prima_zona; 

		do
		{
			if (turno == 0)
				{
					inizializza();
					player = rand() % 2;
				}

			else if(Giocatori[0] -> stato_giocatore != 1 && Giocatori[1] -> stato_giocatore != 1 && mossa == 0)
			{
				mossa = 1;
				turno++;
				player = !player;
			}

			else if (Giocatori[0] -> stato_giocatore == 1 && Giocatori[1] -> stato_giocatore == 1)
			{
				puts("\n***********\n*Game Over*\n***********\n");

				puts("\nAvviare una nuova partita?\n\n1) Sì\n\n2) No\n\n");
				scanf("%d", &a);

				switch(a)
				{
					case 1:
					main();
					break;

					case 2:
					termina_gioco();
					break;

					default:
					printf("\n****************************\nScelta non valida, riprovare\n****************************\n\n");
					break;
				}
			}

			else if (Giocatori[0] -> stato_giocatore == 1 || Giocatori[1] -> stato_giocatore == 1)
			{
			 	if (Giocatori[0] -> stato_giocatore == 1)
			 	{
			 		player = 1;
			 	}

			 	else
			 	{
			 		player = 0;
			 	}
			 	turno ++;
			}


			printf("\n\n*******************************************************\nTurno: %d\n\nGiocatore: %s\n\nStato del Giocatore: %s\n\nZona in cui si trova il giocatore: ", (turno+1)/2, player == 0 ? "Giacomo" : "Marzia", Giocatori[player] -> stato_giocatore == 3 ? "Vivo" : "Ferito");
			
			switch(Giocatori[player] -> posizione-> zona)
			{
				case 1:
				printf("Cucina\n");
				break;

				case 2:
				printf("Soggiorno\n");
				break;
				
				case 3:
				printf("Rimessa\n");
				break;

				case 4:
				printf("Strada\n");
				break;
				
				case 5:
				printf("Lungo Lago\n");
				break;
				
				case 6:
				printf("Uscita del Campeggio\n");
				break;
				
			}
			printf("*******************************************************\n\n");
			printf("\n\n1) Avanza di zona\n\n2) Mostra l'oggetto presente nella zona\n\n3) Raccogli l'oggetto presente nella zona\n\n4) Curati\n\n5) Usa l'adrenalina\n\n6) Visualizza zaino\n\n7) Esci dal gioco\n\n\n");
			scanf("%1d", &a);

			switch (a)
			{
				case 1 :
				avanza(Giocatori[player]);
				break;

				case 2 :
				mostra_oggetto(Giocatori[player]);
				break;

				case 3:
				prendi_oggetto(Giocatori[player]);
				break;

				case 4:
				cura(Giocatori[player]);
				break;

				case 5:
				usa_adrenalina(Giocatori[player]);
				break;

				case 6:
				zaino(Giocatori[player]);
				player = !player;
				break;

				case 7:
				puts("\nSei sicuro?\n\n1) Sì\n\n2) No\n\n");
				scanf("%1d", &a);
					switch(a)
					{
						case 1:
						termina_gioco();
						break;

						case 2:
						gioca();
						turno --;
						break;

						default:
					printf("\n****************************\nScelta non valida, riprovare\n****************************\n\n");
					turno --;
					break;	
					}
				break;

				default:
				printf("\n****************************\nScelta non valida, riprovare\n****************************\n\n");
				turno --;
				break;
			}

		}

		while(1);
	}
}
