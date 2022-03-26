#include <vector>

#include "heap.h"

Heap::Heap() = default;

void Heap::AddNode(Node* node) {
    nodes_.push_back(node);
    size_t cur_ind = nodes_.size() - 1;
    while (cur_ind > 0 && node->weight < nodes_[cur_ind / 2]->weight) {
        std::swap(nodes_[cur_ind], nodes_[cur_ind / 2]);
        cur_ind /= 2;
    }
}

Heap::~Heap() {
    nodes_.clear();
}

Node* Heap::PopMin() {
    Node* answer = nodes_[0];
    nodes_[0] = nodes_.back();
    nodes_.pop_back();
    if (nodes_.empty()) {
        return answer;
    }
    size_t i = 0;
    while (i * 2 + 1 < nodes_.size() &&
           nodes_[i]->weight > std::min(nodes_[i * 2]->weight, nodes_[i * 2 + 1]->weight)) {
        size_t to;
        if (nodes_[i * 2]->weight < nodes_[i * 2 + 1]->weight) {
            to = i * 2;
        } else {
            to = i * 2 + 1;
        }
        std::swap(nodes_[i], nodes_[to]);
        i = to;
    }
    if (i * 2 == nodes_.size() - 1 && nodes_[i]->weight > nodes_[i * 2]->weight) {
        std::swap(nodes_[i], nodes_[i * 2]);
    }
    return answer;
}

size_t Heap::Size() const {
    return nodes_.size();
}
