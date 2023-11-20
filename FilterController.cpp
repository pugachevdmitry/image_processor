#include <iostream>
#include <stdexcept>

#include "FilterController.h"
#include "filters/Crop.h"
#include "filters/Negative.h"
#include "filters/Grayscale.h"
#include "filters/Sharpening.h"
#include "filters/Edge.h"
#include "filters/GaussianBlur.h"
#include "filters/FishEye.h"

Image FilterController::ApplyFilter(const Image& img, std::string filter_name,
                                    const std::vector<std::string>& arguments) {
    if (!filters.contains(filter_name)) {
        throw std::invalid_argument("No filter named " + filter_name);
    }
    if (arguments.size() != filters[filter_name]->arguments_cnt) {
        throw std::invalid_argument("Wrong number of arguments for filter " + filter_name);
    }
    return filters[filter_name]->ApplyFilter(img, arguments);
}

FilterController::FilterController() {
    filters["crop"] = std::make_unique<Crop>();
    filters["neg"] = std::make_unique<Negative>();
    filters["gs"] = std::make_unique<Grayscale>();
    filters["sharp"] = std::make_unique<Sharpening>();
    filters["edge"] = std::make_unique<Edge>();
    filters["blur"] = std::make_unique<GaussianBlur>();
    filters["fisheye"] = std::make_unique<FishEye>();
}