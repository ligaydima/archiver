#include <vector>
#include <algorithm>

#include "encoder.h"
#include "heap.h"
#include "trie.h"

uint16_t GetBit(uint16_t code, size_t i) {
    return (code & (1 << i));
}

void SwapBits(uint16_t& code, size_t a, size_t b) {
    uint16_t x = GetBit(code, a);
    uint16_t y = GetBit(code, b);
    code ^= x;
    code ^= y;
    if (x > 0) {
        code += (1 << b);
    }
    if (y > 0) {
        code += (1 << a);
    }
}

uint16_t ReverseCode(uint16_t code, size_t length) {
    for (size_t i = 0; i * 2 + 1 < length; ++i) {
        SwapBits(code, i, length - i - 1);
    }
    return code;
}

std::vector<uint16_t> Encoder::GetCodes(const std::vector<size_t>& code_lengths) {
    std::vector<uint16_t> answer(code_lengths.size());
    std::vector<size_t> permutation(code_lengths.size());
    for (size_t i = 0; i < code_lengths.size(); ++i) {
        permutation[i] = i;
    }
    std::sort(permutation.begin(), permutation.end(),
              [&code_lengths](size_t a, size_t b) { return code_lengths[a] < code_lengths[b]; });
    uint16_t prev_answer = 0;
    for (size_t i = 0; i < permutation.size(); ++i) {
        if (code_lengths[permutation[i]] == 0) {
            continue;
        }
        answer[permutation[i]] = ReverseCode(prev_answer, code_lengths[permutation[i]]);
        ++prev_answer;
        if (i + 1 != permutation.size()) {
            prev_answer <<= code_lengths[permutation[i + 1]] - code_lengths[permutation[i]];
        }
    }
    return answer;
}

std::vector<size_t> Encoder::HuffmanCodeLengths(const std::vector<size_t>& frequencies) {
    Heap heap;
    for (size_t i = 0; i < frequencies.size(); ++i) {
        if (frequencies[i] > 0) {
            heap.AddNode(new Node(frequencies[i], i));
        }
    }
    while (heap.Size() > 1) {
        Node* a = heap.PopMin();
        Node* b = heap.PopMin();
        heap.AddNode(new Node(a, b));
    }
    Trie trie(heap.PopMin());
    return trie.GetCodeLengths();
}
