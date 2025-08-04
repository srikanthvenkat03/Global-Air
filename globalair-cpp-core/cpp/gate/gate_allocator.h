#ifndef GATE_ALLOCATOR_H
#define GATE_ALLOCATOR_H

#include <vector>
#include <string>
#include <algorithm>

struct Flight {
    std::string id;
    int priority;
};

class GateAllocator {
public:
    GateAllocator(std::vector<Flight> initial_flights);
    void sortFlights();
    std::vector<std::string> getGateAllocations();

private:
    std::vector<Flight> flights;
};

#endif