#include <algorithm>
#include <stdexcept>

#include "PixelArray.h"

PixelArray::PixelArray(int32_t width, uint32_t height, const std::span<char> file)
    : width_(width), height_(static_cast<int32_t>(height)), pixels_(height) {
    // TODO: catch invalid argument -- file.size() % 4 != 0
    int file_ptr = 0;
    const int32_t paddings_in_row = GetPaddingsInRow();
    for (size_t row = 0; row < height; row++) {
        pixels_[row].resize(width);
        for (size_t column = 0; column < width; column++) {
            pixels_[row][column] = Color<uint8_t>(file[file_ptr], file[file_ptr + 1], file[file_ptr + 2]);
            file_ptr += 3;
        }
        file_ptr += paddings_in_row;
    }
}

PixelArray::PixelArray() {
    height_ = width_ = 0;
}

int32_t PixelArray::GetPaddingsInRow() const {
    return (ROW_ALIGN - (CELL_SIZE * GetWidth()) % ROW_ALIGN) % ROW_ALIGN;
}

int32_t PixelArray::GetWidth() const {
    return width_;
}

Color<uint8_t> PixelArray::GetColor(size_t row, size_t column) const {
    return pixels_[row][column];
}

uint32_t PixelArray::GetSizeInBytes() const {
    return (GetWidth() * CELL_SIZE + GetPaddingsInRow()) * GetHeight();
}

int32_t PixelArray::GetHeight() const {
    return height_;
}

PixelArray::PixelArray(int32_t width, int32_t height) : width_(width), height_(height) {
    pixels_.resize(height_);
    std::for_each(pixels_.begin(), pixels_.end(), [this](std::vector<Color<uint8_t>>& row) { row.resize(width_); });
}

void PixelArray::SetColor(size_t row, size_t column, Color<uint8_t> col) {
    if (row >= GetHeight() || column >= GetWidth()) {
        throw std::runtime_error("Out of bounds.");
    }
    pixels_[row][column] = col;
}

Color<uint8_t> PixelArray::GetNearestColor(const int32_t& row, const int32_t& column) const {
    if (GetHeight() == 0 || GetWidth() == 0) {
        throw std::runtime_error("Empty image");
    }
    return GetColor(std::min(GetHeight() - 1, std::max(0, row)), std::min(GetWidth() - 1, std::max(0, column)));
}