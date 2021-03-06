#ifndef Imaginary_CONFIG_H
#define Imaginary_CONFIG_H

/** Google Logging Library */
// Minimum LOG level. 0 = Everything, 1 = Ignore LOG (INFO), ...
#define GOOGLE_STRIP_LOG 0

#include <glog/logging.h>

#ifdef ERRORS_AS_WARNINGS
#define THROW(error) {              \
    LOG (WARNING) << error.what();  \
    throw error;                    \
}; true
#else
#define THROW(error) {              \
    LOG (ERROR) << error.what();    \
    throw error;                    \
}; true
#endif

#include <opencv2/opencv.hpp>
using Image = std::pair <std::string, cv::Mat>;

#include <filesystem>

namespace fs = std::filesystem;

// TODO: factor out into a "Config" struct
//fs::path const IMG_IN  = PROJECT_ROOT "/../../Pictures/Nightcore";
fs::path const IMG_IN  = PROJECT_ROOT "/in";
fs::path const IMG_OUT = PROJECT_ROOT "/out";

#define NO_SYMLINK

#define IMAGE_OVERWRITE

//#define ORIGINAL
//#define GRAYIFY
#define REVIEW
//#define RANDOM

#endif //Imaginary_CONFIG_H

/* Copyright (C) 2022 Aaron Alef */
