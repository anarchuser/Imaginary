#ifndef _IMAGINARY_GRAYIFY_HPP
#define _IMAGINARY_GRAYIFY_HPP

#include <opencv2/opencv.hpp>

struct Color_BGR {
    unsigned char value[3];
    
    unsigned char & blue() { return value[0]; };
    unsigned char & green() { return value[1]; };
    unsigned char & red() { return value[2]; };
    
    unsigned char & operator[] (unsigned int index) {
        return value[index];
    }
};

cv::Mat grayify (cv::Mat img) {
    for (int y = 0; y < img.rows; y++) {
        for (int x = 0; x < img.cols; x++) {
            Color_BGR & color = img.ptr <Color_BGR> (y) [x];
            unsigned char avg = (color.red() + color.green() + color.blue()) / 3;
            color.red() = avg;
            color.green() = avg;
            color.blue() = avg;
        }
    }
    return img;
}

#endif //_IMAGINARY_GRAYIFY_HPP

/* Copyright (C) Aaron Alef */