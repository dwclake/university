/*
 *  CSCI 115 - 03
 *  Lab 15
 *
 *  Devon Webb
 */

#include "Queue.h"

struct DisjointSet {
    DisjointSet();

    bool find_set(int u);
    Queue::Priority<std::tuple<double, int>> get_union(int u, int v);

    private:
        Queue::Priority<std::tuple<double, int>> setA;
        Queue::Priority<std::tuple<double, int>> setB;
};
