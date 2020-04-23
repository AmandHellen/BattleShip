lib:
	gcc -c src/utils.c src/map.c src/ship.c src/player.c
	ar -rc libbattleship.a utils.o map.o ship.o player.o 
	ar -t libbattleship.a
test_map:
	gcc -Wall tests/test_map.c -o test_map -L. -lbattleship
test_ship:
	gcc -Wall tests/test_ship.c -o test_ship -L. -lbattleship
test_player:
	gcc -Wall tests/test_player.c -o test_player -L. -lbattleship
game:
	gcc -Wall src/game.c -o battleship -L. -lbattleship
