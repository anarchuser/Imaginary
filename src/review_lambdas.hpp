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
#include "color.hpp"
#include "bgr_t.hpp"

#include <cmath>
#include <filesystem>
#include <iostream>

#define REVIEW_SIZE 9

namespace fs = std::filesystem;

namespace review {
    static auto const mean_l = [] (Image const & image) {
        auto kernel = cv::Mat (REVIEW_SIZE, REVIEW_SIZE, CV_64FC1, 1);
        
        // Extrapolate
        auto extrapolate = dilute (image.second, REVIEW_SIZE / 2);
        extrapolate = convolute (extrapolate, kernel);
        extrapolate = erode     (extrapolate, REVIEW_SIZE / 2);
        write_image (std::string ("review/mean_extrapolate"), {image.first, extrapolate});
        
        
    };

    static auto const median_l = [] (Image const & image) {
        // Extrapolate
        auto extrapolate = dilute (image.second, REVIEW_SIZE / 2);
        extrapolate = median (extrapolate, REVIEW_SIZE);
        extrapolate = erode  (extrapolate, REVIEW_SIZE / 2);
        write_image (std::string ("review/median_extrapolate"), {image.first, extrapolate});
        
        
    };

    static auto const component_l = [] (Image const & image) {
        // RGB
        write_image (std::string ("review/colour_RGB_red"),        {image.first, component (image.second, RED)});
        write_image (std::string ("review/colour_RGB_green"),      {image.first, component (image.second, GREEN)});
        write_image (std::string ("review/colour_RGB_blue"),       {image.first, component (image.second, BLUE)});

        // CMY
        write_image (std::string ("review/colour_CMY_cyan"),       {image.first, component (image.second, CYAN)});
        write_image (std::string ("review/colour_CMY_magenta"),    {image.first, component (image.second, MAGENTA)});
        write_image (std::string ("review/colour_CMY_yellow"),     {image.first, component (image.second, YELLOW)});

        // HSI
        write_image (std::string ("review/colour_HSI_hue"),        {image.first, component (image.second, HUE)});
        write_image (std::string ("review/colour_HSI_saturation"), {image.first, component (image.second, SATURATION)});
        write_image (std::string ("review/colour_HSI_intensity"),  {image.first, component (image.second, INTENSITY)});
    };
}

#endif //IMAGINARY_REVIEW_LAMBDAS_H

/* Copyright (C) Aaron Alef */
