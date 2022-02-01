#ifndef IMAGINARY_CONVOLUTE_HPP
#define IMAGINARY_CONVOLUTE_HPP

#include <opencv2/opencv.hpp>
#include <opencv2/core/hal/interface.h>

#include "bgr_t.hpp"

#include "config.h"

bool within_bounds (cv::Mat const & matrix, int x, int y);

cv::Mat convolute (cv::Mat const & original, cv::Mat const & kernel);

cv::Mat convolute_gray (cv::Mat const & original, cv::Mat const & kernel);

#endif //IMAGINARY_CONVOLUTE_HPP

/* Copyright (C) Aaron Alef */