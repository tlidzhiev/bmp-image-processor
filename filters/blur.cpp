#include "blur.h"
#include "../exception/exception.h"

#include <cassert>
#include <cmath>
#include <numbers>

namespace filter {

GaussianBlur::GaussianBlur(const std::vector<std::string_view>& args) {
    if (required_args_ != args.size()) {
        throw my_exception::FiltersException("blur requires exactly 1 argument");
    }

    try {
        sigma_ = std::stod(static_cast<const std::string>(args[0]));
    } catch (...) {
        throw my_exception::FiltersException("invalid blur argument");;
    }

    ComputeKernel();
}

void GaussianBlur::operator()(bmp::Image& image) const {
    assert(!kernel_.empty());
    assert(!kernel_[0].empty());

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

void GaussianBlur::ComputeKernel() {
    size_t kernel_size = std::max(kMinKernelSize, static_cast<size_t>(std::ceil(kernel_coeff_ * sigma_)));
    if (kernel_size % 2 == 0) {
        --kernel_size;
    }

    double sigma_coeff = 2 * sigma_ * sigma_;
    double sum = 0.0;
    int kernel_bound = static_cast<int>(kernel_size) / 2;
    Kernel kernel(kernel_size, std::vector<double>(kernel_size, 0.0));

    for (int x = -kernel_bound; x <= kernel_bound; x++) {
        for (int y = -kernel_bound; y <= kernel_bound; y++) {
            double exponent = std::exp(-(x * x + y * y) / sigma_coeff);
            kernel[x + kernel_bound][y + kernel_bound] = exponent / (std::numbers::pi * sigma_coeff);
            sum += kernel[x + kernel_bound][y + kernel_bound];
        }
    }

    for (size_t i = 0; i < kernel_size; i++) {
        for (size_t j = 0; j < kernel_size; j++) {
            kernel[i][j] /= sum;
        }
    }

    kernel_ = std::move(kernel);
}

} // filter namespace
