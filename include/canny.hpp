#ifndef _IMAGINARY_CANNY_HPP
#define _IMAGINARY_CANNY_HPP

// Canny edge detection following this article:
// https://towardsdatascience.com/canny-edge-detection-step-by-step-in-python-computer-vision-b49c3a2d8123

#include <opencv2/opencv.hpp>

#include "grayify.hpp"
#include "convolute.hpp"

#include "config.h"

#define THRESHOLD 80

// Sobel approximation taken from here:
// https://homepages.inf.ed.ac.uk/rbf/HIPR2/sobel.htm
cv::Mat sobel_approx_magnitude (cv::Mat const & src);

cv::Mat threshold_gray (cv::Mat const & src, double threshold);

cv::Mat canny (cv::Mat const & src);

#endif //_IMAGINARY_CANNY_HPP

/* Copyright (C) Aaron Alef */
