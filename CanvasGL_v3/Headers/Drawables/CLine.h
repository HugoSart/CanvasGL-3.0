#pragma once

#include "../Canvas/Coord.h"
#include "CObject.h"

class CLine : virtual public CObject {
private:
	Coord start;
	Coord end;

public:
	CLine(Coord start, Coord end);
	~CLine();

	Coord GetStart();
	Coord GetEnd();

	virtual bool Belongs(Coord c) override;
	virtual void Draw() override;

};

