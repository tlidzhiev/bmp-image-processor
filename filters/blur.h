#pragma once

#include "../image/image.h"
#include "convolution_kernel.h"

#include <vector>
#include <string>

namespace filter {

constexpr size_t kMinKernelSize = 3;

class GaussianBlur {
public:
    explicit GaussianBlur(const std::vector<std::string_view>& args);
    void operator()(bmp::Image& image) const;
private:
    void ComputeKernel();
    Kernel kernel_;
    const double kernel_coeff_ = 6.0;
    double sigma_ = 1.0;
    const size_t required_args_ = 1;
};

} // filter namespace
