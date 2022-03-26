#ifndef ARCHIVER_ENCODER_H
#define ARCHIVER_ENCODER_H

#include <vector>

class Encoder {
public:
    static std::vector<uint16_t> GetCodes(const std::vector<size_t>& code_lengths);

    static std::vector<size_t> HuffmanCodeLengths(const std::vector<size_t>& frequencies);
};

#endif //ARCHIVER_ENCODER_H
