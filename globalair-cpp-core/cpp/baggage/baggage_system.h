// cpp/baggage/baggage_system.h
#ifndef BAGGAGE_SYSTEM_H
#define BAGGAGE_SYSTEM_H

#include <string>
#include <vector>
#include <queue>

struct Baggage {
    std::string id;
    std::string type; // e.g., "Checked", "Carry-On"
    int passengerPriority; // e.g., 1 = First, 2 = Business, 3 = Economy
    int securityRisk; // 1 = High risk, 2 = Medium, 3 = Low
    int urgencyScore; // computed as (priority * 10 + risk * 5)

    bool operator<(const Baggage& other) const {
        return urgencyScore > other.urgencyScore; // for min heap
    }
};

class BaggageNode {
public:
    Baggage data;
    BaggageNode* left;
    BaggageNode* right;

    BaggageNode(const Baggage& b);
};

class BaggageBST {
public:
    BaggageBST();
    void insert(const Baggage& baggage);
    void inOrderTraversal();

private:
    BaggageNode* root;
    void insertNode(BaggageNode*& node, const Baggage& baggage);
    void inOrder(BaggageNode* node);
};

class BaggageMinHeap {
public:
    void push(const Baggage& baggage);
    Baggage pop();
    bool isEmpty() const;

private:
    std::priority_queue<Baggage> minHeap;
};

#endif
