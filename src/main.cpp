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
#include "gray_lambdas.hpp"

#include <functional>
#include <execution>

#define SHORT(first, second) ((unsigned short) (first + 256 * second))

using namespace cv;
using namespace std::placeholders;
namespace fs = std::filesystem;
namespace exec = std::execution;

int main (int argc, char * argv[]) {
    google::InitGoogleLogging (argv[0]);

    LOG (INFO) << "Read images";
    auto originals = read_images (argc - 1, argv + 1);

#ifndef IMAGE_OVERWRITE
    LOG (INFO) << "Clear output directory";
    init_out();
#else
    LOG (INFO) << "Overwrite previous images";
#endif

#ifdef ORIGINAL
    std::cout << "Write original images" << std::endl;
    for (auto const & original : originals) {
        write_image ("original", original);
    }

    LOG (INFO) << "Apply operations to original images";
    {
        auto apply = [& originals] (Image lambda (Image const &)) {
            std::for_each (exec::par_unseq, originals.begin (), originals.end (), lambda);
        };
//        std::cout << "mean, 3" << std::endl;
//        APPLY (original::mean_l, 3);
//        std::cout << "mean, 5" << std::endl;
//        APPLY (original::mean_l, 5);
//        std::cout << "mean, 13" << std::endl;
//        APPLY (original::mean_l, 13);
//        std::cout << "median, 3" << std::endl;
//        APPLY (original::median_l, 3);
//        std::cout << "median, 5" << std::endl;
//        APPLY (original::median_l, 5);
//        std::cout << "median, 13" << std::endl;
//        APPLY (original::median_l, 13);
//        std::cout << "convolute_gaussian, 5" << std::endl;
//        APPLY (original::convolute_gaussian_l, 5);
//        std::cout << "convolute_gaussian, 9" << std::endl;
//        APPLY (original::convolute_gaussian_l, 9);
//        std::cout << "convolute_gaussian, 19" << std::endl;
//        APPLY (original::convolute_gaussian_l, 19);
//        std::cout << "double, 1" << std::endl;
//        APPLY (original::double_l, 1);
//        std::cout << "double, 2" << std::endl;
//        APPLY (original::double_l, 2);
//        //std::cout << "double, 3" << std::endl;
//        //APPLY (original::double_l, 3);
//        //std::cout << "double, 4" << std::endl;
//        //APPLY (original::double_l, 4);
//        std::cout << "resize, 0.4" << std::endl;
//        APPLY (original::resize_l, 0.4);
//        std::cout << "resize, 1.5" << std::endl;
//        APPLY (original::resize_l, 1.5);
//        std::cout << "resize, 1.7" << std::endl;
//        APPLY (original::resize_l, 1.7);
//        std::cout << "resize, 2.3" << std::endl;
//        APPLY (original::resize_l, 2.3);
//        std::cout << "resize_dims, 401 x 809" << std::endl;
//        apply ([](Image const & image) { return original::resize_dims_l (image, 809, 401); });
//        std::cout << "1:1 original scale" << std::endl;
//        APPLY (original::intensity_scale_l, [] (Color_BGR input) { return input; });
//        std::cout << "original with inverted colours" << std::endl;
//        APPLY (original::intensity_scale_l, ([] (Color_BGR input) -> Color_BGR {
//            return { (unsigned char) (255 - input.blue()), (unsigned char) (255 - input.green()), (unsigned char) (255 - input.red()) };
//        }));
//        std::cout << "original as gray scale" << std::endl;
//        APPLY (original::intensity_scale_l, ([] (Color_BGR input) -> Color_BGR {
//            unsigned char avg = input.average();
//            return { avg, avg, avg };
//        }));
//        std::cout << "original scaled to [0..255]" << std::endl;
//        APPLY (original::scale_l, SHORT (0, 255));
//        std::cout << "original scaled to [96..160]" << std::endl;
//        APPLY (original::scale_l, SHORT (96, 160));
//        std::cout << "original sharpened" << std::endl;
//        APPLY (original::sharpen_l, nullptr);
//        std::cout << "original unsharp masked, 0.0" << std::endl;
//        APPLY (original::unsharp_mask_l, 0.0);
//        std::cout << "original unsharp masked, 1.0" << std::endl;
//        APPLY (original::unsharp_mask_l, 1.0);
//        std::cout << "original unsharp masked, 2.0" << std::endl;
//        APPLY (original::unsharp_mask_l, 2.0);
//        std::cout << "original unsharp masked, 3.0" << std::endl;
//        APPLY (original::unsharp_mask_l, 3.0);
//        std::cout << "original unsharp masked, 4.0" << std::endl;
//        APPLY (original::unsharp_mask_l, 4.0);
//        std::cout << "original unsharp masked, 5.0" << std::endl;
//        APPLY (original::unsharp_mask_l, 5.0);
//        std::cout << "original unsharp masked, 6.0" << std::endl;
//        APPLY (original::unsharp_mask_l, 6.0);
//        std::cout << "original unsharp masked, 7.0" << std::endl;
//        APPLY (original::unsharp_mask_l, 7.0);
//        std::cout << "original unsharp masked, 8.0" << std::endl;
//        APPLY (original::unsharp_mask_l, 8.0);
//        std::cout << "original unsharp masked, 9.0" << std::endl;
//        APPLY (original::unsharp_mask_l, 9.0);
//        std::cout << "original unsharp masked, 10.0" << std::endl;
//        APPLY (original::unsharp_mask_l, 10.0);
//        std::cout << "original bit planes" << std::endl;
//        APPLY (original::bits_l, nullptr);
    }
#endif

#ifdef GRAYIFY
    std::cout << "Convert to gray and write images" << std::endl;
    std::vector <Image> gray_scales;
    std::transform (originals.begin(), originals.end(), std::back_inserter (gray_scales), gray::grayify_l);

    LOG (INFO) << "Apply operations to gray images";
    {
        auto apply = [& gray_scales] (Image lambda (Image const &)) {
            std::for_each (exec::par_unseq, gray_scales.begin (), gray_scales.end (), lambda);
        };
//        std::cout << "gray_mean, 3" << std::endl;
//        APPLY (gray::mean_l, 3);
//        std::cout << "gray_mean, 5" << std::endl;
//        APPLY (gray::mean_l, 5);
//        std::cout << "gray_mean, 13" << std::endl;
//        APPLY (gray::mean_l, 13);
//        std::cout << "gray_median, 3" << std::endl;
//        APPLY (gray::median_l, 3);
//        std::cout << "gray_median, 5" << std::endl;
//        APPLY (gray::median_l, 5);
//        std::cout << "gray_median, 13" << std::endl;
//        APPLY (gray::median_l, 13);
//        std::cout << "gray_convolute_gaussian, 5" << std::endl;
//        APPLY (gray::convolute_gaussian_l, 5);
//        std::cout << "gray_convolute_gaussian, 9" << std::endl;
//        APPLY (gray::convolute_gaussian_l, 9);
//        std::cout << "gray_convolute_gaussian, 19" << std::endl;
//        APPLY (gray::convolute_gaussian_l, 19);
//        std::cout << "gray_double, 1" << std::endl;
//        APPLY (gray::double_l, 1);
//        std::cout << "gray_double, 2" << std::endl;
//        APPLY (gray::double_l, 2);
//        //std::cout << "gray_double, 3" << std::endl;
//        //APPLY (gray::double_l, 3);
//        //std::cout << "gray_double, 4" << std::endl;
//        //APPLY (gray::double_l, 4);
//        std::cout << "gray_resize, 0.4" << std::endl;
//        APPLY (gray::resize_l, 0.4);
//        std::cout << "gray_resize, 1.5" << std::endl;
//        APPLY (gray::resize_l, 1.5);
//        std::cout << "gray_resize, 1.7" << std::endl;
//        APPLY (gray::resize_l, 1.7);
//        std::cout << "gray_resize, 2.3" << std::endl;
//        APPLY (gray::resize_l, 2.3);
//        std::cout << "gray_resize_dims, 401 x 809" << std::endl;
//        apply ([](Image const & image) { return gray::resize_dims_l (image, 809, 401); });
//        std::cout << "canny edge detection" << std::endl;
//        APPLY (gray::canny_l, nullptr);
//        std::cout << "canny edge detection with threshold 80" << std::endl;
//        APPLY (gray::threshold_l, 80);
//        std::cout << "1:1 gray scale" << std::endl;
//        APPLY (gray::intensity_scale_l, [] (double input) { return input; });
//        std::cout << "gray inverted" << std::endl;
//        APPLY (gray::intensity_scale_l, [] (double input) -> double { return 255 - input; });
//        std::cout << "gray scaled to [0..255]" << std::endl;
//        APPLY (gray::scale_l, SHORT (0, 255));
//        std::cout << "gray scaled to [96..160]" << std::endl;
//        APPLY (gray::scale_l, SHORT (96, 160));
//        std::cout << "gray sharpened" << std::endl;
//        APPLY (gray::sharpen_l, nullptr);
//        std::cout << "gray unsharp masked, 0.0" << std::endl;
//        APPLY (gray::unsharp_mask_l, 0.0);
//        std::cout << "gray unsharp masked, 1.0" << std::endl;
//        APPLY (gray::unsharp_mask_l, 1.0);
//        std::cout << "gray unsharp masked, 2.0" << std::endl;
//        APPLY (gray::unsharp_mask_l, 2.0);
//        std::cout << "gray unsharp masked, 3.0" << std::endl;
//        APPLY (gray::unsharp_mask_l, 3.0);
//        std::cout << "gray unsharp masked, 4.0" << std::endl;
//        APPLY (gray::unsharp_mask_l, 4.0);
//        std::cout << "gray unsharp masked, 5.0" << std::endl;
//        APPLY (gray::unsharp_mask_l, 5.0);
//        std::cout << "gray unsharp masked, 6.0" << std::endl;
//        APPLY (gray::unsharp_mask_l, 6.0);
//        std::cout << "gray unsharp masked, 7.0" << std::endl;
//        APPLY (gray::unsharp_mask_l, 7.0);
//        std::cout << "gray unsharp masked, 8.0" << std::endl;
//        APPLY (gray::unsharp_mask_l, 8.0);
//        std::cout << "gray unsharp masked, 9.0" << std::endl;
//        APPLY (gray::unsharp_mask_l, 9.0);
//        std::cout << "gray unsharp masked, 10.0" << std::endl;
//        APPLY (gray::unsharp_mask_l, 10.0);
//        std::cout << "gray bit planes" << std::endl;
//        APPLY (gray::bits_l, nullptr);
//        std::cout << "gray dct compression" << std::endl;
//        APPLY (gray::compress_l, 0b1111111011111100111110001111000011100000110000001000000000000000);
//        APPLY (gray::compress_l, ~ long(0));
//        APPLY (gray::compress_l, 0b1000000000000000000000000000000000000000000000000000000000000000);
        std::cout << "gray fdct" << std::endl;
        APPLY (gray::fast_dct_l, nullptr);
//        std::cout << "gray dct" << std::endl;
//        APPLY (gray::dct_l, nullptr);
    }
#endif

#ifdef RANDOM
    std::cout << "Constructing random images" << std::endl;
    cv::Mat random (500, 800, CV_8UC3);
    randu(random, cv::Scalar::all(0), cv::Scalar::all(255));
    write_image ("random", Image ("random.png", random));
#endif
}
