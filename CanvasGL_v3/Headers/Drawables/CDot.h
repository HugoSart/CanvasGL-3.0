#pragma once

#include "../Canvas/Coord.h"
#include "CObject.h"

class CDot : public CObject {
public:
	CDot(float x, float y);
	CDot(Coord coord);
	~CDot();

	Coord GetCoord();
	void SetCoord(Coord c);
	virtual void Draw() override;


private:
	Coord coord;

};

