#pragma once

#include "../FilterInterface.h"

class FishEye : virtual public FilterInterface {
public:
    FishEye();

    Image ApplyFilter(const Image&, const std::vector<std::string>&) override;
};
