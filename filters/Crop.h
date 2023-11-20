#pragma once

#include "../FilterInterface.h"

class Crop : virtual public FilterInterface {
public:
    Crop();

    Image ApplyFilter(const Image&, const std::vector<std::string>&) override;
};
