/*
 * @author: Devon Webb
 *
 * CSCI 114
 * Section 01
 * Programming Assignment 4
 *
 * How to execute:
 *
 * gcc CSCI114_P4.cpp --std=c++11 -lstdc++ -o CSCI114_P4
 * ./CSCI114_P4 5
 */

#include <thread>
#include <fstream>
#include <iostream>

using namespace std;

enum heading {
    NORTH,
    SOUTH
};

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("expected N passed as an argument\n");
        return -1;
    }

    int N = atoi(argv[1]);
    printf("N: %d\n", N);

    int northbound_waiting = 0;
    int northbound_active = 0;
    mutex m_northbound;
    queue<bool> northbound;

    int southbound_waiting = 0;
    int southbound_active = 0;
    mutex m_southbound;
    queue<bool> southbound;

    heading active_direction;
    thread active[N + 1];

    ifstream File;
    File.open("cars.txt", ios::in);

    while (!File.eof()) {
        string car;
        getline(File, car);

        switch (car[0]) {
            case 'N':
                // Check amount of waiting cars and the current direction
                northbound.push(true);
                printf("north\n");
                break;
            case 'S':
                // Check amount of waiting cars and the current direction
                southbound.push(true);
                printf("south\n");
                break;
        }
    }
}
