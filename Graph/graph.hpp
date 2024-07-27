#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <utility>

#include <iostream>
#include <vector>

class Graph {
    int V = 0;
    int E = 0;
    std::vector<std::vector<int>> adj;

public:
    Graph(const int& v) : V(v), adj(v + 1) {} // +1 to account for 1-based index

    Graph(const int& v, std::vector<std::pair<int, int>>& in) : V(v), adj(v + 1) {
        E = in.size(); // Set the number of edges
        for (auto& e : in) {
            AddEdge(e.first, e.second);
        }
    }

    void AddEdge(int v, int w) {
        adj[v].push_back(w);
        adj[w].push_back(v); // Assuming an undirected graph
    }

    void PrintGraph() {
        for (int v = 1; v <= V; ++v) {
            std::cout << "Adjacency list of vertex " << v << ": ";
            for (auto x : adj[v]) {
                std::cout << x << " ";
            }
            std::cout << std::endl;
        }
    }
};

