#include "crop.h"

#include "../exception/exception.h"

namespace filter {

Crop::Crop(const std::vector<std::string_view>& args) {
    if (args.size() != required_args_) {
        throw my_exception::FiltersException("crop requires exactly 2 arguments");
    }

    try {
        width_ = std::stoull(static_cast<const std::string>(args[0]));
        height_ = std::stoull(static_cast<const std::string>(args[1]));
        if (height_ <= 0 || width_ <= 0) {
            throw std::exception();
        }
    } catch (...) {
        throw my_exception::FiltersException("crop requires positive arguments");
    }
}

void Crop::operator()(bmp::Image& image) const {
    image.Resize(height_, width_);
}

} // filter namespace
