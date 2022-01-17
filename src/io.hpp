#ifndef IMAGINARY_IO_HPP
#define IMAGINARY_IO_HPP

#include "config.h"

#include <string>

void init_out () {
    // Clear output directory
    fs::remove_all (IMG_OUT);

    // Recreate output directory
    fs::create_directories (IMG_OUT);
    LOG_ASSERT (fs::exists (IMG_OUT));
}

void write_image (std::string const & relative_path, std::pair <std::string, cv::Mat> const & image) {
    fs::path folder = IMG_OUT / relative_path;
    fs::create_directories (folder);
    LOG_ASSERT (fs::exists (folder));
    LOG_ASSERT (! fs::exists (folder / image.first));
    cv::imwrite (folder / image.first, image.second);
    LOG_ASSERT (fs::exists (folder / image.first));

    fs::path sym_folder = IMG_OUT / image.first;
    fs::create_directories (sym_folder);
    LOG_ASSERT (fs::exists (sym_folder));
    LOG_ASSERT (! fs::exists (sym_folder / relative_path));
    fs::create_symlink (folder / image.first, sym_folder / relative_path);
    LOG_ASSERT (fs::exists (sym_folder / relative_path));
}

#endif //IMAGINARY_IO_HPP

/* Copyright (C) Aaron Alef */
