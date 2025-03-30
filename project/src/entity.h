/*
 *  CSCI 115 - 01
 *  Project
 *
 *  Devon Webb
 *
 *  Classes for Entities and Position
 */

#ifndef ENTITY_H
#define ENTITY_H

#include <tuple>
#include <cstdio>
#include <algorithm>

#include "ds/queue.h"

// Class representing a 2D position
class Pos {
    int _x{0}, _y{0};

    public:
        Pos(): _x(0), _y(0) {}
        Pos(const int& x, const int& y) {
            this->_x = x;
            this->_y = y;
        }

        int x() { return this->_x; }
        int y() { return this->_y; }

        void set(int x, int y) {
            this->_x = x;
            this->_y = y;
        }

        void set_clamped(int x, int y, int xmax, int ymax) {
            this->_x = std::clamp(x, 1, xmax - 2);
            this->_y = std::clamp(y, 1, ymax - 2);
        }
};

// A struct representing a entity, used as a base class for player and enemies
struct Entity {
      Pos pos;
      int* path;

      Entity(): path(nullptr) {}
      Entity(int* path): path(path) {}
      ~Entity() { if (path) delete this->path; }

      int* get_path() { return this->path; }
      void set_path(int* path) { this->path = path; }
      virtual void debug();
};

// Struct for the player
struct Player: public Entity {
  Player() {}
  Player(Pos pos) { this->pos = pos; }

  void debug();
};

// Struct for the gray
struct Gray: public Entity {
  Gray() {}
  Gray(Pos pos) { this->pos = pos; }

  void debug();
};

// Struct for the hal
struct Hal: public Entity {
  Hal() {}
  Hal(Pos pos) { this->pos = pos; }

  void debug();
};

// Struct for the sniper
struct Sniper: public Entity {
  Sniper() {}
  Sniper(Pos pos) { this->pos = pos; }

  void debug();
};

#endif // !ENTITY_H
