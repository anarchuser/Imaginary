#ifndef IMAGINARY_DILUTE_HPP
#define IMAGINARY_DILUTE_HPP

#include <opencv2/opencv.hpp>

#include "config.h"

#include "bgr_t.hpp"

cv::Mat dilute (cv::Mat const & src);
cv::Mat erode (cv::Mat const & src);

#endif //IMAGINARY_DILUTE_HPP
