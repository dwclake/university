/*
 *  CSCI 115 - 01
 *  Shortest-Path Project
 *
 *  Devon Webb
 */

#include <iostream>

#include "world.h"

// Prompt for game controls
const char* PROMPT = R"(
  Enter W, A, S, D to move, 
  M to select a new map,
  SPACE to skip turn, or Q to exit:
)";

// Prompt for map selection
const char* MAPPROMPT = R"(
  Map Selection:

  1. Map 1
  2. Map 2
  3. Map 3
  4. Map 4
  5. Map 5

  Enter the NUMBER of the desired map: 
)";

int main() {
    bool loop = true;
    char input;

    World world;

    world.map_selector(MAPPROMPT);

    while (loop) {
        world.draw(PROMPT);

        // Player movement control
        input = std::cin.get();

        if (input == 'q') {
            loop = false;
        } else if (input == 'w') {
            world.move(Direction::Up);
        } else if (input == 'a') {
            world.move(Direction::Left);
        } else if (input == 's') {
            world.move(Direction::Down);
        } else if (input == 'd') {
            world.move(Direction::Right);
        } else if (input == ' ') {
            world.move(Direction::None);
        } else if (input == 'm') {
            world.map_selector(MAPPROMPT);
        }
    }
}
