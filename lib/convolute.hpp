#ifndef IMAGINARY_CONVOLUTE_HPP
#define IMAGINARY_CONVOLUTE_HPP

#include <opencv2/opencv.hpp>
#include <opencv2/core/hal/interface.h>

#include "bgr_t.hpp"

#include "config.h"

bool within_bounds (cv::Mat const & matrix, int x, int y) {
    return x >= 0 && y >= 0 && x < matrix.cols && y < matrix.rows;
}

cv::Mat convolute_gray (cv::Mat const & original, cv::Mat const & kernel) {
    cv::Mat modified (original.rows, original.cols, CV_64FC1);

    LOG_ASSERT (kernel.cols % 2 && kernel.rows % 2);

    int kernel_sum = 0;
    for (int y = 0; y < kernel.rows; y++) {
        auto kernel_row = kernel.ptr <unsigned char> (y);
        for (int x = 0; x < kernel.cols; x++) {
            kernel_sum += kernel_row [x];
        }
    }

    for (int y = 0; y < modified.rows; y++) {
        auto mod_row = modified.ptr <double> (y);

        for (int x = 0; x < modified.cols; x++) {
            double sum = 0;
            for (int j = - kernel.rows / 2; j <= kernel.rows / 2; j++) {
                for (int i = - kernel.cols / 2; i <= kernel.cols / 2; i++) {
                    sum += ( within_bounds (original, x + i, y + j) )
                           ? original.at <double> (y + j, x + i) * kernel.at <unsigned char> (j + kernel.rows / 2, i + kernel.cols / 2)
                           : original.at <double> (y, x) * kernel.at <unsigned char> (kernel.rows / 2, kernel.cols / 2);
                }
            }
            mod_row [x] = sum / kernel_sum;
        }
    }
    return modified;
}

#endif //IMAGINARY_CONVOLUTE_HPP

/* Copyright (C) Aaron Alef */
