#pragma once

#include <array>

#include "../FilterInterface.h"
#include "../MatrixFilter.h"

class Edge : virtual public FilterInterface, public MatrixFilter<int32_t> {
public:
    Edge();

    Image ApplyFilter(const Image&, const std::vector<std::string>&) override;
};
