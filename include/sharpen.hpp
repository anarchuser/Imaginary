#ifndef IMAGINARY_SHARPEN_HPP
#define IMAGINARY_SHARPEN_HPP

#include <opencv2/opencv.hpp>

#include "convolute.hpp"

#include "config.h"

#define GAUSSIAN_SIZE 3
#define GAUSSIAN_SIGMA 1.5

cv::Mat sharpen (cv::Mat const & src);
cv::Mat sharpen_gray (cv::Mat const & src);

cv::Mat unsharp_mask (cv::Mat const & src, double weight);
cv::Mat unsharp_mask_gray (cv::Mat const & src, double weight);

#endif //IMAGINARY_SHARPEN_HPP

/* Copyright (C) Aaron Alef */
