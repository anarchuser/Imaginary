#include "dct.hpp"

BitMask::BitMask (uint64 mask) : mask {mask} {}

BitMask::BitMask (unsigned char const mask [8]) : mask {* (unsigned long *) mask} {}

bool BitMask::check (unsigned char x, unsigned char y) const {
    unsigned char ix = 7 - x;
    unsigned char iy = 7 - y;
    return mask & (long(1) << (8 * iy + ix));
}

double dct_forward_scale (double freq) {
    // scale values between ~[-1.000.000, 1.000.000] to [0, 256]
    double sign  = (freq > 0) - (freq < 0);
    double value = std::abs (freq);
    return sign * 1 * log (value) + 127;
}

double dct_backward_scale (double freq) {
    double scaled = freq - 127;
    double sign  = (scaled > 0) - (scaled < 0);
    double value = std::abs (scaled);
    return scaled;
}

cv::Mat dct_gray (cv::Mat const & src) {
    LOG_ASSERT (src.channels() == 1);

    cv::Mat dest (src.rows / DCT_COMPRESS, src.cols / DCT_COMPRESS, CV_64FC1);

#pragma omp parallel for
    for (int v = 0; v < dest.rows; v++) {
        auto drow = dest.ptr <double> (v);

        for (int u = 0; u < dest.cols; u++) {
            double z = 0.0;
            double Cu = u ? 1.0 : (1.0 / sqrt (2.0));
            double Cv = v ? 1.0 : (1.0 / sqrt (2.0));

            for (int y = 0; y < src.rows; y++) {
                auto srow = src.ptr <double> (y);

                for (int x = 0; x < src.cols; x++) {
                    double S = srow [x];
                    double q = S *
                               cos ((2.0 * x + 1) * u * PI / (2 * dest.cols)) *
                               cos ((2.0 * y + 1) * v * PI / (2 * dest.rows));
                    z += q;
                }
            }
            drow [u] = dct_forward_scale (0.25 * Cu * Cv * z);
            //if (!v) std::cout << "F(" << u << ",\t" << v << ") = " << drow [u] << std::endl;
        }
    }
    std::cout << "DCT Done" << std::endl;
    return dest;
}

cv::Mat fast_dct_gray (cv::Mat const & src) {
    LOG_ASSERT (src.channels() == 1);

    cv::Mat dest ((src.rows / 8) * 8, (src.cols / 8) * 8, CV_64FC1);

#pragma omp parallel for
    for (int y = 0; y < dest.rows; y += 8) {
        for (int x = 0; x < dest.cols; x += 8) {
            cv::Rect2i section (x, y, 8, 8);
            int window[8][8];
            fast_dct_window_gray ({src, section}, window);
            for (int j = 0; j < 8; j++) {
                for (int i = 0; i < 8; i++) {
                    //if (!i && !j) window [j][i] /= 8;
                    //else window [j][i] *= 16;
                    //window [j][i] += 128;
                    //window [j][i] = std::log (window [j][i]);
                    dest.at <double> (y + j, x + i) = std::min (255.0, std::max (0.0, (double) window [j][i]));
                }
            }
        }
    }
    return dest;
}

cv::Mat idct_gray (cv::Mat const & src) {
    LOG_ASSERT (src.channels() == 1);

    cv::Mat dest (src.rows * DCT_COMPRESS, src.cols * DCT_COMPRESS, CV_64FC1);

#pragma omp parallel for
    for (int y = 0; y < dest.rows; y++) {
        auto drow = dest.ptr <double> (y);

        for (int x = 0; x < dest.cols; x++) {
            double z = 0.0;

            for (int v = 0; v < src.rows; v++) {
                auto srow = src.ptr <double> (v);

                for (int u = 0; u < src.cols; u++) {
                    double S = dct_backward_scale (srow [u]);
                    double Cu = u ? 1.0 : (1.0 / sqrt (2.0));
                    double Cv = v ? 1.0 : (1.0 / sqrt (2.0));
                    double q = Cu * Cv * S *
                               cos ((2.0 * x + 1) * u * PI / (2 * dest.cols)) *
                               cos ((2.0 * y + 1) * v * PI / (2 * dest.rows));
                    z += q;
                }
            }
            drow [x] = std::max (0.0, std::min (255.0, 0.125 * z + 127));
            //if (!y) std::cout << "I(" << x << ",\t" << y << ") = " << drow [x] << std::endl;
        }
        //std::cout << y << " / " << dest.rows << std::endl;
    }
    std::cout << "Inverse DCT Done" << std::endl;
    return dest;
}

cv::Mat fast_idct_gray (cv::Mat const & src) {
    LOG_ASSERT (src.channels() == 1);

    cv::Mat dest (src.rows, src.cols, CV_64FC1);

#pragma omp parallel for
    for (int y = 0; y < dest.rows; y += 8) {
        for (int x = 0; x < dest.cols; x += 8) {
            cv::Rect2i section (x, y, 8, 8);
            int window[8][8];
            for (int j = 0; j < 8; j++) {
                auto srow = src.ptr <double> (y + j);

                for (int i = 0; i < 8; i++) {
                    window [j][i] = srow [x + i];
                    //window [j][i] = exp (window [j][i]);
                    //window [j][i] -= 128;
                    //if (!i && !j) window [j][i] *= 8;
                    //else window [j][i] /= 16;
                }
            }
            fast_idct_window_gray (window, {dest, section});
        }
    }
    return dest;
}


void mask_gray (int window [8][8], BitMask mask) {
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            window [x][y] *= mask.check (x, y);
        }
    }
}

cv::Mat compress_dct_gray (cv::Mat const & src, BitMask mask) {
    LOG_ASSERT (src.channels() == 1);

    // Truncate to modulo 8 == 0 in either dimension. TODO: fix this
    cv::Mat dest ((src.rows / 8) * 8, (src.cols / 8) * 8, CV_64FC1);

    for (int y = 0; y < dest.rows; y += 8) {
        for (int x = 0; x < dest.cols; x += 8) {
            cv::Rect2i section (x, y, 8, 8);
            int window [8][8];
            fast_dct_window_gray ({src, section}, window);
            mask_gray (window, mask);
            fast_idct_window_gray (window, {dest, section});
        }
    }
    return dest;
}

void fast_dct_window_gray (cv::Mat const && src, int window [8][8]) {
    LOG_ASSERT (src.channels() == 1);
    LOG_ASSERT (src.rows == 8);
    LOG_ASSERT (src.cols == 8);

    int x[9];
    static int const c1   = int (cos (    PI / 16)) << 10,
                     s1   = int (sin (    PI / 16)) << 10,
                     c3   = int (cos (3 * PI / 16)) << 10,
                     s3   = int (sin (3 * PI / 16)) << 10,
                     r2c6 = int (sqrt (2) * cos (6 * PI / 16)) << 10,
                     r2s6 = int (sqrt (2) * sin (6 * PI / 16)) << 10,
                     r2   = int (sqrt (2)) << 7;

    // Transform Rows
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            x[j] = src.at <double> (i, j);
        }

        // Stage 1
        x[8] = x[7] + x[0];
        x[0] = x[0] - x[7];
        x[7] = x[1] + x[6];
        x[1] = x[1] - x[6];
        x[6] = x[2] + x[5];
        x[2] = x[2] - x[5];
        x[5] = x[3] + x[4];
        x[3] = x[3] - x[4];

        // Stage 2
        x[4] =              x[8] + x[5] ;
        x[8] =              x[8] - x[5] ;
        x[5] =              x[7] + x[6] ;
        x[7] =              x[7] - x[6] ;
        x[6] = (     c1) * (x[1] + x[2]);
        x[2] = (-s1 -c1) *  x[2] + x[6] ;
        x[1] = ( s1 -c1) *  x[1] + x[6] ;
        x[6] = (     c3) * (x[0] + x[3]);
        x[3] = (-s3 -c3) *  x[3] + x[6] ;
        x[0] = ( s3 -c3) *  x[0] + x[6] ;

        // Stage 3
        x[6] =                  x[4] + x[5] ;
        x[4] =                  x[4] - x[5] ;
        x[5] = (       r2c6) * (x[7] + x[8]);
        x[7] = (-r2s6 -r2c6) *  x[7] + x[5] ;
        x[8] = ( r2s6 -r2c6) *  x[8] + x[5] ;
        x[5] =                  x[0] + x[2] ;
        x[0] =                  x[0] - x[2] ;
        x[2] =                  x[3] + x[1] ;
        x[3] =                  x[3] - x[1] ;

        // Stage 4 & output
        window [i][0] =  x[6] ;
        window [i][4] =  x[4] ;
        window [i][2] =  x[8]  >> 10;
        window [i][6] =  x[7]  >> 10;
        window [i][7] = (x[2] - x[5]) >> 10;
        window [i][1] = (x[2] + x[5]) >> 10;
        window [i][3] = (r2   * x[3]) >> 17;
        window [i][5] = (r2   * x[0]) >> 17;
    }

    // Transform Cols
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            x[j] = window [j][i];
        }

        // Stage 1
        x[8] = x[7] + x[0];
        x[0] = x[0] - x[7];
        x[7] = x[1] + x[6];
        x[1] = x[1] - x[6];
        x[6] = x[2] + x[5];
        x[2] = x[2] - x[5];
        x[5] = x[3] + x[4];
        x[3] = x[3] - x[4];

        // Stage 2
        x[4] =              x[8] + x[5] ;
        x[8] =              x[8] - x[5] ;
        x[5] =              x[7] + x[6] ;
        x[7] =              x[7] - x[6] ;
        x[6] = (     c1) * (x[1] + x[2]);
        x[2] = (-s1 -c1) *  x[2] + x[6] ;
        x[1] = ( s1 -c1) *  x[1] + x[6] ;
        x[6] = (     c3) * (x[0] + x[3]);
        x[3] = (-s3 -c3) *  x[3] + x[6] ;
        x[0] = ( s3 -c3) *  x[0] + x[6] ;

        // Stage 3
        x[6] =                  x[4] + x[5] ;
        x[4] =                  x[4] - x[5] ;
        x[5] = (       r2c6) * (x[7] + x[8]);
        x[7] = (-r2s6 -r2c6) *  x[7] + x[5] ;
        x[8] = ( r2s6 -r2c6) *  x[8] + x[5] ;
        x[5] =                  x[0] + x[2] ;
        x[0] =                  x[0] - x[2] ;
        x[2] =                  x[3] + x[1] ;
        x[3] =                  x[3] - x[1] ;

        // Stage 4 & output
        window [0][i] = (x[6] + 16) >> 3;
        window [4][i] = (x[4] + 16) >> 3;
        window [2][i] = (x[8] + 16384) >> 13;
        window [6][i] = (x[7] + 16384) >> 13;
        window [7][i] = (x[2] - x[5] + 16384) >> 13;
        window [1][i] = (x[2] + x[5] + 16384) >> 13;
        window [3][i] = ((x[3] >> 8) * r2 + 8192) >> 12;
        window [5][i] = ((x[0] >> 8) * r2 + 8192) >> 12;
    }
}

cv::Mat fast_idct_window_gray (int window [8][8], cv::Mat && dest) {
    LOG_ASSERT (dest.channels() == 1);
    LOG_ASSERT (dest.rows == 8);
    LOG_ASSERT (dest.cols == 8);

    for (int y = 0; y < 8; y++) {
        auto drow = dest.ptr <double> (y);

        for (int x = 0; x < 8; x++) {
            double z = 0.0;

            for (int v = 0; v < 8; v++) {
                for (int u = 0; u < 8; u++) {
                    double S = window [v][u];
                    double Cu = u ? 1.0 : 1.0 / sqrt (2.0);
                    double Cv = v ? 1.0 : 1.0 / sqrt (2.0);
                    double q = Cu * Cv * S *
                            cos ((2.0 * x + 1) * u * (PI / 16.0)) *
                            cos ((2.0 * y + 1) * v * (PI / 16.0));

                    z += q;
                }
            }
            drow [x] = std::min (255.0, std::max (0.0, z / 4.0));
        }
    }
    return dest;
}

/* Copyright (C) Aaron Alef */
