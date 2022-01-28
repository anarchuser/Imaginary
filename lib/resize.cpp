#include "resize.hpp"

cv::Mat resize (cv::Mat const & src, cv::Mat && dest) {
    return dest = src.clone();
}

double average_gray (cv::Mat const & src, cv::Rect2d precise_area) {
    static int c = 0;
    
    auto const & pa = precise_area;
    cv::Rect2i rounded_area (std::max (int (pa.x), 0),
                             std::max (int (pa.y), 0),
                             std::min (int (std::ceil (pa.x + pa.width)  - std::floor (pa.x)), src.cols - int (pa.x)),
                             std::min (int (std::ceil (pa.y + pa.height) - std::floor (pa.y)), src.rows - int (pa.y)));
    auto const & ra = rounded_area;
    cv::Mat section (src, rounded_area);
    double sum = 0.0;
    
    // Trivial case: section covers 1 pixel only => return that one pixel
    if (ra.area() == 1) {
        sum = src.at <double> (ra.y, ra.x);
        if (c > 0) {
            std::cout << "Trivial case : " << sum << std::endl;
        }
    }

    // Simple case: Section fits without rounding (section borders align to grid
    else if (pa.x == ra.x && pa.y == ra.y && pa.width == ra.width && pa.height == ra.height) {
        for (int y = 0; y < section.rows; y++) {
            auto row = section.ptr <double> (y);
            for (int x = 0; x < section.cols; x++) {
                sum += row [x];
            }
        }
        sum /= ra.area();
        if (c > 0) {
            std::cout << "Simple case : " << sum << std::endl;
        }
    }
    
    // Complex case: Weighted rectangle needed
    else {
        double lower_x_weight = (std::ceil (pa.x) - pa.x) ?: 1;
        double lower_y_weight = (std::ceil (pa.y) - pa.y) ?: 1;
        double upper_x_weight = (pa.x + pa.width  - std::floor (pa.x + pa.width))  ?: 1;
        double upper_y_weight = (pa.y + pa.height - std::floor (pa.y + pa.height)) ?: 1;

        for (int y = 0; y < section.rows; y++) {
            auto     row = section.ptr <double> (y);
            for (int x   = 0; x < section.cols; x++) {
                double weight = 1.0;
                if (x == 0) weight *= lower_x_weight;
                if (y == 0) weight *= lower_y_weight;
                if (x == section.cols - 1) weight *= upper_x_weight;
                if (y == section.rows - 1) weight *= upper_y_weight;
                sum += weight * row[x];
            }
        }
        sum /= precise_area.area();
        if (c > 0) {
            std::cout << "Complex case : " << sum << std::endl;
            std::cout << "weights: " << lower_x_weight << " / " << lower_y_weight << " // "
                      << upper_x_weight << " / " << upper_y_weight << std::endl;
        }
    }
    
    if (c > 0) {
        std::cout << "Section: " << section << std::endl;
        std::cout << "Precise: " << pa << std::endl;
        std::cout << "Rounded: " << ra << '\n' << std::endl;
        c--;
    }
    
    return sum;
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

/* Copyright (C) Aaron Alef */
