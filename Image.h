#pragma once

#include <cstdint>
#include <vector>
#include <array>

#include "PixelArray.h"

class Image {
public:
    explicit Image(std::string);

    Image(int32_t, uint32_t);

    void WriteToFile(std::string) const;

    int32_t GetWidth() const;

    int32_t GetHeight() const;

    Color<uint8_t> GetColor(const int32_t&, const int32_t&) const;

    void SetColor(const int32_t&, const int32_t&, const Color<uint8_t>&);

    Color<uint8_t> GetNearestColor(const int32_t&, const int32_t&) const;

    std::vector<std::vector<Color<uint8_t>>> GetMatrix(const int32_t&, const int32_t&, const int32_t&) const;

#pragma pack(push, 1)

    struct BMPHeader {
        uint16_t type;
        uint32_t size;
        uint16_t reserved_1;
        uint16_t reserved_2;
        uint32_t off_bits;
    };

    struct BITMAPINFOHEADER {
        uint32_t size;
        int32_t width;
        uint32_t height;
        uint16_t planes;
        uint16_t bit_count;
        uint32_t compression;
        uint32_t size_image;
        int32_t x_pels_per_meter;
        int32_t y_pels_per_meter;
        uint32_t clr_used;
        uint32_t clr_important;
    };

#pragma pack(pop)

    using DIBHeader = BITMAPINFOHEADER;

    BMPHeader bmp_header;
    DIBHeader dib_header;
    PixelArray pixel_array;
};
