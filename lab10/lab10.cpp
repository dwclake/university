/*
 *  CSCI 115 - 03
 *  Lab 10
 *
 *  Devon Webb
 */

#include <cstdio>
#include <tuple>

#include "Graph.h"

int main() {
    Graph::AdjMatrix graph(5);
    // Setup graph with some edges
    graph.add_undirected_edge(2, 3, 0.5);
    graph.add_undirected_edge(4, 1, 0.75);
    graph.delete_directed_edge(4, 1);
    graph.add_undirected_edge(1, 4, 0.5);
    graph.add_directed_edge(2, 1, 0.75);
    graph.add_directed_edge(4, 0, 0.75);
    graph.add_undirected_edge(2, 2, 0.5);
    // Display graph 
    graph.debug();

    // Bfs
    graph.bfs(2);
}
