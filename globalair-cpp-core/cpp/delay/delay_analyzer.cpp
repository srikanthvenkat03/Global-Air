// cpp/delay/delay_analyzer.cpp
#include "delay_analyzer.h"
#include <iostream>
#include <limits>

void DelayAnalyzer::loadMockData() {
    // Simulated historical delay data (min)
    delayData["JFK"][1] = 70;
    delayData["JFK"][2] = 60;
    delayData["LAX"][1] = 55;
    delayData["LAX"][2] = 40;
    delayData["DEL"][1] = 90;
    delayData["DEL"][2] = 110;
    delayData["MAA"][1] = 45;
    delayData["MAA"][2] = 60;
    delayData["SFO"][1] = 65;
    delayData["SFO"][2] = 50;
}

int DelayAnalyzer::getAvgDelay(const std::string& airport, int month) {
    if (cache[airport].count(month)) {
        return cache[airport][month]; // return memoized result
    }

    if (delayData.count(airport) && delayData[airport].count(month)) {
        int delay = delayData[airport][month];
        cache[airport][month] = delay;
        return delay;
    }

    return -1; // no data
}

std::string DelayAnalyzer::getWorstDelayAirport(int month) {
    int maxDelay = std::numeric_limits<int>::min();
    std::string worstAirport = "N/A";

    for (const auto& [airport, monthlyData] : delayData) {
        if (monthlyData.count(month)) {
            int delay = getAvgDelay(airport, month);
            if (delay > maxDelay) {
                maxDelay = delay;
                worstAirport = airport;
            }
        }
    }

    return worstAirport;
}

void DelayAnalyzer::printAirportMonthlyDelays(const std::string& airport) {
    if (!delayData.count(airport)) {
        std::cout << "No delay data for " << airport << "\n";
        return;
    }

    std::cout << "Monthly average delays for " << airport << ":\n";
    for (const auto& [month, delay] : delayData[airport]) {
        std::cout << "Month " << month << ": " << delay << " minutes\n";
    }
}
