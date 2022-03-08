#ifndef IMAGINARY_BGR_T_HPP
#define IMAGINARY_BGR_T_HPP

#include <iostream>

//#define GRAY_WEIGHT_RED   0.333
//#define GRAY_WEIGHT_GREEN 0.333
//#define GRAY_WEIGHT_BLUE  0.333

// "Basics of Image Analysis", Fernando and Renfu, 2015
#define GRAY_WEIGHT_RED   0.2162
#define GRAY_WEIGHT_GREEN 0.7152
#define GRAY_WEIGHT_BLUE  0.0722

struct Color_BGR {
private:
    unsigned char value[3];

public:
    unsigned char & blue();
    unsigned char & green();
    unsigned char & red();

    [[nodiscard]] unsigned char blue() const;
    [[nodiscard]] unsigned char green() const;
    [[nodiscard]] unsigned char red() const;

    Color_BGR (int blue, int green, int red);
    explicit Color_BGR (unsigned char const values [3]);
    Color_BGR & operator = (unsigned char const values [3]);

    unsigned char & operator [] (unsigned int index);
    unsigned char   operator [] (unsigned int index) const;

    Color_BGR   operator *  (double factor) const;

    Color_BGR   operator /  (double divisor) const;
    Color_BGR & operator /= (double divisor);
    
    bool operator == (Color_BGR const & other) const;
    
    Color_BGR operator & (unsigned char mask) const;

    [[nodiscard]] unsigned int sum() const;
    [[nodiscard]] double average() const;

    [[nodiscard]] unsigned char const * begin() const;
    [[nodiscard]] unsigned char       * begin();

    [[nodiscard]] unsigned char const * end() const;
    [[nodiscard]] unsigned char       * end();
    
    static unsigned char bound (int value);
};

std::ostream & operator << (std::ostream & os, Color_BGR const & color);

#endif //IMAGINARY_BGR_T_HPP

/* Copyright (C) Aaron Alef */
