/*
 *  CSCI 115 - 03
 *  Lab 15
 *
 *  Devon Webb
 */

#include <cstdio>
#include "Graph.h"

int main() {
    Graph::AdjMatrix g(7);

    g.add_undirected_edge(0, 1, 5);
    g.add_undirected_edge(1, 2, 13);
    g.add_undirected_edge(0, 3, 17);
    g.add_undirected_edge(1, 3, 12);
    g.add_undirected_edge(2, 4, 6);
    g.add_undirected_edge(2, 6, 11);
    g.add_undirected_edge(3, 6, 8);
    g.add_undirected_edge(4, 6, 14);
    g.add_undirected_edge(1, 6, 8);
    g.add_undirected_edge(3, 5, 10);
    g.add_undirected_edge(5, 6, 4);


    g.debug();
}
