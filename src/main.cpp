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
#include "io.hpp"

using namespace cv;
namespace fs = std::filesystem;

int main (int argc, char * argv[]) {
    google::InitGoogleLogging (argv[0]);

    auto originals = read_images (argc - 1, argv + 1);

    std::vector <std::pair <std::string, Mat>> gray_scales;
    std::transform (originals.begin(), originals.end(), std::back_inserter (gray_scales),
                    [] (std::pair <std::string, Mat> const & pair) -> std::pair <std::string, Mat> {
                        return {pair.first, grayify (pair.second.clone())};
    });

    init_out();
    for (auto const & original : originals) {
        write_image ("original", original);
    }
    for (auto const & gray_scale : gray_scales) {
        write_image ("gray", gray_scale);
    }
}
