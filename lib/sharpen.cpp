#include "sharpen.hpp"

cv::Mat sharpen_gray (cv::Mat const & src) {
    auto gaussian = cv::getGaussianKernel (GAUSSIAN_SIZE * GAUSSIAN_SIZE, 1.5, CV_64F).reshape (1, GAUSSIAN_SIZE);
    auto dest = src.clone();

    for (int y = 1; y < src.rows - 1; y++) {
        for (int x = 1; x < src.cols - 1; x++) {
            double sum = 5 *
                    src.at <double> (y + 0, x + 0) -
                    src.at <double> (y + 1, x + 0) -
                    src.at <double> (y + 0, x + 1) -
                    src.at <double> (y - 1, x - 0) -
                    src.at <double> (y - 0, x - 1);
            std::cout << "Sum " << sum << std::endl;
            dest.at <double> (y, x) = sum;
        }
    }

    return dest;
}

/* Copyright (C) Aaron Alef */
