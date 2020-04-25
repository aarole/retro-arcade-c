#include <stdio.h>
#include <stdbool.h>

int main()
{
    
    //keep track of winner
    int win = false;
    //counter for number of turn
    int x = 0;
    int table[9];
    int index;
    int player_symbol;
    int player;
    int flag;
    int i, j, k;
    int again = 1;
    a:
      player = 1;
      x = 0;
      for (i = 0; i < 9; i++)
      {
        table[i] = ' ';
      }

    
	
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

            printf("Move for player %d(1-9):", player);
            scanf("%d", &index);

            if (index < 1 || index > 9) 
            {
                printf("Allowed index is 1 to 9!!\n");
                sleep(2);
                continue;
            }

            else if (table[index - 1] == 'O' || table[index - 1] == 'X') 
            {
                printf("Position Already occupied!!\n");
                sleep(2);
                continue;
            }
            
            table[index - 1] = player_symbol;
            x++;

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

            if ((table[0] == player_symbol && table[4] == player_symbol && table[8] == player_symbol) || (table[2] == player_symbol && table[4] == player_symbol && table[6] ==  player_symbol)) 
            {
                win = 1;
                goto w;
            }
        }
        w:
            system("clear");
            printf("\n\n");
            printf("\t\t\t  %c | %c | %c  \n", table[0], table[1], table[2]);
            printf("\t\t\t----+---+----\n");
            printf("\t\t\t  %c | %c | %c  \n", table[3], table[4], table[5]);
            printf("\t\t\t----+---+----\n");
            printf("\t\t\t  %c | %c | %c  \n", table[6], table[7], table[8]);
            if (win) 
            {
                printf("Player %d is the winner. Congrats!!\n", player);
                
            } 
            else 
            {
                    printf("Draw\n");
            }
            

            printf("Would you like to play again? 1 (Yes) | 2 (No): ");
            scanf("%d", &again);
            
            if(again = 1)
            {
                goto a;
            }
            else
            {
                
                exit(0);
            }
            
            return 0;
            
    
}