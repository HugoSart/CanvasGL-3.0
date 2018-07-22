#include "Coord.h"
#include <cmath>

Coord::Coord() : x(0), y(0) {}

Coord::Coord(float x, float y) {
	Set(x, y);
}

Coord::~Coord() {
}

float Coord::GetX() {
	return x;
}

float Coord::GetY() {
	return y;
}

void Coord::SetX(float x) {
	this->x = x;
}

void Coord::SetY(float y) {
	this->y = y;
}

void Coord::Set(float x, float y) {
	SetX(x);
	SetY(y);
}

float Coord::Distance(Coord c) {
	return sqrt(pow(GetX() - c.GetX(), 2) + pow(GetY() - c.GetY(), 2));
}