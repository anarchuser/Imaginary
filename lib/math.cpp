#include "math.hpp"

long long ceil_e (double val) {
    if (std::abs (val - std::floor (val)) < EPSILON) return std::floor (val);
    return std::ceil (val);
}

/* Copyright (C) Aaron Alef */
