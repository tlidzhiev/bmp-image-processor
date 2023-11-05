#include "negative.h"

namespace filter {

void Negative::operator()(bmp::Image& image) const {
    size_t height = image.GetHeight();
    size_t width = image.GetWidth();

    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            const auto& pixel = image.GetPixel(i, j);
            bmp::Pixel new_pixel(
                bmp::kMaxColorValue - pixel.b,
                bmp::kMaxColorValue - pixel.g,
                bmp::kMaxColorValue - pixel.r
            );

            image.SetPixel(new_pixel, i, j);
        }
    }
}

} // filter namespace
