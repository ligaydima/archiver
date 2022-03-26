#include <vector>
#include <algorithm>
#include "gtest/gtest.h"
#include "../encoder.h"

TEST(HuffmanSuite, Test) {
    std::vector<size_t> freq = {1, 1, 1, 1, 4};
    std::vector<size_t> expected = {3, 3, 3, 3, 1};
    EXPECT_EQ(Encoder::HuffmanCodeLengths(freq), expected);
}

TEST(HuffmanSuite, Test2) {
    std::vector<size_t> freq = {1, 1, 1, 1, 4};
    std::vector<size_t> expected = {3, 3, 3, 3, 1};
    std::vector<uint16_t> codes = Encoder::GetCodes(Encoder::HuffmanCodeLengths(freq));
    EXPECT_EQ(codes.back(), 0);
    bool was = false;
    std::vector<uint16_t> cur = {1, 5, 3, 7, 0};
    do {
        if (cur == codes) {
            was = true;
            break;
        }
    } while (std::next_permutation(cur.begin(), cur.begin() + 4));
    EXPECT_EQ(was, true);
}