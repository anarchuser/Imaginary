#ifndef IMAGINARY_DILUTE_HPP
#define IMAGINARY_DILUTE_HPP

#include <opencv2/opencv.hpp>
#include <cmath>

#include "config.h"

#include "bgr_t.hpp"

cv::Mat dilute (cv::Mat const & src, int size = 1);
cv::Mat erode  (cv::Mat const & src, int size = 1);

#endif //IMAGINARY_DILUTE_HPP
