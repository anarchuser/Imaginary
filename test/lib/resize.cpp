#include <catch2/catch.hpp>

#include "resize.hpp"
#include "deviation.hpp"

TEST_CASE ("Coloured resizing works for x1 clones") {
    cv::Mat src (10, 20, CV_8UC3);
    randu(src, cv::Scalar::all(0), cv::Scalar::all(255));
    auto dest = resize (src, cv::Mat (10, 20, CV_8UC3));
    
    for (int y = 0; y < src.rows; y++) {
        auto src_row = src.ptr <Color_BGR> (y);
        auto dest_row = dest.ptr <Color_BGR> (y);
        for (int x = 0; x < src.cols; x++) {
            REQUIRE (dest_row [x] == src_row [x]);
        }
    }
}

TEST_CASE ("Coloured resizing works for factor 2.0/0.5") {
    cv::Mat const src (100, 100, CV_8UC3);
    randu(src, cv::Scalar::all(0), cv::Scalar::all(255));
    auto dest = resize (resize (src, cv::Mat (200, 200, CV_8UC3)), cv::Mat (100, 100, CV_8UC3));
    
    auto dev = deviation (src, dest);
    REQUIRE (dev.first == 0);
    REQUIRE (dev.second == 0);
}

TEST_CASE ("Coloured resizing works for factor 2.0 without resizing back") {
    cv::Mat const src (100, 100, CV_8UC3);
    randu(src, cv::Scalar::all(0), cv::Scalar::all(255));
    auto dest = resize (src, cv::Mat (200, 200, CV_8UC3));
    
    auto dev = deviation (src, dest);
    REQUIRE (dev.first == 0);
    REQUIRE (dev.second == 0);
}

TEST_CASE ("Coloured resizing between different fractions works within confidence interval") {
    double const AVERAGE_DEVIATION = 1e-3;
    
    cv::Mat src (18, 10, CV_8UC3);
    randu(src, cv::Scalar::all(0), cv::Scalar::all(255));
    src = resize (src, cv::Mat (10 * src.rows, 10 * src.cols, CV_8UC3));
    
    for (int divisor = 2; divisor < 20; divisor++) {
        for (int dividend = divisor; dividend < 40; ++dividend) {
            auto dest = resize (src, cv::Mat (src.rows * dividend / divisor,
                    src.cols * dividend / divisor, CV_8UC3));
            
            auto dev = deviation (src, dest);
            REQUIRE (dev.first  < AVERAGE_DEVIATION * dest.cols * dest.rows);
        }
    }
}

TEST_CASE ("Gray resizing works for x1 clones") {
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
    cv::Mat const src (100, 100, CV_64FC1);
    randu(src, cv::Scalar::all(0), cv::Scalar::all(255));
    auto dest = resize_gray (resize_gray (src, cv::Mat (200, 200, CV_64FC1)), cv::Mat (100, 100, CV_64FC1));

    auto dev = deviation_gray (src, dest);
    REQUIRE (dev.first == 0);
    REQUIRE (dev.second == 0);
}

TEST_CASE ("Gray resizing works for factor 2.0 without resizing back") {
    cv::Mat const src (100, 100, CV_64FC1);
    randu(src, cv::Scalar::all(0), cv::Scalar::all(255));
    auto dest = resize_gray (src, cv::Mat (200, 200, CV_64FC1));

    auto dev = deviation_gray (src, dest);
    REQUIRE (dev.first == 0);
    REQUIRE (dev.second == 0);
}

TEST_CASE ("Gray resizing between different fractions works within confidence interval") {
    double const AVERAGE_DEVIATION = 1e-3;
    
    cv::Mat src (18, 10, CV_64FC1);
    randu(src, cv::Scalar::all(0), cv::Scalar::all(255));
    src = resize_gray (src, cv::Mat (10 * src.rows, 10 * src.cols, CV_64FC1));
    
    for (int divisor = 2; divisor < 20; divisor++) {
        for (int dividend = divisor; dividend < 40; ++dividend) {
            auto dest = resize_gray (src, cv::Mat (src.rows * dividend / divisor,
                                                   src.cols * dividend / divisor, CV_64FC1));
            
            auto dev = deviation_gray (src, dest);
            REQUIRE (dev.first  < AVERAGE_DEVIATION * dest.cols * dest.rows);
        }
    }
}

/* Copyright (C) Aaron Alef */
