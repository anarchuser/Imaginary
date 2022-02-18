#include "canny.hpp"

cv::Mat sobel_approx_magnitude (cv::Mat const & src) {
    LOG_ASSERT (src.channels() == 1);

    cv::Mat out (src.rows - 2, src.cols - 2, CV_64FC1);

    for (int y = 0; y < out.rows; y++) {
        auto row = out.ptr <double> (y);

        for (int x = 0; x < out.cols; x++) {
            auto src_at = [& src, x, y] (int x_offset, int y_offset) {
                return src.at <double> (y + y_offset, x + x_offset);
            };
            double sum = std::abs (
                            (src_at (0, 0) + 2 * src_at (1, 0) + src_at (2, 0)) -
                            (src_at (0, 2) + 2 * src_at (1, 2) + src_at (2, 2))
                    ) + std::abs (
                            (src_at (2, 0) + 2 * src_at (2, 1) + src_at (2, 2)) -
                            (src_at (0, 0) + 2 * src_at (0, 1) + src_at (0, 2))
                    );
            row [x] = sum;
        }
    }

    return out;
}

double average_gray (cv::Mat const & src) {
    LOG_ASSERT (src.channels() == 1);

    double accu = 0;

    for (int y = 0; y < src.rows; y++) {
        auto row = src.ptr <double> (y);

        for (int x = 0; x < src.cols; x++) {
            accu += row [x];
        }
    }
    return accu / src.rows / src.cols;
}

cv::Mat threshold_gray (cv::Mat const & src, double threshold) {
    LOG_ASSERT (src.channels() == 1);
    if (threshold < 0) {
        threshold = average_gray (src);
    }

    auto img = src.clone();
    for (int y = 0; y < img.rows; y++) {
        auto row = img.ptr <double> (y);

        for (int x = 0; x < src.cols; x++) {
            row [x] = 255 * (row [x] >= threshold);
        }
    }
    return img;
}

cv::Mat canny (cv::Mat const & src) {
    // Make gray if not gray
    auto img = (src.channels() == 1) ? src : grayify (src);

    // Apply gaussian blur
    auto const gaussian = cv::getGaussianKernel (25, 1.5, CV_64FC1).reshape (1, 5);
    img = convolute_gray (img, gaussian);

    // Apply sobel kernels
    img = sobel_approx_magnitude (img);

    // TODO: thin lines (e.g., non-maximum suppression)

    // Make black-white
//    img = threshold_gray (img, THRESHOLD);

    return img;
}

/* Copyright (C) Aaron Alef */
