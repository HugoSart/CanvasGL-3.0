#pragma once

#include <vector>
#include "../Canvas/Coord.h"
#include "CObject.h"
#include "../Canvas/Color.h"

class CObject {
public:
	std::vector<Coord*> coords;
	Color color;

	CObject();
	virtual ~CObject();

	virtual void OnStart();
	virtual void OnUpdate();
	virtual void OnRender();
	virtual void Destroy();

	void virtual Move(float x, float y);
	void virtual Translate(Coord c);
	void virtual Rotate(float angle);
	void virtual Scale(float sx, float sy);
	
	void SetPivot(Coord *c);
	Coord *GetPivot();

	virtual bool Belongs(Coord c);
	virtual void Draw() = 0;

private:
	Coord *pivot = nullptr;

};

