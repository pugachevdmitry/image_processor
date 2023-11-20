#include <cmath>
#include <vector>
#include <cstdint>

#include "GaussianBlur.h"
#include "../DPixelArray.h"

GaussianBlur::GaussianBlur() : FilterInterface(1) {
}

Image GaussianBlur::ApplyFilter(const Image& img, const std::vector<std::string>& arguments) {
    int32_t width = img.GetWidth();
    int32_t height = img.GetHeight();
    double sigma = std::stod(arguments[0]);

    if (sigma == 0) {
        throw std::invalid_argument("Sigma is equal to zero.");
    }

    int32_t bound = std::min(std::max(img.GetWidth(), img.GetHeight()), static_cast<int32_t>(3 * sigma));

    DPixelArray tmp(height, width);
    for (int32_t row = 0; row < height; row++) {
        for (int32_t column = 0; column < width; column++) {
            Color<double> col;
            for (int32_t diff_row = -bound; diff_row <= bound; diff_row++) {
                col += ConvertColor<uint8_t, double>(img.GetNearestColor(row + diff_row, column)) /
                       std::exp(diff_row * diff_row * 1.0 / (2 * sigma * sigma));
            }
            tmp.SetColor(row, column, col);
        }
    }

    Image result(width, height);
    for (int32_t row = 0; row < height; row++) {
        for (int32_t column = 0; column < width; column++) {
            Color<double> col;
            for (int32_t diff_column = -bound; diff_column <= bound; diff_column++) {
                col += tmp.GetNearestColor(row, column + diff_column) /
                       std::exp(diff_column * diff_column * 1.0 / (2 * sigma * sigma));
            }
            col = col / (2 * M_PI * sigma * sigma);
            result.SetColor(row, column, ConvertColor<double, uint8_t>(Normalize(col)));
        }
    }

    return result;
}
