#ifndef IMAGINARY_DEVIATION_HPP
#define IMAGINARY_DEVIATION_HPP

#include "config.h"

#include "bgr_t.hpp"
#include "deviation.hpp"

#include <cmath>

using Deviation = std::pair <double, double>;

Deviation deviation (cv::Mat const & original, cv::Mat const & comparee) {
    // TODO: resize comparee to fit original

    auto area = original.cols * original.rows;
    double sum = 0.0;
    double max = 0.0;
    for (int y = 0; y < original.rows && y < comparee.rows; y++) {
        auto orow = original.ptr<Color_BGR> (y);
        auto drow = comparee.ptr<Color_BGR> (y);

        for (int x = 0; x < original.cols && comparee.cols; x++) {
            double dev = abs (orow [x].red() - drow [x].red());
            dev += abs (orow [x].green() - drow [x].green());
            dev += abs (orow [x].blue() - drow [x].blue());
            sum += dev;
            max = std::max (max, dev);
        }
    }
    return Deviation (sum / area / 3, max);
}

/// Returns a pair ov average and max
Deviation deviation_gray (cv::Mat const & original, cv::Mat const & comparee) {
    auto modified = resize (comparee, cv::Mat (original.rows, original.cols, CV_64FC1));
    
    auto area = original.cols * original.rows;
    double sum = 0.0;
    double max = 0.0;
    for (int y = 0; y < original.rows && y < modified.rows; y++) {
        auto orow = original.ptr <double> (y);
        auto drow = modified.ptr <double> (y);

        for (int x = 0; x < original.cols && x < modified.cols; x++) {
            double dev = abs (orow [x] - drow [x]);
            sum += dev;
            max = std::max (max, dev);
        }
    }
    return Deviation (sum / area, max);
}

std::ostream & operator << (std::ostream & os, Deviation dev) {
    return os << "average " << dev.first << " / max: " << dev.second;
}

#endif //IMAGINARY_DEVIATION_HPP

/* Copyright (C) Aaron Alef */
