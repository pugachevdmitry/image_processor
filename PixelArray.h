#pragma once

#include <vector>
#include <span>
#include <fstream>
#include <cstdint>

#include "Color.h"

class PixelArray {
public:
    static const int32_t ROW_ALIGN = 4;
    static const int32_t CELL_SIZE = 3;

    PixelArray();

    PixelArray(int32_t, int32_t);

    PixelArray(int32_t, uint32_t, const std::span<char>);

    int32_t GetWidth() const;

    int32_t GetHeight() const;

    int32_t GetPaddingsInRow() const;

    Color<uint8_t> GetColor(size_t, size_t) const;

    void SetColor(size_t, size_t, Color<uint8_t>);

    uint32_t GetSizeInBytes() const;

    Color<uint8_t> GetNearestColor(const int32_t&, const int32_t&) const;

private:
    int32_t width_;
    int32_t height_;
    std::vector<std::vector<Color<uint8_t>>> pixels_;
};
