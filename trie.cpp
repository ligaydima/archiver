#include <vector>

#include "trie.h"
#include "node.h"

void Trie::AddBit(bool bit) {
    if (bit) {
        if (current_->right == nullptr) {
            current_->right = new Node();
        }
        current_ = current_->right;
    } else {
        if (current_->left == nullptr) {
            current_->left = new Node();
        }
        current_ = current_->left;
    }
}

size_t Trie::GetSymbolId() const {
    return current_->symbol_id;
}

void Trie::MoveToRoot() {
    current_ = root_;
}

bool Trie::IsLeaf() const {
    return current_->left == nullptr;
}

Trie::Trie(Node* _root) : root_(_root), current_(_root) {
}

void Trie::DFS(const Node* vertex, size_t dist, std::vector<size_t>& answer) const {
    if (vertex->left == nullptr) {
        if (answer.size() < vertex->symbol_id + 1) {
            answer.resize(vertex->symbol_id + 1, 0);
        }
        answer[vertex->symbol_id] = dist;
        return;
    }
    DFS(vertex->left, dist + 1, answer);
    DFS(vertex->right, dist + 1, answer);
}

std::vector<size_t> Trie::GetCodeLengths() const {
    std::vector<size_t> answer;
    DFS(root_, 0, answer);
    return answer;
}

Trie::~Trie() {
    delete root_;
}

void Trie::AddCode(uint16_t code, size_t length, size_t symbol_id) {
    MoveToRoot();
    for (size_t bit = 0; bit < length; ++bit) {
        AddBit((code & (1 << bit)) > 0);
    }
    current_->symbol_id = symbol_id;
    MoveToRoot();
}
