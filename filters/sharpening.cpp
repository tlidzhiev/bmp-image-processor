#include "sharpening.h"

namespace filter {

void Sharpening::operator()(bmp::Image& image) const {
    size_t height = image.GetHeight();
    size_t width = image.GetWidth();

    const bmp::PixelMatrix readonly_pixels = image.GetPixels();
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            auto new_pixel = convolution_kernel::ApplyKernel(kernel_, readonly_pixels, i, j);
            image.SetPixel(new_pixel, i, j);
        }
    }
}

} // filter namespace
