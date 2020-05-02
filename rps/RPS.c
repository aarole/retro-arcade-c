#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "../hotbits/hotbits.c"

//global counters for score
int playerScore = 0;
int computerScore = 0;
//method for rps
void RPS(char input[10])
{
    for(int i =0; i< 10; i++)
    {
      input[i]= tolower(input[i]);
    }
    int conversion = 0;
    int computer = ((get_rand() % 3) + 1);
    //changes player input to an interger
    if (strcmp(input,"rock") ==0)
    {
        conversion = 1;
    }
    else if(strcmp(input,"paper") ==0)
    {
        conversion = 2;
    }
    else if(strcmp(input,"scissors") == 0)
    {
        conversion = 3;
    }
    else{
    	printf("Please try again.\n");
	return;
    }

    //check whether the player tied, loss, or won
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
    //in case error
    else
    {
        printf("There was an error please try again\n");
    } 
    return;
}    

int rockpaperscissors()
{
    //storage for input
    char input[10];
    int yesNo;
    system("clear");
    printf("\nWelcome to RPS \n");
    printf("Please Select Rock, Paper, Or Scissors: ");
    scanf("%s", input); 
    printf("\n");
    RPS(input);
    printf("The current score is %d - %d\n", playerScore, computerScore);
    printf("\nWould you like to play again? (1 for Yes, 2 for No): ");
    //player input for continued play
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
