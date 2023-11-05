#pragma once

#include "../image/image.h"

#include <vector>
#include <string>

namespace filter {

class Crop {
public:
    explicit Crop(const std::vector<std::string_view>& args);
    void operator()(bmp::Image& image) const;
private:
    size_t width_ = 0;
    size_t height_ = 0;
    const size_t required_args_ = 2;
};

} // filter namespace
