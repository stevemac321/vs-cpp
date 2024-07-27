#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include <tuple>

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
    UndirectedGraph(const size_t& v) : V(v), adj(v + 1) {} // +1 to account for 1-based index

    UndirectedGraph(const size_t& v, const std::vector<std::pair<size_t, size_t>>& in) : V(v), adj(v + 1) {
        for (const auto& e : in) {
            AddEdge(e.first, e.second);
        }
    }

    size_t getV() const { return V; }
    size_t getE() const { return E; }

    void AddEdge(size_t v, size_t w) {
        adj[v].push_back(w);
        adj[w].push_back(v); // Assuming an undirected graph
        E++;
    }

    void PrintGraph() const {
        for (size_t v = 1; v <= V; ++v) {
            std::cout << "Adjacency list of vertex " << v << ": ";
            for (auto x : adj[v]) {
                std::cout << x << " ";
            }
            std::cout << std::endl;
        }
    }

    size_t degree(const size_t& v) const {
        std::map<std::pair<size_t, size_t>, bool, PairCompare> m;
        for (size_t i : adj[v]) {
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

