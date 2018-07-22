#include "Util.h"
#include <cmath>

Util::Util() {}
Util::~Util() {}

bool Util::BelongToLine(Coord cs, Coord cf, Coord c, float aprox) {

	if (cs.GetX() < cf.GetX()) {
		if (c.GetX() < cs.GetX() || c.GetX() > cf.GetX()) return false;
	} else if (cs.GetX() > cf.GetX()) {
		if (c.GetX() < cf.GetX() || c.GetX() > cs.GetX()) return false;
	}

	float m = (cf.GetY() - cs.GetY()) / (cf.GetX() - cs.GetX());
	float leftSide = c.GetY() - cs.GetY();
	float rightSide = m * (c.GetX() - cs.GetX());

	return abs(leftSide - rightSide) <= aprox;

}
