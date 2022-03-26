#ifndef ARCHIVER_ARGUMENTPARSER_H
#define ARCHIVER_ARGUMENTPARSER_H

#include <set>
#include <string>
#include <vector>
#include <string>

class ArgumentParser {
public:
    ArgumentParser(int argc, char** argv, const std::vector<std::string>& options);

    bool ContainsOption(const std::string& option) const;

    const std::vector<std::string>& GetFileNames() const;

private:
    std::set<std::string> options_;
    std::vector<std::string> file_names_;
};

#endif //ARCHIVER_ARGUMENTPARSER_H
