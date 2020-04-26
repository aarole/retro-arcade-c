#include "./pacman/pacman.c"
#include "./tictactoe/tic-tac-toe.c"
#include "./snake/snake.c"
#include <stdio.h>

int main()
{
    while (1)
    {
        int game;
        printf("Welcome to Retro Arcade\n");
        printf("Made by Aditya Arole, Resul Ucar, Will Woo, Will Grech, Zixiao Li\n");
        printf("__________________________________________________________________________________________\n")
        printf("Select a game:\n");
        printf("1. Snake\n");
        printf("2. Pacman\n");
        printf("3. Tic-Tac-Toe\n");
        printf("4. Minesweeper\n");
        printf("Please enter the game number (0 to exit): ");
        scanf("%d", &game);
        switch (game)
        {
            case 0:
            {
                exit(0);
            }
            case 1
            {
                snake();
            }
            case 1
            {
                pacman();
            }
            case 1
            {
                tictactoe();
            }
            case 1
            {
                minesweeper();
            }
        }
    }
}