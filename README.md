# BattleShip
C implementation of the classic "Battleship" game by Amanda Delgado and Guilherme Lima

## Table of contents
* [Build instructions](#build-instructions)
* [How to play](#how-to-play)

## Build instructions
To compile and run, open a terminal on this folder and issue the following commands:
```
$ make
$ make game
$ ./battleship
```

## How to play
* Choose the map generation mode (RANDOM/MANUAL) (0/1 + ENTER)
* The RANDOM mode generates a map of random size (between 10x10 and 40x40) and places the ships in arbitrary positions
* The MANUAL mode prompts the user for the map size and lets the user manually place the ships (w/a/s/d/r + [ENTER] to move them around)
* When the ship is in the desired position, the user presses [SPACE] + [ENTER] to place it
* The main game loop then follows, prompting each user at a time for the desired attack coordinates (x and y) (int + [ENTER])
