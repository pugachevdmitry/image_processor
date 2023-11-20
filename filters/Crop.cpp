#include <cstdint>

#include "Crop.h"

Image Crop::ApplyFilter(const Image& img, const std::vector<std::string>& arguments) {
    int32_t width = std::min(std::stoi(arguments[0]), img.GetWidth());
    int32_t height = std::min(std::stoi(arguments[1]), img.GetHeight());
    Image result(width, height);
    for (int32_t row = 0; row < height; row++) {
        for (int32_t column = 0; column < width; column++) {
            result.SetColor(row, column, img.GetColor(img.GetHeight() - height + row, column));
        }
    }

    return result;
}

Crop::Crop() : FilterInterface(2) {
}
