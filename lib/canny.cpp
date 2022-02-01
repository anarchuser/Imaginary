#include "canny.hpp"

cv::Mat canny (cv::Mat const & src) {
    // Make gray if not gray
    auto img = (src.channels() == 1) ? src : grayify (src);
//    write_image ("canny", Image ("input", img));
    
    // Apply gaussian blur
    auto const gaussian = cv::getGaussianKernel (25, 1.4, CV_64FC1).reshape (1, 5);
//    img = convolute_gray (img, gaussian);
//    write_image ("canny", Image ("blurred", img));
    
    // Apply sobel kernels
    auto const sobel_x = cv::Mat ({-1, 0, 1, -2, 0, 2, -1, 0, 1}).reshape (1, 3);
//    auto const sobel_y = cv::Mat ({1, 2, 1, 0, 0, 0, -1, -2, -1}).reshape (1, 3);
//    auto const sobel_x = cv::Mat ({1, 2, 1, 2, 3, 2, 1, 2, 1}).reshape (1, 3);
//    auto const sobel_y = cv::Mat ({0, 0, 0, 0, 1, 0, 0, 0, 0}).reshape (1, 3);
    
//    std::cout << sobel_x << std::endl << sobel_y << std::endl;
    
    img = convolute_gray (img, sobel_x);
//    img = convolute_gray (img, sobel_y);
//    write_image ("canny", Image ("sobel", img));
    
    return img;
}

/* Copyright (C) Aaron Alef */