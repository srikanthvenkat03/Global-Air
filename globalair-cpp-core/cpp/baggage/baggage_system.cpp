// cpp/baggage/baggage_system.cpp
#include "baggage_system.h"
#include <iostream>

// ===== Baggage Node (BST Node) =====
BaggageNode::BaggageNode(const Baggage& b) : data(b), left(nullptr), right(nullptr) {}

// ===== BaggageBST Implementation =====
BaggageBST::BaggageBST() : root(nullptr) {}

void BaggageBST::insert(const Baggage& baggage) {
    insertNode(root, baggage);
}

void BaggageBST::insertNode(BaggageNode*& node, const Baggage& baggage) {
    if (!node) {
        node = new BaggageNode(baggage);
        return;
    }

    if (baggage.passengerPriority < node->data.passengerPriority) {
        insertNode(node->left, baggage);
    } else {
        insertNode(node->right, baggage);
    }
}

void BaggageBST::inOrderTraversal() {
    std::cout << "Baggage BST In-Order:\n";
    inOrder(root);
}

void BaggageBST::inOrder(BaggageNode* node) {
    if (!node) return;
    inOrder(node->left);
    std::cout << "ID: " << node->data.id
              << " | Priority: " << node->data.passengerPriority
              << " | Type: " << node->data.type
              << " | Risk: " << node->data.securityRisk
              << "\n";
    inOrder(node->right);
}

// ===== Min Heap Implementation =====
void BaggageMinHeap::push(const Baggage& baggage) {
    minHeap.push(baggage);
}

Baggage BaggageMinHeap::pop() {
    if (minHeap.empty()) {
        throw std::runtime_error("Heap is empty.");
    }
    Baggage top = minHeap.top();
    minHeap.pop();
    return top;
}

bool BaggageMinHeap::isEmpty() const {
    return minHeap.empty();
}
