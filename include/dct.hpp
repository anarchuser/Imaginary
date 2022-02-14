#ifndef IMAGINARY_DCT_HPP
#define IMAGINARY_DCT_HPP

/* Fast DCT algorithm - AAN (Arai/Agui/Nakajima)
 * Implementation adapted from Emil Mikulic (https://unix4lyfe.org/dct/)
 */

#include <opencv2/opencv.hpp>

#include <cmath>
#define PI M_PI

#include "config.h"

struct BitMask {
private:
    uint64 const mask;

public:
    explicit BitMask (uint64 mask);
    explicit BitMask (unsigned char const mask [8]);

    [[nodiscard]] bool check (unsigned char x, unsigned char y) const;
};

cv::Mat dct  (cv::Mat const & src);
cv::Mat idct (cv::Mat const & src);

cv::Mat dct_gray  (cv::Mat const & src);
cv::Mat idct_gray (cv::Mat const & src);

cv::Mat fast_dct_gray      (cv::Mat const & src);
void mask_gray (int window [8][8], BitMask mask);
cv::Mat compress_dct_gray  (cv::Mat const & src, BitMask mask);
void fast_dct_window_gray  (cv::Mat const && src, int window [8][8]);
cv::Mat fast_idct_window_gray (int window [8][8], cv::Mat && dest);

#endif //IMAGINARY_DCT_HPP

/* Copyright (C) Aaron Alef */
