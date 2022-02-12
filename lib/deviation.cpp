#include "deviation.hpp"

Deviation deviation (cv::Mat const & original, cv::Mat const & comparee) {
    auto modified = resize (comparee, cv::Mat (original.rows, original.cols, CV_8UC3));

    auto area = original.cols * original.rows;
    double sum = 0.0;
    double max = 0.0;
    for (int y = 0; y < original.rows && y < modified.rows; y++) {
        auto orow = original.ptr<Color_BGR> (y);
        auto drow = modified.ptr<Color_BGR> (y);

        for (int x = 0; x < original.cols && modified.cols; x++) {
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
    // make comparee gray, if needed
    auto gray = comparee.channels() == 1 ? comparee : grayify (comparee);

    // let comparee match size of original
    auto modified = resize_gray (gray, cv::Mat (original.rows, original.cols, CV_64FC1));
    
    auto area = original.cols * original.rows;
    double sum = 0.0;
    double max = 0.0;

    for (int y = 0; y < original.rows && y < modified.rows; y++) {
        auto orow = original.ptr <double> (y);
        auto mrow = modified.ptr <double> (y);

        for (int x = 0; x < original.cols && x < modified.cols; x++) {
            double dev = abs (orow [x] - mrow [x]);
            sum += dev;
            max = std::max (max, dev);
        }
    }
    return Deviation (sum / area, max);
}

std::ostream & operator << (std::ostream & os, Deviation dev) {
    return os << "average " << dev.first << " / max: " << dev.second;
}

/* Copyright (C) Aaron Alef */
