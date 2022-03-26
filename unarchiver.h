#ifndef ARCHIVER_UNARCHIVER_H
#define ARCHIVER_UNARCHIVER_H

#include <vector>
#include <string>
#include <fstream>
#include <cstdint>

#include "datareader.h"
#include "trie.h"

class Unarchiver {
public:
    static const uint16_t FILENAME_END = 256;
    static const uint16_t ONE_MORE_FILE = 257;
    static const uint16_t ARCHIVE_END = 258;
    static const size_t BLOCK_SIZE = 9;

    explicit Unarchiver(std::ifstream& stream);

    void Unarchive();

private:
    std::vector<size_t> GetCodeData(size_t symbols_count);

    std::string GetFileName(const std::vector<uint16_t>& symbols, Trie& trie);

    // true если является последним файлом в архиве иначе false
    bool DecodeFile(const std::string& file_name, Trie& trie, const std::vector<uint16_t>& symbols);

    std::istream archive_stream_;
    DataReader reader_;
};

#endif //ARCHIVER_UNARCHIVER_H
