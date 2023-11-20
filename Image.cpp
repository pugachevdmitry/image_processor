#include "Image.h"

#include <fstream>
#include <span>
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <memory>

Image::Image(std::string path_to_file) {
    try {
        std::ifstream input(path_to_file, std::ifstream::binary | std::ifstream::in);
        input.seekg(0, input.end);
        std::streamsize length = input.tellg();
        if (length < sizeof bmp_header + sizeof dib_header) {
            throw std::invalid_argument("Bad file.");
        }
        input.seekg(0, input.beg);
        std::unique_ptr<char[]> buffer = std::make_unique<char[]>(length);
        input.read(buffer.get(), length);
        std::memcpy(&this->bmp_header, buffer.get(), sizeof bmp_header);
        std::memcpy(&this->dib_header, buffer.get() + sizeof bmp_header, sizeof dib_header);
        pixel_array = PixelArray(dib_header.width, dib_header.height,
                                 std::span{buffer.get() + sizeof(bmp_header) + sizeof(dib_header),
                                           length - sizeof(bmp_header) - sizeof(dib_header)});
        input.close();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

void Image::WriteToFile(std::string file) const {
    try {
        std::ofstream out_file(file, std::ofstream::out | std::ofstream::binary);
        uint32_t length = bmp_header.size;
        std::unique_ptr<char[]> buffer = std::make_unique<char[]>(length);
        std::memcpy(buffer.get(), &bmp_header, sizeof bmp_header);
        std::memcpy(buffer.get() + sizeof bmp_header, &dib_header, sizeof dib_header);
        int32_t ptr = sizeof bmp_header + sizeof dib_header;
        const int32_t paddings_in_row = pixel_array.GetPaddingsInRow();
        for (size_t row = 0; row < GetHeight(); row++) {
            for (size_t column = 0; column < GetWidth(); column++) {
                auto pixel = pixel_array.GetColor(row, column);
                buffer[ptr++] = static_cast<char>(pixel.blue);
                buffer[ptr++] = static_cast<char>(pixel.green);
                buffer[ptr++] = static_cast<char>(pixel.red);
            }
            for (int32_t padding = 0; padding < paddings_in_row; padding++) {
                buffer[ptr++] = 0;
            }
        }
        out_file.write(buffer.get(), length);

        out_file.close();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

int32_t Image::GetWidth() const {
    return dib_header.width;
}

int32_t Image::GetHeight() const {
    if (dib_header.height < 0) {
        return static_cast<int32_t>(-dib_header.height);
    }
    return static_cast<int32_t>(dib_header.height);
}

Image::Image(int32_t width, uint32_t height) {
    pixel_array = PixelArray(width, static_cast<int32_t>(height));
    bmp_header = {19778, 54 + pixel_array.GetSizeInBytes(), 0, 0, 54};                             // NOLINT
    dib_header = {40, width, height, 1, 24, 0, pixel_array.GetSizeInBytes(), 11811, 11811, 0, 0};  // NOLINT
}

Color<uint8_t> Image::GetColor(const int32_t& row, const int32_t& column) const {
    return pixel_array.GetColor(row, column);
}

void Image::SetColor(const int32_t& row, const int32_t& column, const Color<uint8_t>& col) {
    pixel_array.SetColor(row, column, col);
}

Color<uint8_t> Image::GetNearestColor(const int32_t& row, const int32_t& column) const {
    return pixel_array.GetNearestColor(row, column);
}

std::vector<std::vector<Color<uint8_t>>> Image::GetMatrix(const int32_t& row, const int32_t& column,
                                                          const int32_t& size) const {
    std::vector result(2 * size + 1, std::vector<Color<uint8_t>>(2 * size + 1));
    for (int32_t diff_row = -size; diff_row <= size; ++diff_row) {
        for (int32_t diff_column = -size; diff_column <= size; ++diff_column) {
            result[size + diff_row][size + diff_column] = GetNearestColor(row + diff_row, column + diff_column);
        }
    }

    return result;
}
