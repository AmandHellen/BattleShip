lib:
        gcc -c map.c ship.c player.c
        ar -rc libbattleship.a map.o ship.o player.o
        ar -t libbattleship.a
test:
    	gcc -Wall game.c -o battleship -L. -lbattleship
        ./battleship