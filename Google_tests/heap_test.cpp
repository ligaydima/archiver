#include "gtest/gtest.h"
#include "../heap.h"

TEST(HeapSuite, Test) {
    Heap heap;
    Node* a = new Node(1, 1);
    Node* b = new Node(1, 1);
    heap.AddNode(a);
    heap.AddNode(b);
    EXPECT_EQ(heap.PopMin()->weight, 1);
    EXPECT_EQ(heap.PopMin()->weight, 1);
    EXPECT_EQ(heap.Size(), 0);
    heap.AddNode(new Node(100, 100));
    heap.AddNode(new Node(200, 100));
    heap.AddNode(new Node(300, 100));
    heap.AddNode(new Node(200, 100));
    EXPECT_EQ(heap.Size(), 4);
    EXPECT_EQ(heap.PopMin()->weight, 100);
    EXPECT_EQ(heap.PopMin()->weight, 200);
    EXPECT_EQ(heap.PopMin()->weight, 200);
    EXPECT_EQ(heap.PopMin()->weight, 300);
}
