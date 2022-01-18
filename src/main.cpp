/* Copyright (C) 2022 Aaron Alef <aaron.alef@code.berlin>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program (e.g., ./LICENSE).
 * If not, see <https://www.gnu.org/licenses/>.
 */

#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>

#include "config.h"

#include "grayify.hpp"
#include "multiply.hpp"

#include "io.hpp"

using namespace cv;
namespace fs = std::filesystem;

int main (int argc, char * argv[]) {
    google::InitGoogleLogging (argv[0]);

    auto originals = read_images (argc - 1, argv + 1);

    // Write originals
    init_out();
    for (auto const & original : originals) {
        write_image ("original", original);
    }

#ifdef MULTIPLY_x2
    std::cout << "Calculating originals x2" << std::endl;
    std::vector <std::pair <std::string, Mat>> originals_2;
    std::transform (originals.begin(), originals.end(), std::back_inserter (originals_2),
                    [] (std::pair <std::string, Mat> const & pair) -> std::pair <std::string, Mat> {
                        return {pair.first, twice (pair.second)};
    });
    for (auto const & original : originals_2) {
        write_image ("original_2", original);
    }

#ifdef MULTIPLY_x16
    std::cout << "Calculating originals x16" << std::endl;
    std::vector <std::pair <std::string, Mat>> originals_16;
    std::transform (originals_2.begin(), originals_2.end(), std::back_inserter (originals_16),
                    [] (std::pair <std::string, Mat> const & pair) -> std::pair <std::string, Mat> {
                        return {pair.first, twice (twice (twice (twice (pair.second))))};
                    });
    for (auto const & original : originals_16) {
        write_image ("original_16", original);
    }
#endif
#endif

#ifdef GRAYIFY
    std::cout << "Calculating gray scale" << std::endl;
    std::vector <std::pair <std::string, Mat>> gray_scales;
    std::transform (originals.begin(), originals.end(), std::back_inserter (gray_scales),
                    [] (std::pair <std::string, Mat> const & pair) -> std::pair <std::string, Mat> {
                        return {pair.first, grayify (pair.second)};
                    });
    for (auto const & gray_scale : gray_scales) {
        write_image ("gray", gray_scale);
    }

#ifdef MULTIPLY_x2
    std::cout << "Calculating gray scale x2" << std::endl;
    std::vector <std::pair <std::string, Mat>> gray_scales_2;
    std::transform (gray_scales.begin(), gray_scales.end(), std::back_inserter (gray_scales_2),
                    [] (std::pair <std::string, Mat> const & pair) -> std::pair <std::string, Mat> {
                        return {pair.first, twice_gray (pair.second)};
                    });
    for (auto const & gray_scale : gray_scales_2) {
        write_image ("gray_2", gray_scale);
    }

#ifdef MULTIPLY_x16
    std::cout << "Calculating gray scale x16" << std::endl;
    std::vector <std::pair <std::string, Mat>> gray_scales_16;
    std::transform (gray_scales_2.begin(), gray_scales_2.end(), std::back_inserter (gray_scales_16),
                    [] (std::pair <std::string, Mat> const & pair) -> std::pair <std::string, Mat> {
                        return {pair.first, twice_gray (twice_gray (twice_gray (pair.second)))};
                    });
    for (auto const & gray_scale : gray_scales_16) {
        write_image ("gray_16", gray_scale);
    }
#endif
#endif
#endif
}
