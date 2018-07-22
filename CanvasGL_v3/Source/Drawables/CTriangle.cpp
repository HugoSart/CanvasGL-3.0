#include <GL/glew.h>
#include <glm/glm.hpp>
#include <Canvas/Drawer.h>
#include <Drawables/CTriangle.h>
#include <Canvas/Util.h>

CTriangle::CTriangle(Coord c1, Coord c2, Coord c3) : c1(c1), c2(c2), c3(c3) {
	coords.emplace_back(&this->c1);
	coords.emplace_back(&this->c2);
	coords.emplace_back(&this->c3);
	SetPivot(&this->c1);
}
CTriangle::~CTriangle() {}

void CTriangle::Draw() {
	Drawer::DrawLine(c1, c2, color);
	Drawer::DrawLine(c2, c3, color);
	Drawer::DrawLine(c3, c1, color);
}

bool CTriangle::Belongs(Coord c) {
	for (int i = 0; i < 3; i++) {
		Coord cs = *coords.at(i % 3), cf = *coords.at((i + 1) % 3);
		if (Util::BelongToLine(cs, cf, c, 10)) return true;
	}

	return false;
}
