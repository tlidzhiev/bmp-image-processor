#pragma once

#include "crop.h"
#include "grayscale.h"
#include "negative.h"
#include "sharpening.h"
#include "edge_detection.h"
#include "blur.h"
#include "../image/image.h"
#include "../command-parser/parser.h"

#include <string_view>
#include <variant>
#include <vector>

namespace filter {

using Filter = std::variant<Crop, Grayscale, Negative, Sharpening, Edge, GaussianBlur>;

constexpr std::string_view kFilterCropName = "-crop";
constexpr std::string_view kFilterGrayscaleName = "-gs";
constexpr std::string_view kFilterNegativeName = "-neg";
constexpr std::string_view kFilterSharpeningName = "-sharp";
constexpr std::string_view kFilterEdgeDetectionName = "-edge";
constexpr std::string_view kFilterGaussianBlurName = "-blur";

enum class FiltersList : unsigned char {
    None,
    Crop,
    Grayscale,
    Negative,
    Sharpening,
    EdgeDetection,
    GaussianBlur,
};

FiltersList GetFilter(std::string_view filter_name);
void ApplyFilters(const std::vector<command_parser::FilterArgs>& filters, bmp::Image& image);

} // filter namespace
