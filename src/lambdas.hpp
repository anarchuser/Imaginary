#ifndef IMAGINARY_LAMBDAS_H
#define IMAGINARY_LAMBDAS_H

#include "config.h"

#include "multiply.hpp"
#include "convolute.hpp"
#include "resize.hpp"
#include "deviation.hpp"
#include "canny.hpp"
#include "spatial.hpp"
#include "sharpen.hpp"
#include "median.hpp"
#include "io.hpp"

#include <cmath>
#include <filesystem>
#include <iostream>

#ifndef APPLY
#define APPLY(function, val) apply ([](Image const & image) { return function (image, val); })
#endif

namespace fs = std::filesystem;

namespace original {
    std::string square_string (int size) {
        auto out = std::to_string (size);
        return out + 'x' + out;
    }

    static auto const mean_l = [] (Image const & image, int size) -> Image {
        auto kernel = cv::Mat (size, size, CV_64FC1, 1);
        auto convoluted = convolute (image.second, kernel);
        auto out = Image (image.first, convoluted);
        LOG (INFO) << "Original '" << image.first << "'\tconvoluted with " << square_string (size) << " mean filter: "
                   << deviation (image.second, out.second);
        write_image (std::string ("mean/") + square_string (size), out);
        return out;
    };

    static auto const median_l = [] (Image const & image, int size) -> Image {
        auto processed = median (image.second, size);
        auto out = Image (image.first, processed);
        LOG (INFO) << "Original '" << image.first << "'\t with " << square_string (size) << " median filter applied: "
                   << deviation (image.second, out.second);
        write_image (std::string ("median/") + square_string (size), out);
        return out;
    };

    static auto const convolute_gaussian_l = [] (Image const & image, int size) -> Image {
        auto kernel = cv::getGaussianKernel (size * size, 0.5 * size, CV_64F).reshape (1, size);
        auto convoluted = convolute (image.second, kernel);
        auto out = Image (image.first, convoluted);
        LOG (INFO) << "Original '" << image.first << "'\tconvoluted with gaussian " << square_string (size)
                   << " matrix: " << deviation (image.second, out.second);
        write_image (std::string ("gaussian/") + square_string (size), out);
        return out;
    };

    static auto const double_l = [] (Image const & image, int iterations) -> Image {
        auto multiplied = image.second;
        for (int i = 0; i < iterations; i++)
            multiplied = twice (multiplied);
        auto out = Image (image.first, multiplied);
        LOG (INFO) << "Original '" << image.first << "'\tdoubled " << iterations << " times: "
                   << deviation (image.second, out.second);
        write_image (std::string ("original/") + std::to_string ((int) std::pow (2, iterations)), out);
        return out;
    };

    static auto const resize_l = [] (Image const & image, double factor) -> Image {
        auto resized = resize (image.second,
                               cv::Mat (round (image.second.rows * factor), round (image.second.cols * factor),
                                        CV_8UC3));
        auto out = Image (image.first, resized);
        LOG (INFO) << "Original '" << image.first << "'\tresized by factor " << factor << ": "
                   << deviation (image.second, out.second);
        write_image (std::string ("original/resize/") + std::to_string (factor), out);
        return out;
    };

    static auto const resize_dims_l = [] (Image const & image, int width, int height) -> Image {
        auto resized = resize (image.second, cv::Mat (width, height, CV_8UC3));
        auto out = Image (image.first, resized);
        LOG (INFO) << "Original '" << image.first << "'\tresized to dimensions " << width << "x" << height << ": "
                   << deviation (image.second, out.second);
        write_image (std::string ("original/resize/") + std::to_string (height) + 'x' + std::to_string (width), out);
        return out;
    };

    static auto const intensity_scale_l = [] (Image const & image, Color_BGR (lambda) (Color_BGR)) -> Image {
        static int img_index = 0;
        auto scaled = intensity_scale (image.second, lambda);
        auto out = Image (image.first, scaled);
        LOG (INFO) << "Original '" << image.first << "'\tscaled by some lambda. Deviation: "
                   << deviation (image.second, out.second);
        write_image (std::string ("original/spatial/") + std::to_string (img_index++), out);
        return out;
    };

    static auto const scale_l = [] (Image const & image, unsigned short const args) -> Image {
        auto * _args = (unsigned char const *) & args;
        auto scaled = scale (image.second, _args[0], _args[1]);
        auto out = Image (image.first, scaled);
        LOG (INFO) << "Original '" << image.first << "'\tscaled to [" << (unsigned int) _args[0] << ".."
                   << (unsigned int) _args[1] << "]: " << deviation (image.second, out.second);
        write_image (std::string ("original/scaled/") + std::to_string ((unsigned int) _args[0]) + ".." +
                     std::to_string ((unsigned int) _args[1]), out);
        return out;
    };

    static auto const sharpen_l = [] (Image const & image, void * _) -> Image {
        auto sharpened = sharpen (image.second);
        auto out = Image (image.first, sharpened);
        LOG (INFO) << "Original '" << image.first << "'\tsharpened using laplace: "
                   << deviation (image.second, sharpened);
        write_image (std::string ("original/sharpen"), out);
        return out;
    };

    static auto const unsharp_mask_l = [] (Image const & image, double weight) -> Image {
        auto sharpened = unsharp_mask (image.second, weight);
        auto out = Image (image.first, sharpened);
        LOG (INFO) << "Original '" << image.first << "'\tsharpened using unsharp masking with weight " << weight << ": "
                   << deviation (image.second, sharpened);
        write_image (std::string ("original/unsharp/") + std::to_string (weight), out);
        return out;
    };

    static auto const bits_l = [] (Image const & image, void * _) -> Image {
        std::vector<Image> planes;
        planes.emplace_back (image.first, intensity_scale (image.second, [] (Color_BGR intensity) -> Color_BGR { return intensity & (1 << 0); }));
        planes.emplace_back (image.first, intensity_scale (image.second, [] (Color_BGR intensity) -> Color_BGR { return intensity & (1 << 1); }));
        planes.emplace_back (image.first, intensity_scale (image.second, [] (Color_BGR intensity) -> Color_BGR { return intensity & (1 << 2); }));
        planes.emplace_back (image.first, intensity_scale (image.second, [] (Color_BGR intensity) -> Color_BGR { return intensity & (1 << 3); }));
        planes.emplace_back (image.first, intensity_scale (image.second, [] (Color_BGR intensity) -> Color_BGR { return intensity & (1 << 4); }));
        planes.emplace_back (image.first, intensity_scale (image.second, [] (Color_BGR intensity) -> Color_BGR { return intensity & (1 << 5); }));
        planes.emplace_back (image.first, intensity_scale (image.second, [] (Color_BGR intensity) -> Color_BGR { return intensity & (1 << 6); }));
        planes.emplace_back (image.first, intensity_scale (image.second, [] (Color_BGR intensity) -> Color_BGR { return intensity & (1 << 7); }));

        for (int i = 0; i < planes.size (); i++) {
            LOG (INFO) << "Original '" << image.first << "'\t, bit plane " << i << ": "
                       << deviation_gray (image.second, planes[i].second);
            write_image (std::string ("original/planes/") + std::to_string (i), planes[i]);
        }
        LOG (INFO) << "test" << std::endl;
        return image;
    };
}

#endif //IMAGINARY_LAMBDAS_H

/* Copyright (C) Aaron Alef */
