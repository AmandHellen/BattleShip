#include "player.h"
#include "ship.h"
#include "map.h"

int main(){
	int n_ships = 16;
	int game_shapes[n_ships];
		for(int i=0; i<n_ships; i++){
			game_shapes[i] = rand() % 9;
		}
	PLAYER *p1 = create_player(20, n_ships, game_shapes, MANUAL, true);
	//print_dashboard(p1);
	return 0;
}