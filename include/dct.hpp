#ifndef IMAGINARY_DCT_HPP
#define IMAGINARY_DCT_HPP

/* Fast DCT algorithm - AAN (Arai/Agui/Nakajima)
 * Implementation adapted from Emil Mikulic (https://unix4lyfe.org/dct/)
 */

#include <opencv2/opencv.hpp>

#include "config.h"

#define DCT_WINDOW_SIZE 8

cv::Mat dct        (cv::Mat const & src);
cv::Mat dct_window (cv::Mat const && window, cv::Mat && dest);

cv::Mat idct        (cv::Mat const & src);
cv::Mat idct_window (cv::Mat const && window, cv::Mat && dest);

cv::Mat dct_gray        (cv::Mat const & src);
cv::Mat dct_window_gray (cv::Mat const && window, cv::Mat && dest);

cv::Mat idct_gray        (cv::Mat const & src);
cv::Mat idct_window_gray (cv::Mat const && window, cv::Mat && dest);

#endif //IMAGINARY_DCT_HPP

/* Copyright (C) Aaron Alef */
