//GIACOMO SURACE MATRICOLA N.

typedef enum tipo_zona {CUCINA = 1, SOGGIORNO, RIMESSA, STRADA, LUNGO_LAGO, USCITA_CAMPEGGIO} tipo_zona;
typedef enum tipo_oggetto {CIANFRUSAGLIA, BENDE, COLTELLO, PISTOLA, BENZINA, ADRENALINA} tipo_oggetto;
typedef enum stato_giocatore {MORTO=1, FERITO, VIVO} stato_giocatore;

typedef struct Zona
{
	tipo_zona zona;
	tipo_oggetto oggetto;
	struct Zona * zona_successiva;
} Zona;

typedef struct Giocatore
{
	stato_giocatore stato_giocatore;
	unsigned int zaino[6];
	int turn;
	int ZoneNumber;
	Zona *posizione;
} Giocatore;

void crea_mappa();

int main();

void dealloca();

void gioca();

void tutorial();
