#pragma once

#include <GL/glew.h>

class Color {

	public: unsigned char r, g, b;
	public: unsigned char a;

	// Constructors and destructos
	public: Color();
	public: Color(unsigned char r, unsigned char g, unsigned char b);
	public: Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	public: ~Color();

};

