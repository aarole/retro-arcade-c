#include "./pacman/pacman.c"
#include "./tictactoe/tic-tac-toe.c"
//#include "./snake/snake.c"
#include "./minesweeper/minesweeper.c"
#include "./rps/RPS.c"
#include "./json/ext_time.c"
#include <stdio.h>

int main()
{
    int count = 0;
    while (1)
    {
        system("clear");
        char today[10];
        get_date(today);
        int game;
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
        switch (game)
        {
            case 1:
            {
		printf("Snake is not ready yet.\n");
                //snake();
            }
            case 2:
            {
                count++;
                pacman();
                break;
            }
            case 3:
            {
                count++;
                tictactoe();
                break;
            }
            case 4:
            {
                count++;
                minesweeper();
                break;
            }
            case 5:
            {
                count++;
                rockpaperscissors();
                break;
            }
            default:
            {
                printf("\nThanks for playing! Good bye!\n");
                exit(0);
            }
        }
    }
}
