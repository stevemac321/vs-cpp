#include "graph.hpp"
int main() {
    std::vector<std::pair<size_t, size_t>> edges = {
        {1, 2}, {1, 5},
        {2, 1}, {2, 5}, {2, 3}, {2, 4},
        {3, 2}, {3, 4},
        {4, 2}, {4, 3}, {4, 5},
        {5, 1}, {5, 2}, {5, 4}
    };

    UndirectedGraph g(5, edges);
    g.PrintGraph();
    std::cout << "Max degree: " << g.maxDegree() << std::endl;
    std::cout << "Average degree: " << g.aveDegree() << std::endl;

    return 0;
}