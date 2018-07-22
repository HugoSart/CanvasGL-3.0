#include "Color.h"

// Constructors and destructos
Color::Color() : r(255), g(255), b(255), a(255) {};
Color::Color(unsigned char r, unsigned char g, unsigned char b) : r(r), g(g), b(b), a(255) {}
Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) : r(r), g(g), b(b), a(a) {}
Color::~Color() {}


