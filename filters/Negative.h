#pragma once

#include "../FilterInterface.h"

class Negative : virtual public FilterInterface {
public:
    Negative();

    Image ApplyFilter(const Image&, const std::vector<std::string>&) override;
};
