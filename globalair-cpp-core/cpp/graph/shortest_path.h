// cpp/graph/shortest_path.h
#ifndef SHORTEST_PATH_H
#define SHORTEST_PATH_H

#include "graph.h"
#include <unordered_map>
#include <string>
#include <vector>

class ShortestPath {
public:
    static std::vector<std::string> dijkstra(const Graph& graph, const std::string& start, const std::string& end, const std::string& weightType);
    static std::vector<std::string> bellmanFord(const Graph& graph, const std::string& start, const std::string& end, const std::string& weightType);
};

#endif
