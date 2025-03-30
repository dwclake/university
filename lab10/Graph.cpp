/*
 *  CSCI 115 - 03
 *  Lab 10
 *
 *  Devon Webb
 */

#include "Graph.h"
#include <iomanip>
#include <tuple>

namespace Graph {
    AdjMatrix::AdjMatrix(int n) {
        this->n = n;
        this->weights = new double[n*n]{0};
        this->current = new int[n]{0};
        this->degrees = new int[n]{0};
    }

    AdjMatrix::~AdjMatrix() {
        delete [] weights;
        delete [] current;
        delete [] degrees;
    }

    // Converts two-d indices into a one-d index
    int AdjMatrix::get_index(int u, int v) {
        return u*n + v;
    }

    // Finds the degree of a virtex
    int AdjMatrix::find_degree(int v) {
        int degree = 0;
        for (int i = 0; i < n; i++) {
            if (has_edge(v, i) != 0) {
                degree++;
            }
        }

        return degree;
    }

    // Gets the edge from u -> v
    double AdjMatrix::get_edge(int u, int v) {
        return weights[get_index(u, v)];
    }

    // Checks if the two vertices have an egde
    bool AdjMatrix::has_edge(int u, int v) {
        return weights[get_index(u, v)] != 0;
    }

    // Adds undirected edges from a -> b and b -> a
    void AdjMatrix::add_undirected_edge(int a, int b, double weight) {
        weights[get_index(a, b)] = weight;
        weights[get_index(b, a)] = weight;

        degrees[a] = find_degree(a);
        degrees[b] = find_degree(b);
    }

    // Adds a directed edge from source -> sink
    void AdjMatrix::add_directed_edge(int source, int sink, double weight) {
        weights[get_index(source, sink)] = weight;

        degrees[source] = find_degree(source);
    }

    // Deletes edges from a -> b and b -> a
    void AdjMatrix::delete_undirected_edge(int a, int b) {
        weights[get_index(a, b)] = 0;
        weights[get_index(b, a)] = 0;

        degrees[a] = find_degree(a);
        degrees[b] = find_degree(b);

    }

    // Deletes directed edge from source -> sink
    void AdjMatrix::delete_directed_edge(int source, int sink) {
        weights[get_index(source, sink)] = 0;

        degrees[source] = find_degree(source);
    }

    // Enum for keeping track of visited nodes
    enum class Color {
        Visited,
        Unvisited,
        Finished
    };

    void _bfs(int v, AdjMatrix* graph, Color* &color, int* &distance, int* &pi) {
        int n = graph->num_verticies();
        if (!(v >= 0 && v < n)) {
            std::cout << "Invalid matrix or v" << std::endl;
            return;
        }

        Queue<int> q;
        color = new Color[n];
        distance = new int[n];
        pi = new int[n];

        for (int i = 0; i < n; i++) {
            color[i] = Color::Unvisited;
            distance[i] = 0;
            pi[i] = 0;
        }

        color[v] = Color::Visited;
        distance[v] = 0;
        pi[v] = -1;

        q.enqueue(v);

        while (!q.is_empty()) {
            int u = q.dequeue();

            for (int i = 0; i < n; i++) {
                if (graph->has_edge(u, i)   ) {
                    if (color[i] == Color::Unvisited) {
                        color[i] = Color::Visited;
                        distance[i] = distance[u] + 1;
                        pi[i] = u;
                        q.enqueue(i);
                    }
                }
            }
            color[u] = Color::Finished;
        }
    }

    void AdjMatrix::bfs(int v) {
        std::cout << "BFS" << std::endl;

        Color* color;
        int* distance;
        int* pi;

        _bfs(v, this, color, distance, pi);

        for (int u = 0; u < this->n; u++) {
            std::cout << "from " << v << " to " << u 
                << " Distance: " << distance[u]
                << " Pi: " << pi[u] 
                << std::endl;
        }

        delete [] color;
        delete [] distance;
        delete [] pi;
    }

    void AdjMatrix::debug() {
        std::cout << "[" << std::endl;
        for (int i = 0; i < n; i++) {
            std::cout << "    ";
            for (int j = 0; j < n; j++) {
                std::cout << std::fixed << std::setprecision(2);
                if (j != n - 1) {
                    std::cout << weights[get_index(i, j)] << ", ";
                } else {
                    std::cout << weights[get_index(i, j)] << std::endl;
                }
            }
        }

        std::cout << "]" << std::endl;
    }
}
