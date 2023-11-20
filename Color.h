#pragma once

#include <cstdint>
#include <concepts>
#include <cmath>
#include <vector>
#include <stdexcept>

template <typename T>
concept arithmetic = std::integral<T> or std::floating_point<T>;

constexpr double BlueCoeff = 0.114;
constexpr double GreenCoeff = 0.587;
constexpr double RedCoeff = 0.299;
constexpr int32_t MaxIntegralVal = 255;

template <arithmetic T>
class Color {
public:
    Color();

    Color(const T&, const T&, const T&);

    void SetValue(const T&);

    T blue;
    T green;
    T red;
};

template <arithmetic T>
void Color<T>::SetValue(const T& val) {
    blue = green = red = val;
}

template <arithmetic T>
Color<T>::Color(const T& blue, const T& green, const T& red) : blue(blue), green(green), red(red) {
}

template <arithmetic T>
Color<T>::Color() : blue(0), green(0), red(0) {
}

template <std::floating_point T>
T GetMax() {
    return static_cast<T>(1);
}

template <std::integral T>
T GetMax() {
    return static_cast<T>(MaxIntegralVal);
}

template <arithmetic T>
T GetMin() {
    return static_cast<T>(0);
}

template <arithmetic T>
Color<T> Normalize(const Color<T>& col) {
    Color<T> result;
    result.blue = std::max(GetMin<T>(), std::min(GetMax<T>(), col.blue));
    result.green = std::max(GetMin<T>(), std::min(GetMax<T>(), col.green));
    result.red = std::max(GetMin<T>(), std::min(GetMax<T>(), col.red));
    return result;
}

template <arithmetic T>
Color<T> GetNegative(const Color<T>& col) {
    return Color<T>(std::numeric_limits<T>::max() - col.blue, std::numeric_limits<T>::max() - col.green,
                    std::numeric_limits<T>::max() - col.red);
}

template <arithmetic T>
Color<T> GetGrayscale(const Color<T>& col) {
    int32_t new_value =
        static_cast<int32_t>(std::round(RedCoeff * col.red + GreenCoeff * col.green + BlueCoeff * col.blue));
    Color<T> result;
    result.SetValue(new_value);
    return result;
}

template <arithmetic T>
Color<T> operator*(const Color<T>& col, const int32_t& mul) {
    return Color<T>(col.blue * mul, col.green * mul, col.red * mul);
}

template <std::integral From, std::floating_point To>
Color<To> ConvertColor(const Color<From>& col) {
    Color<To> result;
    result.blue = static_cast<To>(col.blue) / static_cast<To>(GetMax<From>());
    result.green = static_cast<To>(col.green) / static_cast<To>(GetMax<From>());
    result.red = static_cast<To>(col.red) / static_cast<To>(GetMax<From>());
    return result;
}

template <std::floating_point From, std::integral To>
Color<To> ConvertColor(const Color<From>& col) {
    Color<To> result;
    result.blue = std::round(col.blue * static_cast<From>(GetMax<To>()));
    result.green = std::round(col.green * static_cast<From>(GetMax<To>()));
    result.red = std::round(col.red * static_cast<From>(GetMax<To>()));
    return result;
}

template <std::integral From, std::integral To>
Color<To> ConvertColor(const Color<From>& col) {
    Color<To> result;
    result.blue = static_cast<To>(col.blue);
    result.green = static_cast<To>(col.green);
    result.red = static_cast<To>(col.red);
    return result;
}

template <arithmetic T>
Color<T> operator+=(Color<T>& lhs, const Color<T>& rhs) {
    lhs.blue += rhs.blue;
    lhs.green += rhs.green;
    lhs.red += rhs.red;
    return lhs;
}

template <arithmetic T, arithmetic U>
Color<T> ApplyMatrix(const std::vector<std::vector<Color<T>>>& col, const std::vector<std::vector<U>>& matrix) {
    if (col.size() != matrix.size() || col.size() % 2 == 0 || col[0].size() != matrix[0].size() ||
        col[0].size() % 2 == 0) {
        throw std::invalid_argument("Invalid size of matrix");
    }

    Color<U> result;

    for (int32_t row = 0; row < col.size(); ++row) {
        for (int32_t column = 0; column < col[row].size(); ++column) {
            result += ConvertColor<T, U>(col[row][column]) * matrix[row][column];
        }
    }

    return ConvertColor<U, T>(Normalize<U>(result));
}

template <arithmetic T>
bool IsBlack(const Color<T>& col) {
    return col.blue == GetMin<T>() && col.green == GetMin<T>() && col.red == GetMin<T>();
}

Color<double> operator/(const Color<double>& col, const double& div);
