/*
 * @author: Devon Webb
 *
 * CSCI 114
 * Section 01
 * Programming Assignment 2
 *
 * How to execute:
 *
 * gcc CSCI114_P2.cpp -lstdc++ -o CSCI114_P2
 * ./CSCI114_P2
 */

#include <fstream>
#include <stdio.h>
#include <unistd.h>

using namespace std;

int main() {
    ifstream in;
    ofstream out;
    char byte;
    int a_pipe[2];
    int ok;
    pid_t id;

    // Open data.in
    in.open("data.in", ios::in | ios::binary);
    if (!in.is_open()) {
        printf("Failed to open data.in\n");
        return -1;
    }

    // Open data.out
    out.open("data.out", ios::out | ios::binary);
    if (!out.is_open()) {
        printf("Failed to create data.out\n");
        return -1;
    }
    
    // Open pipe
    ok = pipe(a_pipe);
    if (ok != 0) {
        printf("Failed to open pipe\n");
        return -1;
    }

    // Fork process
    id = fork();

    if (id == 0) {
        // Process A
        // Close unneeded read end of pipe
        close(a_pipe[0]);

        // Until eof is reached, copy a byte from the in file to the write end of the pipe
        while (!in.eof()) {
            in.read(&byte, sizeof(byte));
            write(a_pipe[1], &byte, sizeof(byte));
        }

        // Close write end of pipe
        close(a_pipe[1]);
    } else {
        // Process B
        // Close unneeded write end of pipe
        close(a_pipe[1]);

        // Until eof is reached, copy a byte from the read end of the pipe to the out file
        while (read(a_pipe[0], &byte, sizeof(byte)) != 0) {
            out.write(&byte, sizeof(byte));
        }

        // Close read end of pipe
        close(a_pipe[0]);
    }

    // Close files and return
    in.close();
    out.close();

    return 0;
}
