#pragma once

#include "../image/image.h"
#include "grayscale.h"
#include "convolution_kernel.h"

#include <vector>

namespace filter {

class Edge {
public:
    explicit Edge(const std::vector<std::string_view>& params);
    void operator()(bmp::Image& image) const;
private:
    const Kernel kernel_ = {{0.0, -1.0, 0.0}, {-1.0, 4.0, -1.0}, {0.0, -1.0, 0.0}};
    int threshold_ = 0;
    const size_t required_args_ = 1;
};

} // filter namespace
