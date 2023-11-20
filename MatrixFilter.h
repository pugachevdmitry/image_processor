#pragma once

#include <vector>
#include <cstdint>
#include <concepts>
#include "Color.h"

template <arithmetic T>
class MatrixFilter {
public:
    std::vector<std::vector<T>> matrix;

    MatrixFilter(const int32_t&, const int32_t&);

    explicit MatrixFilter(const std::vector<std::vector<T>>&);
};

template <arithmetic T>
MatrixFilter<T>::MatrixFilter(const std::vector<std::vector<T>>& matrix) : matrix(matrix) {
}

template <arithmetic T>
MatrixFilter<T>::MatrixFilter(const int32_t& height, const int32_t& width) {
    matrix.assign(height, std::vector<T>(width));
}
