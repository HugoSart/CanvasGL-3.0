#pragma once

#include "Coord.h"
#include "Color.h"

class Drawer {
public:
	Drawer();
	~Drawer();

	static void DrawLine(Coord c1, Coord c2);
	static void DrawLine(Coord c1, Coord c2, Color color);
	static void DrawDot(Coord c);
	static void DrawGrid(int interval, Color color);
	static void DrawTriangle(Coord c1, Coord c2, Coord c3, Color color);
	static void DrawPivot(Coord c);


};

