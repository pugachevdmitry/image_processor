#include <cstdint>
#include <cmath>

#include "Edge.h"
#include "Grayscale.h"

Edge::Edge() : FilterInterface(1), MatrixFilter({{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}}) {
}

Image Edge::ApplyFilter(const Image& img, const std::vector<std::string>& arguments) {
    int32_t width = img.GetWidth();
    int32_t height = img.GetHeight();
    int32_t threshold = static_cast<int32_t>(std::round(stod(arguments[0]) * GetMax<uint8_t>()));

    Grayscale grayscale_filter = Grayscale();
    Image grayscale_img = grayscale_filter.ApplyFilter(img, {});

    Image result(width, height);
    for (int32_t row = 0; row < height; row++) {
        for (int32_t column = 0; column < width; column++) {
            Color<uint8_t> col = ApplyMatrix<uint8_t, int32_t>(grayscale_img.GetMatrix(row, column, 1), matrix);
            if (col.green > threshold) {
                col.SetValue(GetMax<uint8_t>());
            } else {
                col.SetValue(GetMin<uint8_t>());
            }
            result.SetColor(row, column, col);
        }
    }

    return result;
}
