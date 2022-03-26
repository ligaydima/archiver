#ifndef ARCHIVER_NODE_H
#define ARCHIVER_NODE_H

#include <cinttypes>
#include <cstddef>

class Node {
public:
    size_t weight = 0;
    Node* left = nullptr;
    Node* right = nullptr;
    size_t symbol_id = 0;

    Node();
    Node(size_t weight, size_t symbol_id);
    Node(Node* left, Node* right);
    ~Node();
};

#endif //ARCHIVER_NODE_H
