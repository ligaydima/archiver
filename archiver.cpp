#include <vector>
#include <iostream>
#include <set>
#include <string>
#include <algorithm>
#include <fstream>

#include "datareader.h"
#include "encoder.h"
#include "archiver.h"

void AddSymbol(uint16_t symbol, std::vector<size_t>& frequencies) {
    if (frequencies.size() < static_cast<size_t>(symbol) + 1) {
        frequencies.resize(static_cast<size_t>(symbol) + 1);
    }
    ++frequencies[static_cast<size_t>(symbol)];
}

void GetFileFrequencies(const std::string& file_name, std::vector<size_t>& frequencies) {
    for (const char& c: file_name) {
        AddSymbol(static_cast<uint16_t>(c), frequencies);
    }
    AddSymbol(Archiver::FILENAME_END, frequencies);
    std::fstream file_stream(file_name, std::ios_base::in | std::ios_base::binary);
    DataReader reader(file_stream);
    if (reader.IsFail()) {
        throw std::runtime_error("Couldn't open file " + file_name);
    }
    while (reader.CanRead()) {
        uint16_t symbol;
        try {
            symbol = reader.ReadBits(8);
        } catch (const std::exception& exception) {
            throw std::runtime_error("Couldn't read file " + file_name);
        }
        AddSymbol(symbol, frequencies);
    }
}

void Archiver::WriteFileContents(const std::string& file_name, const std::vector<uint16_t>& codes,
                                 const std::vector<size_t>& lengths) {
    std::fstream file_stream(file_name, std::ios_base::in | std::ios_base::binary);
    DataReader reader(file_stream);
    for (const char& c: file_name) {
        writer_.Write(codes[static_cast<size_t>(c)], lengths[static_cast<size_t>(c)]);
    }
    writer_.Write(codes[FILENAME_END], lengths[FILENAME_END]);
    while (reader.CanRead()) {
        uint16_t symbol;
        try {
            symbol = reader.ReadBits(8);
        } catch (const std::exception& exception) {
            throw std::runtime_error("Couldn't read file " + file_name);
        }
        writer_.Write(codes[static_cast<size_t>(symbol)], lengths[static_cast<size_t>(symbol)]);
    }
}

Archiver::Archiver(std::ofstream& stream) : archive_stream_(stream.rdbuf()),
                                            writer_(archive_stream_) {
}

void Archiver::Archive(const std::vector<std::string>& file_names) {
    size_t index = 0;
    std::set<std::string> files;
    for (const std::string& file_name: file_names) {
        if (files.find(file_name) != files.end()) {
            continue;
        }
        files.insert(file_name);
        ++index;
        std::vector<size_t> frequencies;
        if (index == file_names.size()) {
            AddSymbol(ARCHIVE_END, frequencies);
        } else {
            AddSymbol(ONE_MORE_FILE, frequencies);
        }
        GetFileFrequencies(file_name, frequencies);

        std::vector<size_t> lengths = Encoder::HuffmanCodeLengths(frequencies);
        std::vector<uint16_t> codes = Encoder::GetCodes(lengths);

        WriteEncodingData(codes, lengths);
        WriteFileContents(file_name, codes, lengths);

        if (index == file_names.size()) {
            writer_.Write(codes[ARCHIVE_END], lengths[ARCHIVE_END]);
        } else {
            writer_.Write(codes[ONE_MORE_FILE], lengths[ONE_MORE_FILE]);
        }
    }
    writer_.Close();
}

void Archiver::WriteEncodingData(const std::vector<uint16_t>& codes, const std::vector<size_t>& lengths) {
    uint16_t symbols_count = lengths.size() - count(lengths.begin(), lengths.end(), 0);
    writer_.Write(static_cast<uint16_t>(symbols_count), BLOCK_SIZE);
    std::vector<size_t> symbols(lengths.size());
    for (size_t i = 0; i < lengths.size(); ++i) {
        symbols[i] = i;
    }
    std::sort(symbols.begin(), symbols.end(), [&lengths](size_t a, size_t b) { return lengths[a] < lengths[b]; });
    for (size_t i: symbols) {
        if (lengths[i] > 0) {
            writer_.Write(static_cast<uint16_t>(i), BLOCK_SIZE);
        }
    }
    std::vector<size_t> count_sizes((*std::max_element(lengths.begin(), lengths.end())) + 1);
    for (unsigned long length: lengths) {
        ++count_sizes[length];
    }
    for (size_t i = 1; i < count_sizes.size(); ++i) {
        writer_.Write(count_sizes[i], BLOCK_SIZE);
    }
}
