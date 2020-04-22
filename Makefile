lib:
	gcc -c src/map.c src/ship.c src/player.c
	ar -rc libbattleship.a map.o ship.o player.o
	ar -t libbattleship.a

test_map:
	gcc -Wall tests/test_map.c -o test_map -L. -lbattleship
	./test_map

test_ship:
	gcc -Wall tests/test_ship.c -o test_ship -L. -lbattleship
	./test_ship

test_player:
	gcc -Wall tests/test_player.c -o test_player -L. -lbattleship 
	./test_player

game:
	gcc -Wall src/game.c -o battleship -L. -lbattleship
	./battleship