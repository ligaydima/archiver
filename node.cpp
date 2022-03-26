#include <cinttypes>
#include <cstddef>

#include "node.h"

Node::Node(Node* left, Node* right) : left(left), right(right), symbol_id(0) {
    weight = left->weight + right->weight;
}

Node::Node() : weight(0), left(nullptr), right(nullptr), symbol_id(0) {
}

Node::Node(size_t weight, size_t symbol_id) : weight(weight), left(nullptr),
                                       right(nullptr), symbol_id(symbol_id) {
}

Node::~Node() {
    delete left;
    delete right;
}
