#pragma once

#include <string_view>
#include <vector>

namespace command_parser {

constexpr int kMinArgsCount = 3;
constexpr char kFilterNameFlag = '-';

struct FilterArgs {
    std::string_view name;
    std::vector<std::string_view> args;
};

struct CommandArgs {
    std::string_view input_path;
    std::string_view output_path;
    std::vector<FilterArgs> filters;
};

CommandArgs ParseCommand(int argc, const char* argv[]);

} // command_parser namespace
