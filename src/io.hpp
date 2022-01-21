#ifndef IMAGINARY_IO_HPP
#define IMAGINARY_IO_HPP

#include "config.h"

#include <string>
#include <vector>

/// Read all files from program args and IMG_IN directory
std::vector <std::pair <std::string, cv::Mat>> read_images (int argc, char * argv[]) {
    std::vector <std::pair <std::string, cv::Mat>> originals;
    // Read all files from argv
    std::cout << "Files read from arguments:" << std::endl;
    for (std::size_t i = 0; i < argc; i++) {
        auto image = cv::imread (argv [i]);
        if (image.empty ()) continue;
        std::cout << argv [i] << ":\t" << image.rows << 'x' << image.cols << std::endl;
        originals.emplace_back (fs::path (argv [i]).filename(), std::move (image));
    }

    // Read all files in IMG_IN dir
    std::cout << "Files read from IMG_IN directory:" << std::endl;
    for (auto const & file : fs::directory_iterator (IMG_IN)) {
        auto image = cv::imread (file.path());
        if (image.empty ()) continue;
        std::cout << file.path() << ":\t" << image.rows << 'x' << image.cols << std::endl;
        originals.emplace_back (fs::path (file).filename(), std::move (image));
    }
    return originals;
}

void init_out () {
    // Clear output directory
    fs::remove_all (IMG_OUT);

    // Recreate output directory
    fs::create_directories (IMG_OUT);
    LOG_ASSERT (fs::exists (IMG_OUT));
}

void write_image (std::string const & relative_path, std::pair <std::string, cv::Mat> const & image) {
    // Save each modified image sorted by the path given
    fs::path parent = IMG_OUT / relative_path;
    fs::path path = parent / image.first;
    fs::create_directories (parent);
    LOG_ASSERT (fs::exists (parent));
    LOG_ASSERT (! fs::exists (path));
    cv::imwrite (path, image.second);
    LOG_ASSERT (fs::exists (path));

    // Create sym links or duplicate images sorted by input image name
    fs::path sym_path = (IMG_OUT / image.first / relative_path) += fs::path (image.first).extension();
    fs::path sym_parent = sym_path.parent_path();

    fs::create_directories (sym_parent);
    LOG_ASSERT (fs::exists (sym_parent));

    LOG_ASSERT (! fs::exists (sym_path));
#ifdef NO_SYMLINK
    cv::imwrite (sym_path, image.second);
#else
    fs::create_symlink (folder / image.first, sym_path);
#endif
    LOG_ASSERT (fs::exists (sym_path));
}

#endif //IMAGINARY_IO_HPP

/* Copyright (C) Aaron Alef */
