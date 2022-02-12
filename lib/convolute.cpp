#include "convolute.hpp"

bool within_bounds (cv::Mat const & matrix, int x, int y) {
    return x >= 0 && y >= 0 && x < matrix.cols && y < matrix.rows;
}

cv::Mat convolute (cv::Mat const & original, cv::Mat const & kernel) {
    cv::Mat modified (original.rows, original.cols, CV_8UC3);

    LOG_ASSERT (kernel.cols % 2 && kernel.rows % 2);

    for (int y = 0; y < modified.rows; y++) {
        auto mod_row = modified.ptr <Color_BGR> (y);

        for (int x = 0; x < modified.cols; x++) {
            double kernel_sum = 0;
            double red = 0;
            double green = 0;
            double blue = 0;
            for (int ky = - kernel.rows / 2; ky <= kernel.rows / 2; ky++) {
                for (int kx = - kernel.cols / 2; kx <= kernel.cols / 2; kx++) {
                    if (within_bounds (original, x + kx, y + ky)) {
                        kernel_sum += kernel.at <double> (ky + kernel.rows / 2, kx + kernel.cols / 2);
                        red   += original.at <Color_BGR> (y + ky, x + kx).red()   * kernel.at <double> (ky + kernel.rows / 2, kx + kernel.cols / 2);
                        green += original.at <Color_BGR> (y + ky, x + kx).green() * kernel.at <double> (ky + kernel.rows / 2, kx + kernel.cols / 2);
                        blue  += original.at <Color_BGR> (y + ky, x + kx).blue()  * kernel.at <double> (ky + kernel.rows / 2, kx + kernel.cols / 2);
                    } else {
                        kernel_sum += kernel.at <double> (kernel.rows / 2, kernel.cols / 2);
                        red   += (double) original.at <Color_BGR> (y, x).red()   * kernel.at <double> (kernel.rows / 2, kernel.cols / 2);
                        green += (double) original.at <Color_BGR> (y, x).green() * kernel.at <double> (kernel.rows / 2, kernel.cols / 2);
                        blue  += (double) original.at <Color_BGR> (y, x).blue()  * kernel.at <double> (kernel.rows / 2, kernel.cols / 2);
                    }
                }
            }
            mod_row [x].red()   = (red   / (kernel_sum ?: 1));
            mod_row [x].green() = (green / (kernel_sum ?: 1));
            mod_row [x].blue()  = (blue  / (kernel_sum ?: 1));
        }
    }
    return modified;
}

cv::Mat convolute_gray (cv::Mat const & original, cv::Mat const & kernel) {
    cv::Mat modified (original.rows, original.cols, CV_64FC1);

    LOG_ASSERT (original.channels() == 1);
    LOG_ASSERT (modified.channels() == 1);

    LOG_ASSERT (kernel.cols % 2 && kernel.rows % 2);

    for (int y = 0; y < modified.rows; y++) {
        auto mod_row = modified.ptr <double> (y);

        for (int x = 0; x < modified.cols; x++) {
            double sum = 0;
            double kernel_sum = 0;
            for (int j = - kernel.rows / 2; j <= kernel.rows / 2; j++) {
                for (int i = - kernel.cols / 2; i <= kernel.cols / 2; i++) {
                    kernel_sum += ( within_bounds (original, x + i, y + j) )
                           ? kernel.at <double> (j + kernel.rows / 2, i + kernel.cols / 2)
                           : kernel.at <double> (kernel.rows / 2, kernel.cols / 2);
                    sum += ( within_bounds (original, x + i, y + j) )
                           ? original.at <double> (y + j, x + i) * kernel.at <double> (j + kernel.rows / 2, i + kernel.cols / 2)
                           : original.at <double> (y, x) * kernel.at <double> (kernel.rows / 2, kernel.cols / 2);
                }
            }
            mod_row [x] = sum / (kernel_sum ?: 1);
        }
    }
    return modified;
}

/* Copyright (C) Aaron Alef */
