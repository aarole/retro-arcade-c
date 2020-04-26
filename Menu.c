#include "./pacman/pacman.c"
#include "./tictactoe/tic-tac-toe.c"
//#include "./snake/snake.c"
#include "./minesweeper/minesweeper.c"
#include "./rps/RPS.c"
#include <stdio.h>

int main()
{
    while (1)
    {
        system("clear");
        int game;
        printf("Welcome to Retro Arcade\n");
        printf("Made by Aditya Arole, Resul Ucar, Will Grech, Will Woo, Zixiao Li\n");
        printf("__________________________________________________________________________________________\n");
        printf("Select a game:\n");
        printf("1. Snake\n");
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
                //snake();
            }
            case 2:
            {
                pacman();
                break;
            }
            case 3:
            {
                tictactoe();
                break;
            }
            case 4:
            {
                minesweeper();
                break;
            }
            case 5:
            {
                rockpaperscissors();
                break;
            }
            default:
            {
                exit(0);
            }
        }
    }
}