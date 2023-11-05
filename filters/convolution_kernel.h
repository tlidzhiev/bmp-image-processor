#pragma once

#include "../image/image.h"

#include <vector>

namespace filter {

using Kernel = std::vector<std::vector<double>>;

namespace convolution_kernel {

bmp::Pixel ApplyKernel(const Kernel& kernel, const bmp::PixelMatrix& pixels, size_t pixel_height, size_t pixel_width);

} // convolution_kernel namespace

} // filter namespace
