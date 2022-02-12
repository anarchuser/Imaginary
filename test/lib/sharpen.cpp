
#include <catch2/catch.hpp>

#include "sharpen.hpp"
#include "deviation.hpp"

TEST_CASE ("Unmask sharpening with factor 0 doesn't modify the image") {
    cv::Mat original (10, 20, CV_8UC3);
    randu(original, cv::Scalar::all(0), cv::Scalar::all(255));
    auto sharpened = unsharp_mask (original, 0);

    for (int y = 0; y < original.rows; y++) {
        auto orow = original.ptr <Color_BGR> (y);
        auto srow = sharpened.ptr <Color_BGR> (y);
        for (int x = 0; x < original.cols; x++) {
            REQUIRE (srow [x] == orow [x]);
        }
    }
}

/* Copyright (C) Aaron Alef */