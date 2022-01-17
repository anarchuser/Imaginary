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

#include <filesystem>

namespace fs = std::filesystem;

// TODO: factor out into a "Config" struct
fs::path const IMG_IN  = PROJECT_ROOT "/in";
fs::path const IMG_OUT = PROJECT_ROOT "/out";

#endif //Imaginary_CONFIG_H

/* Copyright (C) 2022 Aaron Alef */
