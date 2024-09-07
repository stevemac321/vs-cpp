#pragma once

#include <iostream>
#include <cstddef>  // for std::size_t

// StaticHeap allocator
template <typename T, std::size_t N = 4096>
class StaticHeap {
    static constexpr std::size_t heapSize = N / sizeof(T);
    alignas(T) unsigned char buffer[heapSize * sizeof(T)];
    bool used[heapSize] = { false };

public:
    using value_type = T;

    T* allocate() {
        for (std::size_t i = 0; i < heapSize; ++i) {
            if (!used[i]) {
                used[i] = true;
                return reinterpret_cast<T*>(&buffer[i * sizeof(T)]);
            }
        }
        return nullptr;  // No space available
    }

    void deallocate(T* ptr) {
        for (std::size_t i = 0; i < heapSize; ++i) {
            if (ptr == reinterpret_cast<T*>(&buffer[i * sizeof(T)])) {
                ptr->~T();
                used[i] = false;
                return;
            }
        }
    }

    template <typename U, typename... Args>
    void construct(U* ptr, Args&&... args) {
        new (ptr) U(std::forward<Args>(args)...);
    }

    template <typename U>
    void destroy(U* ptr) {
        ptr->~U();
    }
};

enum class EventField : uint32_t {
    // Regular events
    PIN_IN = 0x00000001,  // Example event
    PIN_OUT = 0x00000002,  // Example event
    INTERRUPT = 0x00000004,  // Example event

    // Colors using the most significant bits (MSBs) in the 32-bit field
    WHITE = 0x00000000,  // 00 in the LSBs
    GRAY = 0x40000000,  // 01 in the MSBs (6th bit)
    BLACK = 0x80000000   // 11 in the MSBs (7th bit)
};

// Templatized Graph class using adjacency lists
template <typename T, typename Allocator = StaticHeap<T>>
class UndirectedGraph {
    std::size_t V;  // Number of vertices
    Allocator& allocator;
    T** adjList;  // Array of adjacency lists

public:
   
    // Constructor
    UndirectedGraph(std::size_t vertices, Allocator& alloc)
        : V(vertices), allocator(alloc) {
        adjList = new T * [V];  // Create an array of T* pointers
        for (std::size_t i = 0; i < V; ++i) {
            adjList[i] = nullptr;
        }
    }

    // Destructor to free the memory
    ~UndirectedGraph() {
        for (std::size_t i = 0; i < V; ++i) {
            T* current = adjList[i];
            while (current) {
                T* temp = current;
                current = current->next;
                allocator.destroy(temp);
                allocator.deallocate(temp);
            }
        }
        delete[] adjList;
    }

    // Add edge to the undirected graph
    void addEdge(std::size_t v, std::size_t w, const T& value) {
        T* newNode = allocator.allocate();
        allocator.construct(newNode, value);
        newNode->next = adjList[v];
        adjList[v] = newNode;

        // Since it's undirected, add an edge from w to v as well
        newNode = allocator.allocate();
        allocator.construct(newNode, value);
        newNode->next = adjList[w];
        adjList[w] = newNode;
    }

    template <typename F>
    void TraverseGraph(F visitor) const {
        for (std::size_t i = 0; i < V; ++i) {
            T* current = adjList[i];  // Traverse adjacency list for vertex `i`
            while (current != nullptr) {
                visitor(current);  // Call the visitor with the current element
                current = current->next;  // Move to the next item
            }
        }
}



};
