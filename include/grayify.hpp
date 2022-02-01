#ifndef _IMAGINARY_GRAYIFY_HPP
#define _IMAGINARY_GRAYIFY_HPP

#include <opencv2/opencv.hpp>
#include <opencv2/core/hal/interface.h>

#include <cmath>

#include "bgr_t.hpp"

#include "config.h"

cv::Mat grayify (cv::Mat const & src);

cv::Mat twice_gray (cv::Mat const & original);

#endif //_IMAGINARY_GRAYIFY_HPP

/* Copyright (C) Aaron Alef */
