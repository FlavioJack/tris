// Tris

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 3

enum status {WON, LOST, DRAW, NEWGAME, RUNNING}; 
enum players {PLAYER, ENEMY};

int random_max_min(int, int); 							// random number generator
void game(char campo[][SIZE], enum players *, enum status *); // manage a single game
void enemyGame(char campo[][SIZE], enum players *);		// manage enemy player play
void playerGame(char campo[][SIZE], enum players *);	// manage main player play
void checkVictory(const char campo[][SIZE], enum status *); 	// checks win, loss, draw
void clearField(char campo[][SIZE]);					// clear the field so empty the array
void printField(const char campo[][SIZE]); 					// print the field to show it graphically

// ============================================================================= //
// ============================================================================= //
// ====================                MAIN              ======================= //
// ============================================================================= //
// ============================================================================= //

int main(void)
{
	enum status gameStatus; 		// stores game status
	enum players selectedPlayer; 	// stores playing player 
	char campo[SIZE][SIZE]; 		// field as an array where the players assign 'X' and 'O'
	bool playAgain; 				// stores if you want to start another game

	srand(time(NULL));

	do
	{
		gameStatus = NEWGAME;

		game(campo, &selectedPlayer, &gameStatus);

		switch(gameStatus)
		{
			case WON:
				puts("Complimenti, hai vinto!");
				break;
			case LOST:
				puts("Ops, mi dispiace hai perso.");
				break;
			case DRAW:
				puts("Hai pareggiato.");
				break;
			default:
				puts("Qualcosa è andato storto.");
		}

		puts("Vuoi avviare una nuova partita? s -> si");
		while(getchar() != '\n');
		
		if(getchar() == 's')
		{
			playAgain = true;
		}
		else playAgain = false;
	}
	while(playAgain);
	
   	return 0;
}

// ============================================================================= //
// ============================================================================= //
// ====================             END  MAIN            ======================= //
// ============================================================================= //
// ============================================================================= //

void game(char campo[][SIZE], enum players * selectedPlayer, enum status * gameStatus)
{
	clearField(campo); // clear the field
	printField(campo); // print the field in the terminal
	
	// choose first player based on random number
	if(random_max_min(0, 1)) 
	{
		*selectedPlayer = PLAYER; // start player1
	}  
	else *selectedPlayer = ENEMY; // start player2

	*gameStatus = RUNNING; // after i selected the player we can consider the game is running

	// players can play until anyone win
	while(*gameStatus == RUNNING) 
	{
		// one of the two players play a turn 
		if(*selectedPlayer == PLAYER)
		{
			playerGame(campo, selectedPlayer); 
		}
		else enemyGame(campo, selectedPlayer); 
		printField(campo);
		checkVictory(campo, gameStatus); 
	}
}


void enemyGame(char campo[][SIZE], enum players * selectedPlayer)
{	
	puts("E' il turno dell'avversario.");
	size_t x, y;
	do
	{	// generate random coordinates between 0 and 2
		x = random_max_min(0, 2); 
		y = random_max_min(0, 2);
	}
	while(campo[x][y] != ' '); // if the field is already signed, generate another random position

	campo[x][y] = 'O'; // insert enemy player sign

	*selectedPlayer = PLAYER;
}


void playerGame(char campo[][SIZE], enum players * selectedPlayer)
{
	puts("E' il tuo turno.");
	size_t x, y; // coordinates
	do
	{
		puts("Inserisci coordinata x: ");
		scanf("%zu", &x);
		puts("Inserisci coordinata y: ");
		scanf("%zu", &y);
	}
	// field must be empty and coordinates between 0 and 2
	while( x<0 || x>2 || y<0 || y>2 || campo[x][y] != ' ' );
	
	campo[x][y] = 'X'; // insert player sign
	
	*selectedPlayer = ENEMY;
}


// check if the player wins, looses or it's a draw
void checkVictory(const char campo[][SIZE], enum status *gameStatus)
{
	bool endGame = false;
	char storeWinner; // store the mark (X or O) of the winner

	// check horizontal tris
	for(size_t x=0; x<SIZE; x++)
	{
		if( campo[x][0] != ' ' && campo[x][0] == campo[x][1] && campo[x][1] == campo[x][2] )
		{
			endGame = true;
			storeWinner = campo[x][0];
			break; 
		}
	}

	// check vertical tris
	for(size_t y=0; y<SIZE; y++)
	{
		if( campo[0][y] != ' ' && campo[0][y] == campo[1][y] && campo[1][y] == campo[2][y] )
		{
			endGame = true;
			storeWinner = campo[0][y];
			break;
		}
	}
	
	// check diagonal tris
	if( campo[1][1] != ' ' && ((campo[0][0] == campo[1][1] && campo[1][1] == campo[2][2]) || (campo[2][0] == campo[1][1] && campo[1][1] == campo[0][2])) )
	{
		endGame = true;
		storeWinner = campo[1][1]; 
	}

	// check draw
	short countMarked = 0; // count number of full spaces to check the draw
	for(size_t i=0; i<SIZE; i++)
	{
		for(size_t j=0; j<SIZE; j++)
		{	// count marked spaces
			if( (campo[i][j] != ' ') && (campo[i][j] == 'X' || campo[i][j] == 'O') ) // la casella non deve essere vuota e contemporaneamente essere o X oppure O
			{
				countMarked++;
			}
			else countMarked--;
		}
	}
	if(countMarked == 9 && !endGame) // if the spaces are all full and anyone won or lost (endGame is true in those cases)
	{
		*gameStatus = DRAW;
	}

	// check who won
	if(endGame)
	{	
		*gameStatus = (storeWinner == 'X') ? WON : LOST;
	}
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
void printField(const char campo[][SIZE])
{
	printf(" %c | %c | %c \n", campo[0][0], campo[0][1], campo[0][2]);
	printf("%s\n", "---+---+---");
	printf(" %c | %c | %c \n", campo[1][0], campo[1][1], campo[1][2]);
	printf("%s\n", "---+---+---");
	printf(" %c | %c | %c \n\n", campo[2][0], campo[2][1], campo[2][2]);
}


// random generator function
int random_max_min(int min, int max){
    return (rand()+min) % (max+1);
}

