/*
* Well, I do know the basics, but have not gotten to more complex tree-like structures,
* just adjacency lists and matrices.  Do I know enough to take on automata, or do I need
* more background with directed graphs (I know they edges are "one way") using more
* complex data structures?  Given my goal to think more like a state machine, so I know
* enough about graphs?  This code should give you an idea where I am at:
*/

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include <tuple>
#include <iomanip>

// Custom comparison functor
struct PairCompare {
    bool operator()(const std::pair<size_t, size_t>& lhs, const std::pair<size_t, size_t>& rhs) const {
        if (lhs == rhs || (lhs.first == rhs.second && lhs.second == rhs.first)) {
            return false;
        }
        return std::tie(lhs.first, lhs.second) < std::tie(rhs.first, rhs.second);
    }
};

class UndirectedGraph {
    size_t V = 0;
    size_t E = 0;
    std::vector<std::vector<size_t>> adj;

public:
    UndirectedGraph(size_t v, const std::vector<std::vector<std::tuple<size_t, size_t, size_t>>>& in) : V(v), adj(v + 1) {
        // Initialize each adjacency list with the desired size
        for (size_t i = 0; i <= V; i++) {  // Fix loop bound to include V
            adj[i].resize(i + 1);
            std::fill(adj[i].begin(), adj[i].end(), 0);
        }
        for (size_t i = 0; i < V; i++) {
            for (size_t j = 0; j < in[i].size(); j++) {  // Use in[i].size() for correct bounds
                AddEdge(std::get<0>(in[i][j]), std::get<1>(in[i][j]), std::get<2>(in[i][j]));
            }
        }
    }

    size_t getV() const { return V; }
    size_t getE() const { return E; }

    void AddEdge(const size_t& v, const size_t& pos, const size_t& weight) {
        if (v > 0 && v <= V && pos > 0 && pos <= v) {  // Ensure indices are within bounds
            adj[v - 1][pos - 1] = weight;
            E++;
        }
    }

    void PrintGraph() const {
        std::cout << "Number of vertices: " << V << std::endl;
        for (size_t i = 0; i < V; ++i) {
            for (size_t j = 0; j < V; ++j) {
                if (j <= i) {
                    std::cout << std::setw(3) << adj[i][j] << " "; // Set width for alignment
                }
                else {
                    std::cout << std::setw(3) << adj[j][i] << " "; // Set width for alignment
                }
            }
            std::cout << std::endl;
        }
    }

    size_t degree(const size_t& v) const {
        std::map<std::pair<size_t, size_t>, bool, PairCompare> m;
        for (size_t i : adj[v - 1]) {  // Access adj[v-1] to account for 1-based indexing
            std::pair<size_t, size_t> p = std::make_pair(v, i);
            m.insert(std::make_pair(p, true));
        }
        return m.size();
    }

    size_t maxDegree() const {
        size_t vertex_count = adj.size();
        size_t max = 0;
        for (size_t i = 1; i < vertex_count; i++) {
            size_t deg = degree(i);
            if (deg > max) {
                max = deg;
            }
        }
        return max;
    }

    double aveDegree() const {
        size_t vertex_count = adj.size();
        size_t total_degrees = 0;
        for (size_t i = 1; i < vertex_count; i++) {
            total_degrees += degree(i);
        }
        return static_cast<double>(total_degrees) / (vertex_count - 1);
    }
};
