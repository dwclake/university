/*
 *  CSCI 115 - 03
 *  Project
 *
 *  Devon Webb
 */

#include "graph.h"

namespace Graph {
    AdjList::AdjList(int width, int height) {
        this->n = width * height;
        this->width = width;
        this->height = height;
        this->l = new ALNode*[n];
        this->current = new ALNode*[n];
        this->degrees = new int[n];

        for (int u = 0; u < n; u++) {
            l[u] = nullptr;
            current[u] = nullptr;
            degrees[u] = 0;
        }
    }

    AdjList::~AdjList() {
        for (int i = 0; i < n; i++) {
            ALNode* current = l[i];
            while (current) {
                ALNode* next = current->next;
                delete current;
                current = next;
            }
        }

        delete [] l;
        delete [] current;
        delete [] degrees;
    }

    // Converts two-d indices into a one-d index
    int AdjList::get_index(int u, int v) {
        return u*n + v;
    }

    // Gets the edge from u -> v
    double AdjList::get_edge(int u, int v) {
        if (u < n) {
            ALNode* current = l[u];
            while (current != nullptr) {
                if (current->v == v) {
                    return current->weight;
                } else {
                    current = current->next;
                }
            }

            return 0.0;
        } else {
            return 0.0;
        }
    }

    // Checks if the two vertices have an egde
    bool AdjList::has_edge(int u, int v) {
        if (u < n) {
            ALNode* current = l[u];
            while (current != nullptr) {
                if (current->v == v) {
                    return true;
                } else {
                    current = current->next;
                }
            }

            return false;
        } else {
            return false;
        }
    }

    // Adds undirected edges from a -> b and b -> a
    void AdjList::add_undirected_edge(int a, int b, double weight) {
        this->add_directed_edge(a, b, weight);
        this->add_directed_edge(b, a, weight);
    }

    // Adds a directed edge from source -> sink
    void AdjList::add_directed_edge(int source, int sink, double weight) {
        if (!this->has_edge(source, sink)) {
            ALNode* tmp = new ALNode(sink, weight);
            tmp->next = l[source];
            l[source] = tmp;
            degrees[source]++;
        }
    }

    // Deletes edges from a -> b and b -> a
    void AdjList::delete_undirected_edge(int a, int b) {
        this->delete_directed_edge(a, b);
        this->delete_directed_edge(b, a);
    }

    // Deletes directed edge from source -> sink
    void AdjList::delete_directed_edge(int source, int sink) {
        ALNode* current = l[source];
        if (current) {
            if (current->v == sink) {
                l[source] = current->next;
                delete current;
            } else {
                if (current->next) {
                    ALNode* prev = current;
                    current = current->next;

                    bool found = false;
                    while (current && !found) {
                        if (current->v == sink) {
                            prev->next = current->next;
                            delete current;
                            found = true;
                        } else {
                            prev = current;
                            current = current->next;
                        }
                    }
                }
            }
        }

        degrees[source]--;
    }

    int* AdjList::dijkstra(std::tuple<int, int> source) {
        Queue::Priority paths(n);
        Queue::Queue<int>* path = new Queue::Queue<int>;

        int sourcex, sourcey;
        std::tie(sourcex, sourcey) = source;

        double* d = new double[n];
        int* pi = new int[n];

        for (int u = 0; u < n; u++) {
            d[u] = DBL_MAX;
            pi[u] = -1;
        }

        d[this->get_index(sourcex, sourcey)] = 0;

        for (int u = 0; u < n; u++) {
            paths.enqueue({u, d[u]});
        }

        while (!paths.is_empty()) {
            int idx, distance;
            std::tie(idx, distance) = paths.dequeue();
        
            path->enqueue(idx);
        
            this->set_current(idx);
        
            while (this->exist_adjacent(idx)) {
                int v = this->next_adjacent(idx);
        
                double w = this->get_edge(idx, v);
                if (d[v] > d[idx] + w) {
                    d[v] = d[idx] + w;
                    pi[v] = idx;
                    paths.decrease_key({v, d[v]});
                }
            }
        }

        delete [] d;
        return pi;
    }
    
    bool AdjList::exist_adjacent(int u) {
        return current[u] != nullptr;
    }

    void AdjList::set_current(int u) {
        current[u] = l[u];
    }

    int AdjList::next_adjacent(int u) {
        int v = current[u]->v;
        current[u] = current[u]->next;
        return v;
    }
}
