#pragma once

#include "../Canvas/Coord.h"
#include "CObject.h"

class CTriangle : public CObject {
public:
	CTriangle(Coord c1, Coord c2, Coord c3);
	~CTriangle();

	virtual bool Belongs(Coord c) override;
	virtual void Draw() override;

private:
	Coord c1, c2, c3;
};

