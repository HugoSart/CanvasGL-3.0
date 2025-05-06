#include <Drawables/CRectangle.h>
#include <Canvas/Drawer.h>
#include <Canvas/Util.h>

CRectangle::CRectangle(Coord c1, Coord c3) : c1(c1), c3(c3) {
	this->c2 = Coord(this->c3.GetX(), this->c1.GetY());
	this->c4 = Coord(this->c1.GetX(), this->c3.GetY());
	coords.emplace_back(&this->c1);
	coords.emplace_back(&this->c2);
	coords.emplace_back(&this->c3);
	coords.emplace_back(&this->c4);
	SetPivot(&this->c1);
}
CRectangle::~CRectangle() {}

bool CRectangle::Belongs(Coord c) {
	for (int i = 0; i < 4; i++)
		if (Util::BelongToLine(*coords.at(i % 4), *coords.at((i + 1) % 4), c, 10))
			return true;
	return false;
}

void CRectangle::Draw() {
	Drawer::DrawLine(c1, c2, color);
	Drawer::DrawLine(c2, c3, color);
	Drawer::DrawLine(c3, c4, color);
	Drawer::DrawLine(c4, c1, color);
}
