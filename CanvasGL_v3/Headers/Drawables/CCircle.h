#pragma once

#include "Canvas/Coord.h"
#include "CObject.h"

class CCircle : public CObject {
	
	private: Coord center;
	private: float radius;

	public: CCircle(Coord center, float radius);
	public: ~CCircle();

	public: float GetRadius();
	public: void SetRadius(float radius);

	public: virtual void Scale(float sx, float sy);

	public: virtual bool Belongs(Coord c);
	public: virtual void Draw() override;

};

