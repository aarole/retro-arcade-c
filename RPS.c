#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "../hotbits/hotbits.c"

// Global counters for score
int playerScore = 0;
int computerScore = 0;
// Method for rps
void RPS(char input[10])
{
    // Runs through user inputs and makes every letter lowercase to make it not matter if it's in different cases
    for(int i =0; i< 10; i++)
    {
      input[i]= tolower(input[i]);
    }

    // Varible that will store the user's input as a number so it's easier to compare them to the computer.
    int conversion = 0;

    // Generates computer's input as a number that will be used later to compare to the user's input.
    int computer = ((get_rand() % 3) + 1);
    
    // Changes player input to an interger by comparing them to either rock, paper, or scissors and changing conversions to correspond with the correct number.
    if (strcmp(input,"rock")==0)
    {
        conversion = 1;
        return;
    }
    else if(strcmp(input,"paper")==0)
    {
        conversion = 2;
        return;
    }
    else if(strcmp(input,"scissors")==0)
    {
        conversion = 3;
        return;
    }
    else
    {
        printf("Please try again.\n");
	    return;
    }

    // Checks whether the player tied, loss, or won
    if (computer == conversion)
    {
        printf("You and the computer tied\n");
    }
    else if (conversion == 1 && computer == 2)
    {
        printf("The computer selected paper.\n");
        printf("You lost to the computer\n");
        computerScore++;
    }
    else if (conversion == 1 && computer == 3)
    {
        printf("The computer selected scissors.\n");
        printf("You beat the computer\n");
        playerScore++;
    }
    else if (conversion == 2 && computer == 1)
    {
        printf("The computer selected rock.\n");
        printf("You beat the computer\n");
        playerScore++;

    }
    else if (conversion == 2 && computer == 3)
    {
        printf("The computer selected scissors.\n");
        printf("You lost to the computer\n");
        computerScore++;
    }    
    else if (conversion == 3 && computer == 1)
    {
        printf("The computer selected rock.\n");
        printf("You lost to the computer\n");
        computerScore++;
    }    
    else if (conversion == 3 && computer == 2)
    {
        printf("The computer selected paper.\n");
        printf("You beat the computer\n");
        playerScore++;
    }   
    // In case there is an error with computer generating number outside of 1-3
    else
    {
        printf("There was an error please try again\n");
    } 
    return;
}    

int rockpaperscissors()
{
    // Storage for input.
    char input[10];
    // Varible for user's input whether they want to play again
    int yesNo;
    system("clear");
    printf("\nWelcome to RPS \n");
    printf("Please Select Rock, Paper, Or Scissors: ");
    scanf("%s", input); 
    printf("\n");
    RPS(input);
    printf("The current score is %d - %d\n", playerScore, computerScore);
    printf("\nWould you like to play again? (1 for Yes, 2 for No): ");
    // Player input for continued play
    scanf("%d", &yesNo);
    if (yesNo == 2)
    {
        return 0;
    }
    else
    {
        rockpaperscissors();
    }
}
