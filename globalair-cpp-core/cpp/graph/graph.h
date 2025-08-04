// cpp/graph/graph.h
#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <unordered_map>
#include <vector>

class Graph {
public:
    void loadFromCSV(const std::string& filename);
    void setWeightType(const std::string& weight_type);
    void printGraph();

    struct Edge {
        std::string dest;
        double distance;
        double delay;
        double cost;
    };

    const std::unordered_map<std::string, std::vector<Edge>>& getAdjList() const;

private:
    std::unordered_map<std::string, std::vector<Edge>> adjList;
    std::string weightType = "distance";

    void parseLine(const std::string& line);
};

#endif
