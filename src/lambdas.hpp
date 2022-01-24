#ifndef IMAGINARY_LAMBDAS_H
#define IMAGINARY_LAMBDAS_H

#include "config.h"

#include "grayify.hpp"
#include "multiply.hpp"
#include "convolute.hpp"
#include "resize.hpp"

#include <cmath>
#include <filesystem>

#define APPLY(function, val) apply ([](Image const & image) { return function (image, val); })

using namespace cv;
namespace fs = std::filesystem;

using Image = std::pair <std::string, Mat>;

std::string square_string (int size) {
    auto out = std::to_string (size);
    return out + 'x' + out;
}

static auto const convolute_1s_l = [] (Image const & image, int size) -> Image {
    auto kernel = Mat (size, size, CV_64FC1, 1);
    auto convoluted = convolute (image.second, kernel);
    auto out = Image (image.first, convoluted);
    write_image (std::string ("convoluted/1's/") + square_string (size), out);
    return out;
};

static auto const convolute_gaussian_l = [] (Image const & image, int size) -> Image {
    auto kernel = cv::getGaussianKernel (size * size, 1, CV_64F).reshape (1, size);
    auto convoluted = convolute (image.second, kernel);
    auto out = Image (image.first, convoluted);
    write_image (std::string ("convoluted/gaussian/") + square_string (size), out);
    return out;
};

static auto const double_l = [] (Image const & image, int iterations) -> Image {
    auto multiplied = image.second;
    for (int i = 0; i < iterations; i++)
        multiplied = twice (multiplied);
    auto out = Image (image.first, multiplied);
    write_image (std::string ("original/") + std::to_string (std::pow (2, iterations)), out);
    return out;
};

static auto const grayify_l = [] (Image const & image) -> Image {
    Image out (image.first, grayify (image.second));
    write_image ("gray", out);
    return out;
};

static auto const gray_resize_l = [] (Image const & image, double factor) -> Image {
    auto resized = resize_gray (image.second, cv::Mat (round (image.second.rows * factor), round (image.second.cols * factor), CV_64FC1));
    auto out = Image (image.first, resized);
    write_image (std::string ("resize/") + std::to_string (factor), out);
    return out;
};

static auto const gray_convolute_1s_l = [] (Image const & image, int size) -> Image {
    auto kernel = Mat (size, size, CV_64FC1, 1);
    auto convoluted = convolute (image.second, kernel);
    auto out = Image (image.first, convoluted);
    write_image (std::string ("convoluted/1's") + square_string (size), out);
    return out;
};

static auto const gray_convolute_gaussian_l = [] (Image const & image, int size) -> Image {
    auto kernel = cv::getGaussianKernel (size * size, 1, CV_64F).reshape (1, size);
    auto convoluted = convolute (image.second, kernel);
    auto out = Image (image.first, convoluted);
    write_image (std::string ("convoluted/gaussian") + square_string (size), out);
    return out;
};

static auto const gray_double_l = [] (Image const & image, int iterations) -> Image {
    auto multiplied = image.second;
    for (int i = 0; i < iterations; i++)
        multiplied = twice (multiplied);
    auto out = Image (image.first, multiplied);
    write_image (std::string ("gray/") + std::to_string (std::pow (2, iterations)), out);
    return out;
};

#endif //IMAGINARY_LAMBDAS_H

/* Copyright (C) Aaron Alef */