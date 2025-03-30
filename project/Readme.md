# Devon Webb - CSCI 115 Project - Shortest Path

## Contains
- 5 map files in the map folder
- 11 c++ files in the src folder
- CMakeList.txt file for building with cmake
- This readme file

## How to build/run:
This project uses cmake as the build system. 

To build and run this project (on linux/macos):

- download project.zip
- extract the project zip
- then run these commands in the terminal
```bash
cd path/to/project
cmake -S . -B .build
cmake --build .build
```
- then to run the game
```bash
.build/project
```

## Features:
- Read map from file
- Display map, weights of nearby vertices, current turn, players and enemies, controls
- Player movement
- Switching maps
- Game restart on player/enemy collision

## Unimplemented:
- Dijkstra's algorithm not finished
- Enemy movement

## How to use:
To use this project, first build it and run the executable. First you will be presented with the map selection screen which will let you select the starting map. Afterwards the game will start, the map name, the turn number, and the map will be drawn on the terminal. Below that the controls will be drawn. the controls are wasd for moving the character,  SPACE for advancing one turn without moving, q for quitting, and m for changing the map. There are four kinds of tiles, Walls(#) which no-one can walk thought, hidden(H) tiles which only players can walk throught, grass(-) tiles which players and enemies can walk throught, but they take 4 times  as many turns to cross, and regular( ) tiles which enemies and players can walk through which only takes 1 turn. If an enemy moves to the same tile as the player, the player is moved to a hidden tile. 

The following is an explanation of how the unimplemented parts would function. The enemies will approach the player, using the shortest path algorithm.