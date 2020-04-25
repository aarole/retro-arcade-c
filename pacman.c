#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include"json/ext_time.c"

#define SIZE 30
#define TRUE 1

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

struct Record{
	char name[30];
	int score;
	char date[10];
	char day[10];
};

struct Node{
	struct Record data;
	struct Node* next;
};

char get_input(){
	char input;
	
	system("/bin/stty raw");
	system("/bin/stty -echo");
	input = getchar();
	system("/bin/stty echo");
	system("/bin/stty cooked");

	return input;
}

void print_map(char lcl_map[SIZE][SIZE], int pts){
	system("clear");
	generate_point(lcl_map);
	generate_ghost(lcl_map,pts);
	printf("	Points: %d\n\n", pts);

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

int is_valid(char lcl_map[SIZE][SIZE], int r, int c){
	if(r>=0 && r<SIZE && c>=0 && c<SIZE && (lcl_map[r][c] == ' ' || lcl_map[r][c] == 'o') && lcl_map[r][c] != 'G'){
		return 1;
	}

	return 0;
}

int move(char lcl_map[SIZE][SIZE], int r, int c, int p){
	system("clear");
	lcl_map[r][c] = 'P';
	print_map(lcl_map, p);
}

int generate_point(char lcl_map[SIZE][SIZE]){
	int exists = 0;
	int p_row = 0;
	int p_col = 0;

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

	if(!exists){
		while(TRUE){
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

void generate_ghost(char lcl_map[SIZE][SIZE], int points){
	int count = 0;
	int p_row = 0;
	int p_col = 0;

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
	for(int k = 0; k < SIZE; k++){
		for(int l = 0; l < SIZE; l++){
			if(lcl_map[k][l] == 'G'){
				count++;
			}
		}
	}

	int row = 0;
	int col = 0;

	if(((points > 3 && points <= 6) && count == 4) || ((points > 6) && count == 5)){
		while(TRUE){
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

int ghost_valid(char lcl_map[SIZE][SIZE], int r, int c){
	if(r>=0 && r<SIZE && c>=0 && c<SIZE && (lcl_map[r][c] == 'o' || lcl_map[r][c] == ' ')){
		return 1;
	}

	return 0;
}

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

int get_rand(int lower, int upper){ 
    int i; 
    int num = (rand() % (upper - lower + 1)) + lower;
	return num;
} 

/*
int start = 0;
void move_ghost(char lcl_map[SIZE][SIZE], int r, int c){
	int choice = get_rand(1, 4);
	if(ghost_valid(lcl_map, r, c)){
		if(choice == 1){
			ghost_left(lcl_map,r,c);
		}
		if(choice == 2){
			ghost_right(lcl_map,r,c);
		}
		if(choice == 3){
			ghost_down(lcl_map,r,c);
		}
		else{
			ghost_up(lcl_map,r,c);
		}
	}


}*/

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

void yellow(){
	printf("\033[1;33m");
}

void red(){
	printf("\033[1;31m");
}

void green(){
	printf("\033[1;32m");
}

void reset(){
	printf("\033[0m");
	printf("\e[0m");
}

int main(){
	char player[25];
	struct Node* head = (struct Node*)malloc(sizeof(struct Node));

	while(TRUE){
		system("clear");
		//New row: {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'}
		//New col: ,' ',' ',' ',' ','#'

		char map[SIZE][SIZE] = { {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
								 {'#',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ','#'},
								 {'#',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ','#'},
								 {'#',' ',' ',' ',' ','#',' ',' ','#','#',' ',' ',' ',' ',' ','#',' ',' ',' ',' ','#','#',' ',' ',' ','#','#',' ',' ','#'},
								 {'#',' ','#',' ',' ','#',' ',' ',' ','#',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ','G',' ',' ','#',' ',' ',' ','#'},
								 {'#',' ','#',' ','#','#',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
								 {'#',' ','#',' ','#',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ','#',' ',' ',' ',' ',' ',' ','#'},
								 {'#',' ',' ',' ','G',' ',' ',' ',' ','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ','#'},
								 {'#',' ',' ','#',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ','#'},
								 {'#',' ',' ','#',' ',' ',' ','#','#',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','#',' ',' ',' ','#'},
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
								 {'#',' ',' ','#',' ','G',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','#',' ',' ','#'},
								 {'#',' ',' ','#',' ',' ',' ',' ','#','#','#','#','#',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
								 {'#',' ',' ','#',' ',' ',' ',' ',' ',' ','#',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ','G',' ',' ',' ',' ',' ','#'},
								 {'#',' ',' ','#',' ',' ',' ',' ',' ',' ','#',' ',' ',' ','#',' ',' ',' ',' ','#','#','#','#',' ',' ',' ',' ',' ',' ','#'},
								 {'#',' ',' ','#','#','#','#',' ',' ',' ','#',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ','#'},
								 {'#',' ',' ',' ',' ',' ','#',' ',' ',' ','#',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ','#'},
								 {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ','#'},
								 {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ','#'},
								 {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'}};
	
		int points = 0;
		int moves = 0;

		int coord[2];

		get_player_loc(map, coord);

		int row = coord[0];
		int column = coord[1];

		printf("Player name (no spaces): ");
		scanf("%s", &player);

		FILE* leaderboard;
		leaderboard = fopen("leaderboard_pacman.txt","r");
		char buffer[255];
		
		if(leaderboard == NULL){
			printf("Error: Leaderboard file not opened.\n");
			return 1;
		}
		else{
			printf("File opened.\n");
		}

		struct Node* current = head;

		char *names[5];
		int scores[5];
		char *dates[5];
		char *days[5];
		
		int i = 0;
		while(fgets(buffer,255,leaderboard) != NULL){
			char delim[] = " ";
			char *ptr = strtok(buffer,delim);
			char *data[4];
			int z = 0;
			while(ptr){
				data[z++] = ptr;
				ptr = strtok(NULL,delim);
			}
			
			strcpy(names[i],data[0]);
			scores[i] = atoi(data[1]);
			strcpy(dates[i], data[2]);
			strcpy(days[i], data[3]);
			printf("%s %d %s %s",names[i++],scores[i++],dates[i++],days[i++]);
			//sscanf(buffer, "%s %s %s %s", names[i], scores[i], dates[i],days[i]);
			i++;
		}
		//exit(0);
		/*while(fgets(buffer,255,leaderboard)){
			sscanf(buffer,"%s %d %s %s",&names[i],&scores[i],&dates[i],&days[i]);
			i++;
		}*/
		printf("\nName\tScore\tAchievement Date and Day\n");
		int f = 0;
		while(f<5){
			printf("%s %d %s %s\n",names[f++],scores[f++],dates[f++],days[f++]);
		}
		exit(0);

		/*
		time_t start = time(NULL);

		int caught = 0;
		
		for(int a = 0; a < SIZE; a++){
			for(int b = 0; b < SIZE; b++){
				if(map[a][b] == 'G'){
					int temp_a = a;
					int temp_b = b;
					alt_move(map, temp_a, temp_b);
				}
			}
		}
		//start = 1;

		while(points != 5){
			char x = get_input();
			print_map(map, points);

			switch (x){
				//Move up
				case 'w':{
					if(player_caught(map, row, column)){
						caught = 1;
						break;
					}
					for(int a = 0; a < SIZE; a++){
						for(int b = 0; b < SIZE; b++){
							if(map[a][b] == 'G'){
								int temp_a = a;
								int temp_b = b;
								move_ghost(map, temp_a, temp_b);
							}
						}
					}
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
					if(player_caught(map, row, column)){
						caught = 1;
						break;
					}
					for(int a = 0; a < SIZE; a++){
						for(int b = 0; b < SIZE; b++){
							if(map[a][b] == 'G'){
								int temp_a = a;
								int temp_b = b;
								move_ghost(map, temp_a, temp_b);
							}
						}
					}
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
					if(player_caught(map, row, column)){
						caught = 1;
						break;
					}
					for(int a = 0; a < SIZE; a++){
						for(int b = 0; b < SIZE; b++){
							if(map[a][b] == 'G'){
								int temp_a = a;
								int temp_b = b;
								move_ghost(map, temp_a, temp_b);
							}
						}
					}
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
					if(player_caught(map, row, column)){
						caught = 1;
						break;
					}
					for(int a = 0; a < SIZE; a++){
						for(int b = 0; b < SIZE; b++){
							if(map[a][b] == 'G'){
								int temp_a = a;
								int temp_b = b;
								move_ghost(map, temp_a, temp_b);
							}
						}
					}
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

			if(caught){
				break;
			}
		}

		time_t end = time(NULL);

		if(!caught){
			int score = (int)(end-start);
			printf("\nGame Complete\n");
			printf("%s's score: %d seconds\n", player, score);

			char cdate[10];
			char* cday;
			get_date(cdate, cday);
			int owpos = 0;
			for(int a = 0; a < 5; a++){
				if(score < scores[a]){
					owpos = a;
				}
			}
			for(int b = 4; b > (5 - (owpos + 1)); b--){
				names[b] = names[b-1];
				scores[b] = scores[b-1];
				dates[b] = dates[b-1];
				days[b] = days[b-1];
			}
			names[owpos] = player;
			scores[owpos] = score;
			dates[owpos] = cdate;
			days[owpos] = cday;
			printf("\n==============================");
			printf("\n\tLeaderboard:");
			printf("\n==============================");

			printf("\nName\tScore\tAchievement Date and Day");
			for(int c = 0; c < 5; c++){
				printf("\n%s\t%d\t%s\t%s",names[i],scores[i],dates[i],days[i]);
			}
			fclose(leaderboard);
			leaderboard = fopen("leaderboard_pacman.txt","w");
			for(int d = 0; d < 5; d++){
				fprintf(leaderboard,"%s %d %s %s",player,score,cdate,cday);
			}
			fclose(leaderboard);
		}

		printf("\nRestart? (y/n): \n");

		if(getchar() == 'n'){
			break;
		}
		*/
	}
	

	return 0;
	
}
