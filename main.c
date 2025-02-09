// Tris

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SIZE 3

enum status {WON, LOST, DRAW, NEWGAME, RUNNING}; 
enum players {PLAYER, ENEMY};

int random_max_min(int, int); 			// function for random number generator
void game(); // a single game
void enemyGame(char campo[][SIZE], enum players *);		// 
void playerGame(char campo[][SIZE], enum players *);	//
void checkVictory(); 					// function that checks if anyone won
void clearField(char campo[][SIZE]);	// clear the field so empty the array
void printField(char campo[][SIZE]); 	// print the field to show it graphically


// ============================================================================= //
// ============================================================================= //
// ====================                MAIN              ======================= //
// ============================================================================= //
// ============================================================================= //

int main(void)
{
	
	enum status gameStatus = NEWGAME; // as soon you start the program we can assume we're starting a new game
	enum players selectedPlayer; // stores which player is playing

	srand(time(NULL));

	// define the field as a char array assigning 'X' and 'O'
	char campo[SIZE][SIZE]; 
	
	clearField(campo); // clear the field
	printField(campo); // print the field in the terminal
	
	// choose first player, if new game then select player based on random number
	if(random_max_min(0, 1) && gameStatus == NEWGAME) 
	{
		selectedPlayer = PLAYER; // start player1
	}  
	else selectedPlayer = ENEMY; // start player2

	gameStatus = RUNNING; // after i selected the player we can consider the game is running

	// players can make a game until no one win
	while(gameStatus == RUNNING) 
	{
		// one of the two players makes a game 
		if(selectedPlayer == PLAYER)
		{
			playerGame(campo, &selectedPlayer);
		}
		else enemyGame(campo, &selectedPlayer);
		// printField();
		// checkVictory();
	}
   	
}

// ============================================================================= //
// ============================================================================= //
// ====================             END  MAIN            ======================= //
// ============================================================================= //
// ============================================================================= //

void game()
{
	/*
	clearField(campo); // clear the field
	printField(campo); // print the field in the terminal
	
	// choose first player, if new game then select player based on random number
	if(random_max_min(0, 1) && gameStatus == NEWGAME) 
	{
		selectedPlayer = PLAYER; // start player1
	}  
	else selectedPlayer = ENEMY; // start player2

	gameStatus = RUNNING; // after i selected the player we can consider the game is running

	// players can make a game until no one win
	while(gameStatus == RUNNING) 
	{
		// one of the two players makes a game 
		if(selectedPlayer == PLAYER)
		{
			playerGame(campo, &selectedPlayer);
		}
		else enemyGame(campo, &selectedPlayer);
		// printField();
		// checkVictory();
	}
	*/
}


void enemyGame(char campo[][SIZE], enum players *selectedPlayer)
{
	// generate random coordinates between 0 and 2
	short x = random_max_min(0, 2); // (short)
	short y = random_max_min(0, 2);

	while (campo[x][y] != ' ') // if the field is already signed, generate another random position
	{
		x = random_max_min(0, 2);
		y = random_max_min(0, 2);
	}

	campo[x][y] = 'O'; // insert enemy player sign

	*selectedPlayer = PLAYER;
}


void playerGame(char campo[][SIZE], enum players *selectedPlayer)
{
	short x, y; // coordinates
	do
	{
		puts("Inserisci coordinata x: ");
		scanf("%hd", &x);
		puts("Inserisci coordinata y: ");
		scanf("%hd", &y);
	}
	// field must be empty and coordinates between 0 and 2
	while( (x<0 || x>2) && (y<0 || y>2) && (campo[x][y] != ' ') );
	
	campo[x][y] = 'X'; // insert player sign
	
	*selectedPlayer = ENEMY;
}

void checkVictory()
{
	// controlla se qualcuno ha fatto tris
	// se player ha fatto allora gameStatus = WON, se enemy allora gameStatus = LOST 
	// altrimenti se campo e' tutto pieno e nessuno ha vinto allora gameStatus = DRAW	
	// chiedi se iniziare nuova partita o uscire, 
	// se avvio nuova partita fai game(); e game() include tutto il main da cleanField() alla fine
}


// clear the field so empty the array
void clearField(char campo[][SIZE])
{
	for(size_t i=0; i<SIZE; i++)
	{
		for(size_t j=0; j<SIZE; j++)
		{
			campo[i][j] = ' ';
		}
	}
}



// print the field on the cli
void printField(char campo[][SIZE])
{
	printf(" %c | %c | %c \n", campo[0][0], campo[0][1], campo[0][2]);
	printf("%s\n", "---+---+---");
	printf(" %c | %c | %c \n", campo[1][0], campo[1][1], campo[1][2]);
	printf("%s\n", "---+---+---");
	printf(" %c | %c | %c \n", campo[2][0], campo[2][1], campo[2][2]);
}


// random generator function
int random_max_min(int min, int max){
    return (rand()+min) % (max+1);
}



/*

	svuota il campo,
	stampa il campo,
	tira a sorte per chi inizia,
	finché non finisce la partita (vittoria o pareggio) si alternano,
		player1,
		stampa il campo,
		player2,
		stampa il campo,
		...
	inizia nuovo gioco o esci

*/