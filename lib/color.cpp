#include "color.hpp"

cv::Mat component (cv::Mat const & src, Color component) {
    LOG_ASSERT (src.channels() == 3);

    cv::Mat dest (src.rows, src.cols, CV_8UC1);

    for (int y = 0; y < src.rows; y++) {
        auto srow = src.ptr <Color_BGR> (y);
        auto drow = dest.ptr <unsigned char> (y);

        for (int x = 0; x < src.cols; x++) {
            drow [x] = srow [x].component (component);
        }
    }
    return dest;
}

/* Copyright (C) Aaron Alef */
