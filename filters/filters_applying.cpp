#include "filters_applying.h"

#include "../exception/exception.h"

namespace filter {

FiltersList GetFilter(std::string_view filter_name) {
    if (filter_name == kFilterCropName) {
        return FiltersList::Crop;
    } else if (filter_name == kFilterGrayscaleName) {
        return FiltersList::Grayscale;
    } else if (filter_name == kFilterNegativeName) {
        return FiltersList::Negative;
    } else if (filter_name == kFilterSharpeningName) {
        return FiltersList::Sharpening;
    } else if (filter_name == kFilterEdgeDetectionName) {
        return FiltersList::EdgeDetection;
    } else if (filter_name == kFilterGaussianBlurName) {
        return FiltersList::GaussianBlur;
    }

    return FiltersList::None;
}

void ApplyFilters(const std::vector<command_parser::FilterArgs>& filters, bmp::Image& image) {
    std::vector<Filter> requested_filters;

    for (const auto& filter : filters) {
        switch (GetFilter(filter.name)) {
            case FiltersList::Crop: {
                requested_filters.emplace_back(Crop(filter.args));
                continue;
            }
            case FiltersList::Grayscale: {
                requested_filters.emplace_back(Grayscale());
                continue;
            }
            case FiltersList::Negative: {
                requested_filters.emplace_back(Negative());
                continue;
            }
            case FiltersList::Sharpening: {
                requested_filters.emplace_back(Sharpening());
                continue;
            }
            case FiltersList::EdgeDetection: {
                requested_filters.emplace_back(Edge(filter.args));
                continue;
            }
            case FiltersList::GaussianBlur: {
                requested_filters.emplace_back(GaussianBlur(filter.args));
                continue;
            }
            default: throw my_exception::FiltersException("Unknown filter name");
        }
    }

    auto caller = [&image](const auto& f) { f(image); };
    for (const Filter& requested_filter : requested_filters) {
        std::visit(caller, requested_filter);
    }
}

} // filter namespace
