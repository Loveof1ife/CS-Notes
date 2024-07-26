Directed Graph Library
Overview

The Directed Graph Library is a C++ library designed to provide a robust and efficient implementation of a directed graph data structure. This library supports operations such as insertion, deletion, and traversal of nodes and edges, as well as advanced iterator support.
Features

    Node and Edge Management: Insert and remove nodes and edges.
    Iterators: Bidirectional iterators to traverse the graph.
    Smart Pointer Integration: Uses std::shared_ptr for safe memory management.
    Container Integration: Compatible with STL containers.
    Const Correctness: Supports both mutable and immutable graph operations.

Getting Started
Requirements

    C++17 or later
    C++ standard library
Usage
      
    #include "directed_graph.h"
    #include <iostream>
    
    int main() {
        // Create a graph
        Graph::directed_graph<int> graph;

    // Insert nodes
    graph.insert(1);
    graph.insert(2);
    graph.insert(3);

    // Insert edges
    graph.insert_edge(1, 2);
    graph.insert_edge(2, 3);

    // Iterate through nodes
    for (auto it = graph.begin(); it != graph.end(); ++it) {
        std::cout << *it << " ";
    }

    // Access nodes
    std::cout << "Node at index 1: " << graph[1] << std::endl;

    return 0;
    }
