#ifndef IMAGINARY_DEVIATION_HPP
#define IMAGINARY_DEVIATION_HPP

#include "config.h"

#include "bgr_t.hpp"
#include "resize.hpp"
#include "grayify.hpp"

#include <cmath>

using Deviation = std::pair <double, double>;

Deviation deviation (cv::Mat const & original, cv::Mat const & comparee);

/// Returns a pair ov average and max
Deviation deviation_gray (cv::Mat const & original, cv::Mat const & comparee);

std::ostream & operator << (std::ostream & os, Deviation dev);

#endif //IMAGINARY_DEVIATION_HPP

/* Copyright (C) Aaron Alef */
