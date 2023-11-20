#pragma once

#include <vector>
#include <span>
#include <fstream>
#include <cstdint>

#include "Color.h"

class DPixelArray {
public:
    DPixelArray();

    DPixelArray(int32_t, int32_t);

    int32_t GetWidth() const;

    int32_t GetHeight() const;

    Color<double> GetColor(size_t, size_t) const;

    Color<double> GetNearestColor(const int32_t&, const int32_t&) const;

    void SetColor(size_t, size_t, Color<double>);

private:
    int32_t width_;
    int32_t height_;
    std::vector<std::vector<Color<double>>> pixels_;
};
