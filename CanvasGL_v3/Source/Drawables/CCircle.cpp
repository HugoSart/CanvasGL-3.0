#include <GL/glew.h>
#include <glm/glm.hpp>
#include <iostream>
#include <Canvas/Drawer.h>
#include <Drawables/CCircle.h>

CCircle::CCircle(Coord center, float radius) : center(center), radius(radius) {
	coords.emplace_back(&this->center);
	SetPivot(&this->center);
}
CCircle::~CCircle() {}

void CCircle::Draw() {

	int num_segments = 1000;
	
	glBegin(GL_LINE_LOOP);
	glColor4ub(255, 0, 0, 0);
	
	Coord current, last;
	for (int ii = 0; ii < num_segments; ii++) {
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 

		float x = radius * cosf(theta);//calculate the x component 
		float y = radius * sinf(theta);//calculate the y component 

		current = Coord(x + center.GetX(), y + center.GetY());
		if (ii != 0)
			Drawer::DrawLine(Coord(x + center.GetX(), y + center.GetY()), Coord(last.GetX(), last.GetY()), color);
		last = current;

	}
	glEnd();

}

float CCircle::GetRadius() {
	return radius;
}

void CCircle::SetRadius(float radius) {
	this->radius = radius;
}

bool CCircle::Belongs(Coord c) {
	float dist = coords.at(0)->Distance(c);
	return dist >= 0.9 * radius && dist <= 1.1 * radius;
}

void CCircle::Scale(float sx, float sy) {
	radius *= sx;
}
