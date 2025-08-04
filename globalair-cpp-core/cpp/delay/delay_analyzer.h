// cpp/delay/delay_analyzer.h
#ifndef DELAY_ANALYZER_H
#define DELAY_ANALYZER_H

#include <string>
#include <unordered_map>
#include <vector>

class DelayAnalyzer {
public:
    void loadMockData(); // Simulated loading (replaceable with CSV later)
    int getAvgDelay(const std::string& airport, int month);
    std::string getWorstDelayAirport(int month);
    void printAirportMonthlyDelays(const std::string& airport);

private:
    std::unordered_map<std::string, std::unordered_map<int, int>> delayData; // airport -> month -> avg delay
    std::unordered_map<std::string, std::unordered_map<int, int>> cache;
};

#endif
