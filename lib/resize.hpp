#ifndef IMAGINARY_RESIZE_HPP
#define IMAGINARY_RESIZE_HPP

#include <opencv2/opencv.hpp>

#include "config.h"

cv::Mat resize (cv::Mat const & src, cv::Mat && dest) {

}

cv::Mat resize_gray (cv::Mat const & src, cv::Mat && dest) {
    LOG_ASSERT (src.channels() == 1);
    LOG_ASSERT (dest.channels() == 1);

    if ((src.cols == dest.cols) && (src.rows == dest.rows))
        return dest = src.clone();


}

#endif //IMAGINARY_RESIZE_HPP

/* Copyright (C) Aaron Alef */
