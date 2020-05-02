//import games and header files
#include "./pacman/pacman.c"
#include "./tictactoe/tic-tac-toe.c"
//#include "./snake/snake.c"
#include "./minesweeper/minesweeper.c"
#include "./rps/RPS.c"
#include "./json/ext_time.c"
#include <stdio.h>

int main()
{
    int count = 0;// count for no. of games played
    while (1)// constantly loop until exit
    {
	// clear terminal
        system("clear");
	// get current date
        char today[10];
        get_date(today);
	// create variable for input
        int game;
	// display menu
        printf("\nWelcome to Retro Arcade\n");
        printf("Made by Aditya Arole, Resul Ucar, Will Grech, Will Woo, Zixiao Li\n");
        printf("__________________________________________________________________________________________\n");
        printf("Total games played on %s: %d\n",today,count);
        printf("__________________________________________________________________________________________\n");
        printf("Select a game:\n");
        printf("1. Snake (upcoming)\n");
        printf("2. Pacman\n");
        printf("3. Tic-Tac-Toe\n");
        printf("4. Minesweeper\n");
        printf("5. Rock, Paper, Scissors\n");
        printf("Please enter the game number (0 to exit): ");
        scanf("%d", &game);
	// read in input and call relevant game
        switch (game)
        {
            case 1:// snake game is not ready
            {
		printf("Snake is not ready yet.\n");
                //snake();
            }
            case 2:// pacman game
            {
                count++;
                pacman();
                break;
            }
            case 3:// tictactoe game
            {
                count++;
                tictactoe();
                break;
            }
            case 4:// minesweeper game
            {
                count++;
                minesweeper();
                break;
            }
            case 5:// rock paper scissors game
            {
                count++;
                rockpaperscissors();
                break;
            }
            default:// if not any of the previous selections, exit
            {
                printf("\nThanks for playing! Good bye!\n");
                exit(0);
            }
        }
    }
}
