#include "dilute.hpp"

cv::Mat dilute (cv::Mat const & src) {
    LOG_ASSERT (src.channels() == 3);

    cv::Mat dest (src.rows + 2, src.cols + 2, CV_8UC3);

    for (int y = 0; y < dest.rows; y++) {
        auto drow = dest.ptr <Color_BGR> (y);

        for (int x = 0; x < dest.cols; x++) {
            // Border cases
            if (x == 0 || x == dest.cols - 1 || y == 0 || y == dest.rows - 1) {
                int src_1_x, src_1_y;
                if (x == 0 || x == dest.cols - 1) {
                    src_1_x = x + (x ? -1 : 1);
                } else {
                    src_1_x = x;
                }
                if (y == 0 || y == dest.rows - 1) {
                    src_1_y = y + (y ? -1 : 1);
                } else {
                    src_1_y = y;
                }

                src_1_x--;
                src_1_y--;

                auto src_1 = src.at <Color_BGR> (src_1_y, src_1_x);
                auto src_2 = src.at <Color_BGR> (2 * src_1_y - y + 1, 2 * src_1_x - x + 1);
                drow [x] = {
                    (unsigned char) std::min (255, std::max (0, (2 * int (src_1.blue())  - src_2.blue()))),
                    (unsigned char) std::min (255, std::max (0, (2 * int (src_1.green()) - src_2.green()))),
                    (unsigned char) std::min (255, std::max (0, (2 * int (src_1.red())   - src_2.red())))
                };
            }
            else {
                drow [x] = src.at <Color_BGR> (y - 1, x - 1);
            }
        }
    }
    return dest;
}

cv::Mat erode (cv::Mat const & src) {
    LOG_ASSERT (src.channels () == 3);

    cv::Mat dest (src.rows - 2, src.cols - 2, CV_8UC3);

    for (int y = 0; y < dest.rows; y++) {
        auto srow = src.ptr <Color_BGR> (y + 1);
        auto drow = dest.ptr <Color_BGR> (y);

        for (int x = 0; x < dest.cols; x++) {
            drow [x] = srow [x + 1];
        }
    }
    return dest;
}
