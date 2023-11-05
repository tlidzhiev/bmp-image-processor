#include "edge_detection.h"

#include "../exception/exception.h"

namespace filter {

Edge::Edge(const std::vector<std::string_view>& args) {
    if (required_args_ != args.size()) {
        throw my_exception::FiltersException("edge requires exactly 1 arguments");
    }

    try {
        threshold_ = std::stoi(static_cast<const std::string>(args[0]));
        if (threshold_ > bmp::kMaxColorValue) {
            throw std::exception();
        }
    } catch (...) {
        throw my_exception::FiltersException("edge requires argument between 0 and 256");
    }
}

void Edge::operator()(bmp::Image& image) const {
    size_t height = image.GetHeight();
    size_t width = image.GetWidth();

    Grayscale().operator()(image);
    const bmp::PixelMatrix readonly_pixels = image.GetPixels();
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            auto new_pixel = convolution_kernel::ApplyKernel(kernel_, readonly_pixels, i, j);
            if (new_pixel.r > threshold_) {
                new_pixel.r = bmp::kMaxColorValue;
                new_pixel.g = bmp::kMaxColorValue;
                new_pixel.b = bmp::kMaxColorValue;
            } else {
                new_pixel.r = bmp::kMinColorValue;
                new_pixel.g = bmp::kMinColorValue;
                new_pixel.b = bmp::kMinColorValue;
            }

            image.SetPixel(new_pixel, i, j);

        }
    }
}

} // filter namespace
