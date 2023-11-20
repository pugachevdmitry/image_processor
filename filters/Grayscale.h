#pragma once

#include "../FilterInterface.h"

class Grayscale : virtual public FilterInterface {
public:
    Grayscale();

    Image ApplyFilter(const Image&, const std::vector<std::string>&) override;
};
