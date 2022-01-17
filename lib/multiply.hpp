#ifndef IMAGINARY_MULTIPLY_HPP
#define IMAGINARY_MULTIPLY_HPP

#include <opencv2/opencv.hpp>
#include <opencv2/core/hal/interface.h>

#include "bgr_t.hpp"

#include "config.h"

cv::Mat twice (cv::Mat const & original) {
    cv::Mat img (2 * original.rows, 2 * original.cols, CV_8UC3);
    for (int y = 0; y < img.rows; y++) {
        auto original_row = original.ptr <Color_BGR> (y / 2);
        auto img_row = img.ptr <double> (y);

        for (int x = 0; x < img.cols; x++) {
            Color_BGR color = original_row [x / 2];
            img_row [x] = (double) (color.red() + color.green() + color.blue()) / 3;
        }
    }
    return img;
}

#endif //IMAGINARY_MULTIPLY_HPP

/* Copyright (C) Aaron Alef */
