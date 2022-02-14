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
    auto dest = src.clone();

    unsigned char _min = 255;
    unsigned char _max = 0;
    for (int y = 0; y < src.rows; y++) {
        auto row = src.ptr <Color_BGR> (y);

        for (int x = 0; x < src.cols; x++) {
            for (auto const color : row [x]) {
                _min = std::min (color, _min);
                _max = std::max (color, _max);
            }
        }
    }

    double factor = double (max) / (_max - _min + min);
    for (int y = 0; y < src.rows; y++) {
        auto row = dest.ptr <Color_BGR> (y);

        for (int x = 0; x < src.cols; x++) {
            for (auto & color : row [x]) {
                color = factor * (color + min - _min);
            }
        }
    }

    return dest;
}

cv::Mat scale_gray (cv::Mat const & src, unsigned char min, unsigned char max) {
    auto dest = src.clone();

    double _min = 255;
    double _max = 0;
    for (int y = 0; y < src.rows; y++) {
        auto row = src.ptr <double> (y);

        for (int x = 0; x < src.cols; x++) {
            _min = std::min (row [x], _min);
            _max = std::max (row [x], _max);
        }
    }

    double factor = double (max) / (_max - _min + min);
    for (int y = 0; y < src.rows; y++) {
        auto drow = dest.ptr <double> (y);

        for (int x = 0; x < src.cols; x++) {
            drow [x] = factor * (drow [x] + min - _min);
        }
    }

    return dest;
}

cv::Mat scale_gray2 (cv::Mat const & src, unsigned char min, unsigned char max) {
    auto dest = src.clone();

    int _min = 255;
    int _max = 0;
    for (int y = 0; y < src.rows; y++) {
        auto row = src.ptr <int> (y);

        for (int x = 0; x < src.cols; x++) {
            _min = std::min (row [x], _min);
            _max = std::max (row [x], _max);
        }
    }

    double factor = double (max) / (_max - _min + min);
    for (int y = 0; y < src.rows; y++) {
        auto drow = dest.ptr <int> (y);

        for (int x = 0; x < src.cols; x++) {
            drow [x] = factor * (drow [x] + min - _min);
        }
    }

    return dest;
}

/* Copyright (C) Aaron Alef */
