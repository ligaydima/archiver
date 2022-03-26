#include <cinttypes>
#include <cstddef>
#include <string>

#include <ostream>
#include "datawriter.h"

DataWriter::DataWriter(std::ostream& stream) : stream_(stream) {
}

void DataWriter::WriteByte() {
    unsigned char data = (buffer_ & 255);
    if (!stream_.write(reinterpret_cast<char*>(&data), 1)) {
        throw std::runtime_error("error - cannot write in file");
    }
}

void DataWriter::Write(uint16_t msg, size_t msg_size) {
    buffer_ += (msg << buffer_size_);
    buffer_size_ += msg_size;
    while (buffer_size_ >= 8) {
        WriteByte();
        buffer_size_ -= 8;
        buffer_ >>= 8;
    }
}

void DataWriter::Close() {
    if (buffer_size_ > 0) {
        WriteByte();
        buffer_size_ = 0;
        buffer_ = 0;
    }
}

DataWriter::~DataWriter() {
    Close();
}
