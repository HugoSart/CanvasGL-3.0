#include <GL/glew.h>
#include <glm/glm.hpp>
#include <Canvas/Drawer.h>
#include <Drawables/CObject.h>

CObject::CObject() : color(Color(255, 255, 255)) {}
CObject::~CObject() {}

void CObject::OnStart() {}
void CObject::OnUpdate() {}
void CObject::OnRender() {}
void CObject::Draw() {}

void CObject::Move(float x, float y) {
	for (auto &c : coords)
		c->Set(c->GetX() + x, c->GetY() + y);
}

void CObject::Translate(Coord c) {
	Move(c.GetX() - pivot->GetX(), c.GetY() - pivot->GetY());
}

void CObject::Rotate(float angle) {
	
	float cos = glm::cos((angle * 3.1415) / 180), sin = glm::sin((angle * 3.1415) / 180);
	glm::mat2 r = {
		cos,	-sin,
		sin,	cos
	};

	for (int i = 0; i < coords.size(); i++) {
		
		Coord *c1 = pivot;
		Coord *c2 = coords.at(i);

		float x1 = c1->GetX(), x2 = c2->GetX(), y1 = c1->GetY(), y2 = c2->GetY();

		glm::mat2 mobj = {
			0, 0,
			x2 - x1, y2 - y1
		};

		glm::mat2 resp = r * mobj;

		c1->Set(x1, y1);
		c2->Set(resp[1][0] + x1, resp[1][1] + y1);
	}

}

void CObject::Scale(float sx, float sy) {
	for (auto &c : coords)
		c->Set((c->GetX() -  pivot->GetX()) * sx + pivot->GetX(), (c->GetY() - pivot->GetY()) * sy + pivot->GetY());
}

bool CObject::Belongs(Coord c) {
	return false;
}

void CObject::SetPivot(Coord *c) {
	this->pivot = c;
}

Coord *CObject::GetPivot() {
	return pivot;
}

void CObject::Destroy() {
	for (int i = 0; i < coords.size(); i++) {
		Coord *coord = coords.at(i);
		coords.erase(coords.begin() + i);
		delete coord;
	}
	delete this;
}