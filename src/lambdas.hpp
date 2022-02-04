#ifndef IMAGINARY_LAMBDAS_H
#define IMAGINARY_LAMBDAS_H

#include "config.h"

#include "grayify.hpp"
#include "multiply.hpp"
#include "convolute.hpp"
#include "resize.hpp"
#include "deviation.hpp"
#include "canny.hpp"
#include "spatial.hpp"

#include <cmath>
#include <filesystem>
#include <iostream>

#define APPLY(function, val) apply ([](Image const & image) { return function (image, val); })

namespace fs = std::filesystem;

std::string square_string (int size) {
    auto out = std::to_string (size);
    return out + 'x' + out;
}

static auto const convolute_1s_l = [] (Image const & image, int size) -> Image {
    auto kernel = cv::Mat (size, size, CV_64FC1, 1);
    auto convoluted = convolute (image.second, kernel);
    auto out = Image (image.first, convoluted);
    LOG (INFO) << "Original '" << image.first << "'\tconvoluted with " << square_string (size) << " matrix filled with 1's: " << deviation (image.second, out.second);
    write_image (std::string ("convoluted/1's/") + square_string (size), out);
    return out;
};

static auto const convolute_gaussian_l = [] (Image const & image, int size) -> Image {
    auto kernel = cv::getGaussianKernel (size * size, 1.5, CV_64F).reshape (1, size);
    auto convoluted = convolute (image.second, kernel);
    auto out = Image (image.first, convoluted);
    LOG (INFO) << "Original '" << image.first << "'\tconvoluted with gaussian " << square_string (size) << " matrix: " << deviation (image.second, out.second);
    write_image (std::string ("convoluted/gaussian/") + square_string (size), out);
    return out;
};

static auto const double_l = [] (Image const & image, int iterations) -> Image {
    auto multiplied = image.second;
    for (int i = 0; i < iterations; i++)
        multiplied = twice (multiplied);
    auto out = Image (image.first, multiplied);
    LOG (INFO) << "Original '" << image.first << "'\tdoubled " << iterations << " times: " << deviation (image.second, out.second);
    write_image (std::string ("original/") + std::to_string ((int) std::pow (2, iterations)), out);
    return out;
};

static auto const resize_l = [] (Image const & image, double factor) -> Image {
    auto resized = resize (image.second, cv::Mat (round (image.second.rows * factor), round (image.second.cols * factor), CV_8UC3));
    auto out = Image (image.first, resized);
    LOG (INFO) << "Original '" << image.first << "'\tresized by factor " << factor << ": " << deviation (image.second, out.second);
    write_image (std::string ("original/resize/") + std::to_string (factor), out);
    return out;
};

static auto const resize_dims_l = [] (Image const & image, int width, int height) -> Image {
    auto resized = resize (image.second, cv::Mat (width, height, CV_8UC3));
    auto out = Image (image.first, resized);
    LOG (INFO) << "Original '" << image.first << "'\tresized to dimensions " << width << "x" << height << ": " << deviation (image.second, out.second);
    write_image (std::string ("original/resize/") + std::to_string (height) + 'x' + std::to_string (width), out);
    return out;
};

static auto const intensity_scale_l = [] (Image const & image, Color_BGR (lambda) (Color_BGR)) -> Image {
    static int img_index = 0;
    auto scaled = intensity_scale (image.second, lambda);
    auto out = Image (image.first, scaled);
    LOG (INFO) << "Original '" << image.first << "'\tscaled by some lambda. Deviation: " << deviation (image.second, out.second);
    write_image (std::string ("original/spatial/") + std::to_string (img_index++), out);
    return out;
};

static auto const scale_l = [] (Image const & image, void * _) -> Image {
    auto scaled = scale (image.second);
    auto out = Image (image.first, scaled);
    LOG (INFO) << "Original '" << image.first << "'\tscaled to [0..255]: " << deviation (image.second, out.second);
    write_image (std::string ("original/scaled"), out);
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
    LOG (INFO) << "Gray '" << image.first << "'\tresized by factor " << factor << ": " << deviation_gray (image.second, out.second);
    write_image (std::string ("gray/resize/") + std::to_string (factor), out);
    return out;
};

static auto const gray_resize_dims_l = [] (Image const & image, int width, int height) -> Image {
    auto resized = resize_gray (image.second, cv::Mat (width, height, CV_64FC1));
    auto out = Image (image.first, resized);
    LOG (INFO) << "Gray '" << image.first << "'\tresized to dimensions " << width << "x" << height << ": " << deviation_gray (image.second, out.second);
    write_image (std::string ("gray/resize/") + std::to_string (height) + 'x' + std::to_string (width), out);
    return out;
};

static auto const gray_convolute_1s_l = [] (Image const & image, int size) -> Image {
    auto kernel = cv::Mat (size, size, CV_64FC1, 1);
    auto convoluted = convolute_gray (image.second, kernel);
    auto out = Image (image.first, convoluted);
    LOG (INFO) << "Gray '" << image.first << "'\tconvoluted with " << square_string (size) << " matrix filled with 1's: " << deviation_gray (image.second, out.second);
    write_image (std::string ("gray/convoluted/1's/") + square_string (size), out);
    return out;
};

static auto const gray_convolute_gaussian_l = [] (Image const & image, int size) -> Image {
    auto kernel = cv::getGaussianKernel (size * size, 1.5, CV_64F).reshape (1, size);
    auto convoluted = convolute_gray (image.second, kernel);
    auto out = Image (image.first, convoluted);
    LOG (INFO) << "Gray '" << image.first << "'\tconvoluted with " << square_string (size) << " gaussian kernel: " << deviation_gray (image.second, out.second);
    write_image (std::string ("gray/convoluted/gaussian/") + square_string (size), out);
    return out;
};

static auto const gray_double_l = [] (Image const & image, int iterations) -> Image {
    auto multiplied = image.second;
    for (int i = 0; i < iterations; i++)
        multiplied = twice_gray (multiplied);
    auto out = Image (image.first, multiplied);
    LOG (INFO) << "Gray '" << image.first << "'\tdoubled " << iterations << " times: " << deviation_gray (image.second, out.second);
    write_image (std::string ("gray/") + std::to_string ((int) std::pow (2, iterations)), out);
    return out;
};

static auto const canny_l = [] (Image const & image, void * _) {
    auto out = Image (image.first, canny (image.second));
    LOG (INFO) << "Apply canny edge detection to '" << image.first << "'" << std::endl;
    write_image (std::string ("canny"), out);
    return out;
};

static auto const threshold_l = [] (Image const & image, int threshold) {
    auto out = Image (image.first, threshold_gray (canny (image.second), threshold));
    LOG (INFO) << "Apply threshold " << threshold << " to canny '" << image.first << "'" << std::endl;
    write_image (std::string ("canny/threshold/") + std::to_string (threshold), out);
    return out;
};

static auto const gray_intensity_scale_l = [] (Image const & image, double (lambda) (double)) -> Image {
    static int img_index = 0;
    auto scaled = intensity_scale (image.second, lambda);
    auto out = Image (image.first, scaled);
    LOG (INFO) << "Gray '" << image.first << "'\tscaled by some lambda. Deviation: " << deviation_gray (image.second, out.second);
    write_image (std::string ("gray/spatial/") + std::to_string (img_index++), out);
    return out;
};

static auto const gray_scale_l = [] (Image const & image, unsigned short const args) -> Image {
    auto * _args = (unsigned char const *) & args;
    auto scaled = scale_gray (image.second, _args[0], _args[1]);
    auto out = Image (image.first, scaled);
    LOG (INFO) << "Gray '" << image.first << "'\tscaled to [" << (unsigned int) _args[0] << ".." << (unsigned int) _args[1] << "]: " << deviation_gray (image.second, out.second);
    write_image (std::string ("gray/scaled"), out);
    return out;
};

#endif //IMAGINARY_LAMBDAS_H

/* Copyright (C) Aaron Alef */
