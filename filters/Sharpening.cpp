#include <cstdint>

#include "Sharpening.h"

const int32_t MIDDLE_COEFF = 5;

Sharpening::Sharpening() : FilterInterface(0), MatrixFilter({{0, -1, 0}, {-1, MIDDLE_COEFF, -1}, {0, -1, 0}}) {
}

Image Sharpening::ApplyFilter(const Image& img, const std::vector<std::string>& arguments) {
    int32_t width = img.GetWidth();
    int32_t height = img.GetHeight();

    Image result(width, height);
    for (int32_t row = 0; row < height; row++) {
        for (int32_t column = 0; column < width; column++) {
            result.SetColor(row, column, ApplyMatrix<uint8_t, int32_t>(img.GetMatrix(row, column, 1), matrix));
        }
    }

    return result;
}
