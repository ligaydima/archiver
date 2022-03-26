#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include "unarchiver.h"

#include "argumentparser.h"
#include "archiver.h"

const std::string HELP_STRING = "Command usage:\n"
                                "Arguments:\n"
                                "-h - print this message\n"
                                "-c archive_name file1 [file2...] - archive files file1, file2... into file archive_name\n"
                                "-d archive_name - unarchive file archive_name in this directory";

int main(int argc, char* argv[]) {
    ArgumentParser parser(argc, argv, {"-h", "-d", "-c"});
    std::vector<std::string> files = parser.GetFileNames();
    if (parser.ContainsOption("-h")) {
        std::cout << HELP_STRING << std::endl;
        return 0;
    }
    bool archive = parser.ContainsOption("-c");
    bool unarchive = parser.ContainsOption("-d");
    if (!archive && !unarchive) {
        std::cout << "No arguments have been passed. You can view the documentation by passing -h argument." << std::endl;
        return 0;
    }
    if (archive && unarchive) {
        std::cout << "Two arguments have been passed at the same time." << std::endl;
        return 0;
    }
    if (files.empty()) {
        std::cout << "No files have been passed." << std::endl;
        return 0;
    }
    std::string archive_name = files[0];
    files.erase(files.begin());
    try {
        if (archive) {
            if (files.empty()) {
                std::cout << "No files to be archived." << std::endl;
                return 0;
            }
            std::ofstream stream(archive_name, std::ios_base::binary);
            Archiver archiver(stream);
            archiver.Archive(files);
        } else {
            std::ifstream stream(archive_name, std::ios_base::binary);
            Unarchiver unarchiver(stream);
            unarchiver.Unarchive();
        }
    } catch (const std::exception& exception) {
        std::cout << exception.what() << std::endl;
    }
    return 0;
}
