#pragma once
#include "CObject.h"

class CRectangle : public CObject {
	public: CRectangle(Coord c1, Coord c3);
	public: ~CRectangle();

	public: virtual bool Belongs(Coord c);
	public: virtual void Draw();

	private: Coord c1, c2, c3, c4;

};

