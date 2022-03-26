#ifndef ARCHIVER_ARCHIVER_H
#define ARCHIVER_ARCHIVER_H

#include <vector>
#include <string>

#include "datawriter.h"

class Archiver {
public:
    static const uint16_t FILENAME_END = 256;
    static const uint16_t ONE_MORE_FILE = 257;
    static const uint16_t ARCHIVE_END = 258;
    static const size_t BLOCK_SIZE = 9;

    explicit Archiver(std::ofstream& stream);

    void Archive(const std::vector<std::string>& file_names);

private:
    void WriteFileContents(const std::string& file_name, const std::vector<uint16_t>& codes,
                           const std::vector<size_t>& lengths);

    void WriteEncodingData(const std::vector<uint16_t>& codes, const std::vector<size_t>& lengths);

    std::ostream archive_stream_;
    DataWriter writer_;
};

#endif //ARCHIVER_ARCHIVER_H
