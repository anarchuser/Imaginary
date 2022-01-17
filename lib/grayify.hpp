#ifndef _IMAGINARY_GRAYIFY_HPP
#define _IMAGINARY_GRAYIFY_HPP

#include <opencv2/opencv.hpp>
#include <opencv2/core/hal/interface.h>

#include "bgr_t.hpp"

#include "config.h"

// TODO: replace 3 color channels with 1 average channel
cv::Mat grayify (cv::Mat const & original) {
    cv::Mat img (original.rows, original.cols, CV_64FC1);
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

cv::Mat twice_gray (cv::Mat const & original) {
    cv::Mat img (2 * original.rows, 2 * original.cols, CV_64FC1);
    for (int y = 0; y < img.rows; y++) {
        auto original_row = original.ptr <double> (y / 2);
        auto img_row = img.ptr <double> (y);

        for (int x = 0; x < img.cols; x++) {
            int ctr = 1;
            auto color = original_row [x / 2];
            if ((x-1)/2 > 0) {
                ctr++;
                color += original.at <double> (y/2, (x-1)/2);
            }
            if ((y-1)/2 > 0) {
                ctr++;
                color += original.at <double> ((y-1)/2, x/2);
            }
            if ((x+1)/2 < original.rows) {
                ctr++;
                color += original.at <double> (y/2, (x+1)/2);
            }
            if ((y+1)/2 < original.cols) {
                ctr++;
                color += original.at <double> ((y+1)/2, x/2);
            }
            if ((x-1)/2 > 0 && (y-1)/2 > 0) {
                ctr++;
                color += original.at <double> ((y-1)/2, (x-1)/2);
            }
            if ((x-1)/2 > 0 && (y+1)/2 < original.cols) {
                ctr++;
                color += original.at <double> ((y-1)/2, (x+1)/2);
            }
            if ((x+1)/2 < original.rows && (y-1)/2 > 0) {
                ctr++;
                color += original.at <double> ((y+1)/2, (x-1)/2);
            }
            if ((x+1)/2 < original.rows && (y+1)/2 < original.cols) {
                ctr++;
                color += original.at <double> ((y+1)/2, (x+1)/2);
            }
            img_row [x] = color / ctr;
        }
    }
    return img;
}

#endif //_IMAGINARY_GRAYIFY_HPP

/* Copyright (C) Aaron Alef */
