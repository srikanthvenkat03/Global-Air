#include "monitor_dashboard.h"
#include <iostream>
#include <algorithm>

void MonitorDashboard::record_delay(const std::string& route, int delayMin) {
    routeDelayMap[route] += delayMin;
}

void MonitorDashboard::report_baggage_jam(const std::string& location, int count) {
    jamMap[location] += count;
}

void MonitorDashboard::record_risk_flight(const std::string& flightId, int score) {
    riskFlights.push({flightId, score});
}

std::vector<RouteDelay> MonitorDashboard::get_top_delays(int count) {
    std::priority_queue<RouteDelay> pq;
    for (const auto& pair : routeDelayMap) {
        pq.push({pair.first, pair.second});
    }

    std::vector<RouteDelay> top_delays;
    for (int i = 0; i < count && !pq.empty(); ++i) {
        top_delays.push_back(pq.top());
        pq.pop();
    }
    return top_delays;
}

std::vector<BaggageJam> MonitorDashboard::get_top_baggage_jams(int count) {
    std::priority_queue<BaggageJam> pq;
    for (const auto& pair : jamMap) {
        pq.push({pair.first, pair.second});
    }

    std::vector<BaggageJam> top_jams;
    for (int i = 0; i < count && !pq.empty(); ++i) {
        top_jams.push_back(pq.top());
        pq.pop();
    }
    return top_jams;
}

std::vector<RiskFlight> MonitorDashboard::get_risk_flights(int count) {
    std::priority_queue<RiskFlight> temp_pq = riskFlights;
    std::vector<RiskFlight> top_risks;
    for (int i = 0; i < count && !temp_pq.empty(); ++i) {
        top_risks.push_back(temp_pq.top());
        temp_pq.pop();
    }
    return top_risks;
}