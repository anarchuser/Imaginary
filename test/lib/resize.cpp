#include <catch2/catch.hpp>

#include "resize.hpp"

TEST_CASE ("Resizing x1 clones") {
    cv::Mat src (10, 20, CV_64FC1);
    randu(src, cv::Scalar::all(0), cv::Scalar::all(1));
    auto dest = resize_gray (src, cv::Mat (10, 20, CV_64FC1));

    for (int y = 0; y < src.rows; y++) {
        auto src_row = src.ptr <double> (y);
        auto dest_row = dest.ptr <double> (y);
        for (int x = 0; x < src.cols; x++) {
            REQUIRE (dest_row [x] == src_row [x]);
        }
    }
}

/* Copyright (C) Aaron Alef */
