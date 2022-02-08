#include "median.hpp"

cv::Mat median (cv::Mat const & src, int size) {
    LOG_ASSERT (size % 2);
    LOG_ASSERT (src.channels() == 3);

    auto dest = src.clone();

    for (int y = 0; y < src.rows; y++) {
        auto row = dest.ptr <Color_BGR> (y);

        for (int x = 0; x < src.cols; x++) {
            std::vector <unsigned char> reds;
            std::vector <unsigned char> greens;
            std::vector <unsigned char> blues;

            for (int j = - size / 2; j < size / 2; j++) {
                for (int i = - size / 2; i < size / 2; i++) {
                    if (within_bounds (src, x + i, y + j)) {
                        auto red   = src.at <Color_BGR> (y + j, x + i).red();
                        auto green = src.at <Color_BGR> (y + j, x + i).green();
                        auto blue  = src.at <Color_BGR> (y + j, x + i).blue();
                        reds.insert (std::lower_bound (reds.begin(), reds.end(), red), red);
                        greens.insert (std::lower_bound (greens.begin(), greens.end(), green), green);
                        blues.insert (std::lower_bound (blues.begin(), blues.end(), blue), blue);
                    }
                }
            } 
            row [x] = {blues [size / 2], greens [size / 2], reds [size / 2]};
        }
    }
    return dest;
}

cv::Mat median_gray (cv::Mat const & src, int size) {
    LOG_ASSERT (size % 2);
    LOG_ASSERT (src.channels() == 1);

    auto dest = src.clone();

    for (int y = 0; y < src.rows; y++) {
        auto row = dest.ptr <double> (y);

        for (int x = 0; x < src.cols; x++) {
            std::vector <double> values;

            for (int j = - size / 2; j < size / 2; j++) {
                for (int i = - size / 2; i < size / 2; i++) {
                    if (within_bounds (src, x + i, y + j)) {
                        double value = src.at <double> (y + j, x + i);
                        values.insert (std::lower_bound (values.begin(), values.end(), value), value);
                    }
                }
            } 
            row [x] = values [size / 2];
        }
    }
    return dest;
}

/* Copyright (C) Aaron Alef */
