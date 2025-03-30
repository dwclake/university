/*
 * @author: Devon Webb
 *
 * CSCI 114
 * Section 01
 * Programming Assignment 1
 *
 * How to execute:
 *
 * gcc CSCI114_P1.cpp -lstdc++ -o CSCI114_P1 
 * ./CSCI114_P1
 */

#include <cstdio>
#include <fstream>
#include <sys/stat.h>

using namespace std;

// The maximum number of bytes to read/write at a time
#define BYTES 100

// Calculates the GCF of BYTES and the file size to determine how
// many bytes can be copied at a time while ensuring no 
// extra or missing bytes
long long get_gcf_of_file_size(const char* filename) {
    off_t size;
    off_t least;

    // Get file information
    struct stat st;
    if (stat(filename, &st) != 0) {
        return 0;
    }

    size = st.st_size;

    if (BYTES <= size) {
        least = BYTES;
    } else {
        least = size;
    }

    // Calculate the GCF
    for (off_t i = least; i > 1; i--) {
        if (size % i == 0 & BYTES % i == 0) {
            return i;
        }
    }

    return 1;
}

int main() {
    ifstream in;
    ofstream out;
    char buf[BYTES];
    long long bytes_to_read;

    // Open data.in
    in.open("data.in", ios::in | ios::binary);

    if (!in.is_open()) {
        printf("Failed to open data.in\n");
        return -1;
    }

    bytes_to_read = get_gcf_of_file_size("data.in");
    if (bytes_to_read == 0) {
        // If unable to calculate GCF, read one byte at a time
        bytes_to_read = 1;
    }
    printf("Copying %lld bytes at a time\n", bytes_to_read);

    // Open data.out
    out.open("data.out", ios::out | ios::binary);

    if (!out.is_open()) {
        printf("Failed to open data.out\n");
        return -1;
    }

    // Until end of data.in is reached, copy bytes_to_read number of bytes
    // from data.in to buf, and then from buf to data.out
    while (!in.eof()) {
        in.read((char*) &buf, sizeof(char) * bytes_to_read);
        out.write((char*) &buf, sizeof(char) * bytes_to_read);
    }

    // Close files and return
    in.close();
    out.close();

    printf("Success: copied data from data.in to data.out\n");

    return 0;
}
