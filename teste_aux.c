#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#define DIM 10
#define MAX_SIZE 5

typedef enum {EMPTY, FILLED, HIT} TILE;

int rotate_point(int i, int j, int r){
    switch(r % 4){
        case 0: return i * MAX_SIZE + j;
        case 1: return 20 + i - (j * MAX_SIZE);
        case 2: return 24 - (i * MAX_SIZE) - j;
        case 3: return 4 - i + (j * MAX_SIZE);
    }
    return 0;
}

bool DoesPieceFit(char *shape, int nRotation, int oldX, int oldY, int nPosX, int nPosY, char *pField, TILE *map)
{
	int oldPosition;
	for (int i = 0; i < MAX_SIZE; i++)
		for (int j = 0; j < MAX_SIZE; j++)
		{
			oldPosition = (oldY + i)*DIM + (oldX + j);
			if(map[oldPosition] != FILLED)
            	pField[oldPosition] = '.';
			// Get index into piece
			int pi = rotate_point(i, j, nRotation);

            if (shape[pi] != '.'){
                if ((nPosY +i < 0 || nPosY + i >= DIM) || (nPosX + j < 0 || nPosX + j >= DIM)){
                    return false;
                }
            }
		}
	return true;
}

int placeShip(char *shape, TILE *map, char *pField, int nCurrentX, int nCurrentY, int nRotation){
	for (int i = 0; i < MAX_SIZE; i++){
        for (int j = 0; j < MAX_SIZE; j++){
            if ((map[(nCurrentY + i)*DIM + (nCurrentX + j)] == FILLED) && (shape[rotate_point(i, j, nRotation)] != '.')){
            	return -1;
            }
        }
    }

	for (int i = 0; i < MAX_SIZE; i++){
        for (int j = 0; j < MAX_SIZE; j++){
            if (shape[rotate_point(i, j, nRotation)] != '.'){
            	map[(nCurrentY + i)*DIM + (nCurrentX + j)] = FILLED;
            	pField[(nCurrentY + i)*DIM + (nCurrentX + j)] = 'O';
            }
        }
    }

    return 0;
}

int main()
{
	// Game Logic
	char bKey;
	int oldX, oldY;
	int nCurrentRotation = 0;
	int nCurrentX = DIM / 2;
	int nCurrentY = 0;
	char nCurrentPiece[MAX_SIZE*MAX_SIZE + 1] = {"..X....X....X....X....X.."};
    char pField[DIM*DIM + 1]; // Create play field buffer
    TILE map[DIM*DIM];

	//create map
	for (int i = 0; i < DIM; i++){
		for (int j = 0; j < DIM; j++){
			map[i*DIM + j] = EMPTY;
		}
	}

    for (int i = 0; i < DIM; i++){
		for (int j = 0; j < DIM; j++){
			pField[i*DIM + j] = '.';
		}
	}

    // Place ship on the map
    for (int i = 0; i < MAX_SIZE; i++){
        for (int j = 0; j < MAX_SIZE; j++){
            if (nCurrentPiece[i * MAX_SIZE + j] != '.')
                pField[(nCurrentY + i)*DIM + (nCurrentX + j)] = 'X';
        }
    }

    oldX = nCurrentX;
    oldY = nCurrentY;

	while (1) // Main Loop
	{
        // Draw Field
		printf("  ");
		for (int i = 0; i < DIM; i++)
			printf("%.2d ", i);

		printf("\n");
		for (int i = 0; i < DIM; i++){
			printf("%.2d", i);
			for (int j = 0; j < DIM; j++){
				printf(" %c ",pField[i*DIM + j]);
			}
			printf("\n");
		}

		// Draw MAP
		printf("  ");
		for (int i = 0; i < DIM; i++)
			printf("%.2d ", i);

		printf("\n");
		for (int i = 0; i < DIM; i++){
			printf("%.2d", i);
			for (int j = 0; j < DIM; j++){
				printf(" %d ", map[i*DIM + j]);
			}
			printf("\n");
		}

		// Input ========================
		scanf("%c", &bKey);
		getchar();

		switch(tolower(bKey)){
			case 'w':
				nCurrentY -= (DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY, nCurrentX, nCurrentY - 1, pField, map)) ? 1 : 0;
				break;
			case 's':
				nCurrentY += (DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY, nCurrentX, nCurrentY + 1, pField, map)) ? 1 : 0;
				break;
			case 'd':
				nCurrentX += (DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY, nCurrentX + 1, nCurrentY, pField, map)) ? 1 : 0;
				break;
			case 'a':
				nCurrentX -= (DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY, nCurrentX - 1, nCurrentY, pField, map)) ? 1 : 0;
				break;
			case 'r':
				nCurrentRotation += (DoesPieceFit(nCurrentPiece, nCurrentRotation + 1, nCurrentX, nCurrentY, nCurrentX, nCurrentY, pField, map)) ? 1 : 0;
                break;
            case 32: 
            	if(placeShip(nCurrentPiece, map, pField, nCurrentX, nCurrentY, nCurrentRotation) == -1){
            		printf("You can't put the ship here!\n");
            	}
            	fflush(stdin);
            	continue;
			default:
				printf("Invalid key!\n");
		}

		fflush(stdin);

        // Display ======================

        // Place ship on the map
		for (int i = 0; i < MAX_SIZE; i++)
			for (int j = 0; j < MAX_SIZE; j++)
                if (nCurrentPiece[rotate_point(i, j, nCurrentRotation)] != '.'){
                    pField[(nCurrentY + i)*DIM + (nCurrentX + j)] = 'X';
                    if(map[(oldY + i)*DIM + (oldX + j)] == FILLED)
                    	pField[(oldY + i)*DIM + (oldX + j)] = 'O';	
                }


        oldX = nCurrentX;
        oldY = nCurrentY;
	}

	return 0;
}
