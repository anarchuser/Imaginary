#include "dilute.hpp"

cv::Mat dilute (cv::Mat const & src, int size) {
    LOG_ASSERT (src.channels() == 3);
    
    cv::Mat dest (src.rows + 2 * size, src.cols + 2 * size, CV_8UC3);
    
    // Copy untouched center region
    for (int y = 0; y < src.rows; y++) {
        auto srow = src.ptr <Color_BGR> (y);
        auto drow = dest.ptr <Color_BGR> (y + size);

        for (int x = 0; x < src.cols; x++) {
            drow [x + size] = srow [x];
        }
    }
    
    // Corners
    for (int i = size - 1; i >= 0; i--) {
        for (auto y : {i, dest.rows - 1 - i}) {
            auto drow = dest.ptr <Color_BGR> (y);
            
            for (auto x : {i, dest.cols - 1 - i}) {
                auto src_1 = dest.at <Color_BGR> (y + (y < size ? 1 : -1), x + (x < size ? 1 : -1));
                auto src_2 = dest.at <Color_BGR> (y + (y < size ? 2 : -2), x + (x < size ? 2 : -2));
                
                drow [x] = {
                        (unsigned char) std::min (255, std::max (0, (2 * int (src_1.blue())  - src_2.blue()))),
                        (unsigned char) std::min (255, std::max (0, (2 * int (src_1.green()) - src_2.green()))),
                        (unsigned char) std::min (255, std::max (0, (2 * int (src_1.red())   - src_2.red())))
                };
            }
        }
    }
    
    for (int i = size - 1; i >= 0; i--) {
        // Vertical borders
        for (auto x : {i, dest.cols - 1 - i}) {
            for (int y = i + 1; y < dest.rows - i - 1; y++) {
                auto drow = dest.ptr <Color_BGR> (y);

                auto src_1 = dest.at <Color_BGR> (y, x + (x < size ? 1 : -1));
                auto src_2 = dest.at <Color_BGR> (y, x + (x < size ? 2 : -2));

                drow[x] = {(unsigned char) std::min (255, std::max (0, (2 * int (src_1.blue ()) - src_2.blue ())))
                          , (unsigned char) std::min (255, std::max (0, (2 * int (src_1.green ()) - src_2.green ())))
                          , (unsigned char) std::min (255, std::max (0, (2 * int (src_1.red ()) - src_2.red ())))
                };
            }
        }
        
        // Horizontal borders
        for (auto y : {i, dest.rows - 1 - i}) {
            auto drow = dest.ptr <Color_BGR> (y);
            auto src_1_row = dest.ptr <Color_BGR> (y + (y < size ? 1 : -1));
            auto src_2_row = dest.ptr <Color_BGR> (y + (y < size ? 2 : -2));

            for (int x = i + 1; x < dest.cols - i - 1; x++) {
                drow[x] = { 2 * int (src_1_row [x].blue ()) - src_2_row [x].blue ()
                          , 2 * int (src_1_row [x].green ()) - src_2_row [x].green ()
                          , 2 * int (src_1_row [x].red ()) - src_2_row [x].red ()
                };
            }
        }
    }
    
    return dest;
}

cv::Mat erode (cv::Mat const & src, int size) {
    LOG_ASSERT (src.channels () == 3);
    
    cv::Mat dest (src, cv::Rect2i (size, size, src.cols - 2 * size, src.rows - 2 * size));
    return dest;
}
