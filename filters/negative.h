#pragma once

#include "../image/image.h"

#include <vector>
#include <string>

namespace filter {

class Negative {
public:
    void operator()(bmp::Image& image) const;
};

} // filter namespace
