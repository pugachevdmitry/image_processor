#pragma once

#include <map>
#include <memory>

#include "FilterInterface.h"
#include "Image.h"

class FilterController {
public:
    std::map<std::string, std::unique_ptr<FilterInterface>> filters;

    FilterController();

    Image ApplyFilter(const Image&, std::string, const std::vector<std::string>&);
};
