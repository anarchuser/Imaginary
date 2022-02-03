#ifndef _IMAGINARY_SPATIAL_HPP
#define _IMAGINARY_SPATIAL_HPP

#include <opencv2/opencv.hpp>

#include "bgr_t.hpp"

#include "config.h"

cv::Mat intensity_scale (cv::Mat const & src, Color_BGR (lambda) (Color_BGR));

cv::Mat intensity_scale (cv::Mat const & src, double (lambda) (double));

cv::Mat scale (cv::Mat const & src, unsigned char min = 0, unsigned char max = 255);

cv::Mat scale_gray (cv::Mat const & src, unsigned char min = 0, unsigned char max = 255);

#endif //_IMAGINARY_SPATIAL_HPP

/* Copyright (C) Aaron Alef */