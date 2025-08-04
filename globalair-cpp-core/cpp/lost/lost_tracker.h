#ifndef LOST_TRACKER_H
#define LOST_TRACKER_H

#include <string>
#include <unordered_map>

class LostTracker {
public:
    struct Node {
        int key;
        std::string baggageId;
        std::string status;
        Node *prev, *next;
    };

    void add(int key, const std::string& baggageId, const std::string& status);
    void update(int key, const std::string& newStatus);
    Node* find(int key);

private:
    std::unordered_map<int, Node*> cache;
    Node *head = nullptr, *tail = nullptr;
};

#endif