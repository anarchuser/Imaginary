#ifndef _IMAGINARY_GRAYIFY_HPP
#define _IMAGINARY_GRAYIFY_HPP

#include <opencv2/opencv.hpp>
#include <opencv2/core/hal/interface.h>

#include "config.h"

struct Color_BGR {
    unsigned char value[3];
    
    unsigned char & blue() { return value[0]; };
    unsigned char & green() { return value[1]; };
    unsigned char & red() { return value[2]; };

    [[nodiscard]] unsigned char blue() const { return value[0]; };
    [[nodiscard]] unsigned char green() const { return value[1]; };
    [[nodiscard]] unsigned char red() const { return value[2]; };

    unsigned char & operator [] (unsigned int index) { return value[index]; }
    unsigned char operator [] (unsigned int index) const { return value[index]; }
};

// TODO: replace 3 color channels with 1 average channel
cv::Mat grayify (cv::Mat const & original) {
    cv::Mat img (original.rows, original.cols, CV_64F);
    for (int y = 0; y < original.rows; y++) {
        auto original_row = original.ptr <Color_BGR> (y);
        auto img_row = img.ptr <double> (y);

        for (int x = 0; x < original.cols; x++) {
            Color_BGR color = original_row [x];
            img_row [x] = (double) (color.red() + color.green() + color.blue()) / 3;
        }
    }
    return img;
}

#endif //_IMAGINARY_GRAYIFY_HPP

/* Copyright (C) Aaron Alef */