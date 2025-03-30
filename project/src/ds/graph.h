/*
 *  CSCI 115 - 01
 *
 *  Devon Webb
 *
 *  Graph class
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <tuple>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cfloat>
#include <climits>
#include <cmath>

#include "queue.h"
#include "../util.h"

namespace Graph {
    struct ALNode {
        ALNode(int v, double weight): v(v), weight(weight), next(nullptr) {}
        ~ALNode() {}

        int v{0};
        double weight{0};
        ALNode* next{nullptr};
    };

    struct AdjList {
        // Constructors and destructors
        AdjList(int width, int height);
        ~AdjList();

        // Getters
        int num_verticies() { return n; }
        int get_degree(int v) { return this->degrees[v]; }
        int get_index(int u, int v);
        double get_edge(int u, int v);

        // Check for conditions
        bool has_edge(int u, int v);

        // Creation and destruction of edges
        void add_undirected_edge(int a, int b, double weight);
        void add_directed_edge(int source, int sink, double weight);
        void delete_undirected_edge(int a, int b);
        void delete_directed_edge(int source, int sink);

        // Iteration
        bool exist_adjacent(int u);
        void set_current(int u);
        int next_adjacent(int u);

        // Algorithms
        int* dijkstra(std::tuple<int, int> source);

        int width;
        int height;
        private: 
            int n;
            ALNode** l;
            ALNode** current;
            int* degrees;
    };
}

#endif
