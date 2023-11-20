#include <cmath>

#include "FishEye.h"

bool IsPosGood(int32_t pos, int32_t size) {
    return 0 <= pos && pos < size;
}

Image FishEye::ApplyFilter(const Image& img, const std::vector<std::string>& arguments) {
    int32_t width = img.GetWidth();
    int32_t height = img.GetHeight();

    Image result(width, height);
    for (int32_t row = 0; row < height; row++) {
        for (int32_t column = 0; column < width; column++) {
            double row_normalized = (1.0 * (2 * row) / height) - 1;
            double column_normalized = (1.0 * (2 * column) / width) - 1;
            double radius = sqrt(row_normalized * row_normalized + column_normalized * column_normalized);
            if (radius <= 1) {
                double new_radius = (radius + (1 - sqrt(1 - radius * radius))) / 2;
                if (new_radius <= 1) {
                    double theta = std::atan2(column_normalized, row_normalized);
                    int32_t new_row = static_cast<int32_t>(((new_radius * std::cos(theta) + 1) * height) / 2);
                    int32_t new_column = static_cast<int32_t>(((new_radius * std::sin(theta) + 1) * width) / 2);
                    if (IsPosGood(new_row, height) && IsPosGood(new_column, width)) {
                        result.SetColor(row, column, img.GetColor(new_row, new_column));
                    }
                }
            }
        }
    }

    for (int32_t row = 0; row < height; row++) {
        for (int32_t column = 0; column < width; column++) {
            if (IsBlack(result.GetColor(row, column))) {
                result.SetColor(row, column, img.GetColor(row, column));
            }
        }
    }

    return result;
}

FishEye::FishEye() : FilterInterface(0) {
}
