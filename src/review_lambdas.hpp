#ifndef IMAGINARY_REVIEW_LAMBDAS_H
#define IMAGINARY_REVIEW_LAMBDAS_H

#include "config.h"

#include "dilute.hpp"
#include "grayify.hpp"
#include "multiply.hpp"
#include "convolute.hpp"
#include "resize.hpp"
#include "deviation.hpp"
#include "canny.hpp"
#include "spatial.hpp"
#include "sharpen.hpp"
#include "median.hpp"
#include "io.hpp"
#include "dct.hpp"

#include <cmath>
#include <filesystem>
#include <iostream>

#define REVIEW_SIZE 7

namespace fs = std::filesystem;

namespace review {
    static auto const mean_l = [] (Image const & image) {
        auto kernel = cv::Mat (REVIEW_SIZE, REVIEW_SIZE, CV_64FC1, 1);
        
        // Extrapolate
        std::cout << "\tdilute" << std::endl;
        auto extrapolate = dilute (image.second, REVIEW_SIZE / 2);
        std::cout << "\tmean" << std::endl;
        extrapolate = convolute (extrapolate, kernel);
        std::cout << "\terode" << std::endl;
        extrapolate = erode (extrapolate, REVIEW_SIZE / 2);
        std::cout << "\twrite" << std::endl;
        write_image (std::string ("review/mean_extrapolate"), {image.first, extrapolate});
        
        
    };

    static auto const median_l = [] (Image const & image) {
        // Extrapolate
        std::cout << "\tdilute" << std::endl;
        auto extrapolate = dilute (image.second, REVIEW_SIZE / 2);
//        std::cout << "\tmedian" << std::endl;
//        extrapolate = median (extrapolate, REVIEW_SIZE);
        std::cout << "\terode" << std::endl;
        extrapolate = erode (extrapolate, REVIEW_SIZE / 2);
        std::cout << "\twrite" << std::endl;
        write_image (std::string ("review/median_extrapolate"), {image.first, extrapolate});
        
        
    };
}

#endif //IMAGINARY_REVIEW_LAMBDAS_H

/* Copyright (C) Aaron Alef */
