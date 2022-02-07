#ifndef _IMAGINARY_MEDIAN_HPP
#define _IMAGINARY_MEDIAN_HPP

#include <opencv2/opencv.hpp>

#include <algorithm>

#include "convolute.hpp"
#include "bgr_t.hpp"

#include "config.h"

cv::Mat median (cv::Mat const & src, int size);

cv::Mat median_gray (cv::Mat const & src, int size);

#endif //_IMAGINARY_MEDIAN_HPP
