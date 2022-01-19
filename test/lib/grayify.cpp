#include <catch2/catch.hpp>

#include "grayify.hpp"

TEST_CASE ("Gray conversion works") {
    cv::Mat src (10, 10, CV_8UC3, cv::Scalar (0, 200, 100));
    auto dest = grayify (src);

    REQUIRE (src.total() == dest.total());
    REQUIRE (dest.depth() == CV_64F);
    for (int y = 0; y < src.rows; y++) {
        auto row = dest.ptr <double> (y);
        for (int x = 0; x < src.cols; x++) {
            REQUIRE (row [x] == 100.0);
        }
    }
}

/* Copyright (C) Aaron Alef */
