#ifndef IMAGINARY_BGR_T_HPP
#define IMAGINARY_BGR_T_HPP

struct Color_BGR {
    unsigned char value[3];

    unsigned char & blue() { return value[0]; };
    unsigned char & green() { return value[1]; };
    unsigned char & red() { return value[2]; };

    [[nodiscard]] unsigned char blue() const { return value[0]; };
    [[nodiscard]] unsigned char green() const { return value[1]; };
    [[nodiscard]] unsigned char red() const { return value[2]; };

    unsigned char & operator [] (unsigned int index) { return value[index]; }
    unsigned char operator [] (unsigned int index) const { return value[index]; }
};

#endif //IMAGINARY_BGR_T_HPP

/* Copyright (C) Aaron Alef */
