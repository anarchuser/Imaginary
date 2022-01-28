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

#include "config.h"

#include "io.hpp"
#include "lambdas.hpp"

#include <functional>

using namespace cv;
using namespace std::placeholders;
namespace fs = std::filesystem;

int main (int argc, char * argv[]) {
    google::InitGoogleLogging (argv[0]);

    LOG (INFO) << "Read images";
    auto originals = read_images (argc - 1, argv + 1);

    LOG (INFO) << "Clear output directory";
    init_out();

    LOG (INFO) << "Write original images";
    for (auto const & original : originals) {
        write_image ("original", original);
    }

    LOG (INFO) << "Convert to gray and write images";
    std::vector <Image> gray_scales;
    std::transform (originals.begin(), originals.end(), std::back_inserter (gray_scales), grayify_l);

    LOG (INFO) << "Apply operations to original images";
    {
        auto apply = [& originals] (Image lambda (Image const &)) {
            std::for_each (originals.begin (), originals.end (), lambda);
        };
//        LOG (INFO) << "convolute_1s, 3";
//        APPLY (convolute_1s_l, 3);
//        LOG (INFO) << "convolute_1s, 5";
//        APPLY (convolute_1s_l, 5);
//        LOG (INFO) << "convolute_1s, 13";
//        APPLY (convolute_1s_l, 13);
//        LOG (INFO) << "convolute_gaussian, 5";
//        APPLY (convolute_gaussian_l, 5);
//        LOG (INFO) << "convolute_gaussian, 9";
//        APPLY (convolute_gaussian_l, 9);
//        LOG (INFO) << "convolute_gaussian, 19";
//        APPLY (convolute_gaussian_l, 19);
//        LOG (INFO) << "double, 1";
//        APPLY (double_l, 1);
//        LOG (INFO) << "double, 2";
//        APPLY (double_l, 2);
//        LOG (INFO) << "double, 3";
//        APPLY (double_l, 3);
//        LOG (INFO) << "double, 4";
//        APPLY (double_l, 4);
    }

    LOG (INFO) << "Apply operations to gray images";
    {
        auto apply = [& gray_scales] (Image lambda (Image const &)) {
            std::for_each (gray_scales.begin (), gray_scales.end (), lambda);
        };
//        LOG (INFO) << "gray_convolute_1s, 3";
//        APPLY (gray_convolute_1s_l, 3);
//        LOG (INFO) << "gray_convolute_1s, 5";
//        APPLY (gray_convolute_1s_l, 5);
//        LOG (INFO) << "gray_convolute_1s, 13";
//        APPLY (gray_convolute_1s_l, 13);
//        LOG (INFO) << "gray_convolute_gaussian, 5";
//        APPLY (gray_convolute_gaussian_l, 5);
//        LOG (INFO) << "gray_convolute_gaussian, 9";
//        APPLY (gray_convolute_gaussian_l, 9);
//        LOG (INFO) << "gray_convolute_gaussian, 19";
//        APPLY (gray_convolute_gaussian_l, 19);
//        LOG (INFO) << "gray_double, 1";
//        APPLY (gray_double_l, 1);
//        LOG (INFO) << "gray_double, 2";
//        APPLY (gray_double_l, 2);
//        LOG (INFO) << "gray_double, 3";
//        APPLY (gray_double_l, 3);
//        LOG (INFO) << "gray_double, 4";
//        APPLY (gray_double_l, 4);

//        LOG (INFO) << "gray_resize, 0.25";
//        APPLY (gray_resize_l, 0.25);
//        LOG (INFO) << "gray_resize, 0.5";
//        APPLY (gray_resize_l, 0.5);
//        LOG (INFO) << "gray_resize, 0.7";
//        APPLY (gray_resize_l, 0.7);
//        LOG (INFO) << "gray_resize, 1.0";
//        APPLY (gray_resize_l, 1.0);
//        LOG (INFO) << "gray_resize, 1.5";
//        APPLY (gray_resize_l, 1.5);
//        LOG (INFO) << "gray_resize, 2.0";
//        APPLY (gray_resize_l, 2.0);
//        LOG (INFO) << "gray_resize, 2.5";
//        APPLY (gray_resize_l, 2.5);
//        LOG (INFO) << "gray_resize, 1.1";
//        APPLY (gray_resize_l, 1.1);
        for (double d = 1.1; d < 10.1; d += 0.1) {
            LOG (INFO) << "gray_resize, " << d;
            std::for_each (gray_scales.begin (), gray_scales.end (), [d](Image const & image) {
                return gray_resize_l (image, d);
            });
        }
//        for (int y = 100; y < 4500; y += 100) {
//            for (int x = 100; x < 2500; x += 100) {
//                LOG (INFO) << "gray_resize, " << x  << 'x' << y;
//                std::for_each (gray_scales.begin (), gray_scales.end (), [x, y](Image const & image) {
//                    return gray_resize_dims_l (image, x, y);
//                });
//            }
//        }
    }

#ifdef CONVOLUTE
    LOG (INFO) << "Constructing Gaussian Kernels from size 1² to 35²";
    fs::create_directories (IMG_OUT / "gaussian");
    for (int size = 1; size <= 21; size += 2) {
        LOG (INFO) << "Gaussian kernel " << square_string (size);
        auto gaussian = cv::getGaussianKernel (size * size, 10, CV_64F).reshape (1, size);
        std::cout << gaussian << std::endl << std::endl;
        cv::imwrite (IMG_OUT / "gaussian" / (square_string (size) + ".jpg"), gaussian);
    }
#endif

#ifdef RANDOM
    LOG (INFO) << "Constructing random images";
    cv::Mat random (500, 800, CV_64FC1);
    randu(random, cv::Scalar::all(0), cv::Scalar::all(255));
    write_image ("random", Image ("random.png", random));
#endif
}
