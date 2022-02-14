#include "dct.hpp"

cv::Mat dct_gray (cv::Mat const & src) {
    LOG_ASSERT (src.channels() == 1);

    // Truncate to modulo DCT_WINDOW_SIZE == 0 in either dimension. TODO: fix this
    cv::Mat dest ((src.rows / DCT_WINDOW_SIZE) * DCT_WINDOW_SIZE, (src.cols / DCT_WINDOW_SIZE) * DCT_WINDOW_SIZE, CV_64FC1);

    for (int y = 0; y < dest.rows; y += DCT_WINDOW_SIZE) {
        for (int x = 0; x < dest.cols; x += DCT_WINDOW_SIZE) {
            cv::Rect2i window (x, y, DCT_WINDOW_SIZE, DCT_WINDOW_SIZE);
            dct_window_gray ({src, window}, {dest, window});
        }
    }
    return dest;
}

cv::Mat dct_window_gray (cv::Mat const && src, cv::Mat && dest) {
    LOG_ASSERT (src.channels() == 1);
    LOG_ASSERT (dest.channels() == 1);
    LOG_ASSERT (src.rows == DCT_WINDOW_SIZE);
    LOG_ASSERT (src.cols == DCT_WINDOW_SIZE);
    LOG_ASSERT (dest.rows == DCT_WINDOW_SIZE);
    LOG_ASSERT (dest.cols == DCT_WINDOW_SIZE);

    for (int y = 0; y < DCT_WINDOW_SIZE; y++) {
        auto srow = src.ptr <double> (y);
        auto drow = dest.ptr <double> (y);

        for (int x = 0; x < DCT_WINDOW_SIZE; x++) {
            drow [x] = srow [x];
        }
    }
    return dest;
}

cv::Mat idct_gray (cv::Mat const & src) {
    LOG_ASSERT (src.channels() == 1);
    LOG_ASSERT (src.rows % DCT_WINDOW_SIZE == 0);
    LOG_ASSERT (src.cols % DCT_WINDOW_SIZE == 0);

    cv::Mat dest (src.rows, src.cols, CV_64FC1);

    for (int y = 0; y < dest.rows; y += DCT_WINDOW_SIZE) {
        for (int x = 0; x < dest.cols; x += DCT_WINDOW_SIZE) {
            cv::Rect2i window (x, y, DCT_WINDOW_SIZE, DCT_WINDOW_SIZE);
            idct_window_gray ({src, window}, {dest, window});
        }
    }
    return dest;
}

cv::Mat idct_window_gray (cv::Mat const && src, cv::Mat && dest) {
    LOG_ASSERT (src.channels() == 1);
    LOG_ASSERT (dest.channels() == 1);
    LOG_ASSERT (src.rows == DCT_WINDOW_SIZE);
    LOG_ASSERT (src.cols == DCT_WINDOW_SIZE);
    LOG_ASSERT (dest.rows == DCT_WINDOW_SIZE);
    LOG_ASSERT (dest.cols == DCT_WINDOW_SIZE);

    for (int y = 0; y < DCT_WINDOW_SIZE; y++) {
        auto srow = src.ptr <double> (y);
        auto drow = dest.ptr <double> (y);

        for (int x = 0; x < DCT_WINDOW_SIZE; x++) {
            drow [x] = srow [x];
        }
    }
    return dest;
}

/* Copyright (C) Aaron Alef */
