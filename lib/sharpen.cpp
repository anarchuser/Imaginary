#include "sharpen.hpp"

cv::Mat sharpen (cv::Mat const & src) {
    LOG_ASSERT (src.channels() == 3);

    auto gaussian = cv::getGaussianKernel (GAUSSIAN_SIZE * GAUSSIAN_SIZE, 1.5, CV_64F).reshape (1, GAUSSIAN_SIZE);
    auto dest = convolute (src, gaussian);

    for (int y = 1; y < src.rows - 1; y++) {
        for (int x = 1; x < src.cols - 1; x++) {
            unsigned char sums [3];
            for (int i = 0; i < 3; i++) {
                sums [i] = std::max (0, std::min (255, 5 *
                        (int) src.at <Color_BGR> (y + 0, x + 0).value [i] -
                        (int) src.at <Color_BGR> (y + 1, x + 0).value [i] -
                        (int) src.at <Color_BGR> (y + 0, x + 1).value [i] -
                        (int) src.at <Color_BGR> (y - 1, x - 0).value [i] -
                        (int) src.at <Color_BGR> (y - 0, x - 1).value [i]));
            }
            dest.at <Color_BGR> (y, x) = {(unsigned char) sums [0], (unsigned char) sums [1], (unsigned char) sums [2]};
        }
    }
    return dest;
}

cv::Mat sharpen_gray (cv::Mat const & src) {
    LOG_ASSERT (src.channels() == 1);

    auto gaussian = cv::getGaussianKernel (GAUSSIAN_SIZE * GAUSSIAN_SIZE, 1.5, CV_64F).reshape (1, GAUSSIAN_SIZE);
    auto dest = convolute (src, gaussian);

    for (int y = 1; y < src.rows - 1; y++) {
        for (int x = 1; x < src.cols - 1; x++) {
            double sum = 5 *
                    src.at <double> (y + 0, x + 0) -
                    src.at <double> (y + 1, x + 0) -
                    src.at <double> (y + 0, x + 1) -
                    src.at <double> (y - 1, x - 0) -
                    src.at <double> (y - 0, x - 1);
            dest.at <double> (y, x) = sum;
        }
    }

    return dest;
}

/* Copyright (C) Aaron Alef */
