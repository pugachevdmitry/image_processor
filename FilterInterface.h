#pragma once

#include <cstdint>

#include "Image.h"

class FilterInterface {
public:
    virtual Image ApplyFilter(const Image&, const std::vector<std::string>&) = 0;

    virtual ~FilterInterface() = default;

    explicit FilterInterface(int32_t);

    int32_t arguments_cnt;
};
