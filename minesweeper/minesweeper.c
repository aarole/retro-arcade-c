#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

//Definitions of static variables
#define BOARD_SIZE 6
#define TRUE 0
#define FALSE 1

//Global variables needed to be refrenced
//by most of the game

char board[BOARD_SIZE][BOARD_SIZE];
char gameBoard[BOARD_SIZE][BOARD_SIZE];
int lost = 0;

//Creation of function prototypes
//Allows for references of functions before they are declared

void start();
int checkForNearMines(int, int);
void createMines();
void buildGameBoard();
void playAgain();
int playGame();
int checkForWin();
void printFullBoard();
void buildBoard();
void checkForMine(int, int);
void printBoard();
int playGame() {
  int r_selection = 0, c_selection = 0,
    nearbymines = 0, nearbymines2 = 0,
    nearbymines3 = 0, nearbymines4 = 0,
    nearbymines5 = 0, nearbymines6 = 0,
    nearbymines7 = 0, nearbymines8 = 0,
    i = 0;
  do {
    printf("\nMake a selection (ie. row [ENTER] col): \n");
    printf("Row--> ");
    scanf("%d", & r_selection);
    printf("Col--> ");
    scanf("%d", & c_selection);

  } while (r_selection < 1 || r_selection > BOARD_SIZE || c_selection < 1 || r_selection > BOARD_SIZE);

  checkForMine(r_selection - 1, c_selection - 1);

  if (lost == 1)
    return -1;

  nearbymines = checkForNearMines(r_selection - 1, c_selection - 1);
  gameBoard[r_selection - 1][c_selection - 1] = (char)(((int)
    '0') + nearbymines);

  if (nearbymines == 0) {
    if (c_selection != BOARD_SIZE) {
      i = 0;
      while (nearbymines == 0 && (c_selection - 1 + i) < BOARD_SIZE) {
        nearbymines = checkForNearMines(r_selection - 1, (c_selection - 1 + i));
        if (nearbymines != -1) {
          gameBoard[r_selection - 1][(c_selection - 1) + i] = (char)(((int)
            '0') + nearbymines);
          i++;
        }
      }
      if (r_selection != 1) {
        i = 0;
        while (nearbymines5 == 0 && (c_selection - 1 + i) < BOARD_SIZE && (r_selection - 1 - i) > 0) {
          nearbymines5 = checkForNearMines((r_selection - 1 - i), (c_selection - 1 + i));
          if (nearbymines5 != -1) {
            gameBoard[(r_selection - 1) - i][(c_selection - 1) + i] = (char)(((int)
              '0') + nearbymines5);
            i++;
          }
        }
      }
      if (r_selection != BOARD_SIZE) {
        i = 0;
        while (nearbymines6 == 0 && (r_selection - 1 + i) < BOARD_SIZE && (c_selection - 1 + i) < BOARD_SIZE) {
          nearbymines6 = checkForNearMines((r_selection - 1 + i), (c_selection - 1 + i));
          if (nearbymines != -1) {
            gameBoard[(r_selection - 1) + i][(c_selection - 1) + i] = (char)(((int)
              '0') + nearbymines6);
            i++;
          }
        }
      }
    }

    if (r_selection != BOARD_SIZE) {
      i = 0;
      while (nearbymines2 == 0 && (r_selection - 1 + i) < BOARD_SIZE) {
        nearbymines2 = checkForNearMines((r_selection - 1 + i), c_selection - 1);
        if (nearbymines2 != -1) {
          gameBoard[(r_selection - 1) + i][c_selection - 1] = (char)(((int)
            '0') + nearbymines2);
          i++;
        }
      }

      if (c_selection != BOARD_SIZE) {
        i = 0;
        while (nearbymines7 == 0 && (r_selection - 1 + i) < BOARD_SIZE && (c_selection - 1 - i) > 0) {
            nearbymines7 = checkForNearMines((r_selection - 1 + i), (c_selection - 1 - i));
          if (nearbymines != -1) {
            gameBoard[(r_selection - 1) + i][(c_selection - 1) - i] = (char)(((int)
              '0') + nearbymines7);
            i++;
          }
        }
      }
    }

    if (r_selection != 1) {
      i = 0;
      while (nearbymines3 == 0 && (r_selection - i) > 0) {
        nearbymines3 = checkForNearMines((r_selection - 1 - i), c_selection - 1);
        if (nearbymines3 != -1) {
          gameBoard[(r_selection - 1) - i][c_selection - 1] = (char)(((int)
            '0') + nearbymines3);
          i++;
        }
      }
      if (c_selection != BOARD_SIZE) {
        while (nearbymines8 == 0 && (c_selection - 1 - i) > 0 && (r_selection - 1 - i) > 0) {
          nearbymines8 = checkForNearMines((r_selection - 1 - i), (c_selection - 1 - i));
          if (nearbymines8 != -1) {
            gameBoard[(r_selection - 1) - i][(c_selection - 1) - i] = (char)(((int)
              '0') + nearbymines8);
            i++;
          }
        }
      }
    }

    if (c_selection != 1) {
      i = 0;
      while (nearbymines4 == 0 && (c_selection - i) > 0) {
        nearbymines4 = checkForNearMines(r_selection - 1, (c_selection - 1 - i));
        if (nearbymines4 != -1) {
          gameBoard[r_selection - 1][(c_selection - 1) - i] = (char)(((int)
            '0') + nearbymines4);
          i++;
        }
      }
    }
  }

  // Handles a player winning.
  if (checkForWin() == TRUE) {

    printFullBoard();
    printf("\n\nCongladurations A winner IS you\n\n");
    playAgain();
  }

  return 0;
}



void buildBoard() {
  int i, e;
  //generate board with empty spaces

  for (i = 0; i < BOARD_SIZE; i++) {
    for (e = 0; e < BOARD_SIZE; e++) {
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
  for (i = 0; i < BOARD_SIZE; i++) {
    random = rand() % (BOARD_SIZE);
    board[random][i] = '*';
  }
}
int checkForWin() {
  int row, col;

  for (row = 0; row < BOARD_SIZE; row++)
    for (col = 0; col < BOARD_SIZE; col++) {
      if (gameBoard[row][col] == '.' && board[row][col] != '*')
        return FALSE;
    }

  return TRUE;
}
void buildGameBoard() {
  int i, e;
  int row, col, cur = 4;

  printf("Creating game board");
  //assinging . to all board elements
  for (i = 0; i < BOARD_SIZE; i++) {
    for (e = 0; e < BOARD_SIZE; e++) {
      gameBoard[i][e] = '.';
    }
  }

  //prints the board
  for (col = 0; col < BOARD_SIZE; col++) {
    printf("%d ", col + 1);
  }

  printf("\n");

  for (row = 0; row < BOARD_SIZE; row++) {
    for (col = 0; col < BOARD_SIZE; col++) {
      printf("%c ", gameBoard[row][col]);
    }
    printf(" %d \n", row + 1);
  }
}

//prits actual board



void printBoard() {
  int row, col;

  for (col = 0; col < BOARD_SIZE; col++)
    printf("%d ", col + 1);

  printf("\n\n");
  for (row = 0; row < BOARD_SIZE; row++) {
    for (col = 0; col < BOARD_SIZE; col++) {
      printf("%c ", gameBoard[row][col]);
    }
    printf(" %d ", row + 1);
    printf("\n");
  }
}
void checkForMine(int r_select, int c_select) {
  if (board[r_select][c_select] == '*') {
    printf("\nYou've hit a mine! You lose!\n");
    getchar();
    getchar();
    lost = 1;
  }
}
int checkForNearMines(int r_select, int c_select) {
  int nearby_mine_count = 0;

  if (board[r_select][c_select] == '*') {
    return -1;
  }
  if (r_select < (BOARD_SIZE - 1) && c_select < (BOARD_SIZE - 1)) {
    if (board[r_select + 1][c_select] == '*')
      nearby_mine_count++;
    if (board[r_select][c_select + 1] == '*')
      nearby_mine_count++;
    if (board[r_select + 1][c_select + 1] == '*')
      nearby_mine_count++;
    if (c_select != 0) {
      if (board[r_select + 1][c_select - 1] == '*')
        nearby_mine_count++;
      if (board[r_select][c_select - 1] == '*')
        nearby_mine_count++;
    }

    if (r_select != 0) {
      if (board[r_select - 1][c_select] == '*')
        nearby_mine_count++;
      if (board[r_select - 1][c_select + 1] == '*')
        nearby_mine_count++;
      if (c_select != 0) {
        if (board[r_select - 1][c_select - 1] == '*')
          nearby_mine_count++;
      }
    }
  }

  if (r_select == (BOARD_SIZE - 1) && c_select != (BOARD_SIZE - 1)) {
    if (board[r_select - 1][c_select] == '*')
      nearby_mine_count++;
    if (board[r_select - 1][c_select + 1] == '*')
      nearby_mine_count++;
  }

  if (c_select == (BOARD_SIZE - 1) && r_select != (BOARD_SIZE - 1)) {
    if (board[r_select][c_select - 1] == '*')
      nearby_mine_count++;
    if (board[r_select + 1][c_select - 1] == '*')
      nearby_mine_count++;
  }

  if (r_select == (BOARD_SIZE - 1) && c_select == (BOARD_SIZE - 1)) {
    if (board[r_select][c_select - 1] == '*')
      nearby_mine_count++;
    if (board[r_select - 1][c_select - 1] == '*')
      nearby_mine_count++;
    if (board[r_select - 1][c_select] == '*')
      nearby_mine_count++;
  }

  return nearby_mine_count;
}

void printFullBoard() {
  int row, col;
  for (col = 0; col < BOARD_SIZE; col++)
    printf("%d ", col + 1);

  printf("\n");
  for (row = 0; row < BOARD_SIZE; row++) {
    for (col = 0; col < BOARD_SIZE; col++) {
      printf("%c ", board[row][col]);
    }
    printf(" %d\n", row + 1);

  }
}




void playAgain() {
  char ans;

  printf("\n\nWould you like to play again? (y/n) --> ");
  scanf(" %c", & ans);

  if (toupper(ans) == 'Y') {

    start();
  } else {
    printf("\n\nThanks for playing! Bye.\n");
    return;
  }
}

void start() {
  lost = 0; // User hasn't lost yet
  // Build both game boards (one for the user to see,
  // and the one with the mines).
  buildBoard();
  buildGameBoard();

  // Start playing game
  do {
    playGame();
    printBoard();
  } while (lost != 1); // While the user hasn't lost, loop.

  // Once user is lost, print the board with all the mines.
  printFullBoard();
  playAgain();
}

int minesweeper() {

  start();

  return 0;
}