#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "gamelib.h"

static Zona *prima_zona = NULL;
static Zona *ultima_zona = NULL;
static Zona *temp = NULL;
static Giocatore *Giocatori[2];
static int turn = 0, player = 0, mossa = 1, difficolta = 2, benzina_usata = 0, scelta_oggetti = 0, Spawn = 0, morte = 0, difficolta_selezionata = 0; //player da mettere static per evitare problemi con i turni e con l'alternarsi dei giocatori, mossa serve principalmente per la funzione adrenalina;
static int CountZone = 0, ZoneNumber = 0; //CountZone è il numero di zone presenti

void dealloca()
{
	for(int i = 0; i < 2; i++)
	{
		free(Giocatori[i]);
	}
	int a = CountZone;
	for (int i = 0; i < a; i++)
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
	CountZone--;
	}
}

static void Gieson(Giocatore *Giocatori)
{
	int Gieson = rand() % 100 + 1, scelta_oggetti = 0;

	if (Giocatori -> posizione -> zona == 6)
	{
		if (Gieson <= 75)
		{
			Spawn = 1;
			puts("\n**************************\nAppare un Gieson selvatico\n**************************\n\n");
			for (int i = 2; i < 5; i++)
			{
				if (Giocatori -> zaino[i] != 0)
				{
					scelta_oggetti ++;
				}
			}

			if (scelta_oggetti > 1)
			{
				puts("Cosa usi per difenderti?");
				int a;

				for (int i = 2; i < scelta_oggetti + 2; i++)
				{
					a = 1;
					if (Giocatori -> zaino[i] != 0)
					{
						switch(i)
						{
							case 2:
							printf("\n\n%d) Coltello (%dx)\n", a, Giocatori -> zaino[2]);
							break;

							case 3:
							printf("\n\n%d) Pistola (%dx)\n", a, Giocatori -> zaino[3]);
							break;

							case 4:
							printf("\n\n%d) Benzina (%dx)\n", a, Giocatori -> zaino[4]);
							break;
						}
					a++;
					}
				}

				scanf("%d", &a);
				switch (a)
				{
					case 1:
					if (Giocatori -> zaino[COLTELLO] == 0)
					{
						Giocatori -> zaino[PISTOLA]--;	
						printf("******************************************************************\nGieson ha sentito una sparo e si è spaventato: sei salvo (per ora)\n******************************************************************\n\n");				
					}

					else
					{
						Giocatori -> zaino[COLTELLO]--;
						Giocatori -> stato_giocatore --;
						printf("***********************************************************\nHai usato un Coltello per difenderti, ma sei rimasto ferito\n***********************************************************\n\n");
					}
					break;

					case 2:
					if (Giocatori -> zaino[PISTOLA] == 0)
					{
						Giocatori -> zaino[BENZINA]--;
						benzina_usata = 4;
						printf("**************************************************************************************\nHAI USATO LA BENZINAAAAAA!!! Gieson non apparirà per 2 turni ciascuno o prenderà fuoco\n**************************************************************************************\n\n");
					}

					else
					{
						Giocatori -> zaino[PISTOLA]--;
						printf("******************************************************************\nGieson ha sentito una sparo e si è spaventato: sei salvo (per ora)\n******************************************************************\n\n");				
					}
					break;

					case 3:
					Giocatori -> zaino[BENZINA]--;
					benzina_usata = 4;
					printf("**************************************************************************************\nHAI USATO LA BENZINAAAAAA!!! Gieson non apparirà per 2 turni ciascuno o prenderà fuoco\n**************************************************************************************\n\n");
					break;
				}
			}

			else if (scelta_oggetti == 1)
			{
				if (Giocatori -> zaino[2] != 0)
				{
					Giocatori -> zaino[COLTELLO]--;
					Giocatori -> stato_giocatore --;
					printf("***********************************************************\nHai usato un Coltello per difenderti, ma sei rimasto ferito\n***********************************************************\n\n");
				}

				else if (Giocatori -> zaino[3] != 0)
				{
					Giocatori -> zaino[PISTOLA]--;	
					printf("******************************************************************\nGieson ha sentito una sparo e si è spaventato: sei salvo (per ora)n******************************************************************\n\n");				
				}

				else if (Giocatori -> zaino[BENZINA] != 0)
				{
					Giocatori -> zaino[BENZINA]--;
					benzina_usata = 4;
					printf("**************************************************************************************\nHAI USATO LA BENZINAAAAAA!!! Gieson non apparirà per 2 turni ciascuno o prenderà fuoco\n**************************************************************************************\n\n");
				}
			}

			else
			{
				morte = 1;
				Giocatori -> stato_giocatore = 1;
				printf("*****************************************************************\nNon avevi nulla con cui difenderti e Gieson ti ha fatto le scarpe\n*****************************************************************\n\n");
			}
		}
	}

	else if (difficolta == 1)
	{
		if (Gieson <= 25)
		{
			Spawn = 1;
			puts("\n**************************\nAppare un Gieson selvatico\n**************************\n\n");
			for (int i = 2; i < 5; i++)
			{
				if (Giocatori -> zaino[i] != 0)
				{
					scelta_oggetti ++;
				}
			}

			if (scelta_oggetti > 1)
			{
				puts("Cosa usi per difenderti?");
				int a;

				for (int i = 2; i < scelta_oggetti + 2; i++)
				{
					a = 1;
					if (Giocatori -> zaino[i] != 0)
					{
						switch(i)
						{
							case 2:
							printf("\n\n%d) Coltello (%dx)\n", a, Giocatori -> zaino[2]);
							break;

							case 3:
							printf("\n\n%d) Pistola (%dx)\n", a, Giocatori -> zaino[3]);
							break;

							case 4:
							printf("\n\n%d) Benzina (%dx)\n", a, Giocatori -> zaino[4]);
							break;
						}
					a++;
					}
				}

				scanf("%d", &a);
				switch (a)
				{
					case 1:
					if (Giocatori -> zaino[COLTELLO] == 0)
					{
						Giocatori -> zaino[PISTOLA]--;	
						printf("******************************************************************\nGieson ha sentito una sparo e si è spaventato: sei salvo (per ora)\n******************************************************************\n\n");				
					}

					else
					{
						Giocatori -> zaino[COLTELLO]--;
						Giocatori -> stato_giocatore --;
						printf("***********************************************************\nHai usato un Coltello per difenderti, ma sei rimasto ferito\n***********************************************************\n\n");
					}
					break;

					case 2:
					if (Giocatori -> zaino[PISTOLA] == 0)
					{
						Giocatori -> zaino[BENZINA]--;
						benzina_usata = 4;
						printf("**************************************************************************************\nHAI USATO LA BENZINAAAAAA!!! Gieson non apparirà per 2 turni ciascuno o prenderà fuoco\n**************************************************************************************\n\n");
					}

					else
					{
						Giocatori -> zaino[PISTOLA]--;
						printf("******************************************************************\nGieson ha sentito una sparo e si è spaventato: sei salvo (per ora)\n******************************************************************\n\n");				
					}
					break;

					case 3:
					Giocatori -> zaino[BENZINA]--;
					benzina_usata = 4;
					printf("**************************************************************************************\nHAI USATO LA BENZINAAAAAA!!! Gieson non apparirà per 2 turni ciascuno o prenderà fuoco\n**************************************************************************************\n\n");
					break;
				}
			}

			else if (scelta_oggetti == 1)
			{
				if (Giocatori -> zaino[2] != 0)
				{
					Giocatori -> zaino[COLTELLO]--;
					Giocatori -> stato_giocatore --;
					printf("***********************************************************\nHai usato un Coltello per difenderti, ma sei rimasto ferito\n***********************************************************\n\n");
				}

				else if (Giocatori -> zaino[3] != 0)
				{
					Giocatori -> zaino[PISTOLA]--;	
					printf("******************************************************************\nGieson ha sentito una sparo e si è spaventato: sei salvo (per ora)n******************************************************************\n\n");				
				}

				else if (Giocatori -> zaino[BENZINA] != 0)
				{
					Giocatori -> zaino[BENZINA]--;
					benzina_usata = 4;
					printf("**************************************************************************************\nHAI USATO LA BENZINAAAAAA!!! Gieson non apparirà per 2 turni ciascuno o prenderà fuoco\n**************************************************************************************\n\n");
				}
			}

			else
			{
				morte = 1;
				Giocatori -> stato_giocatore = 1;
				printf("*****************************************************************\nNon avevi nulla con cui difenderti e Gieson ti ha fatto le scarpe\n*****************************************************************\n\n");
			}
		}
	}

	else if (difficolta == 2)
	{
		if (Gieson <= 30)
		{
			Spawn = 1;
			puts("\n**************************\nAppare un Gieson selvatico\n**************************\n\n");
			for (int i = 2; i < 5; i++)
			{
				if (Giocatori -> zaino[i] != 0)
				{
					scelta_oggetti ++;
				}
			}

			if (scelta_oggetti > 1)
			{
				puts("Cosa usi per difenderti?");
				int a;

				for (int i = 2; i < scelta_oggetti + 2; i++)
				{
					a = 1;
					if (Giocatori -> zaino[i] != 0)
					{
						switch(i)
						{
							case 2:
							printf("\n\n%d) Coltello (%dx)\n", a, Giocatori -> zaino[2]);
							break;

							case 3:
							printf("\n\n%d) Pistola (%dx)\n", a, Giocatori -> zaino[3]);
							break;

							case 4:
							printf("\n\n%d) Benzina (%dx)\n", a, Giocatori -> zaino[4]);
							break;
						}
					a++;
					}
				}

				scanf("%d", &a);
				switch (a)
				{
					case 1:
					if (Giocatori -> zaino[COLTELLO] == 0)
					{
						Giocatori -> zaino[PISTOLA]--;	
						printf("******************************************************************\nGieson ha sentito una sparo e si è spaventato: sei salvo (per ora)\n******************************************************************\n\n");				
					}

					else
					{
						Giocatori -> zaino[COLTELLO]--;
						Giocatori -> stato_giocatore --;
						printf("***********************************************************\nHai usato un Coltello per difenderti, ma sei rimasto ferito\n***********************************************************\n\n");
					}
					break;

					case 2:
					if (Giocatori -> zaino[PISTOLA] == 0)
					{
						Giocatori -> zaino[BENZINA]--;
						benzina_usata = 4;
						printf("**************************************************************************************\nHAI USATO LA BENZINAAAAAA!!! Gieson non apparirà per 2 turni ciascuno o prenderà fuoco\n**************************************************************************************\n\n");
					}

					else
					{
						Giocatori -> zaino[PISTOLA]--;
						printf("******************************************************************\nGieson ha sentito una sparo e si è spaventato: sei salvo (per ora)\n******************************************************************\n\n");				
					}
					break;

					case 3:
					Giocatori -> zaino[BENZINA]--;
					benzina_usata = 4;
					printf("**************************************************************************************\nHAI USATO LA BENZINAAAAAA!!! Gieson non apparirà per 2 turni ciascuno o prenderà fuoco\n**************************************************************************************\n\n");
					break;
				}
			}

			else if (scelta_oggetti == 1)
			{
				if (Giocatori -> zaino[2] != 0)
				{
					Giocatori -> zaino[COLTELLO]--;
					Giocatori -> stato_giocatore --;
					printf("***********************************************************\nHai usato un Coltello per difenderti, ma sei rimasto ferito\n***********************************************************\n\n");
				}

				else if (Giocatori -> zaino[3] != 0)
				{
					Giocatori -> zaino[PISTOLA]--;	
					printf("******************************************************************\nGieson ha sentito una sparo e si è spaventato: sei salvo (per ora)n******************************************************************\n\n");				
				}

				else if (Giocatori -> zaino[BENZINA] != 0)
				{
					Giocatori -> zaino[BENZINA]--;
					benzina_usata = 4;
					printf("**************************************************************************************\nHAI USATO LA BENZINAAAAAA!!! Gieson non apparirà per 2 turni ciascuno o prenderà fuoco\n**************************************************************************************\n\n");
				}
			}

			else
			{
				morte = 1;
				Giocatori -> stato_giocatore = 1;
				printf("*****************************************************************\nNon avevi nulla con cui difenderti e Gieson ti ha fatto le scarpe\n*****************************************************************\n\n");
			}
		}
	}

	else if (difficolta == 3)
	{
		if (Gieson <= 35)
		{
			Spawn = 1;
			puts("\n**************************\nAppare un Gieson selvatico\n**************************\n\n");
			for (int i = 2; i < 5; i++)
			{
				if (Giocatori -> zaino[i] != 0)
				{
					scelta_oggetti ++;
				}
			}

			if (scelta_oggetti > 1)
			{
				puts("Cosa usi per difenderti?");
				int a;

				for (int i = 2; i < scelta_oggetti + 2; i++)
				{
					a = 1;
					if (Giocatori -> zaino[i] != 0)
					{
						switch(i)
						{
							case 2:
							printf("\n\n%d) Coltello (%dx)\n", a, Giocatori -> zaino[2]);
							break;

							case 3:
							printf("\n\n%d) Pistola (%dx)\n", a, Giocatori -> zaino[3]);
							break;

							case 4:
							printf("\n\n%d) Benzina (%dx)\n", a, Giocatori -> zaino[4]);
							break;
						}
					a++;
					}
				}

				scanf("%d", &a);
				switch (a)
				{
					case 1:
					if (Giocatori -> zaino[COLTELLO] == 0)
					{
						Giocatori -> zaino[PISTOLA]--;	
						printf("******************************************************************\nGieson ha sentito una sparo e si è spaventato: sei salvo (per ora)\n******************************************************************\n\n");				
					}

					else
					{
						Giocatori -> zaino[COLTELLO]--;
						Giocatori -> stato_giocatore --;
						printf("***********************************************************\nHai usato un Coltello per difenderti, ma sei rimasto ferito\n***********************************************************\n\n");
					}
					break;

					case 2:
					if (Giocatori -> zaino[PISTOLA] == 0)
					{
						Giocatori -> zaino[BENZINA]--;
						benzina_usata = 4;
						printf("**************************************************************************************\nHAI USATO LA BENZINAAAAAA!!! Gieson non apparirà per 2 turni ciascuno o prenderà fuoco\n**************************************************************************************\n\n");
					}

					else
					{
						Giocatori -> zaino[PISTOLA]--;
						printf("******************************************************************\nGieson ha sentito una sparo e si è spaventato: sei salvo (per ora)\n******************************************************************\n\n");				
					}
					break;

					case 3:
					Giocatori -> zaino[BENZINA]--;
					benzina_usata = 4;
					printf("**************************************************************************************\nHAI USATO LA BENZINAAAAAA!!! Gieson non apparirà per 2 turni ciascuno o prenderà fuoco\n**************************************************************************************\n\n");
					break;
				}
			}

			else if (scelta_oggetti == 1)
			{
				if (Giocatori -> zaino[2] != 0)
				{
					Giocatori -> zaino[COLTELLO]--;
					Giocatori -> stato_giocatore --;
					printf("***********************************************************\nHai usato un Coltello per difenderti, ma sei rimasto ferito\n***********************************************************\n\n");
				}

				else if (Giocatori -> zaino[3] != 0)
				{
					Giocatori -> zaino[PISTOLA]--;	
					printf("******************************************************************\nGieson ha sentito una sparo e si è spaventato: sei salvo (per ora)n******************************************************************\n\n");				
				}

				else if (Giocatori -> zaino[BENZINA] != 0)
				{
					Giocatori -> zaino[BENZINA]--;
					benzina_usata = 4;
					printf("**************************************************************************************\nHAI USATO LA BENZINAAAAAA!!! Gieson non apparirà per 2 turni ciascuno o prenderà fuoco\n**************************************************************************************\n\n");
				}
			}

			else
			{	
				morte = 1;
				Giocatori -> stato_giocatore = 1;
				printf("*****************************************************************\nNon avevi nulla con cui difenderti e Gieson ti ha fatto le scarpe\n*****************************************************************\n\n");
			}
		}
	}

	else if (difficolta == 4)
	{
		if (Gieson <= 40)
		{
			Spawn = 1;
			puts("\n**************************\nAppare un Gieson selvatico\n**************************\n\n");
			for (int i = 2; i < 5; i++)
			{
				if (Giocatori -> zaino[i] != 0)
				{
					scelta_oggetti ++;
				}
			}

			if (scelta_oggetti > 1)
			{
				puts("Cosa usi per difenderti?");
				int a;

				for (int i = 2; i < scelta_oggetti + 2; i++)
				{
					a = 1;
					if (Giocatori -> zaino[i] != 0)
					{
						switch(i)
						{
							case 2:
							printf("\n\n%d) Coltello (%dx)\n", a, Giocatori -> zaino[2]);
							break;

							case 3:
							printf("\n\n%d) Pistola (%dx)\n", a, Giocatori -> zaino[3]);
							break;

							case 4:
							printf("\n\n%d) Benzina (%dx)\n", a, Giocatori -> zaino[4]);
							break;
						}
					a++;
					}
				}

				scanf("%d", &a);
				switch (a)
				{
					case 1:
					if (Giocatori -> zaino[COLTELLO] == 0)
					{
						Giocatori -> zaino[PISTOLA]--;	
						printf("******************************************************************\nGieson ha sentito una sparo e si è spaventato: sei salvo (per ora)\n******************************************************************\n\n");				
					}

					else
					{
						Giocatori -> zaino[COLTELLO]--;
						Giocatori -> stato_giocatore --;
						printf("***********************************************************\nHai usato un Coltello per difenderti, ma sei rimasto ferito\n***********************************************************\n\n");
					}
					break;

					case 2:
					if (Giocatori -> zaino[PISTOLA] == 0)
					{
						Giocatori -> zaino[BENZINA]--;
						benzina_usata = 4;
						printf("**************************************************************************************\nHAI USATO LA BENZINAAAAAA!!! Gieson non apparirà per 2 turni ciascuno o prenderà fuoco\n**************************************************************************************\n\n");
					}

					else
					{
						Giocatori -> zaino[PISTOLA]--;
						printf("******************************************************************\nGieson ha sentito una sparo e si è spaventato: sei salvo (per ora)\n******************************************************************\n\n");				
					}
					break;

					case 3:
					Giocatori -> zaino[BENZINA]--;
					benzina_usata = 4;
					printf("**************************************************************************************\nHAI USATO LA BENZINAAAAAA!!! Gieson non apparirà per 2 turni ciascuno o prenderà fuoco\n**************************************************************************************\n\n");
					break;
				}
			}

			else if (scelta_oggetti == 1)
			{
				if (Giocatori -> zaino[2] != 0)
				{
					Giocatori -> zaino[COLTELLO]--;
					Giocatori -> stato_giocatore --;
					printf("***********************************************************\nHai usato un Coltello per difenderti, ma sei rimasto ferito\n***********************************************************\n\n");
				}

				else if (Giocatori -> zaino[3] != 0)
				{
					Giocatori -> zaino[PISTOLA]--;	
					printf("******************************************************************\nGieson ha sentito una sparo e si è spaventato: sei salvo (per ora)n******************************************************************\n\n");				
				}

				else if (Giocatori -> zaino[BENZINA] != 0)
				{
					Giocatori -> zaino[BENZINA]--;
					benzina_usata = 4;
					printf("**************************************************************************************\nHAI USATO LA BENZINAAAAAA!!! Gieson non apparirà per 2 turni ciascuno o prenderà fuoco\n**************************************************************************************\n\n");
				}
			}

			else
			{
				morte = 1;
				Giocatori -> stato_giocatore = 1;
				printf("*****************************************************************\nNon avevi nulla con cui difenderti e Gieson ti ha fatto le scarpe\n*****************************************************************\n\n");
			}
		}
	}

	else if (difficolta == 5)
	{
		if (Gieson <= 45)
		{
			Spawn = 1;
			puts("\n**************************\nAppare un Gieson selvatico\n**************************\n\n");
			for (int i = 2; i < 5; i++)
			{
				if (Giocatori -> zaino[i] != 0)
				{
					scelta_oggetti ++;
				}
			}

			if (scelta_oggetti > 1)
			{
				puts("Cosa usi per difenderti?");
				int a;

				for (int i = 2; i < scelta_oggetti + 2; i++)
				{
					a = 1;
					if (Giocatori -> zaino[i] != 0)
					{
						switch(i)
						{
							case 2:
							printf("\n\n%d) Coltello (%dx)\n", a, Giocatori -> zaino[2]);
							break;

							case 3:
							printf("\n\n%d) Pistola (%dx)\n", a, Giocatori -> zaino[3]);
							break;

							case 4:
							printf("\n\n%d) Benzina (%dx)\n", a, Giocatori -> zaino[4]);
							break;
						}
					a++;
					}
				}

				scanf("%d", &a);
				switch (a)
				{
					case 1:
					if (Giocatori -> zaino[COLTELLO] == 0)
					{
						Giocatori -> zaino[PISTOLA]--;	
						printf("******************************************************************\nGieson ha sentito una sparo e si è spaventato: sei salvo (per ora)\n******************************************************************\n\n");				
					}

					else
					{
						Giocatori -> zaino[COLTELLO]--;
						Giocatori -> stato_giocatore --;
						printf("***********************************************************\nHai usato un Coltello per difenderti, ma sei rimasto ferito\n***********************************************************\n\n");
					}
					break;

					case 2:
					if (Giocatori -> zaino[PISTOLA] == 0)
					{
						Giocatori -> zaino[BENZINA]--;
						benzina_usata = 4;
						printf("**************************************************************************************\nHAI USATO LA BENZINAAAAAA!!! Gieson non apparirà per 2 turni ciascuno o prenderà fuoco\n**************************************************************************************\n\n");
					}

					else
					{
						Giocatori -> zaino[PISTOLA]--;
						printf("******************************************************************\nGieson ha sentito una sparo e si è spaventato: sei salvo (per ora)\n******************************************************************\n\n");				
					}
					break;

					case 3:
					Giocatori -> zaino[BENZINA]--;
					benzina_usata = 4;
					printf("**************************************************************************************\nHAI USATO LA BENZINAAAAAA!!! Gieson non apparirà per 2 turni ciascuno o prenderà fuoco\n**************************************************************************************\n\n");
					break;
				}
			}

			else if (scelta_oggetti == 1)
			{
				if (Giocatori -> zaino[2] != 0)
				{
					Giocatori -> zaino[COLTELLO]--;
					Giocatori -> stato_giocatore --;
					printf("***********************************************************\nHai usato un Coltello per difenderti, ma sei rimasto ferito\n***********************************************************\n\n");
				}

				else if (Giocatori -> zaino[3] != 0)
				{
					Giocatori -> zaino[PISTOLA]--;	
					printf("******************************************************************\nGieson ha sentito una sparo e si è spaventato: sei salvo (per ora)n******************************************************************\n\n");				
				}

				else if (Giocatori -> zaino[BENZINA] != 0)
				{
					Giocatori -> zaino[BENZINA]--;
					benzina_usata = 4;
					printf("**************************************************************************************\nHAI USATO LA BENZINAAAAAA!!! Gieson non apparirà per 2 turni ciascuno o prenderà fuoco\n**************************************************************************************\n\n");
				}
			}

			else
			{
				morte = 1;
				Giocatori -> stato_giocatore = 1;
				printf("*****************************************************************\nNon avevi nulla con cui difenderti e Gieson ti ha fatto le scarpe\n*****************************************************************\n\n");
			}
		}
	}
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
		Giocatori -> ZoneNumber ++;
	}

	else if (Giocatori -> posizione -> zona == USCITA_CAMPEGGIO)
	{
		printf("\n\n*************************************************************************\nSegmentation Fault 11: Gieson non può seguirti fin qui, %s\n*************************************************************************\n\n", player == 0 ? "Giacomo sei salvo!" : "Marzia sei salva!");
		Giocatori -> stato_giocatore = 4;
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

	for (int i = 1; i < 6; i++)
	{
		switch(i)
		{
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
			printf("Adrenalina: %d\n", Giocatori -> zaino[i]);
			break;
		}
	}
	puts("****************************");
}

static void getta_oggetto(Giocatore *Giocatori)
{
	int a, b; //b= quantità di oggetti da gettare
	zaino(Giocatori);
	puts("Cosa desideri gettare?\n\n1) Bende\n\n2) Coltello\n\n3) Pistola\n\n4) Benzina\n\n5) Adrenalina\n\n");
	scanf("%d", &a);
	switch(a)
	{
		case 1:
		if (Giocatori -> zaino[BENDE] == 0)
		{	
			puts("\n***************************************************\nNon puoi gettare delle cose che non hai, svegliati.\n***************************************************\n");
		}

		else
		{
			puts("\nQuante Bende vuoi gettare?\n");
			scanf("%d", &b);
			if (b <= Giocatori -> zaino[BENDE])
			{
				Giocatori -> zaino[BENDE] -= b;
				printf("\n\nHai gettato %d Bende\n", b);
			}

			else
			{
				puts("\n***************************************************\nNon puoi gettare delle cose che non hai, svegliati.\n***************************************************\n");
			}
		}	
		break;

		case 2:
		if (Giocatori -> zaino[COLTELLO] == 0)
		{	
			puts("\n***************************************************\nNon puoi gettare delle cose che non hai, svegliati.\n***************************************************\n");
		}

		else
		{	
			puts("\nQuanti Coltelli vuoi gettare?\n");
			scanf("%d", &b);
			if (b <= Giocatori -> zaino[COLTELLO])
			{
				Giocatori -> zaino[COLTELLO] -= b;
				printf("\n\nHai gettato %d %s\n", b, b > 1 ? "Coltelli" : "Coltello");
			}

			else
			{
				puts("Non puoi gettare delle cose che non hai, svegliati.");
			}
		}			
		break;

		case 3:
		if (Giocatori -> zaino[PISTOLA] == 0)
		{	
			puts("\n***************************************************\nNon puoi gettare delle cose che non hai, svegliati.\n***************************************************\n");
		}

		else
		{	
			puts("\nQuante Pistole vuoi gettare?\n");
			scanf("%d", &b);
			if (b <= Giocatori -> zaino[PISTOLA])
			{
				Giocatori -> zaino[PISTOLA] -= b;
				printf("\n\nHai gettato %d %s\n", b, b > 1? "Pistole" : "Pistola");
			}

			else
			{
				puts("Non puoi gettare delle cose che non hai, svegliati.");
			}
		}	
		break;

		case 4:
		if (Giocatori -> zaino[BENZINA] == 0)
		{	
			puts("\n***************************************************\nNon puoi gettare delle cose che non hai, svegliati.\n***************************************************\n");
		}

		else
		{
			puts("\nQuanta Benzina vuoi gettare?\n");
			scanf("%d", &b);
			if (b <= Giocatori -> zaino[BENZINA])
			{
				Giocatori -> zaino[BENZINA] -= b;
				printf("\n\nHai gettato %d unità di Benzina\n", b);
			}

			else
			{
				puts("Non puoi gettare delle cose che non hai, svegliati.");
			}
		}	
		break;

		case 5:
		if (Giocatori -> zaino[ADRENALINA] == 0)
		{	
			puts("\n***************************************************\nNon puoi gettare delle cose che non hai, svegliati.\n***************************************************\n");
		}

		else
		{	
			puts("\nQuanta Adrenalina vuoi gettare?\n");
			scanf("%d", &b);
			if (b <= Giocatori -> zaino[ADRENALINA])
			{
				Giocatori -> zaino[ADRENALINA] -= b;
				printf("\n\nHai gettato %d unità di Adrenalina\n", b);
			}

			else
			{
				puts("Non puoi gettare delle cose che non hai, svegliati.");
			}
		}	
		break;

	}
}

static void prendi_oggetto(Giocatore *Giocatori)
{
	if (Giocatori -> posizione -> oggetto != CIANFRUSAGLIA)
	{
		int totale_zaino = 0, a;

		for (int i = 0; i < 6; i++)
		{
			totale_zaino += Giocatori -> zaino[i];
		}

		if (totale_zaino < 20)
		{
			if (Giocatori -> posizione -> oggetto != CIANFRUSAGLIA)
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

			else if (Giocatori -> posizione -> oggetto == CIANFRUSAGLIA)
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

		else
		{
			printf("\n\n****************************************************************************\nIl tuo zaino è pieno, desidere gettare degli oggetti per far posto ad altri?\n****************************************************************************\n\n1) Sì\n\n2) No\n\n");
			scanf("%d", &a);

			switch(a)
			{
				case 1:
				getta_oggetto(Giocatori);
				prendi_oggetto(Giocatori);
				break;

				case 2:
				break;

				default:
				printf("\n****************************\nScelta non valida, riprovare\n****************************\n\n");
				break;
			}
		}	
	}

	else if (Giocatori -> posizione -> oggetto == CIANFRUSAGLIA)
	{	
		int a;
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

static void inizializza()
{
	for (int i = 0; i < 2; i++)
	{
		Giocatori[i] = (Giocatore*) malloc(sizeof(Giocatore));
		Giocatori[i] -> stato_giocatore = 3;
		Giocatori[i] -> posizione = prima_zona;
	}

	Giocatori[0] -> zaino[BENDE] = 0;
	Giocatori[1] -> zaino[BENDE] = 0;
	Giocatori[0] -> zaino[COLTELLO] = 1;
	Giocatori[1] -> zaino[COLTELLO] = 0;
	Giocatori[0] -> zaino[PISTOLA] = 0;
	Giocatori[1] -> zaino[PISTOLA] = 0;
	Giocatori[0] -> zaino[BENZINA] = 0;
	Giocatori[1] -> zaino[BENZINA] = 0;
	Giocatori[0] -> zaino[ADRENALINA] = 0;
	Giocatori[1] -> zaino[ADRENALINA] = 2;
	Giocatori[0] -> turn = 1;
	Giocatori[1] -> turn = 1;
	Giocatori[0] -> ZoneNumber = 1;
	Giocatori[1] -> ZoneNumber = 1;
}

static void random_map()
{
	if (prima_zona == NULL)
	{
		prima_zona = (Zona *) malloc(sizeof(Zona));
		ultima_zona = (Zona *) malloc(sizeof(Zona));
		ultima_zona = prima_zona;
		CountZone++;
	}

	if (ultima_zona -> zona == 6)
	{
		puts("\n********************************************************************************\n* L'ultima zona dev'essere per forza l'Uscita del Campeggio: modifica la mappa *\n********************************************************************************\n\n");
	}

	else if (difficolta_selezionata == 1)
	{
		puts("\nHai già selezionato la difficoltà: per poter creare un'altra mappa automaticamente devi riavviare il gioco, eheh\n\n");
	}

	else
	{
		difficolta_selezionata = 1;
		printf("\n\nSelezionare livello di difficoltà:\n\n1) Facile (8 - 10 mappe / Gieson spawna con il 25%s di possibilità)\n\n2) Medio (10 - 25 mappe / Gieson spawna con il 30%s di possibilità)\n\n3) Difficile (25 - 50 mappe / Gieson spawna con il 35%s di possibilità)\n\n4) Folle (50 - 100 mappe / Gieson spawna con il 40%s di possibilità)\n\n5) Non sopravvivrai (100 - 200 mappe / Gieson spawna con il 45%s di possibilità)\n\n", "%", "%", "%", "%", "%");
		int numero_mappe, zone, oggetto;
		scanf("%d", &difficolta);
		puts("");
		switch(difficolta)
		{
			case 1:
			numero_mappe = rand() % (10 - 8) + 8;
			break;

			case 2:
			numero_mappe = rand() % (25 - 10) + 10;
			break;

			case 3:
			numero_mappe = rand() % (50 - 25) + 25;
			break;

			case 4:
			numero_mappe = rand() % (100 - 50) + 50;
			break;

			case 5:
			numero_mappe = rand() % (200 - 100) + 100;
			break;

			default:
			printf("\n****************************\nScelta non valida, riprovare\n****************************\n\n");
			break;
		}

		for (int i = 0; i < (numero_mappe - 1); i++)
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

			CountZone++;
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

		CountZone ++;
	}
}

static void ins_zona()
{	
	int b, oggetto; // b = parametro di scelta nella funzione ins_zona(), oggetto = parametro per la generazione di oggetti nelle mappe
	if (prima_zona == NULL)
	{
	prima_zona = (Zona *) malloc(sizeof(Zona));
	ultima_zona = (Zona *) malloc(sizeof(Zona));
	ultima_zona = prima_zona;
	}

	else if (ultima_zona -> zona == 6)
	{
		printf("\n****************************************************************\nL'ultima zona deve essere necessariamente l'Uscita del Campeggio\n****************************************************************\n");
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
		puts("\n********************************************************\nBisogna aggiungere almeno una zona per poterla eliminare\n********************************************************\n");
	}

	else if (ultima_zona == prima_zona)
	{
		free(ultima_zona);
		prima_zona = NULL;
		ultima_zona = NULL;
		CountZone --;
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
		CountZone --;
	}
}


void crea_mappa()
{
	static int a; // a = parametro di scelta nella funzione crea_mappa()

	do 
	{
		printf("\n\n*************************************\nScegliere un'azione da intraprendere:\n*************************************\n\n\n1) Aggiungi zona\n\n2) Cancella zona\n\n3) Mostra mappa\n\n4) Mappa Random\n\n5) Chiudi mappa\n\n\n");
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
		puts("\n********************************************\n* Poche zone per giocare: aggiungine altre *\n********************************************");
		crea_mappa();
	}

	else if (ultima_zona -> zona != 6) //seconda verifica (ultima zona per forza l'uscita del campeggio)
	{
		puts("\n********************************************************************************\n* L'ultima zona dev'essere per forza l'Uscita del Campeggio: modifica la mappa *\n********************************************************************************");
		crea_mappa();
	}

	else
	{
		int a;
		Zona * temp = prima_zona;
		do
		{
			morte = 0;
			Spawn = 0;

			if (turn == 0)
			{
				inizializza();
				player = rand() % 2;
				turn++;
			}

			if (Giocatori[0] -> stato_giocatore == 4 && Giocatori[1] -> stato_giocatore == 4)
			{	
				puts("*****************************************************************************************\nGiocare a League of Legends durante le spiegazioni di Santini ti ha ripagato, bel lavoro!\n*****************************************************************************************\n");
				puts("\n***********\n*Game Over*\n***********\n");
				puts("\nAvviare una nuova partita?\n\n1) Sì\n\n2) No\n\n");
				scanf("%d", &a);

				switch(a)
				{
					case 1:
					turn = 0, player = 0, mossa = 1, difficolta = 2, benzina_usata = 0, scelta_oggetti = 0;
					inizializza();
					dealloca();
					main();
					break;

					case 2:
					puts("\n***********\n*Game Over*\n***********\n");
					turn = 0, player = 0, mossa = 1, difficolta = 2, benzina_usata = 0, scelta_oggetti = 0;
					inizializza();
					dealloca();
					exit(1);
					break;

					default:
					printf("\n****************************\nScelta non valida, riprovare\n****************************\n\n");
					break;
				}
			}

			if(Giocatori[0] -> stato_giocatore != 1 && Giocatori[1] -> stato_giocatore != 1 && mossa == 0)
			{
				if (benzina_usata <= 0 && Spawn == 0)
				{
					Gieson(Giocatori[player]);
				}
				mossa = 1;
				Giocatori[player] -> turn ++;
				benzina_usata--;
				player = !player;
			}


			if (Giocatori[0] -> stato_giocatore == 1 || Giocatori[1] -> stato_giocatore == 1 || Giocatori[0] -> stato_giocatore == 4 || Giocatori[1] -> stato_giocatore == 4 && mossa == 0)
			{

			 	if (Giocatori[0] -> stato_giocatore == 1 || Giocatori[0] -> stato_giocatore == 4)
			 	{
			 		player = 1;
			 	}

			 	else if (Giocatori[1] -> stato_giocatore == 1 || Giocatori[1] -> stato_giocatore == 4)
			 	{
			 		player = 0;
			 	}

			 	if (benzina_usata <= 0 && Spawn == 0)
				{
					Gieson(Giocatori[player]);
				}

				mossa = 1;
				if (morte == 0)
				{
					Giocatori[player] -> turn ++;
				}
			 	benzina_usata--;
			}

			if (Giocatori[0] -> stato_giocatore == 1 && Giocatori[1] -> stato_giocatore == 1)
			{
				puts("\n***********\n*Game Over*\n***********\n");
				puts("\nAvviare una nuova partita?\n\n1) Sì\n\n2) No\n\n");
				scanf("%d", &a);

				switch(a)
				{
					case 1:
					turn = 0, player = 0, mossa = 1, difficolta = 2, benzina_usata = 0, scelta_oggetti = 0;
					inizializza();
					dealloca();
					main();
					break;

					case 2:
					puts("\n***********\n*Game Over*\n***********\n");
					turn = 0, player = 0, mossa = 1, difficolta = 2, benzina_usata = 0, scelta_oggetti = 0;
					inizializza();
					dealloca();
					exit(1);
					break;

					default:
					printf("\n****************************\nScelta non valida, riprovare\n****************************\n\n");
					break;
				}
			}

			printf("\n\n*******************************************************\nTurno: %d\n\nGiocatore: %s\n\nStato del Giocatore: %s\n\nZona in cui si trova il giocatore: ", Giocatori[player] -> turn, player == 0 ? "Giacomo" : "Marzia", Giocatori[player] -> stato_giocatore == 3 ? "Vivo" : "Ferito");
			
			switch(Giocatori[player] -> posizione-> zona)
			{
				case 1:
				printf("Cucina (%d/%d)\n", Giocatori[player] -> ZoneNumber, CountZone);
				break;

				case 2:
				printf("Soggiorno (%d/%d)\n", Giocatori[player] -> ZoneNumber, CountZone);
				break;
				
				case 3:
				printf("Rimessa (%d/%d)\n", Giocatori[player] -> ZoneNumber, CountZone);
				break;

				case 4:
				printf("Strada (%d/%d)\n", Giocatori[player] -> ZoneNumber, CountZone);
				break;
				
				case 5:
				printf("Lungo Lago (%d/%d)\n", Giocatori[player] -> ZoneNumber, CountZone);
				break;
				
				case 6:
				printf("Uscita del Campeggio (%d/%d)\n", Giocatori[player] -> ZoneNumber, CountZone);
				break;
				
			}
			printf("*******************************************************\n\n");
			printf("\n\n1) Avanza di zona\n\n2) Mostra l'oggetto presente nella zona\n\n3) Raccogli l'oggetto presente nella zona\n\n4) Curati\n\n5) Usa l'adrenalina\n\n6) Visualizza zaino\n\n7) Getta degli oggetti\n\n8) Esci dal gioco\n\n\n");
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
				break;

				case 7:
				getta_oggetto(Giocatori[player]);
				break;

				case 8:
				puts("\nSei sicuro?\n\n1) Sì\n\n2) No\n\n");
				scanf("%1d", &a);
					switch(a)
					{
						case 1:
						puts("\n***********\n*Game Over*\n***********\n");
						turn = 0, player = 0, mossa = 1, difficolta = 2, benzina_usata = 0, scelta_oggetti = 0;
						inizializza();
						dealloca();
						exit(1);
						break;

						case 2:
						gioca();
						Giocatori[player] -> turn --;
						break;

						default:
					printf("\n****************************\nScelta non valida, riprovare\n****************************\n\n");
					Giocatori[player] -> turn --;
					break;	
					}
				break;

				default:
				printf("\n****************************\nScelta non valida, riprovare\n****************************\n\n");
				Giocatori[player] -> turn --;
				break;
			}

		}

		while(1);
	}
}