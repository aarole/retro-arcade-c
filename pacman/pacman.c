//Created by Aditya Arole

//Include header files
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<stdbool.h>

//Create variable to store the map size
#define SIZE 30

//Create fuction prototypes
char get_input();
void print_map(char [SIZE][SIZE], int );
int is_valid(char [SIZE][SIZE], int , int );
int move(char [SIZE][SIZE], int , int , int );
int generate_point(char [SIZE][SIZE]);
void generate_ghost(char [SIZE][SIZE], int );
int player_caught(char [SIZE][SIZE], int , int );
void get_player_loc(char [SIZE][SIZE], int [2]);
int ghost_valid(char [SIZE][SIZE], int , int );
void alt_move(char [SIZE][SIZE], int , int );
void move_ghost(char [SIZE][SIZE], int , int );
int ghost_down(char [SIZE][SIZE], int , int );
int ghost_up(char [SIZE][SIZE], int , int );
int ghost_left(char [SIZE][SIZE], int , int );
int ghost_right(char [SIZE][SIZE], int , int );
void red();
void green();
void yellow();
void reset();

//Function that gets user input without echoing it
char get_input(){
	char input;
	
	system("/bin/stty raw");
	system("/bin/stty -echo");
	input = getchar();
	system("/bin/stty echo");
	system("/bin/stty cooked");

	return input;
}

//Function to print the map in its current state
void print_map(char lcl_map[SIZE][SIZE], int pts){
	system("clear");
	generate_point(lcl_map);
	generate_ghost(lcl_map,pts);
	printf("	Points: %d\n\n", pts);

	//Print the player in yellow, point in green and wall in red
	for(int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			char pt = lcl_map[i][j];
			switch(pt){
				case '#':
					red();
					printf("%c ", pt);
					reset();
					break;
				case 'P':
					yellow();
					printf("%c ", pt);
					reset();
					break;
				case 'o':
					green();
					printf("%c ", pt);
					reset();
					break;
				default:
					printf("%c ", pt);
					break;
			}
		}
		printf("\n");
	}
}

//Check if the player's move is valid
int is_valid(char lcl_map[SIZE][SIZE], int r, int c){
	if(r>=0 && r<SIZE && c>=0 && c<SIZE && (lcl_map[r][c] == ' ' || lcl_map[r][c] == 'o') && lcl_map[r][c] != 'G'){
		return 1;
	}

	return 0;
}

//Move the player to a defined point
int move(char lcl_map[SIZE][SIZE], int r, int c, int p){
	system("clear");
	lcl_map[r][c] = 'P';
	print_map(lcl_map, p);
}

//Generate a point in the map
int generate_point(char lcl_map[SIZE][SIZE]){
	int exists = 0;
	int p_row = 0;
	int p_col = 0;

	//Get the player's coordinates
	for(int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			if(lcl_map[i][j] == 'P'){
				p_row = i;
				p_col = j;
				break;
			}
		}
		if(p_row != 0 && p_col != 0){
			break;
		}
	}

	//Check if there is already a point
	for(int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			if(lcl_map[i][j] == 'o'){
				exists = 1;
				break;
			}
		}
		if(exists){
			break;
		}
	}

	int row = 0;
	int col = 0;

	//Generate a point 3 spaces away from the player (if there isn't one already)
	if(!exists){
		while(true){
			row = (rand() % (SIZE + 1));
			col = (rand() % (SIZE + 1));
			int x_rad = abs((row-p_row));
			int y_rad = abs((col-p_col));

			if(lcl_map[row][col] != 'P' && lcl_map[row][col] != 'G' && lcl_map[row][col] != '#' && x_rad > 3 && y_rad > 3){
				lcl_map[row][col] = 'o';
				break;
			}
		}
	}
}

//Generate a ghost on the map
void generate_ghost(char lcl_map[SIZE][SIZE], int points){
	int count = 0;
	int p_row = 0;
	int p_col = 0;

	//Get the player's coordinates
	for(int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			if(lcl_map[i][j] == 'P'){
				p_row = i;
				p_col = j;
				break;
			}
		}
		if(p_row != 0 && p_col != 0){
			break;
		}
	}
	//Count the number of ghosts in the map
	for(int k = 0; k < SIZE; k++){
		for(int l = 0; l < SIZE; l++){
			if(lcl_map[k][l] == 'G'){
				count++;
			}
		}
	}

	int row = 0;
	int col = 0;

	//Generate 1 ghost 5 spaces away after the player crosses 3 and 6 points
	if(((points > 3 && points <= 6) && count == 4) || ((points > 6) && count == 5)){
		while(true){
			row = (rand() % (SIZE + 1));
			col = (rand() % (SIZE + 1));
			int x_rad = abs((row-p_row));
			int y_rad = abs((col-p_col));

			if(lcl_map[row][col] != 'P' && lcl_map[row][col] != 'G' && lcl_map[row][col] != '#' && lcl_map[row][col] != 'o' && x_rad > 5 && y_rad > 5){
				lcl_map[row][col] = 'G';
				break;
			}
		}
	}
}

//Check if the player is caught
int player_caught(char lcl_map[SIZE][SIZE], int r, int c){
	if(lcl_map[r+1][c] == 'G' || 
	lcl_map[r-1][c] == 'G' ||
	lcl_map[r][c+1] == 'G' ||
	lcl_map[r][c-1] == 'G'){
		red();
		printf("\n	Game Over!\n");
		reset();
		return 1;
	}
	else{
		return 0;
	}
}

//Function to get the player's current coordinates
void get_player_loc(char lcl_map[SIZE][SIZE], int temp[2]){
	for(int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			if(lcl_map[i][j] == 'P'){
				temp[0] = i;
				temp[1] = j;
				return;
			}
		}
	}
}

//Check if the ghost's move is valid
int ghost_valid(char lcl_map[SIZE][SIZE], int r, int c){
	if(r>=0 && r<SIZE && c>=0 && c<SIZE && (lcl_map[r][c] == 'o' || lcl_map[r][c] == ' ')){
		return 1;
	}

	return 0;
}

//Move the ghost randomly based on where it is blocked off
char prev = 'o';
void alt_move(char lcl_map[SIZE][SIZE], int r, int c){
	//Bottom and left
	if(lcl_map[r+1][c] == '#' && lcl_map[r][c-1] == '#'){
		int pick = rand() % 2;
		if(pick){
			ghost_right(lcl_map, r, c);
			prev = 'd';
		}
		else{
			ghost_up(lcl_map, r, c);
			prev = 'w';
		}
	}
	//Top and left
	else if(lcl_map[r-1][c] == '#' && lcl_map[r][c-1] == '#'){
		int pick = rand() % 2;
		if(pick){
			ghost_right(lcl_map, r, c);
			prev = 'd';
		}
		else{
			ghost_down(lcl_map, r, c);
			prev = 's';
		}
	}
	//Top and right
	else if(lcl_map[r-1][c] == '#' && lcl_map[r][c+1] == '#'){
		int pick = rand() % 2;
		if(pick){
			ghost_left(lcl_map, r, c);
			prev = 'a';
		}
		else{
			ghost_down(lcl_map, r, c);
			prev = 's';
		}
	}
	//Bottom and right
	else{
		int pick = rand() % 2;
		if(pick){
			ghost_left(lcl_map, r, c);
			prev = 'a';
		}
		else{
			ghost_up(lcl_map, r, c);
			prev = 'w';
		}
	}
}

//Move the ghost based on its previous move
void move_ghost(char lcl_map[SIZE][SIZE], int r, int c){
	
	if(prev == 's'){
		if(lcl_map[r+1][c] == '#'){
			prev = 'o';
			alt_move(lcl_map,r,c);
		}
		else{
			ghost_down(lcl_map,r,c);
		}
	}
	else if(prev == 'a'){
		if(lcl_map[r][c-1] == '#'){
			prev = 'o';
			alt_move(lcl_map,r,c);
		}
		else{
			ghost_left(lcl_map,r,c);
		}
	}
	else if(prev == 'd'){
		if(lcl_map[r][c+1] == '#'){
			prev = 'o';
			alt_move(lcl_map,r,c);
		}
		else{
			ghost_right(lcl_map,r,c);
		}
	}
	else if(prev == 'w'){
		if(lcl_map[r-1][c] == '#'){
			prev = 'o';
			alt_move(lcl_map,r,c);
		}
		else{
			ghost_up(lcl_map,r,c);
		}
	}
	else{
		
	}
	
}

//Move the ghost down, move two spaces if a point exists
int ghost_down(char lcl_map[SIZE][SIZE], int r, int c){
	if(ghost_valid(lcl_map, r+1, c)){
		lcl_map[r][c] = ' ';
		if(lcl_map[r+1][c] == 'o'){
			if(lcl_map[r+2][c] == '#'){
				//Do nothing
			}
			else{
				r += 2;
			}
		}
		else{
			r += 1;
		}
		if(lcl_map[r][c] == 'G'){
			return 0;
		}
		lcl_map[r][c] = 'G';
	}
}

//Move the ghost up, move two spaces if a point exists
int ghost_up(char lcl_map[SIZE][SIZE], int r, int c){
	if(ghost_valid(lcl_map, r-1, c)){
		lcl_map[r][c] = ' ';
		if(lcl_map[r-1][c] == 'o'){
			if(lcl_map[r-2][c] == '#'){
				//Do nothing
			}
			else{
				r -= 2;
			}
		}
		else{
			r -= 1;
		}
		if(lcl_map[r][c] == 'G'){
			return 0;
		}
		lcl_map[r][c] = 'G';
	}
}

//Move the ghost left, move two spaces if a point exists
int ghost_left(char lcl_map[SIZE][SIZE], int r, int c){
	if(ghost_valid(lcl_map, r, c-1)){
		lcl_map[r][c] = ' ';
		if(lcl_map[r][c-1] == 'o'){
			if(lcl_map[r][c-2] == '#'){
				//Do nothing
			}
			else{
				c -= 2;
			}
		}
		else{
			c -= 1;
		}
		if(lcl_map[r][c] == 'G'){
			return 0;
		}
		lcl_map[r][c] = 'G';
	}
}

//Move the ghost right, move two spaces if a point exists
int ghost_right(char lcl_map[SIZE][SIZE], int r, int c){
	if(ghost_valid(lcl_map, r, c+1)){
		lcl_map[r][c] = ' ';
		if(lcl_map[r][c+1] == 'o'){
			if(lcl_map[r][c+2] == '#'){
				//Do nothing
			}
			else{
				c += 2;
			}
			
		}
		else{
			c += 1;
		}
		if(lcl_map[r][c] == 'G'){
			return 0;
		}
		lcl_map[r][c] = 'G';
	}
}

//Make the terminal yellow
void yellow(){
	printf("\033[1;33m");
}

//Make the terminal red
void red(){
	printf("\033[1;31m");
}

//Make the terminal green
void green(){
	printf("\033[1;32m");
}

//Reset the terminal's color
void reset(){
	printf("\033[0m");
	printf("\e[0m");
}

//Driver function
int pacman(){
	//String to store the players name
	char player[25];

	while(true){
		//Refresh the screen
		system("clear");
		//New row: {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'}
		//New col: ,' ',' ',' ',' ','#'

		//Two-dimensional array to store the map
		char map[SIZE][SIZE] = { {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
								 {'#',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ','#'},
								 {'#',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ','#'},
								 {'#',' ',' ',' ',' ','#',' ',' ','#','#',' ',' ',' ',' ',' ','#',' ',' ',' ',' ','#','#',' ',' ',' ','#','#',' ',' ','#'},
								 {'#',' ','#',' ',' ','#',' ',' ',' ','#',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ','#'},
								 {'#',' ','#',' ','#','#',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
								 {'#',' ','#',' ','#',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ','#',' ',' ',' ',' ',' ',' ','#'},
								 {'#',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','G',' ',' ',' ',' ',' ','#'},
								 {'#',' ',' ','#',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ','#'},
								 {'#',' ',' ','#',' ','G',' ','#','#',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','#',' ',' ',' ','#'},
								 {'#',' ',' ','#',' ',' ',' ','#',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ','#'},
								 {'#',' ',' ',' ',' ','#','#','#',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ','#'},
								 {'#',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ','#'},
								 {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
								 {'#',' ',' ',' ',' ',' ',' ',' ','#',' ',' ','#',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
								 {'#',' ',' ',' ',' ',' ',' ',' ','#',' ',' ','#',' ',' ','P',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
								 {'#',' ','#','#','#','#',' ',' ','#',' ',' ','#',' ',' ',' ','#',' ',' ','#','#','#','#','#',' ',' ',' ',' ',' ',' ','#'},
								 {'#',' ',' ',' ',' ','#',' ',' ','#',' ',' ',' ',' ',' ',' ','#',' ',' ','#',' ',' ',' ','#',' ',' ',' ',' ',' ',' ','#'},
								 {'#',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ','#','#','#','#',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
								 {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' ',' ','#',' ',' ','#'},
								 {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ','#'},
								 {'#',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','#',' ',' ','#'},
								 {'#',' ',' ','#',' ',' ',' ',' ','#','#','#','#','#',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
								 {'#',' ',' ','#',' ',' ',' ',' ',' ',' ','#',' ',' ',' ','#',' ',' ','G',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
								 {'#',' ',' ','#',' ',' ',' ',' ',' ',' ','#',' ',' ',' ','#',' ',' ',' ',' ','#','#','#','#',' ',' ',' ',' ',' ',' ','#'},
								 {'#',' ',' ','#','#','#','#',' ',' ',' ','#',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ','#'},
								 {'#',' ',' ',' ',' ',' ','#',' ',' ',' ','#',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ','#'},
								 {'#',' ',' ',' ',' ','G',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ','#'},
								 {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ','#'},
								 {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'}};
	
		int points = 0;
		int moves = 0;

		int coord[2];
		//Store player's starting coordinates
		get_player_loc(map, coord);

		int row = coord[0];
		int column = coord[1];

		//Get player's name
		printf("Player name (no spaces): ");
		scanf("%s", &player);

		//Begin stopwatch
		time_t start = time(NULL);

		int caught = 0;
		
		//Make the ghosts' first move
		for(int a = 0; a < SIZE; a++){
			for(int b = 0; b < SIZE; b++){
				if(map[a][b] == 'G'){
					int temp_a = a;
					int temp_b = b;
					alt_move(map, temp_a, temp_b);
				}
			}
		}

		//Loop till the user reaches 10 points
		while(points != 10){
			//Get user input
			char x = get_input();
			print_map(map, points);

			//Switch case to determine input
			switch (x){
				//Move up
				case 'w':{
					//Check if caught
					if(player_caught(map, row, column)){
						caught = 1;
						break;
					}
					//Move ghost
					for(int a = 0; a < SIZE; a++){
						for(int b = 0; b < SIZE; b++){
							if(map[a][b] == 'G'){
								int temp_a = a;
								int temp_b = b;
								move_ghost(map, temp_a, temp_b);
							}
						}
					}
					//Make move
					if(is_valid(map, row-1, column)){
						if(map[row-1][column] == 'o'){
							points++;
						}
						map[row][column] = ' ';
						row -= 1;
						moves += 1;

						move(map, row, column, points);
						
					}
					break;
				}
				//Move left
				case 'a':{
					//Check if caught
					if(player_caught(map, row, column)){
						caught = 1;
						break;
					}
					//Move ghost
					for(int a = 0; a < SIZE; a++){
						for(int b = 0; b < SIZE; b++){
							if(map[a][b] == 'G'){
								int temp_a = a;
								int temp_b = b;
								move_ghost(map, temp_a, temp_b);
							}
						}
					}
					//Make move
					if(is_valid(map, row, column-1)){
						if(map[row][column-1] == 'o'){
							points++;
						}
						map[row][column] = ' ';
						column -= 1;
						moves += 1;

						move(map, row, column, points);
						if(player_caught(map, row, column)){
							caught = 1;
							break;
						}
					}
					break;
				}
				//Move down
				case 's':{
					//Check if caught
					if(player_caught(map, row, column)){
						caught = 1;
						break;
					}
					//Move ghost
					for(int a = 0; a < SIZE; a++){
						for(int b = 0; b < SIZE; b++){
							if(map[a][b] == 'G'){
								int temp_a = a;
								int temp_b = b;
								move_ghost(map, temp_a, temp_b);
							}
						}
					}
					//make move
					if(is_valid(map, row+1, column)){
						if(map[row+1][column] == 'o'){
							points++;
						}
						map[row][column] = ' ';
						row += 1;
						moves += 1;

						move(map, row, column, points);
						if(player_caught(map, row, column)){
							caught = 1;
							break;
						}
					}
					break;
				}
				//Move right
				case 'd':{
					//Check if caught
					if(player_caught(map, row, column)){
						caught = 1;
						break;
					}
					//Move ghost
					for(int a = 0; a < SIZE; a++){
						for(int b = 0; b < SIZE; b++){
							if(map[a][b] == 'G'){
								int temp_a = a;
								int temp_b = b;
								move_ghost(map, temp_a, temp_b);
							}
						}
					}
					//Make move
					if(is_valid(map, row, column+1)){
						if(map[row][column+1] == 'o'){
							points++;
						}
						map[row][column] = ' ';
						column += 1;
						moves += 1;

						move(map, row, column, points);
						if(player_caught(map, row, column)){
							caught = 1;
							break;
						}
					}
					break;
				}
				default:{
					break;
				}
			}
			//Break out of the loop if the user is caught
			if(caught){
				break;
			}
		}
		//Stop time
		time_t end = time(NULL);

		//Print score if the user is not caught
		if(!caught){
			int score = (int)(end-start);
			printf("\nGame Complete\n");
			printf("%s's score: %d seconds\n", player, score);
		}

		//Check if user wants to restart
		printf("\nRestart? (y/n): \n");

		if(getchar() == 'n'){
			break;
		}
		
	}

	return 0;
	
}
