#include "bgr_t.hpp"

unsigned char & Color_BGR::blue()  { return value[0]; };
unsigned char & Color_BGR::green() { return value[1]; };
unsigned char & Color_BGR::red()   { return value[2]; };

unsigned char Color_BGR::blue()  const { return value[0]; };
unsigned char Color_BGR::green() const { return value[1]; };
unsigned char Color_BGR::red()   const { return value[2]; };

unsigned char & Color_BGR::operator [] (unsigned int index)       { return value[index]; }
unsigned char   Color_BGR::operator [] (unsigned int index) const { return value[index]; }

Color_BGR Color_BGR::operator / (double divisor) const {
    return {(unsigned char) (value[0] / divisor), (unsigned char) (value[1] / divisor), (unsigned char) (value [2] / divisor)};
}

Color_BGR & Color_BGR::operator /= (double divisor) {
    for (auto & i : value) { i /= divisor; }
    return * this;
}

std::ostream & Color_BGR::operator << (std::ostream & os) const {
    return os << (short) blue() << " - " << (short) green() << " - " << (short) red();
}

unsigned int Color_BGR::sum()     const { return value [0] + value [1] + value [2]; }
double       Color_BGR::average() const { return (double) sum() / 3; }

/* Copyright (C) Aaron Alef */
