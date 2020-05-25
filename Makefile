matrix:
	gcc -g -c src/utils.c src/matrix.c src/ship.c src/player.c
	ar -rc libbattleship.a utils.o matrix.o ship.o player.o
	ar -t libbattleship.a
qtree:
	gcc -g -c src/utils.c src/qtree.c src/ship.c src/player.c
	ar -rc libbattleship.a utils.o qtree.o ship.o player.o
	ar -t libbattleship.a
test_matrix:
	gcc -g -Wall tests/test_map.c -o test_matrix -L. -lbattleship
test_ship:
	gcc -g -Wall tests/test_ship.c -o test_ship -L. -lbattleship
test_player:
	gcc -g -Wall tests/test_player.c -o test_player -L. -lbattleship
test_qtree:
	gcc -g -Wall tests/test_qtree.c -o test_qtree -L. -lbattleship
game:
	gcc -Wall src/game.c -o battleship -L. -lbattleship
