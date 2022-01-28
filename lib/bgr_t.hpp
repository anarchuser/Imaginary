#ifndef IMAGINARY_BGR_T_HPP
#define IMAGINARY_BGR_T_HPP

#include <iostream>

struct Color_BGR {
    unsigned char value[3];

    unsigned char & blue();
    unsigned char & green();
    unsigned char & red();

    [[nodiscard]] unsigned char blue() const;
    [[nodiscard]] unsigned char green() const;
    [[nodiscard]] unsigned char red() const;

    unsigned char & operator [] (unsigned int index);
    unsigned char operator [] (unsigned int index) const;

    std::ostream & operator << (std::ostream & os) const;

    [[nodiscard]] unsigned int sum() const;
    [[nodiscard]] double average() const;
};

#endif //IMAGINARY_BGR_T_HPP

/* Copyright (C) Aaron Alef */
