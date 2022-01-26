#ifndef IMAGINARY_RESIZE_HPP
#define IMAGINARY_RESIZE_HPP

#include <opencv2/opencv.hpp>

#include <cmath>

#include "config.h"

cv::Mat resize (cv::Mat const & src, cv::Mat && dest) {
    return dest = src.clone();
}

double average_gray (cv::Mat const & src, cv::Rect2d precise_area) {
    auto const & pa = precise_area;
    cv::Rect2i rounded_area (std::max (int (pa.x), 0),
                             std::max (int (pa.y), 0),
                             std::min (int (std::ceil (pa.x + pa.width)  - std::floor (pa.x)), src.cols - int (pa.x)),
                             std::min (int (std::ceil (pa.y + pa.height) - std::floor (pa.y)), src.rows - int (pa.y)));
    auto const & ra = rounded_area;
    // Trivial case: section covers 1 pixel only => return that one pixel
    if (ra.area() == 1) {
        return src.at <double> (ra.y, ra.x);
    }
    
    cv::Mat section (src, rounded_area);
    double sum = 0.0;
    
    // Simple case: Section fits without rounding (section borders align to grid
    if (pa.x == ra.x && pa.y == ra.y && pa.width == ra.width && pa.height == ra.height) {
        for (int y = 0; y < section.rows; y++) {
            auto row = section.ptr <double> (y);
            for (int x = 0; x < section.cols; x++) {
                sum += row [x];
            }
        }
        return sum / rounded_area.area();
    }
    
    // Complex case: Weighted rectangle needed
    

    return sum / precise_area.area();
}

cv::Mat resize_gray (cv::Mat const & src, cv::Mat && dest) {
    LOG_ASSERT (src.channels() == 1);
    LOG_ASSERT (dest.channels() == 1);

    if ((src.cols == dest.cols) && (src.rows == dest.rows))
        return dest = src.clone();

    double factor_x = (double) src.cols / dest.cols;
    double factor_y = (double) src.rows / dest.rows;

    for (int y = 0; y < dest.rows; y++) {
        auto dest_row = dest.ptr <double> (y);

        for (int x = 0; x < dest.cols; x++) {
            dest_row [x] = average_gray (src, cv::Rect2d (factor_x * x, factor_y * y, factor_x, factor_y));
        }
    }
    return dest;
}

#endif //IMAGINARY_RESIZE_HPP

/* Copyright (C) Aaron Alef */
