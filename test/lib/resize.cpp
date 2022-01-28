#include <catch2/catch.hpp>

#include "resize.hpp"
#include "deviation.hpp"

TEST_CASE ("Resizing x1 clones") {
    cv::Mat src (10, 20, CV_64FC1);
    randu(src, cv::Scalar::all(0), cv::Scalar::all(255));
    auto dest = resize_gray (src, cv::Mat (10, 20, CV_64FC1));

    for (int y = 0; y < src.rows; y++) {
        auto src_row = src.ptr <double> (y);
        auto dest_row = dest.ptr <double> (y);
        for (int x = 0; x < src.cols; x++) {
            REQUIRE (dest_row [x] == src_row [x]);
        }
    }
}

TEST_CASE ("Gray resizing works for factor 2.0/0.5") {
    cv::Mat src (100, 100, CV_64FC1);
    randu(src, cv::Scalar::all(0), cv::Scalar::all(255));
    auto dest = resize_gray (resize_gray (src, cv::Mat (200, 200, CV_64FC1)), cv::Mat (100, 100, CV_64FC1));

    auto dev = deviation (src, dest);
    REQUIRE (dev.first == 0);
    REQUIRE (dev.second == 0);
}

TEST_CASE ("Gray resizing works for factor 2.0 without resizing back") {
    cv::Mat src (100, 100, CV_64FC1);
    randu(src, cv::Scalar::all(0), cv::Scalar::all(255));
    auto dest = resize_gray (src, cv::Mat (200, 200, CV_64FC1));

    auto dev = deviation (src, dest);
    REQUIRE (dev.first == 0);
    REQUIRE (dev.second == 0);
}

/* Copyright (C) Aaron Alef */
