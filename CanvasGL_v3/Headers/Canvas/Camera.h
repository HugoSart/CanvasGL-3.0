#pragma once

#include "Coord.h"

class Camera {
public:
	Camera();
	~Camera();
	
	static float zoom;
	static float xOffset;
	static float yOffset;

	static void Initialize(float r, float g, float b, float a);
	static void Translate(float x, float y);
	static void Goto(Coord c);
	static void Zoom(float value);
	static Coord GetWorldLocation();
	static Coord ScreenToWorld(Coord c);

	static void Refresh();
private:
	static float r, g, b, a;


};

