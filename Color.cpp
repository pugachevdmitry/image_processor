#include "Color.h"

Color<double> operator/(const Color<double>& col, const double& div) {
    return Color<double>(col.blue / div, col.green / div, col.red / div);
}