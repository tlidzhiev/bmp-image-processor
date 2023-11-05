#pragma once

#include "../image/image.h"
#include "convolution_kernel.h"

#include <vector>

namespace filter {

class Sharpening {
public:
    Sharpening() = default;
    void operator()(bmp::Image& image) const;
private:
    const Kernel kernel_ = {{0.0, -1.0, 0.0}, {-1.0, 5.0, -1.0}, {0.0, -1.0, 0.0}};
};

} // filter namespace
