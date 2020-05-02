#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

int tictactoe()
{
    
    //keep track of winner
    int win = false;
    //counter for number of turn
    int x = 0;
    //table array
    int table[9];
    int index;
    //whether player is X or O
    int player_symbol;
    //player 1 or 2
    int player;
    //regular flag
    int flag;
    //loop counters
    int i, j, k;
    //variable to loop again
    int again = 1;
    a:
      player = 1;
      x = 0;
      //loop to empty table
      for (i = 0; i < 9; i++)
      {
        table[i] = ' ';
      }

    
        //while players run through 9 turns
        while(x < 9) 
        {
            flag = 0;
            system("clear");
            printf("\n\n");

            //shows player which number belongs in which position
            printf(" Positions:\n");
            printf("\t\t\t  1 | 2 | 3  \n");
            printf("\t\t\t----+---+----\n");
            printf("\t\t\t  4 | 5 | 6  \n");
            printf("\t\t\t----+---+----\n");
            printf("\t\t\t  7 | 8 | 9  \n");

            printf("\n\n");

            //table to display each index or symbol of array 
            printf("\t\t\t  %c | %c | %c  \n", table[0], table[1], table[2]);
            printf("\t\t\t----+---+----\n");
            printf("\t\t\t  %c | %c | %c  \n", table[3], table[4], table[5]);
            printf("\t\t\t----+---+----\n");
            printf("\t\t\t  %c | %c | %c  \n", table[6], table[7], table[8]);

            printf("\n\n");

            //decides what symbol each player gets
            if (x % 2 == 0) 
            {
                player_symbol = 'O';
                player = 1;
            }
            else 
            {
                player_symbol = 'X';
                player = 2;
            }

            //displays the current player
            printf("Move for player %d(1-9):", player);
            scanf("%d", &index);

            //check to see if if player tries to mark something outside the
            if (index < 1 || index > 9) 
            {
                printf("Allowed index is 1 to 9!!\n");
                sleep(2);
                continue;
            }
            //check to see if player chose an occupied position
            else if (table[index - 1] == 'O' || table[index - 1] == 'X') 
            {
                printf("Position Already Occupied!!\n");
                sleep(2);
                continue;
            }
            //current player symbol
            table[index - 1] = player_symbol;
            x++;
            //checks for winning case
            for (i = 0; i < 9; i++)
            {
                if (i % 3 == 0)
                    flag = 0;

                if (table[i] == player_symbol)
                    flag++;

                if (flag == 3) 
                {
                    win = 1;
                    goto w;
                }
            }
            //checks for winning case
            flag = 0;
            for (i = 0; i < 3; i++) 
            {
                for (k = i; k <= i + 6; k = k + 3) 
                {
                    if (table[k] == player_symbol)
                        flag++;
                }
                
                if (flag == 3) 
                {
                    win = 1;
                    goto w;
                }
                            flag = 0;
            }
            //checks for winning case
            if ((table[0] == player_symbol && table[4] == player_symbol && table[8] == player_symbol) || (table[2] == player_symbol && table[4] == player_symbol && table[6] ==  player_symbol)) 
            {
                win = 1;
                goto w;
            }
        }
        //winning label
        w:
            system("clear");
            printf("\n\n");
            printf("\t\t\t  %c | %c | %c  \n", table[0], table[1], table[2]);
            printf("\t\t\t----+---+----\n");
            printf("\t\t\t  %c | %c | %c  \n", table[3], table[4], table[5]);
            printf("\t\t\t----+---+----\n");
            printf("\t\t\t  %c | %c | %c  \n", table[6], table[7], table[8]);
            //read player the winner or draw message
            if (win) 
            {
                printf("Player %d is the winner. Congrats!!\n", player);
                
            } 
            else 
            {
                    printf("Draw\n");
            }
            
            //player can choose whether to play again or not
            printf("Would you like to play again? 1 (Yes) | 2 (No): ");
            scanf("%d", &again);
            
            if(again == 1)
            {
                goto a;
            }
            else
            {
                
                return 0;
            }
            
            return 0;
            
    
}