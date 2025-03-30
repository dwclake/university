/*
 *  CSCI 115 - 03
 *  Lab 10
 *
 *  Devon Webb
 */

#include <string>
#include <tuple>
#include <iostream>

#include "Queue.h"

namespace Graph {
  struct AdjMatrix {
    // Constructors and destructors
    AdjMatrix(int n);
    ~AdjMatrix();

    // Getters
    int num_verticies() { return n; }
    int get_degree(int v) { return this->degrees[v]; }
    int get_index(int u, int v);
    int find_degree(int v);
    double get_edge(int u, int v);

    // Check for conditions
    bool has_edge(int u, int v);

    // Creation and destruction of edges
    void add_undirected_edge(int a, int b, double weight);
    void add_directed_edge(int source, int sink, double weight);
    void delete_undirected_edge(int a, int b);
    void delete_directed_edge(int source, int sink);

    // Iteration
    void set_current(int v);
    int next_adjacent(int v);

    // Algorithms
    void bfs(int v);

    // Display
    void debug();

    private: 
      int n;
      double* weights;
      int* current;
      int* degrees;
  };
}
