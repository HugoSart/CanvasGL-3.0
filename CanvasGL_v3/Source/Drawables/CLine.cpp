#include <GL/glew.h>
#include <glm/glm.hpp>
#include <Canvas/Drawer.h>
#include <Drawables/CLine.h>

// Constructors and Desctructors
CLine::CLine(Coord start, Coord end) : start(start), end(end) {
	coords.emplace_back(&this->start);
	coords.emplace_back(&this->end);
	SetPivot(&this->start);
}
CLine::~CLine() {}

// Getters and Setters
Coord CLine::GetStart()	{ return start; }
Coord CLine::GetEnd()	{ return end; }

void CLine::Draw() {
	Drawer::DrawLine(start, end, color);
}

bool CLine::Belongs(Coord c) {
	return false;
	// return Util::BelongToLine(*coords.at(0), *coords.at(1), c, 10);
}
