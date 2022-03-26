#ifndef ARCHIVER_DATAWRITER_H
#define ARCHIVER_DATAWRITER_H

#include <cinttypes>
#include <cstddef>
#include <string>
#include <ostream>

class DataWriter {
public:
    explicit DataWriter(std::ostream& stream);
    ~DataWriter();

    void Write(uint16_t msg, size_t msg_size);

    void Close();

private:
    void WriteByte();

    size_t buffer_size_ = 0;
    uint16_t buffer_ = 0;
    std::ostream& stream_;
};

#endif //ARCHIVER_DATAWRITER_H
