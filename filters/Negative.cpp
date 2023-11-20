#include <cstdint>

#include "Negative.h"

Image Negative::ApplyFilter(const Image& img, const std::vector<std::string>& arguments) {
    int32_t width = img.GetWidth();
    int32_t height = img.GetHeight();

    Image result(width, height);
    for (int32_t row = 0; row < height; row++) {
        for (int32_t column = 0; column < width; column++) {
            result.SetColor(row, column, GetNegative(img.GetColor(row, column)));
        }
    }

    return result;
}

Negative::Negative() : FilterInterface(0) {
}
