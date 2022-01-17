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

using namespace cv;
namespace fs = std::filesystem;

int main (int argc, char * argv[]) {
    google::InitGoogleLogging (argv[0]);

    std::vector <std::pair <std::string, Mat>> originals;
    // Read all files from argv
    std::cout << "Files read from arguments:" << std::endl;
    for (std::size_t i = 1; i < argc; i++) {
        Mat image = imread (argv [i]);
        if (image.empty ()) continue;
        std::cout << argv [i] << ":\t" << image.rows << 'x' << image.cols << std::endl;
        originals.emplace_back (fs::path (argv [i]).filename(), std::move (image));
    }

    // Read all files in IMG_IN dir
    std::cout << "Files read from IMG_IN directory:" << std::endl;
    for (auto const & file : fs::directory_iterator (IMG_IN)) {
        Mat image = imread (file.path());
        if (image.empty ()) continue;
        std::cout << file.path() << ":\t" << image.rows << 'x' << image.cols << std::endl;
        originals.emplace_back (fs::path (file).filename(), std::move (image));
    }

    for (auto const & original : originals) {
        imwrite (IMG_OUT / original.first, original.second);
    }
}
