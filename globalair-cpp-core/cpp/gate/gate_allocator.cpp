// cpp/gate/gate_allocator.cpp
#include "gate_allocator.h"
#include <iostream>

bool Flight::operator<(const Flight& other) const {
    if (arrivalTime != other.arrivalTime)
        return arrivalTime < other.arrivalTime;
    if (passengerPriority != other.passengerPriority)
        return passengerPriority < other.passengerPriority;
    return flightRisk < other.flightRisk;
}

void GateAllocator::addFlight(const Flight& flight) {
    flights.push_back(flight);
}

void GateAllocator::allocateGates() {
    mergeSort(0, flights.size() - 1);

    std::cout << "=== Gate Allocation (sorted by arrival, priority, risk) ===\n";
    int gate = 1;
    for (const auto& f : flights) {
        std::cout << "Gate " << gate++ << ": Flight " << f.flightId
                  << " | Arrival: " << f.arrivalTime
                  << " | Priority: " << f.passengerPriority
                  << " | Risk: " << f.flightRisk << "\n";
    }
}

void GateAllocator::mergeSort(int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(left, mid);
        mergeSort(mid + 1, right);
        merge(left, mid, right);
    }
}

void GateAllocator::merge(int left, int mid, int right) {
    std::vector<Flight> leftVec(flights.begin() + left, flights.begin() + mid + 1);
    std::vector<Flight> rightVec(flights.begin() + mid + 1, flights.begin() + right + 1);

    int i = 0, j = 0, k = left;

    while (i < leftVec.size() && j < rightVec.size()) {
        if (leftVec[i] < rightVec[j]) {
            flights[k++] = leftVec[i++];
        } else {
            flights[k++] = rightVec[j++];
        }
    }

    while (i < leftVec.size()) flights[k++] = leftVec[i++];
    while (j < rightVec.size()) flights[k++] = rightVec[j++];
}
