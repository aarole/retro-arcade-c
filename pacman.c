#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SIZE 12
#define TRUE 1

char get_input(){
	char input;
	
	system("/bin/stty raw");
	system("/bin/stty -echo");
	input = getchar();
	system("/bin/stty echo");
	system("/bin/stty cooked");

	return input;
}

void print_map(char map[SIZE][SIZE]){
	system("clear");
	for(int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			printf("%c    ", map[i][j]);
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

 int move(char lcl_map[SIZE][SIZE], int r, int c){
	system("clear");
	lcl_map[r][c] = 'P';
	print_map(lcl_map);
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

	while(x != '.'){
		x = get_input();
		print_map(map);

		switch (x){
		//Move up
		case 'w':
			if(is_valid(map, row-1, column)){
				map[row][column] = ' ';
				row -= 1;
				move(map, row, column);
			}
			break;
		//Move left
		case 'a':
			if(is_valid(map, row, column-1)){
				map[row][column] = ' ';
				column -= 1;
				move(map, row, column);
			}
			break;
		//Move down
		case 's':
			if(is_valid(map, row+1, column)){
				map[row][column] = ' ';
				row += 1;
				move(map, row, column);
			}
			break;
		//Move right
		case 'd':
			if(is_valid(map, row, column+1)){
				map[row][column] = ' ';
				column += 1;
				move(map, row, column);
			}
			break;
		default:
			break;
		}
	}

	return 0;
}