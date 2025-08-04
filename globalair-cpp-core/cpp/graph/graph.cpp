#include "graph.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>

void Graph::loadFromCSV(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        // --- DEBUG PRINT ---
        std::cerr << "!!! CRITICAL ERROR: Could not open file: " << filename << std::endl;
        return;
    }

    std::getline(file, line); 

    while (std::getline(file, line)) {
        parseLine(line);
    }
    
    // --- DEBUG PRINT ---
    std::cout << "Successfully loaded CSV. Graph has " << adjList.size() << " airports." << std::endl;
    file.close();
}

void Graph::parseLine(const std::string& line) {
    std::stringstream ss(line);
    std::string src, dest, distStr, delayStr, costStr;
    std::getline(ss, src, ',');
    std::getline(ss, dest, ',');
    std::getline(ss, distStr, ',');
    std::getline(ss, delayStr, ',');
    std::getline(ss, costStr, ',');
    Edge edge;
    edge.dest = dest;
    edge.distance = std::stod(distStr);
    edge.delay = std::stod(delayStr);
    edge.cost = std::stod(costStr);
    adjList[src].push_back(edge);
    if (adjList.find(dest) == adjList.end()) {
        adjList[dest] = {};
    }
}

// ... the rest of the file is the same ...

void Graph::setWeightType(const std::string& weight_type) {
    if (weight_type == "distance" || weight_type == "delay" || weight_type == "cost") {
        weightType = weight_type;
    } else {
        std::cerr << "Invalid weight type! Defaulting to distance.\n";
    }
}

void Graph::printGraph() {
    std::cout << "Graph (weighted by " << weightType << "):\n";
    for (const auto& node : adjList) {
        std::cout << node.first << " -> ";
        for (const auto& edge : node.second) {
            double weight = (weightType == "distance") ? edge.distance :
                            (weightType == "delay") ? edge.delay : edge.cost;
            std::cout << edge.dest << "(" << std::fixed << std::setprecision(1) << weight << ") ";
        }
        std::cout << "\n";
    }
}

const std::unordered_map<std::string, std::vector<Graph::Edge>>& Graph::getAdjList() const {
    return adjList;
}