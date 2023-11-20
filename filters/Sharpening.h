#pragma once

#include <array>

#include "../FilterInterface.h"
#include "../MatrixFilter.h"

class Sharpening : virtual public FilterInterface, public MatrixFilter<int32_t> {
public:
    Sharpening();

    Image ApplyFilter(const Image&, const std::vector<std::string>&) override;
};
