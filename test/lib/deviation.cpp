#include <catch2/catch.hpp>

#include "deviation.hpp"

TEST_CASE ("Coloured deviation works") {
    cv::Mat src (100, 100, CV_8UC3);
    randu(src, cv::Scalar::all(0), cv::Scalar::all(255));

    Deviation dev = deviation (src, src);
    REQUIRE (dev.first == 0);
    REQUIRE (dev.second == 0);
}

TEST_CASE ("Gray deviation works") {
    cv::Mat src (100, 100, CV_64FC1);
    randu(src, cv::Scalar::all(0), cv::Scalar::all(255));
    
    Deviation dev = deviation_gray (src, src);
    REQUIRE (dev.first == 0);
    REQUIRE (dev.second == 0);
}

/* Copyright (C) Aaron Alef */