#include "../src/player.h"
#include "../src/ship.h"
#include "../src/map.h"

int main(){
	int n_ships = 4;
	int game_shapes[n_ships];
	for(int i=0; i<n_ships; i++){
		game_shapes[i] = rand() % NSHAPES;
	}
	PLAYER *p1 = create_player("Amanda", 10, n_ships, game_shapes, RANDOM);
	//PLAYER *p2 = create_player("Gui", 10, n_ships, game_shapes, MANUAL);

	print_map(p1 -> map);

	/*for(int i=0; i < 10*10; i++){
		if(p1 -> map -> matrix[i].state == FILLED)
			printf("%d: %d\n", i, p1 -> map -> matrix[i].ship -> rot);
	}*/
	//print_dashboard(p1);
	//print_dashboard(p2);
	free_player(p1);
	//free_player(p2);
	return 0;
}
