#ifndef _IMAGINARY_SPATIAL_HPP
#define _IMAGINARY_SPATIAL_HPP

#include <opencv2/opencv.hpp>

#include "bgr_t.hpp"

#include "config.h"

cv::Mat intensity_scale (cv::Mat const & src, Color_BGR (lambda) (Color_BGR));

cv::Mat intensity_scale (cv::Mat const & src, double (lambda) (double));

#endif //_IMAGINARY_SPATIAL_HPP

/* Copyright (C) Aaron Alef */