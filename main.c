// Tris

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SIZE 3

int random_max_min(int, int);
void enemyGame(char campo[][SIZE]);		//
void playerGame(char campo[][SIZE]);	//
void newGame(char campo[][SIZE]);		// clear the field so empty the array
void printField(void); 					// print the field to show it graphically


// ============================================================================= //
// ============================================================================= //
// ====================                MAIN              ======================= //
// ============================================================================= //
// ============================================================================= //

int main(void)
{
	srand(time(NULL));

	char campo[SIZE][SIZE]; // definisco il campo come un array di char dove posiziono 'X' e 'O'
	
	newGame(campo); // clear the field
	//printField();
	// choose first player 
   	//playerGame();
   	//enemyGame();
}

// ============================================================================= //
// ============================================================================= //
// ====================             END  MAIN            ======================= //
// ============================================================================= //
// ============================================================================= //


void enemyGame(char campo[][SIZE])
{
	// generate random coordinates between 0 and 2
	short x = random_max_min(0, 2); // (short)
	short y = random_max_min(0, 2);

	while (campo[x][y] != '\0') // if the field is already signed, generate another random position
	{
		x = random_max_min(0, 2);
		y = random_max_min(0, 2);
	}

	campo[x][y] = 'O'; // insert enemy player sign
}


void playerGame(char campo[][SIZE])
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
	while( (x<0 || x>2) && (y<0 || y>2) && (campo[x][y] != '\0') ); 
	

	campo[x][y] = 'X'; // insert player sign

}


// clear the field so empty the array
void newGame(char campo[][SIZE])
{
	for(size_t i=0; i<SIZE; i++)
	{
		for(size_t j=0; j<SIZE; j++)
		{
			campo[i][j] == '\0';
		}
	}
}



// print the field on the cli
void printField(void)
{

}


// random generator function
int random_max_min(int min, int max){
    return (rand()+min) % (max+1);
}






// funzione per generare segno O casuale da parte dell'avversario
// funzione per far inserire al player il segno X
// funzione per stampare grafica del campo
// funzione per pulire campo e avviare nuova partita