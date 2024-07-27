#include "graph.hpp"
int main() {
    std::cout << "Hello from Graph\n";

    std::vector<std::pair<int, int>> edges = {
        {1, 2}, {1, 5},
        {2, 1}, {2, 5}, {2, 3}, {2, 4},
        {3, 2}, {3, 4},
        {4, 2}, {4, 3}, {4, 5},
        {5, 1}, {5, 2}, {5, 4}
    };

    Graph g(5, edges);
    g.PrintGraph();

    return 0;
}
