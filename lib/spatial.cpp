#include "spatial.hpp"

cv::Mat intensity_scale (cv::Mat const & src, Color_BGR (lambda) (Color_BGR)) {
    auto dest = src.clone();
    for (int y = 0; y < src.rows; y++) {
        auto srow = src.ptr <Color_BGR> (y);
        auto drow = dest.ptr <Color_BGR> (y);
        
        for (int x = 0; x < src.cols; x++) {
            drow [x] = lambda (srow [x]);
        }
    }
    return dest;
}

cv::Mat intensity_scale (cv::Mat const & src, double (lambda) (double)) {
    auto dest = src.clone();
    for (int y = 0; y < src.rows; y++) {
        auto srow = src.ptr <double> (y);
        auto drow = dest.ptr <double> (y);
        
        for (int x = 0; x < src.cols; x++) {
            drow [x] = lambda (srow [x]);
        }
    }
    return dest;
}

cv::Mat scale (cv::Mat const & src, unsigned char min, unsigned char max) {
    return src;
}

cv::Mat scale_gray (cv::Mat const & src, unsigned char min, unsigned char max) {
    return src;
}

/* Copyright (C) Aaron Alef */