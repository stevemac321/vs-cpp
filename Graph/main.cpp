#include "graph.hpp"
int main() {
    std::vector<std::vector<std::tuple<size_t, size_t, size_t>>> edges = {
     {{1, 2, 10}, {1, 5, 20}},
     {{2, 1, 10}, {2, 5, 30}, {2, 3, 40}, {2, 4, 50}},
     {{3, 2, 40}, {3, 4, 60}},
     {{4, 2, 50}, {4, 3, 60}, {4, 5, 70}},
     {{5, 1, 20}, {5, 2, 30}, {5, 4, 70}}
    };


    std::cout << edges.size() << std::endl;

    UndirectedGraph g(5, edges);
    g.PrintGraph();
    std::cout << "Max degree: " << g.maxDegree() << std::endl;
    std::cout << "Average degree: " << g.aveDegree() << std::endl;

    return 0;
}