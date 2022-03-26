#include <vector>
#include <algorithm>
#include <string>
#include <fstream>

#include "unarchiver.h"
#include "datawriter.h"
#include "encoder.h"
#include "trie.h"

Unarchiver::Unarchiver(std::ifstream& stream) : archive_stream_(stream.rdbuf()), reader_(archive_stream_) {
}

void Unarchiver::Unarchive() {
    if (reader_.IsFail()) {
        throw std::runtime_error("Couldn't open archive");
    }
    bool archive_end = false;
    while (reader_.CanRead()) {
        size_t symbols_count = reader_.ReadBits(BLOCK_SIZE);
        std::vector<uint16_t> symbols;
        for (size_t i = 0; i < symbols_count; ++i) {
            symbols.push_back(reader_.ReadBits(BLOCK_SIZE));
        }

        std::vector<size_t> code_lengths = GetCodeData(symbols_count);
        std::vector<uint16_t> codes = Encoder::GetCodes(code_lengths);
        Trie trie(new Node());
        for (size_t i = 0; i < symbols_count; ++i) {
            trie.AddCode(codes[i], code_lengths[i], i);
        }
        std::string file_name = GetFileName(symbols, trie);

        if (DecodeFile(file_name, trie, symbols)) {
            archive_end = true;
            break;
        }
    }
    if (!archive_end) {
        throw std::runtime_error("Incorrect archive format");
    }
}

std::vector<size_t> Unarchiver::GetCodeData(size_t symbols_count) {
    size_t lengths_cnt_sum = 0;
    size_t cur_len = 0;
    std::vector<size_t> code_lengths;
    while (lengths_cnt_sum < symbols_count) {
        ++cur_len;
        uint16_t cur_cnt = reader_.ReadBits(BLOCK_SIZE);
        for (size_t i = 0; i < cur_cnt; ++i) {
            code_lengths.push_back(cur_len);
        }
        lengths_cnt_sum += cur_cnt;
    }
    if (lengths_cnt_sum != symbols_count) {
        throw std::runtime_error("File doesn't match archive format");
    }
    return code_lengths;
}

std::string Unarchiver::GetFileName(const std::vector<uint16_t>& symbols, Trie& trie) {
    std::string file_name;
    while (true) {
        while (!trie.IsLeaf()) {
            trie.AddBit(static_cast<bool>(reader_.ReadBits(1)));
        }
        if (symbols[trie.GetSymbolId()] == FILENAME_END) {
            trie.MoveToRoot();
            break;
        }
        file_name.push_back(static_cast<char>(symbols[trie.GetSymbolId()]));
        trie.MoveToRoot();
    }
    return file_name;
}

bool Unarchiver::DecodeFile(const std::string& file_name, Trie& trie, const std::vector<uint16_t>& symbols) {
    std::fstream file_stream(file_name, std::ios_base::binary | std::ios_base::out);
    DataWriter writer(file_stream);
    while (true) {
        while (!trie.IsLeaf()) {
            trie.AddBit(static_cast<bool>(reader_.ReadBits(1)));
        }
        if (symbols[(trie.GetSymbolId())] == ONE_MORE_FILE) {
            trie.MoveToRoot();
            return false;
        }
        if (symbols[trie.GetSymbolId()] == ARCHIVE_END) {
            trie.MoveToRoot();
            return true;
        }
        writer.Write(symbols[trie.GetSymbolId()], 8);
        trie.MoveToRoot();
    }
}
