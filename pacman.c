#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define SIZE 12
#define TRUE 1

char get_input();
void print_map(char [SIZE][SIZE], int );
int is_valid(char [SIZE][SIZE], int , int );
int move(char [SIZE][SIZE], int , int , int );
int generate_point(char [SIZE][SIZE]);

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
	printf("			Points: %d\n\n", pts);
	for(int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			printf("%c    ", lcl_map[i][j]);
		}
		printf("\n\n");
	}
}

int is_valid(char lcl_map[SIZE][SIZE], int r, int c){
	if(r>=0 && r<SIZE && c>=0 && c<SIZE && (lcl_map[r][c] == ' ' || lcl_map[r][c] == 'o')){
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

			if(lcl_map[row][col] != 'P' && lcl_map[row][col] != '#'){
				lcl_map[row][col] = 'o';
				break;
			}
		}
	}
}

int main(){

	char map[SIZE][SIZE] = { {'#','#','#','#','#','#','#','#','#','#','#','#'},
							 {'#','P',' ',' ','#',' ',' ',' ',' ',' ',' ','#'},
							 {'#',' ',' ',' ','#','#',' ',' ',' ',' ',' ','#'},
							 {'#',' ','#',' ',' ','#',' ','#','#','#',' ','#'},
							 {'#',' ','#',' ',' ','#',' ','#',' ',' ',' ','#'},
							 {'#',' ','#',' ','#','#',' ','#','#',' ',' ','#'},
							 {'#',' ','#',' ','#',' ',' ',' ','#',' ',' ','#'},
							 {'#',' ','#',' ','#',' ',' ',' ','#',' ',' ','#'},
							 {'#','#','#',' ',' ',' ',' ',' ','#',' ',' ','#'},
							 {'#',' ',' ',' ',' ','#','#','#','#',' ',' ','#'},
							 {'#',' ',' ',' ','#','#',' ',' ',' ',' ',' ','#'},
							 {'#','#','#','#','#','#','#','#','#','#','#','#'}};

	char x = ',';
	int row = 1;
	int column = 1;
	int points = 0;

	printf("Press SPACE to start");

	while(points != 10){
		x = get_input();
		//generate_point(map);
		print_map(map, points);

		switch (x){
		//Move up
		case 'w':
			if(is_valid(map, row-1, column)){
				if(map[row-1][column] == 'o'){
					points++;
				}
				map[row][column] = ' ';
				row -= 1;
				move(map, row, column, points);
			}
			break;
		//Move left
		case 'a':
			if(is_valid(map, row, column-1)){
				if(map[row][column-1] == 'o'){
					points++;
				}
				map[row][column] = ' ';
				column -= 1;
				move(map, row, column, points);
			}
			break;
		//Move down
		case 's':
			if(is_valid(map, row+1, column)){
				if(map[row+1][column] == 'o'){
					points++;
				}
				map[row][column] = ' ';
				row += 1;
				move(map, row, column, points);
			}
			break;
		//Move right
		case 'd':
			if(is_valid(map, row, column+1)){
				if(map[row][column+1] == 'o'){
					points++;
				}
				map[row][column] = ' ';
				column += 1;
				move(map, row, column, points);
			}
			break;
		default:
			break;
		}
	}

	printf("\nGame Complete\n");
	printf("Score: \n");

	return 0;
}