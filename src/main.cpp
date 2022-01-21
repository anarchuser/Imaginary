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
#include "convolute.hpp"
#include "resize.hpp"

#include "io.hpp"

using namespace cv;
namespace fs = std::filesystem;

using Image = std::pair <std::string, Mat>;

int main (int argc, char * argv[]) {
    google::InitGoogleLogging (argv[0]);

    auto originals = read_images (argc - 1, argv + 1);

    // Write originals
    init_out();
    for (auto const & original : originals) {
        write_image ("original", original);
    }

#ifdef CONVOLUTE
    std::cout << "Convoluting gray scales with 3x3 1's" << std::endl;
    std::vector <Image> convoluted_3x3;
    std::transform (originals.begin(), originals.end(), std::back_inserter (convoluted_3x3),
                    [] (Image const & image) -> Image {
                        auto img = convolute (image.second, Mat (3, 3, CV_8UC1, 1));
                        Image out (image.first, img);
                        write_image ("convoluted/1's/3x3", out);
                        return out;
                    });
    std::cout << "Convoluting gray scales with 7x7 1's" << std::endl;
    std::vector <Image> convoluted_7x7;
    std::transform (originals.begin(), originals.end(), std::back_inserter (convoluted_7x7),
                    [] (Image const & image) -> Image {
                        auto img = convolute (image.second, Mat (7, 7, CV_8UC1, 1));
                        Image out (image.first, img);
                        write_image ("convoluted/1's/7x7", out);
                        return out;
                    });
    std::cout << "Convoluting gray scales with 5x5 Gaussian" << std::endl;
    std::vector <Image> convoluted_5x5_gaussian;
    std::transform (originals.begin(), originals.end(), std::back_inserter (convoluted_5x5_gaussian),
                    [] (Image const & image) -> Image {
                        Image out (image.first, convolute (image.second, Mat_<unsigned char> ({
                                1,  4,  7,  4, 1,
                                4, 16, 26, 16, 4,
                                7, 26, 41, 26, 7,
                                4, 16, 26, 16, 4,
                                1,  4,  7,  4, 1
                        }).reshape (5)));
                        write_image ("convoluted/gaussian/5x5", out);
                        return out;
                    });
    std::cout << "Convoluting gray scales with 5x5 Gaussian (40 times)" << std::endl;
    std::vector <Image> convoluted_5x5_40x_gaussian;
    std::transform (originals.begin(), originals.end(), std::back_inserter (convoluted_5x5_40x_gaussian),
                    [] (Image const & image) -> Image {
                        auto gauss = Mat_<unsigned char> ({
                                1,  4,  7,  4, 1,
                                4, 16, 26, 16, 4,
                                7, 26, 41, 26, 7,
                                4, 16, 26, 16, 4,
                                1,  4,  7,  4, 1
                        }).reshape (5);
                        Mat img = image.second;
                        for (int i = 0; i < 40; i++) {
                            img = convolute (img, gauss);
                        }
                        Image out (image.first, img);
                        write_image ("convoluted/gaussian/5x5_x40", out);
                        return out;
                    });
#endif

#ifdef MULTIPLY_x2
    std::cout << "Calculating originals x2" << std::endl;
    std::vector <Image> originals_2;
    std::transform (originals.begin(), originals.end(), std::back_inserter (originals_2),
                    [] (Image const & image) -> Image {
                        Image out (image.first, twice (image.second));
                        write_image ("original/x2", out);
                        return out;
    });

#ifdef MULTIPLY_x16
    std::cout << "Calculating originals x16" << std::endl;
    std::vector <Image> originals_16;
    std::transform (originals_2.begin(), originals_2.end(), std::back_inserter (originals_16),
                    [] (Image const & image) -> Image {
                        Image out (image.first, twice (twice (twice (image.second))));
                        write_image ("original/x16", out);
                        return out;
    });
#endif
#endif

#ifdef GRAYIFY
    std::cout << "Calculating gray scale" << std::endl;
    std::vector <Image> gray_scales;
    std::transform (originals.begin(), originals.end(), std::back_inserter (gray_scales),
                    [] (Image const & image) -> Image {
                        Image out (image.first, grayify (image.second));
                        write_image ("gray", out);
                        return out;
                    });

#ifdef RESIZE
    std::cout << "Calculating gray scale x1" << std::endl;
    std::vector <Image> gray_scales_x1;
    std::transform (gray_scales.begin(), gray_scales.end(), std::back_inserter (gray_scales_x1),
                    [] (Image const & image) -> Image {
                        Image out (image.first, resize_gray (image.second, image.second.clone()));
                        write_image ("gray/resize/x1", out);
                        return out;
    });

    std::cout << "Calculating gray scale x2" << std::endl;
    std::vector <Image> gray_scales_x2;
    std::transform (gray_scales.begin(), gray_scales.end(), std::back_inserter (gray_scales_x2),
                    [] (Image const & image) -> Image {
                        Image out (image.first, resize_gray (image.second, cv::Mat (image.second.rows * 2, image.second.cols * 2, CV_64FC1)));
                        write_image ("gray/resize/x2", out);
                        return out;
                    });
    std::cout << "Calculating gray scale x3" << std::endl;
    std::vector <Image> gray_scales_x3;
    std::transform (gray_scales.begin(), gray_scales.end(), std::back_inserter (gray_scales_x3),
                    [] (Image const & image) -> Image {
                        Image out (image.first, resize_gray (image.second, cv::Mat (image.second.rows * 3, image.second.cols * 3, CV_64FC1)));
                        write_image ("gray/resize/x3", out);
                        return out;
                    });
#endif

#ifdef CONVOLUTE
    std::cout << "Convoluting gray scales with 3x3 1's" << std::endl;
    std::vector <Image> convoluted_3x3_gray;
    std::transform (gray_scales.begin(), gray_scales.end(), std::back_inserter (convoluted_3x3_gray),
                    [] (Image const & image) -> Image {
                        auto img = convolute_gray (image.second, Mat (3, 3, CV_8UC1, 1));
                        Image out (image.first, img);
                        write_image ("gray/convoluted/1's/3x3", out);
                        return out;
                    });
    std::cout << "Convoluting gray scales with 7x7 1's" << std::endl;
    std::vector <Image> convoluted_7x7_gray;
    std::transform (gray_scales.begin(), gray_scales.end(), std::back_inserter (convoluted_7x7_gray),
                    [] (Image const & image) -> Image {
                        auto img = convolute_gray (image.second, Mat (7, 7, CV_8UC1, 1));
                        Image out (image.first, img);
                        write_image ("gray/convoluted/1's/7x7", out);
                        return out;
                    });
    std::cout << "Convoluting gray scales with 5x5 Gaussian" << std::endl;
    std::vector <Image> convoluted_5x5_gaussian_gray;
    std::transform (gray_scales.begin(), gray_scales.end(), std::back_inserter (convoluted_5x5_gaussian_gray),
                    [] (Image const & image) -> Image {
                        Image out (image.first, convolute_gray (image.second, Mat({
                            1,  4,  7,  4, 1,
                            4, 16, 26, 16, 4,
                            7, 26, 41, 26, 7,
                            4, 16, 26, 16, 4,
                            1,  4,  7,  4, 1,
                        }).reshape (5)));
                        write_image ("gray/convoluted/gaussian/5x5", out);
                        return out;
                    });
#endif

#ifdef MULTIPLY_x2
    std::cout << "Calculating gray scale x2" << std::endl;
    std::vector <Image> gray_scales_2;
    std::transform (gray_scales.begin(), gray_scales.end(), std::back_inserter (gray_scales_2),
                    [] (Image const & image) -> Image {
                        Image out (image.first, twice_gray (image.second));
                        write_image ("gray/x2", out);
                        return out;
    });

#ifdef MULTIPLY_x16
    std::cout << "Calculating gray scale x16" << std::endl;
    std::vector <Image> gray_scales_16;
    std::transform (gray_scales_2.begin(), gray_scales_2.end(), std::back_inserter (gray_scales_16),
                    [] (Image const & image) -> Image {
                        Image out (image.first, twice_gray (twice_gray (twice_gray (image.second))));
                        write_image ("gray/x16", out);
                        return out;
    });
#endif
#endif
#endif

#ifdef RANDOM
    std::cout << "Constructing random images" << std::endl;
    cv::Mat random (500, 800, CV_64FC1);
    randu(random, cv::Scalar::all(0), cv::Scalar::all(255));
    write_image ("random", Image ("random.png", random));

#endif
}
