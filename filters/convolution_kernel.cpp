#include "convolution_kernel.h"

namespace filter::convolution_kernel {

bmp::Pixel ApplyKernel(const Kernel& kernel, const bmp::PixelMatrix& pixels, size_t pixel_height, size_t pixel_width) {
    int kernel_bound_x = static_cast<int>(kernel.size() / 2);
    int kernel_bound_y = static_cast<int>(kernel[0].size() / 2);

    double r = 0;
    double g = 0;
    double b = 0;

    auto cast_pixel_height = static_cast<int32_t>(pixel_height);
    auto cast_pixel_width = static_cast<int32_t>(pixel_width);

    size_t image_height = pixels.size();
    size_t image_width = pixels[0].size();
    for (int32_t i = -kernel_bound_x; i <= kernel_bound_x; ++i) {
        for (int32_t j = -kernel_bound_y; j <= kernel_bound_y; ++j) {

            int32_t neighbour_pixel_height = cast_pixel_height + i;
            int32_t neighbour_pixel_width = cast_pixel_width + j;

            neighbour_pixel_height = std::clamp(neighbour_pixel_height, 0, static_cast<int32_t>(image_height) - 1);
            neighbour_pixel_width = std::clamp(neighbour_pixel_width, 0, static_cast<int32_t>(image_width) - 1);

            const auto& pixel = pixels[neighbour_pixel_height][neighbour_pixel_width];
            double kernel_element = kernel[kernel_bound_y + j][kernel_bound_x + i];
            r += static_cast<double>(pixel.r) * kernel_element;
            g += static_cast<double>(pixel.g) * kernel_element;
            b += static_cast<double>(pixel.b) * kernel_element;
        }
    }

    return {static_cast<int>(b), static_cast<int>(g), static_cast<int>(r)};
}

} // filter::convolution_kernel namespace
