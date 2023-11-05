#pragma once

#include "../image/image.h"

#include <vector>
#include <string>

namespace filter {

class Grayscale {
public:
    void operator()(bmp::Image& image) const;
private:
    const double r_ = 0.299;
    const double g_ = 0.587;
    const double b_ = 0.114;
};

} // filter namespace
