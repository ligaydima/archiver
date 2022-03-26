#ifndef ARCHIVER_HEAP_H
#define ARCHIVER_HEAP_H

#include <vector>

#include "node.h"

class Heap {
public:
    Heap();
    ~Heap();

    // Инвариант - вес вершины i не больше веса вершин i * 2 и i * 2 + 1. Добавляет вершину за O(log размер кучи)
    void AddNode(Node* node);

    size_t Size() const;

    // Удаляет вершину с минимальным весом за O(log размера кучи)
    Node* PopMin();

private:
    std::vector<Node*> nodes_;
};

#endif //ARCHIVER_HEAP_H
