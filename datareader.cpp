#include <cinttypes>
#include <cstddef>

#include "datareader.h"

DataReader::DataReader(std::istream& stream) : stream_(stream) {
}

uint16_t DataReader::ReadBits(size_t count) {
    while (buffer_size_ < count) {
        uint16_t byte = 0;
        if (!stream_.read(reinterpret_cast<char*>(&byte), 1)) {
            throw std::runtime_error("error while reading the file");
        }
        buffer_ += (byte << buffer_size_);
        buffer_size_ += 8;
    }
    buffer_size_ -= count;
    uint16_t answer = (buffer_ & ((1 << count) - 1));
    buffer_ >>= count;
    return answer;
}

bool DataReader::CanRead() const {
    if (buffer_size_ > 0) {
        return true;
    }
    return stream_.peek() != -1;
}

bool DataReader::IsFail() const {
    return stream_.fail();
}
