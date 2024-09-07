#include "graph.hpp"
#include <iomanip>

// Define Vertex struct (including your custom fields)
struct Vertex {
    int timestamp;  // Placeholder for the timestamp
    int event;      // Placeholder for event description or enum
    int gp_registers[8];  // General-purpose registers
    int hw_registers[4];  // Hardware-specific registers
    Vertex* next;    // To hold the next Vertex in the adjacency list

    // Constructor for Vertex
    Vertex(int ts, int ev)
        : timestamp(ts), event(ev), next(nullptr) {
        // Initialize registers with dummy data
        for (int& reg : gp_registers) reg = 0;
        for (int& reg : hw_registers) reg = 0;
    }

    // Set color in the event field
    void setColor(const EventField color) {
        // Clear current color bits (MSB)
        event &= 0x3FFFFFFF;  // Keep the lower 30 bits, clear the top 2 bits

        // Set the new color
        event |= static_cast<uint32_t>(color);
    }

    // Get the current color from the event field
    EventField getColor() const {
        // Extract the top 2 bits
        uint32_t colorBits = event & 0xC0000000;
        return static_cast<EventField>(colorBits);
    }
    // Set the event field, preserving the color bits
    void setEvent(uint32_t newEvent) {
        // Mask out the color bits from the new event
        newEvent &= 0x3FFFFFFF;  // Ensure newEvent doesn't affect the color bits

        // Clear the existing event bits, preserve the color bits
        event &= 0xC0000000;  // Preserve the color bits (MSB)

        // Set the new event value (lower 30 bits)
        event |= newEvent;
    }

    // Get the event value, ignoring the color bits
    uint32_t getEvent() const {
        // Mask out the color bits to return only the event-related bits
        return event & 0x3FFFFFFF;
    }
};
auto print_nodes = [](const Vertex* v) {
    std::cout << "Timestamp: " << v->timestamp << std::endl;
    }; 

int main() {
    StaticHeap<Vertex, 4096> allocator;
    UndirectedGraph<Vertex, StaticHeap<Vertex, 4096>> graph(5, allocator);

    // Add some edges with dummy data
    Vertex v1(100, 1);
    Vertex v2(200, 2);
    graph.addEdge(0, 1, v1);
    graph.addEdge(0, 2, v2);
    graph.TraverseGraph(print_nodes);

    return 0;
}
