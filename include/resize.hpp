#ifndef IMAGINARY_RESIZE_HPP
#define IMAGINARY_RESIZE_HPP

#include <opencv2/opencv.hpp>

#include <cmath>

#include "config.h"

cv::Mat resize (cv::Mat const & src, cv::Mat && dest);

double average_gray (cv::Mat const & src, cv::Rect2d precise_area);

cv::Mat resize_gray (cv::Mat const & src, cv::Mat && dest);

#endif //IMAGINARY_RESIZE_HPP

/* Copyright (C) Aaron Alef */
