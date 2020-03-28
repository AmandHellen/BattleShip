#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 5
#define NUM_SHAPES 2

/*void print_shape(SHAPE s){
	for(int i = 0; i < MAX_SIZE; i++){
		printf("%s\n", s.shape[i]);
	}
}*/

int main (){
	char I[MAX_SIZE][MAX_SIZE + 1] = {"..X..",
									  "..X..",
									  "..X..",
									  "..X..",
									  "..X.."};

	char L[MAX_SIZE][MAX_SIZE + 1] = {"X....",
									  "X....",
									  "X....",
									  "X....",
									  "XXXXX"};
	
	char T[MAX_SIZE][MAX_SIZE + 1] = {"XXXXX",
									  "..X..",
									  "..X..",
									  "..X..",
									  "..X.."};

	char U[MAX_SIZE][MAX_SIZE + 1] = {"X...X",
									  "X...X",
									  "X...X",
									  "X...X",
									  "XXXXX"};
	
	char H[MAX_SIZE][MAX_SIZE + 1] = {"X...X",
									  "X...X",
									  "XXXXX",
									  "X...X",
									  "X...X"};
	
	char Z[MAX_SIZE][MAX_SIZE + 1] = {"XXXXX",
									  "...X.",
									  "..X..",
									  ".X...",
									  "XXXXX"};
	
	for(int i = 0; i < MAX_SIZE; i++){
		printf("%s\n", I[i]);
	}

	return 0;

}