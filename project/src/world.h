/*
 *  CSCI 115 - 01
 *  Project
 *
 *  Devon Webb
 *
 *  Classes for Entities and Position
 */

#ifndef WORLD_H
#define WORLD_H

#include <algorithm>
#include <fstream>
#include <tuple>
#include <iostream>

#include "ds/array.h"
#include "ds/matrix.h"
#include "ds/graph.h"

#include "entity.h"
#include "util.h"

// Class representing a game map
class Map {
    Matrix<char>* matrix{nullptr}; 
    Graph::AdjList* _player_paths{nullptr};
    Graph::AdjList* _entity_paths{nullptr};
    std::string _name{""};
    int _width{0};
    int _height{0};

    public:

        Map(std::string, const int&, const int&, Graph::AdjList*, Graph::AdjList*);
        ~Map();

        static std::tuple<Map*, Player, Array<Entity*>*> load(const char*);
        char* operator[](const int&);

        std::string name() { return this->_name; }
        int height() { return this->_height; }
        int width() { return this->_width; }
        Graph::AdjList* p_paths() { return this->_player_paths; }
        Graph::AdjList* e_paths() { return this->_entity_paths; }

        std::string to_string();
        void debug();
};

Map::Map(std::string name, const int& width, const int& height, Graph::AdjList* p_paths, Graph::AdjList* e_paths) {
    this->_name = name;
    this->_width = width;
    this->_height = height;
    this->matrix = new Matrix<char>(width, height, ' ');
    this->_player_paths = p_paths;
    this->_entity_paths = e_paths;
}

Map::~Map() {
    if (this->matrix) {
        delete this->matrix;
        this->matrix = nullptr;
    }

    if (this->_player_paths) {
        delete this->_player_paths;
        this->_player_paths = nullptr;
    }
    
    if (this->_entity_paths) {
        delete this->_entity_paths;
        this->_entity_paths = nullptr;
    }
}

// Allows indexing into the first dimension Y, 
// returning a char* array of the corresponding row
char* Map::operator[](const int& i) {
    return (*this->matrix)[i];
}

// Converts the map into a string
std::string Map::to_string() {
    return this->matrix->to_string();
}

// Prints out the map to the terminal
void Map::debug() {
    std::printf("%s: [%dx%d] ", this->_name.c_str(), this->_height, this->_width);
    this->matrix->debug();
}

// Loads a map from a file, returning a tuple of Map*, Player, and Array<Entity*>*
std::tuple<Map*, Player, Array<Entity*>*> Map::load(const char* file) {
    std::string line; 
    std::string name; 
    Array<std::string> lines(10);

    Map* map;
    Graph::AdjList* player_paths;
    Graph::AdjList* entity_paths;
    Array<Entity*>* entities = new Array<Entity*>(10);
    Player player;

    std::ifstream map_file;
    map_file.open(file);

    // Take the first line as the map name
    std::getline(map_file, name);

    // Read line by line, storing the line in ien lines array
    while ( std::getline(map_file, line) ) {
        lines.append(line);
    }

    map_file.close();

    // Get the height from number of lines read
    int height = lines.get_size();
    int width = 0;

    // Calculate the width as the max length of all the lines
    for (int i = 0; i < height; i++) {
        if (lines[i].size() > width) {
            width = lines[i].size();
        }
    }
    
    // Allocate the graphs and the map
    player_paths = new Graph::AdjList(width, height);
    entity_paths = new Graph::AdjList(width, height);

    map = new Map(name, width, height, player_paths, entity_paths);

    // Copy the map into the map matrix and get entity positions
    int entities_allocated = 0;
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            char ch = lines[j][i];

            // if ch is 'O', then it is a player
            if (ch == 'O') {
                player.pos.set_clamped(i, j, width, height);
                ch = ' ';
            // if ch is 'X', then it is a entity, which entity type is picked in
            // an arbitrary order
            } else if (ch == 'X') {
                if (entities_allocated < 3) {
                    Pos pos(i, j);

                    switch (entities_allocated) {
                        case 0:
                            entities->append(new Gray(pos));
                            break;
                        case 1:
                            entities->append(new Hal(pos));
                            break;
                        case 2:
                            entities->append(new Sniper(pos));
                            break;
                    }

                    ch = ' ';

                    entities_allocated++;
                } 
            }

            // place the char in the map
            (*map)[j][i] = ch;
        }
    }
    
    // Load the paths into the graph,
    // For each vertex, a edge is added for the north, south, east, and west vertices,
    // for both the player and the entity graph
    for (int j = 1; j < height - 1; j++) {
        for (int i = 1; i < width - 1; i++) {
            char ch = (*map)[j][i];

            // If char is -, set paths to enter tile with weight 4.0 for entity and player
            if (ch == '-') {
                player_paths->add_directed_edge(
                    j * (width+1) + i,
                    (j + 1) * (width+1) + i,
                    4.0
                );
                
                player_paths->add_directed_edge(
                    j * (width+1) + i,
                    (j - 1) * (width+1) + i,
                    4.0
                );
                
                player_paths->add_directed_edge(
                    j * (width+1) + i,
                    j * (width+1) + (i + 1),
                    4.0
                );
                
                player_paths->add_directed_edge(
                    j * (width+1) + i,
                    j * (width+1) + (i - 1),
                    4.0
                );
                
                entity_paths->add_directed_edge(
                    j * (width+1) + i,
                    (j + 1) * (width+1) + i,
                    4.0
                );
                
                entity_paths->add_directed_edge(
                    j * (width+1) + i,
                    (j - 1) * (width+1) + i,
                    4.0
                );
                
                entity_paths->add_directed_edge(
                    j * (width+1) + i,
                    j * (width+1) + (i + 1),
                    4.0
                );
                
                entity_paths->add_directed_edge(
                    j * (width+1) + i,
                    j * (width+1) + (i - 1),
                    4.0
                );
            // If char is ' ', set paths to enter tile with weight 1.0 for entity and player
            } else if (ch == ' ') {
                player_paths->add_directed_edge(
                    j * (width+1) + i,
                    (j + 1) * (width+1) + i,
                    1.0
                );
                
                player_paths->add_directed_edge(
                    j * (width+1) + i,
                    (j - 1) * (width+1) + i,
                    1.0
                );
                
                player_paths->add_directed_edge(
                    j * (width+1) + i,
                    j * (width+1) + (i + 1),
                    1.0
                );
                
                player_paths->add_directed_edge(
                    j * (width+1) + i,
                    j * (width+1) + (i - 1),
                    1.0
                );
                
                entity_paths->add_directed_edge(
                    j * (width+1) + i,
                    (j + 1) * (width+1) + i,
                    1.0
                );
                
                entity_paths->add_directed_edge(
                    j * (width+1) + i,
                    (j - 1) * (width+1) + i,
                    1.0
                );
                
                entity_paths->add_directed_edge(
                    j * (width+1) + i,
                    j * (width+1) + (i + 1),
                    1.0
                );
                
                entity_paths->add_directed_edge(
                    j * (width+1) + i,
                    j * (width+1) + (i - 1),
                    1.0
                );
            // If char is H, set paths to enter tile with weight 1.0 for player 0.0 for entity
            } else if (ch == 'H') {
                player_paths->add_directed_edge(
                    j * (width+1) + i,
                    (j + 1) * (width+1) + i,
                    1.0
                );
                
                player_paths->add_directed_edge(
                    j * (width+1) + i,
                    (j - 1) * (width+1) + i,
                    1.0
                );
                
                player_paths->add_directed_edge(
                    j * (width+1) + i,
                    j * (width+1) + (i + 1),
                    1.0
                );
                
                player_paths->add_directed_edge(
                    j * (width+1) + i,
                    j * (width+1) + (i - 1),
                    1.0
                );
                
                entity_paths->add_directed_edge(
                    j * (width+1) + i,
                    (j + 1) * (width+1) + i,
                    0.0
                );
                
                entity_paths->add_directed_edge(
                    j * (width+1) + i,
                    (j - 1) * (width+1) + i,
                    0.0
                );
                
                entity_paths->add_directed_edge(
                    j * (width+1) + i,
                    j * (width+1) + (i + 1),
                    0.0
                );
                
                entity_paths->add_directed_edge(
                    j * (width+1) + i,
                    j * (width+1) + (i - 1),
                    0.0
                );
            // If char is #, set paths to enter tile with weight 0.0 for entity and player
            } else if (ch == '#') {
                player_paths->add_directed_edge(
                    j * (width+1) + i,
                    (j + 1) * (width+1) + i,
                    0.0
                );
                
                player_paths->add_directed_edge(
                    j * (width+1) + i,
                    (j - 1) * (width+1) + i,
                    0.0
                );
                
                player_paths->add_directed_edge(
                    j * (width+1) + i,
                    j * (width+1) + (i + 1),
                    0.0
                );
                
                player_paths->add_directed_edge(
                    j * (width+1) + i,
                    j * (width+1) + (i - 1),
                    0.0
                );
                
                entity_paths->add_directed_edge(
                    j * (width+1) + i,
                    (j + 1) * (width+1) + i,
                    0.0
                );
                
                entity_paths->add_directed_edge(
                    j * (width+1) + i,
                    (j - 1) * (width+1) + i,
                    0.0
                );
                
                entity_paths->add_directed_edge(
                    j * (width+1) + i,
                    j * (width+1) + (i + 1),
                    0.0
                );
                
                entity_paths->add_directed_edge(
                    j * (width+1) + i,
                    j * (width+1) + (i - 1),
                    0.0
                );
            }
        }
    }

    return {map, player, entities};
}

// Class representing the World
class World {
    Map* map{nullptr};
    Player player;
    Array<Entity*>* entities{nullptr};
    long long turn{0};
    bool alive{false};


    bool can_move(std::tuple<int, int>, std::tuple<int, int>, Graph::AdjList*);
    int index(int, int);

    public:
        World() {}
        ~World();

        void load_map(const char*);
        void map_selector(const char*);
        void move(Direction);
        void draw(const char*);
};

World::~World() {
    if (this->map) {
        delete this->map;
        this->map = nullptr;
    }

    if (this->entities) {
        for (int i = 0; i < this->entities->get_size(); i++) {
            delete ((*this->entities)[i]);
            (*this->entities)[i] = nullptr;
        }

        delete this->entities;
        this->entities = nullptr;
    }
}

// Runs the map selection menu
void World::map_selector(const char* prompt) {
    this->turn = 0;

    // Print prompt
    std::system("clear");
    std::printf("%s\n> ", prompt);

    // Get input and load selected map
    char input = std::cin.get();

    switch (input) {
        case '1':
            this->load_map("maps/map1.txt");
            break;
        case '2':
            this->load_map("maps/map2.txt");
            break;
        case '3':
            this->load_map("maps/map3.txt");
            break;
        case '4':
            this->load_map("maps/map4.txt");
            break;
        case '5':
            this->load_map("maps/map5.txt");
            break;
        default:
            this->map_selector(prompt);
            break;
    }

    alive = true;
}

// Loads a map from the file at path
void World::load_map(const char* path) {
    // If a map is already loaded, free the previous map and entities
    if (this->map) {
        delete this->map;
        this->map = nullptr;

        for (int i = 0; i < this->entities->get_size(); i++) {
            delete ((*this->entities)[i]);
            (*this->entities)[i] = nullptr;
        }

        delete this->entities;
        this->entities = nullptr;
    }

    // Load requested map
    std::tie(this->map, this->player, this->entities) = Map::load(path);
}

// Return's true if entity can move to requested tile
bool World::can_move(std::tuple<int,int> source, std::tuple<int, int> sink, Graph::AdjList* paths) {
    bool result = true;

    int sourcex, sourcey, sinkx, sinky;

    std::tie(sourcex, sourcey) = source;
    std::tie(sinkx, sinky) = sink;

    // Return false if entities requested to move to a wall tile
    if (paths->get_edge(this->index(sinkx, sinky), this->index(sourcex, sourcey)) == 0.0) {
        result = false;
    }

    return result;
}

// Calculates the 1D index from 2D coordinates
int World::index(int x, int y) {
    return (y) * (this->map->width() + 1) + x;
}

void World::move(Direction player_dir) {
    // increment turn count
    this->turn++;

    int x{0};
    int y{0};

    bool player_moved = false;

    // Adjust player's position based on direction chosen
    switch (player_dir) {
        case Direction::Up:
            x = std::clamp(
                this->player.pos.x(), 
                1, 
                this->map->width() - 2
            );

            y = std::clamp(
                this->player.pos.y() - 1, 
                1,
                this->map->height() - 2
            );

            // Check if the weight to move to that vertex is greater than zero
            // If it is zero that tile cannot be moved to
            if (this->can_move({player.pos.x(), player.pos.y()}, {x, y}, this->map->p_paths())) {
                this->player.pos.set(x, y);
                player_moved = true;
            }
            break;
        case Direction::Left:
            x = std::clamp(
                this->player.pos.x() - 1, 
                1, 
                this->map->width() - 2
            );

            y = std::clamp(
                this->player.pos.y(), 
                1,
                this->map->height() - 2
            );

            // Check if the weight to move to that vertex is greater than zero
            // If it is zero that tile cannot be moved to
            if (this->can_move({player.pos.x(), player.pos.y()}, {x, y}, this->map->p_paths())) {
                this->player.pos.set(x, y);
                player_moved = true;
            }
            break;
        case Direction::Down:
            x = std::clamp(
                this->player.pos.x(), 
                1, 
                this->map->width() - 2
            );

            y = std::clamp(
                this->player.pos.y() + 1, 
                1,
                this->map->height() - 2
            );

            // Check if the weight to move to that vertex is greater than zero
            // If it is zero that tile cannot be moved to
            if (this->can_move({player.pos.x(), player.pos.y()}, {x, y}, this->map->p_paths())) {
                this->player.pos.set(x, y);
                player_moved = true;
            }
            break;
        case Direction::Right:
            x = std::clamp(
                this->player.pos.x() + 1, 
                1, 
                this->map->width() - 2
            );

            y = std::clamp(
                this->player.pos.y(), 
                1,
                this->map->height() - 2
            );

            // Check if the weight to move to that vertex is greater than zero
            // If it is zero that tile cannot be moved to
            if (this->can_move({player.pos.x(), player.pos.y()}, {x, y}, this->map->p_paths())) {
                this->player.pos.set(x, y);
                player_moved = true;
            }
            break;
        case Direction::None:
        default:
            break;
    }

    // Run Dijkstra's for each entity to determine which direction the entitiy should take 
    if (player_moved || !this->player.path) {
        Graph::AdjList* e_paths = this->map->e_paths();
    
        int* path = e_paths->dijkstra({this->player.pos.x(), this->player.pos.y()});

        if (this->player.path) {
            delete this->player.path;
            this->player.path = nullptr;
        }

        this->player.set_path(path);

        for (int i = 0; i < this->entities->get_size(); i++) {
            Entity* current = (*this->entities)[i];
            Pos pos = current->pos;


            current->set_path(path);

            int new_idx = path[this->index(pos.x(), pos.y())];
            int new_x = new_idx / this->map->height();
            int new_y = new_idx % this->map->height();

            pos.set(new_x, new_y);
            current->pos = pos;
        } 
    } else {
        for (int i = 0; i < this->entities->get_size(); i++) {
            Entity* current = (*this->entities)[i];
            Pos pos = current->pos;

            int new_idx = this->player.path[this->index(pos.x(), pos.y())];
            int new_x = new_idx / this->map->width();
            int new_y = new_idx % this->map->width();

            pos.set(new_x, new_y);
            current->pos = pos;
        } 
    }

    // Check if entity has moved onto player, if so signal to move player to hidden tile
    for (int i = 0; i < this->entities->get_size(); i++) {
        Entity* current = (*this->entities)[i];
        Pos cpos = current->pos;
        Pos ppos = this->player.pos;
        
        if (cpos.x() == ppos.x() && cpos.y() == ppos.y()) {
            alive = false;
        }
    } 

    // If player isn't alive, move player to hidden tile
    if (!alive) {
        for (int j = 0; j < this->map->height(); j++) {
            for (int i = 0; i < this->map->width(); i++) {
                if ((*this->map)[j][i] == 'H') {
                    this->player.pos.set(i, j);
                    alive = true;
                }
            }
        }
    }
}

// Prints the map with entities spliced into it onto the terminal
void World::draw(const char* prompt) {
    // Convert map to a string
    std::string map = this->map->to_string();

    int px = this->player.pos.x();
    int py = this->player.pos.y();

    // Calculate player's 1D coordinate
    int player_index = this->index(px, py);

    // Set tile at player's coordinate to 'O'
    map[player_index] = 'O';    
    
    for (int i = 0; i < this->entities->get_size(); i++) {
        int ex = (*this->entities)[i]->pos.x();
        int ey = (*this->entities)[i]->pos.y();

        // Calculate entity's 1D coordinate
        int entity_index = ey
            * (this->map->width() + 1) 
            + ex;

        // Set tile at entity's coordinate to 'X'
        map[entity_index] = 'X';
    }

    // Grab the weights to move each cardinal direction
    double north, east, south, west;

    north = this->map->p_paths()->get_edge(
        this->index(px, py - 1),
        player_index
    );
    east = this->map->p_paths()->get_edge(
        this->index(px + 1, py),
        player_index
    );
    south = this->map->p_paths()->get_edge(
        this->index(px, py + 1),
        player_index
    );
    west = this->map->p_paths()->get_edge(
        this->index(px - 1, py),
        player_index
    );
    
    // Draw map name, turn count, directions, map, and prompt
    std::system("clear");
    std::printf("map: %s", this->map->name().c_str());
    std::printf("\tturn: %lld\n", this->turn);
    std::printf("paths n: %.0f e: %.0f s: %.0f w: %.0f\n", north, east, south, west);
    std::printf("%s\n", map.c_str());
    std::printf("%s\n> ", prompt);
}

#endif // !WORLD_H
