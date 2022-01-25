#ifndef IMAGINARY_DEVIATION_HPP
#define IMAGINARY_DEVIATION_HPP

#include "config.h"

#include <cmath>

double deviation (cv::Mat const & original, cv::Mat const & comparee) {
    // TODO: resize comparee to fit original

    auto area = original.cols * original.rows;
    double sum = 0.0;
    for (int y = 0; y < original.rows && y < comparee.rows; y++) {
        auto orow = original.ptr<Color_BGR> (y);
        auto drow = comparee.ptr<Color_BGR> (y);

        for (int x = 0; x < original.cols && comparee.cols; x++) {
            sum += abs (orow [x].red() - drow [x].red());
            sum += abs (orow [x].green() - drow [x].green());
            sum += abs (orow [x].blue() - drow [x].blue());
        }
    }
    return sum / area / 3;
}

double deviation_gray (cv::Mat const & original, cv::Mat const & comparee) {
    // TODO: resize comparee to fit original

    auto area = original.cols * original.rows;
    double sum = 0.0;
    for (int y = 0; y < original.rows && y < comparee.rows; y++) {
        auto orow = original.ptr<double> (y);
        auto drow = comparee.ptr<double> (y);

        for (int x = 0; x < original.cols && comparee.cols; x++) {
            sum += abs (orow [x] - drow [x]);
        }
    }
    return sum / area;
}

#endif //IMAGINARY_DEVIATION_HPP

/* Copyright (C) Aaron Alef */
