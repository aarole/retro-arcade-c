//Created by Will Grech
//Algorithm an structure referenced from: https://cboard.cprogramming.com/c-programming/152639-simple-minesweeper-[c]-kinda-eh.html

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

//Definitions of static variables
#define MSWP_SIZE 6
enum {TRUE, FALSE};

//Global variables needed to be refrenced
//by most of the game

char board[MSWP_SIZE][MSWP_SIZE];
char gameBoard[MSWP_SIZE][MSWP_SIZE];
int lost = 0;

//Creation of function prototypes
//Allows for references of functions before they are declared

void start();
int checkForNearMines(int, int);
void createMines();
void buildGameBoard();
int playGame();
int checkForWin();
void printFullBoard();
void buildBoard();
void checkForMine(int, int);
void printBoard();

int playGame() {
	//actual playing of the game
	int rowSelection = 0; 
	int colSelection = 0;
	int	nearbymines = 0;
	int	nearbymines2 = 0;
	int	nearbymines3 = 0; 
	int	nearbymines4 = 0;
	int	nearbymines5 = 0; 
	int	nearbymines6 = 0;
	int	nearbymines7 = 0;
	int	nearbymines8 = 0;
	int	i = 0;
	//promts user to enter a guess and makes sure that the guess is valid then asks again if not
	do {
		printf("\nMake your move \n");
		printf("Column:");
		scanf("%d", & colSelection);
		printf("Row:");
		scanf("%d", & rowSelection);
		
		if(rowSelection < 1 || rowSelection > MSWP_SIZE || colSelection < 1 || rowSelection > MSWP_SIZE){
			printf("Enter valid values!\n");
		}
	} while (rowSelection < 1 || rowSelection > MSWP_SIZE || colSelection < 1 || rowSelection > MSWP_SIZE);
	//prompts to check mines
	checkForMine(rowSelection - 1, colSelection - 1);
	//if lost then activate losts
	if(lost == 1){
		return -1;
	}

	nearbymines = checkForNearMines(rowSelection - 1, colSelection - 1);
	gameBoard[rowSelection - 1][colSelection - 1] = (char)(48 + nearbymines);


	//Just goes through each of the surrounding area and checks each space to see if there are
	//any mines then tallies those into one number.
	//Use ASCII code of 0 (i.e. 48) and add number of nearby mines and convert to char and display
	if (nearbymines == 0) {
		if (colSelection != MSWP_SIZE) {
			i = 0;
			while (nearbymines == 0 && (colSelection - 1 + i) < MSWP_SIZE) {
				nearbymines = checkForNearMines(rowSelection - 1, (colSelection - 1 + i));
				if (nearbymines != -1) {
					gameBoard[rowSelection - 1][(colSelection - 1) + i] = (char)(48 + nearbymines);
					i++;
				}
			}
			if (rowSelection != 1) {
				i = 0;
				while (nearbymines5 == 0 && (colSelection - 1 + i) < MSWP_SIZE && (rowSelection - 1 - i) > 0) {
					nearbymines5 = checkForNearMines((rowSelection - 1 - i), (colSelection - 1 + i));
					if (nearbymines5 != -1) {
						gameBoard[(rowSelection - 1) - i][(colSelection - 1) + i] = (char)(48 + nearbymines5);
						i++;
					}
				}
			}
			if (rowSelection != MSWP_SIZE) {
				i = 0;
				while (nearbymines6 == 0 && (rowSelection - 1 + i) < MSWP_SIZE && (colSelection - 1 + i) < MSWP_SIZE) {
					nearbymines6 = checkForNearMines((rowSelection - 1 + i), (colSelection - 1 + i));
					if (nearbymines != -1) {
						gameBoard[(rowSelection - 1) + i][(colSelection - 1) + i] = (char)(48 + nearbymines6);
						i++;
					}
				}
			}
		}
		//Just makes sure its inside then checks all surrounding mines
		if (rowSelection != MSWP_SIZE) {
			i = 0;
			while (nearbymines2 == 0 && (rowSelection - 1 + i) < MSWP_SIZE) {
				nearbymines2 = checkForNearMines((rowSelection - 1 + i), colSelection - 1);
				if (nearbymines2 != -1) {
					gameBoard[(rowSelection - 1) + i][colSelection - 1] = (char)(48 + nearbymines2);
					i++;
				}
			}
		//same thing as above but just with collumn
			if (colSelection != MSWP_SIZE) {
				i = 0;
				while (nearbymines7 == 0 && (rowSelection - 1 + i) < MSWP_SIZE && (colSelection - 1 - i) > 0) {
						nearbymines7 = checkForNearMines((rowSelection - 1 + i), (colSelection - 1 - i));
					if (nearbymines != -1) {
						gameBoard[(rowSelection - 1) + i][(colSelection - 1) - i] = (char)(48 + nearbymines7);
						i++;
					}
				}
			}
		}
		//if the row doesn't equal 1(which is the top) then do the full sweep
		if (rowSelection != 1) {
			i = 0;
			while (nearbymines3 == 0 && (rowSelection - i) > 0) {
				nearbymines3 = checkForNearMines((rowSelection - 1 - i), colSelection - 1);
				if (nearbymines3 != -1) {
					gameBoard[(rowSelection - 1) - i][colSelection - 1] = (char)(48 + nearbymines3);
					i++;
				}
			}
			if (colSelection != MSWP_SIZE) {
				while (nearbymines8 == 0 && (colSelection - 1 - i) > 0 && (rowSelection - 1 - i) > 0) {
					nearbymines8 = checkForNearMines((rowSelection - 1 - i), (colSelection - 1 - i));
					if (nearbymines8 != -1) {
						gameBoard[(rowSelection - 1) - i][(colSelection - 1) - i] = (char)(48 + nearbymines8);
						i++;
					}
				}
			}
		}
		//same thing as above then do above
		if (colSelection != 1) {
			i = 0;
			while (nearbymines4 == 0 && (colSelection - i) > 0) {
				nearbymines4 = checkForNearMines(rowSelection - 1, (colSelection - 1 - i));
				if (nearbymines4 != -1) {
					gameBoard[rowSelection - 1][(colSelection - 1) - i] = (char)(48 + nearbymines4);
					i++;
				}
			}
		}
	}

	// Handles a player winning.
	if (checkForWin() == TRUE) {
		printFullBoard();
		printf("\n\nYou did it good job my man\n\n");
	}

	return 0;
}



void buildBoard() {
	int i, e;
	//generate board with empty spaces

	for (i = 0; i < MSWP_SIZE; i++) {
		for (e = 0; e < MSWP_SIZE; e++) {
			board[i][e] = '.';
		}
	}
	//Once finished, the newly made map is populated with mines
	createMines();
}

void createMines() {
	int i, random;
	//seeds the srand function with the current time
	srand(time(0));
	//Replaces the empty spaces with randomly arranged bombs
	for (i = 0; i < MSWP_SIZE; i++) {
		random = rand() % (MSWP_SIZE);
		board[random][i] = 'X';
	}
}
//Goes into board and checks to see if there is any empty spaces left
//if there arent then you win
int checkForWin() {
	int row, col;
	for (row = 0; row < MSWP_SIZE; row++)
		for (col = 0; col < MSWP_SIZE; col++) {
			if (gameBoard[row][col] == '.' && board[row][col] != 'X')
				return FALSE;
		}

	return TRUE;
}
//Builds the board that is displayed to the player and is modified
//built to help keep mines and all the numbers seperate
void buildGameBoard() {
	int i, e;
	int row, col, cur = 4;

	//assinging . to all board elements
	for (i = 0; i < MSWP_SIZE; i++) {
		for (e = 0; e < MSWP_SIZE; e++) {
			gameBoard[i][e] = '.';
		}
	}

	//prints the board
	for (col = 0; col < MSWP_SIZE; col++) {
		printf("%d ", col + 1);
	}

	printf("\n");

	for (row = 0; row < MSWP_SIZE; row++) {
		for (col = 0; col < MSWP_SIZE; col++) {
			printf("%c ", gameBoard[row][col]);
		}
		printf(" %d \n", row + 1);
	}
}

//prints actual board

void printBoard() {
	int row, col;
	printf("\n");
	for (col = 0; col < MSWP_SIZE; col++)
		printf("%d ", col + 1);
	//Just loops through and printes each letter
	printf("\n\n");
	for (row = 0; row < MSWP_SIZE; row++) {
		for (col = 0; col < MSWP_SIZE; col++) {
			printf("%c ", gameBoard[row][col]);
		}
		printf(" %d ", row + 1);
		printf("\n");
	}
}
//checks for mine on the co-ord provided
void checkForMine(int rowSelect, int colSelect) {
	if (board[rowSelect][colSelect] == 'X') {
		printf("\nYou've hit a mine! You lose!\n");
		printf("==================================\n\n");
		lost = 1;
		//makes the person lose if there is a mine
	}
}

//checks for nearby mines
int checkForNearMines(int rowSelect, int colSelect) {
	int nearbyMineCount = 0;
	//Will increment it^
	if (board[rowSelect][colSelect] == 'X') {
		return -1;
	}
	//Checks every space
	if (rowSelect < (MSWP_SIZE - 1) && colSelect < (MSWP_SIZE - 1)) {
		if (board[rowSelect + 1][colSelect] == 'X'){
			nearbyMineCount++;
		}
		if (board[rowSelect][colSelect + 1] == 'X'){
			nearbyMineCount++;
		}
		if (board[rowSelect + 1][colSelect + 1] == 'X'){
			nearbyMineCount++;
		}
		if (colSelect != 0) {
			if (board[rowSelect + 1][colSelect - 1] == 'X'){
				nearbyMineCount++;
			}
			if (board[rowSelect][colSelect - 1] == 'X'){
				nearbyMineCount++;
			}
		}

		if (rowSelect != 0) {
			if (board[rowSelect - 1][colSelect] == 'X'){
				nearbyMineCount++;
			}
			if (board[rowSelect - 1][colSelect + 1] == 'X'){
				nearbyMineCount++;
			}
			if (colSelect != 0) {
				if (board[rowSelect - 1][colSelect - 1] == 'X'){
					nearbyMineCount++;
				}
			}
		}
	}
//also checking spots
	if (rowSelect == (MSWP_SIZE - 1) && colSelect != (MSWP_SIZE - 1)) {
		if (board[rowSelect - 1][colSelect] == 'X'){
			nearbyMineCount++;
		}
		if (board[rowSelect - 1][colSelect + 1] == 'X'){
			nearbyMineCount++;
		}
	}

	if (colSelect == (MSWP_SIZE - 1) && rowSelect != (MSWP_SIZE - 1)) {
		if (board[rowSelect][colSelect - 1] == 'X')
			nearbyMineCount++;
		if (board[rowSelect + 1][colSelect - 1] == 'X')
			nearbyMineCount++;
	}

	if (rowSelect == (MSWP_SIZE - 1) && colSelect == (MSWP_SIZE - 1)) {
		if (board[rowSelect][colSelect - 1] == 'X'){
			nearbyMineCount++;
		}
		if (board[rowSelect - 1][colSelect - 1] == 'X'){
			nearbyMineCount++;
		}
		if (board[rowSelect - 1][colSelect] == 'X'){
			nearbyMineCount++;
		}
	}

	return nearbyMineCount;
}
//prints board that the player is shown
void printFullBoard() {
	int row, col;
	printf("\n");
	for (col = 0; col < MSWP_SIZE; col++){
		printf("%d ", col + 1);
	}

	printf("\n");
	for (row = 0; row < MSWP_SIZE; row++) {
		for (col = 0; col < MSWP_SIZE; col++) {
			printf("%c ", board[row][col]);
		}
		printf(" %d\n", row + 1);

	}
}

void start() {
	system("clear");
	lost = 0; // User hasn't lost yet
	// Build both game boards (one for the user to see,
	// and the one with the mines).
	buildBoard();
	buildGameBoard();

	// Start playing game
	do {
		playGame();
		if(lost != 1){
			printBoard();
		}
	} while (lost != 1); // While the user hasn't lost, loop.

	// Once user is lost, print the board with all the mines.
	printFullBoard();
}

int minesweeper() {

	//Infinite loop for the driver function
	while(1){
		//Run the game
		start();
		int choice = 1;

		//Break out of the infinite loop if the user wants to quit
		printf("\n\nRestart? (1 for yes, 2 for no): ");
		scanf("%d", &choice);

		if(choice == 2) {
			break;
		}
	}

	return 0;
}