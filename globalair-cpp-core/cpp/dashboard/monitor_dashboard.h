#ifndef MONITOR_DASHBOARD_H
#define MONITOR_DASHBOARD_H

#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

// Structs for data transfer
struct RouteDelay {
    std::string route;
    int totalDelay;
    bool operator<(const RouteDelay& other) const { return totalDelay < other.totalDelay; }
};

struct BaggageJam {
    std::string location;
    int count;
    bool operator<(const BaggageJam& other) const { return count < other.count; }
};

struct RiskFlight {
    std::string flightId;
    int riskScore;
    bool operator<(const RiskFlight& other) const { return riskScore < other.riskScore; }
};

class MonitorDashboard {
public:
    void recordDelay(const std::string& route, int delayMin);
    void reportBaggageJam(const std::string& location);
    void recordRiskFlight(const std::string& flightId, int score);

    // --- CORRECTED METHODS ---
    // These now return data, making them usable by the API.
    std::vector<RouteDelay> getTopDelays(int count);
    std::vector<BaggageJam> getTopBaggageJams(int count);
    std::vector<RiskFlight> getFlightsAtRisk(int count);

private:
    std::unordered_map<std::string, int> routeDelayMap;
    std::unordered_map<std::string, int> jamMap;
    std::priority_queue<RiskFlight> riskFlights;
};

#endif