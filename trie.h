#ifndef ARCHIVER_TRIE_H
#define ARCHIVER_TRIE_H

#include <vector>

#include "node.h"

class Trie {
public:
    explicit Trie(Node* _root);
    ~Trie();

    void AddBit(bool bit);

    void MoveToRoot();

    size_t GetSymbolId() const;

    bool IsLeaf() const;

    std::vector<size_t> GetCodeLengths() const;

    void AddCode(uint16_t code, size_t length, size_t symbol_id);

private:
    void DFS(const Node* vertex, size_t dist, std::vector<size_t>& answer) const;

    Node* root_ = nullptr;
    Node* current_ = nullptr;
};

#endif //ARCHIVER_TRIE_H
