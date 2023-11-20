#pragma once

#include <cstdint>

#include "../FilterInterface.h"
#include "../MatrixFilter.h"

class GaussianBlur : virtual public FilterInterface {
public:
    GaussianBlur();

    Image ApplyFilter(const Image&, const std::vector<std::string>&) override;
};
