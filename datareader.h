#ifndef ARCHIVER_DATAREADER_H
#define ARCHIVER_DATAREADER_H

#include <cinttypes>
#include <cstddef>
#include <string>
#include <istream>

class DataReader {
public:
    explicit DataReader(std::istream& stream);

    uint16_t ReadBits(size_t count);

    bool IsFail() const;

    bool CanRead() const;

private:
    size_t buffer_size_ = 0;
    uint16_t buffer_ = 0;
    std::istream& stream_;
};

#endif //ARCHIVER_DATAREADER_H
