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
        auto img_row = img.ptr <Color_BGR> (y);

        for (int x = 0; x < img.cols; x++) {
            int ctr = 1;
            unsigned int red = original_row [x / 2].red();
            unsigned int green = original_row [x / 2].green();
            unsigned int blue = original_row [x / 2].blue();
            if ((x-1)/2 > 0) {
                ctr++;
                red += original.at <Color_BGR> (y/2, (x-1)/2).red();
                green += original.at <Color_BGR> (y/2, (x-1)/2).green();
                blue += original.at <Color_BGR> (y/2, (x-1)/2).blue();
            }
            if ((y-1)/2 > 0) {
                ctr++;
                red += original.at <Color_BGR> ((y-1)/2, x/2).red();
                green += original.at <Color_BGR> ((y-1)/2, x/2).green();
                blue += original.at <Color_BGR> ((y-1)/2, x/2).blue();
            }
            if ((x+1)/2 < original.rows) {
                ctr++;
                red += original.at <Color_BGR> (y/2, (x+1)/2).red();
                green += original.at <Color_BGR> (y/2, (x+1)/2).green();
                blue += original.at <Color_BGR> (y/2, (x+1)/2).blue();
            }
            if ((y+1)/2 < original.cols) {
                ctr++;
                red += original.at <Color_BGR> ((y+1)/2, x/2).red();
                green += original.at <Color_BGR> ((y+1)/2, x/2).green();
                blue += original.at <Color_BGR> ((y+1)/2, x/2).blue();
            }
            if ((x-1)/2 > 0 && (y-1)/2 > 0) {
                ctr++;
                red += original.at <Color_BGR> ((y-1)/2, (x-1)/2).red();
                green += original.at <Color_BGR> ((y-1)/2, (x-1)/2).green();
                blue += original.at <Color_BGR> ((y-1)/2, (x-1)/2).blue();
            }
            if ((x-1)/2 > 0 && (y+1)/2 < original.cols) {
                ctr++;
                red += original.at <Color_BGR> ((y-1)/2, (x+1)/2).red();
                green += original.at <Color_BGR> ((y-1)/2, (x+1)/2).green();
                blue += original.at <Color_BGR> ((y-1)/2, (x+1)/2).blue();
            }
            if ((x+1)/2 < original.rows && (y-1)/2 > 0) {
                ctr++;
                red += original.at <Color_BGR> ((y+1)/2, (x-1)/2).red();
                green += original.at <Color_BGR> ((y+1)/2, (x-1)/2).green();
                blue += original.at <Color_BGR> ((y+1)/2, (x-1)/2).blue();
            }
            if ((x+1)/2 < original.rows && (y+1)/2 < original.cols) {
                ctr++;
                red += original.at <Color_BGR> ((y+1)/2, (x+1)/2).red();
                green += original.at <Color_BGR> ((y+1)/2, (x+1)/2).green();
                blue += original.at <Color_BGR> ((y+1)/2, (x+1)/2).blue();
            }
            img_row [x].red() = red / ctr;
            img_row [x].green() = green / ctr;
            img_row [x].blue() = blue / ctr;
        }
    }
    return img;
}

#endif //IMAGINARY_MULTIPLY_HPP

/* Copyright (C) Aaron Alef */
