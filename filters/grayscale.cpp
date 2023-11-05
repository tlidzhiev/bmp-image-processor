#include "grayscale.h"

namespace filter {

void Grayscale::operator()(bmp::Image& image) const {
    size_t height = image.GetHeight();
    size_t width = image.GetWidth();

    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            const auto& pixel = image.GetPixel(i, j);
            auto new_color = static_cast<uint8_t>(pixel.b * b_ + pixel.g * g_ + pixel.r * r_);
            bmp::Pixel new_pixel(new_color, new_color, new_color);
            image.SetPixel(new_pixel, i, j);
        }
    }
}

} // filter namespace
