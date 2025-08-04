// cpp/graph/shortest_path.cpp
#include "shortest_path.h"
#include <queue>
#include <iostream>
#include <limits>
#include <stack>

std::vector<std::string> ShortestPath::dijkstra(const Graph& graph, const std::string& start, const std::string& end, const std::string& weightType) {
    const auto& adj = graph.getAdjList();
    std::unordered_map<std::string, double> dist;
    std::unordered_map<std::string, std::string> prev;

    for (const auto& node : adj) {
        dist[node.first] = std::numeric_limits<double>::infinity();
    }

    dist[start] = 0.0;

    using P = std::pair<double, std::string>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
    pq.push({0.0, start});

    while (!pq.empty()) {
        auto [currDist, u] = pq.top();
        pq.pop();

        if (u == end) break;

        for (const auto& edge : adj.at(u)) {
            double weight = (weightType == "distance") ? edge.distance :
                            (weightType == "delay") ? edge.delay : edge.cost;

            double alt = dist[u] + weight;
            if (alt < dist[edge.dest]) {
                dist[edge.dest] = alt;
                prev[edge.dest] = u;
                pq.push({alt, edge.dest});
            }
        }
    }

    std::vector<std::string> path;
    for (std::string at = end; at != ""; at = prev[at]) {
        path.push_back(at);
        if (at == start) break;
    }

    std::reverse(path.begin(), path.end());
    if (path.front() != start) path.clear(); // no path

    return path;
}

std::vector<std::string> ShortestPath::bellmanFord(const Graph& graph, const std::string& start, const std::string& end, const std::string& weightType) {
    const auto& adj = graph.getAdjList();
    std::unordered_map<std::string, double> dist;
    std::unordered_map<std::string, std::string> prev;

    for (const auto& node : adj) {
        dist[node.first] = std::numeric_limits<double>::infinity();
    }

    dist[start] = 0.0;

    for (size_t i = 0; i < adj.size() - 1; ++i) {
        for (const auto& [u, edges] : adj) {
            for (const auto& edge : edges) {
                double weight = (weightType == "distance") ? edge.distance :
                                (weightType == "delay") ? edge.delay : edge.cost;
                if (dist[u] + weight < dist[edge.dest]) {
                    dist[edge.dest] = dist[u] + weight;
                    prev[edge.dest] = u;
                }
            }
        }
    }

    std::vector<std::string> path;
    for (std::string at = end; at != ""; at = prev[at]) {
        path.push_back(at);
        if (at == start) break;
    }

    std::reverse(path.begin(), path.end());
    if (path.front() != start) path.clear(); // no path

    return path;
}
