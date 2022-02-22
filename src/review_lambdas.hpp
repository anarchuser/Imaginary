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

#ifndef APPLY
#define APPLY(function, val) apply ([](Image const & image) { return function (image, val); })
#endif

namespace fs = std::filesystem;

namespace review {
    std::string square_string (int size) {
        auto out = std::to_string (size);
        return out + 'x' + out;
    }

    static auto const mean_interpolate_l = [] (Image const & image, int size) -> Image {
        auto kernel = cv::Mat (size, size, CV_64FC1, 1);
        auto diluted = image.second;
        for (int i = 0; i < size / 2; i++) {
            diluted = dilute (diluted);
        }
        auto convoluted = convolute (diluted, kernel);
        for (int i = 0; i < size / 2; i++) {
            convoluted = erode (convoluted);
        }
        auto out = Image (image.first, convoluted);
        LOG (INFO) << "Review '" << image.first << "'\tconvoluted with " << square_string (size) << " mean filter: "
                   << deviation (image.second, out.second);
        write_image (std::string ("review/mean/interpolate/") + square_string (size), out);
        return out;
    };

    static auto const median_interpolate_l = [] (Image const & image, int size) -> Image {
        auto kernel = cv::Mat (size, size, CV_64FC1, 1);
        auto diluted = image.second;
        for (int i = 0; i < size / 2; i++) {
            diluted = dilute (diluted);
        }
        auto smoothed = median (diluted, size);
        for (int i = 0; i < size / 2; i++) {
            smoothed = erode (smoothed);
        }
        auto out = Image (image.first, smoothed);
        LOG (INFO) << "Review '" << image.first << "'\tsmoothed with " << square_string (size) << " median filter: "
                   << deviation (image.second, out.second);
        write_image (std::string ("review/median/interpolate/") + square_string (size), out);
        return out;
    };

}

#endif //IMAGINARY_REVIEW_LAMBDAS_H

/* Copyright (C) Aaron Alef */
