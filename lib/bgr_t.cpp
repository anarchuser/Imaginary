#include "bgr_t.hpp"

unsigned char & Color_BGR::blue()  { return value[0]; };
unsigned char & Color_BGR::green() { return value[1]; };
unsigned char & Color_BGR::red()   { return value[2]; };

unsigned char Color_BGR::blue()  const { return value[0]; };
unsigned char Color_BGR::green() const { return value[1]; };
unsigned char Color_BGR::red()   const { return value[2]; };

Color_BGR::Color_BGR (unsigned char blue, unsigned char green, unsigned char red) {
    value [0] = blue;
    value [1] = green;
    value [2] = red;
}

Color_BGR::Color_BGR (unsigned char const values [3]) {
    for (int i = 0; i < 3; i++)
        value [i] = values [i];
}

Color_BGR & Color_BGR::operator = (unsigned char const values [3]) {
    for (int i = 0; i < 3; i++)
        value [i] = values [i];
    return * this;
}

unsigned char & Color_BGR::operator [] (unsigned int index)       { return value[index]; }
unsigned char   Color_BGR::operator [] (unsigned int index) const { return value[index]; }

Color_BGR Color_BGR::operator * (double factor) const {
    return {(unsigned char) (factor * value[0]), (unsigned char) (factor * value[1]), (unsigned char) (factor * value [2])};
}

Color_BGR Color_BGR::operator / (double divisor) const {
    return {(unsigned char) (value[0] / divisor), (unsigned char) (value[1] / divisor), (unsigned char) (value [2] / divisor)};
}

Color_BGR & Color_BGR::operator /= (double divisor) {
    for (auto & i : value) { i /= divisor; }
    return * this;
}

bool Color_BGR::operator == (Color_BGR const & other) const {
    return  this->red() == other.red() &&
            this->green() == other.green() &&
            this->blue() == other.blue();
}

std::ostream & Color_BGR::operator << (std::ostream & os) const {
    return os << (short) blue() << " - " << (short) green() << " - " << (short) red();
}

Color_BGR Color_BGR::operator & (unsigned char mask) const {
    return {(unsigned char) (value [0] & mask), (unsigned char) (value [1] & mask), (unsigned char) (value [2] & mask)};
}

unsigned int Color_BGR::sum()     const { return value [0] + value [1] + value [2]; }
double       Color_BGR::average() const {
    return GRAY_WEIGHT_RED * red()
         + GRAY_WEIGHT_GREEN * green()
         + GRAY_WEIGHT_BLUE * blue();
}

unsigned char const * Color_BGR::begin() const { return value; }
unsigned char       * Color_BGR::begin()       { return value; }

unsigned char const * Color_BGR::end() const { return value + 3; }
unsigned char       * Color_BGR::end()       { return value + 3; }

/* Copyright (C) Aaron Alef */
