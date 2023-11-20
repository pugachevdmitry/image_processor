#include <stdexcept>

#include "DPixelArray.h"

DPixelArray::DPixelArray() {
    height_ = width_ = 0;
}

int32_t DPixelArray::GetWidth() const {
    return width_;
}

Color<double> DPixelArray::GetColor(size_t row, size_t column) const {
    return pixels_[row][column];
}

int32_t DPixelArray::GetHeight() const {
    return height_;
}

DPixelArray::DPixelArray(int32_t width, int32_t height) : width_(width), height_(height) {
    pixels_.resize(height);
    std::for_each(pixels_.begin(), pixels_.end(), [this](std::vector<Color<double>>& row) { row.resize(width_); });
}

void DPixelArray::SetColor(size_t row, size_t column, Color<double> col) {
    if (row >= GetHeight() || column >= GetWidth()) {
        throw std::runtime_error("Out of bounds.");
    }
    pixels_[row][column] = col;
}

Color<double> DPixelArray::GetNearestColor(const int32_t& row, const int32_t& column) const {
    if (GetHeight() == 0 || GetWidth() == 0) {
        throw std::runtime_error("Empty image");
    }
    return GetColor(std::min(GetHeight() - 1, std::max(0, row)), std::min(GetWidth() - 1, std::max(0, column)));
}
