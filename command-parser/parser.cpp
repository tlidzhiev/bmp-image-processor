#include "parser.h"
#include "../exception/exception.h"

namespace command_parser {

CommandArgs ParseCommand(int argc, const char** argv) {
    if (argc < kMinArgsCount) {
        throw my_exception::ParserException("not enough arguments, required 3 at least");
    }

    CommandArgs command_arguments = {.input_path=argv[1], .output_path=argv[2]};

    int curr_arg = kMinArgsCount;
    while (curr_arg < argc) {
        if (argv[curr_arg][0] != kFilterNameFlag) {
            throw std::exception();
        }

        FilterArgs filter_args = {.name=argv[curr_arg]};
        ++curr_arg;
        while (curr_arg < argc && argv[curr_arg][0] != kFilterNameFlag) {
            filter_args.args.emplace_back(argv[curr_arg]);
            ++curr_arg;
        }

        command_arguments.filters.emplace_back(filter_args);
    }

    return command_arguments;
}

} // command_parser namespace
