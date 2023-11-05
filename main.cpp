#include "command-parser/parser.h"
#include "filters/filters_applying.h"
#include "exception/exception.h"

int main(int argc, const char* argv[]) {
    try {
        command_parser::CommandArgs args = command_parser::ParseCommand(argc, argv);
        bmp::Image image(args.input_path);

        filter::ApplyFilters(args.filters, image);

        image.Save(args.output_path);
    } catch (const my_exception::BaseException& e) {
        my_exception::React(e);
    }

    return 0;
}
