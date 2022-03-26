#include "argumentparser.h"

ArgumentParser::ArgumentParser(int argc, char** argv, const std::vector<std::string>& options) {
    std::set<std::string> all_options_set(options.begin(), options.end());
    for (size_t i = 1; i < argc; ++i) {
        std::string cur_string = argv[i];
        if (all_options_set.find(cur_string) != all_options_set.end()) {
            options_.insert(cur_string);
            continue;
        }
        file_names_.push_back(cur_string);
    }
}

bool ArgumentParser::ContainsOption(const std::string& argument) const {
    return options_.find(argument) != options_.end();
}

const std::vector<std::string>& ArgumentParser::GetFileNames() const {
    return file_names_;
}
