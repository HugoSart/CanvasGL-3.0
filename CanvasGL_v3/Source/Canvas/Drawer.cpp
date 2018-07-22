#include "Drawer.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include "Camera.h"

# define M_PI 3.14159265358979323846  /* pi */

Drawer::Drawer() {}
Drawer::~Drawer() {}

void Drawer::DrawLine(Coord c1, Coord c2) {
	glBegin(GL_LINES);
		glColor3f(255, 255, 255);
		glVertex2f(c1.GetX() / glutGet(GLUT_WINDOW_WIDTH), c1.GetY() / glutGet(GLUT_WINDOW_HEIGHT));
		glVertex2f(c2.GetX() / glutGet(GLUT_WINDOW_WIDTH), c2.GetY() / glutGet(GLUT_WINDOW_HEIGHT));
	glEnd();
}

void Drawer::DrawLine(Coord c1, Coord c2, Color color) {
	glBegin(GL_LINES);
		glColor4ub(color.r, color.g, color.b, color.a);
		glVertex2f(c1.GetX() / glutGet(GLUT_WINDOW_WIDTH), c1.GetY() / glutGet(GLUT_WINDOW_HEIGHT));
		glVertex2f(c2.GetX() / glutGet(GLUT_WINDOW_WIDTH), c2.GetY() / glutGet(GLUT_WINDOW_HEIGHT));
	glEnd();
}

void Drawer::DrawDot(Coord c) {
	glBegin(GL_POINTS);
		glColor3f(1,1,1);
		glPointSize(5.0f);
		glVertex2f(c.GetX() / glutGet(GLUT_WINDOW_WIDTH), c.GetY() / glutGet(GLUT_WINDOW_HEIGHT));
	glEnd();
}

void Drawer::DrawGrid(int interval, Color color) {
	float nLines = 100000;

	for (int i = -nLines; i < nLines; i += interval)
		Drawer::DrawLine(Coord(-999999, i), Coord(999999, i), color);
	for (int i = -nLines; i < nLines; i += interval)
		Drawer::DrawLine(Coord(i, -999999), Coord(i, 999999), color);

	Drawer::DrawLine(Coord(-999999, 0), Coord(999999, 0), Color(0, 255, 0, 100));
	Drawer::DrawLine(Coord(0, -999999), Coord(0, 999999), Color(0, 0, 255, 100));
}

void Drawer::DrawTriangle(Coord c1, Coord c2, Coord c3, Color color) {
	glBegin(GL_TRIANGLES);
		glColor4ub(color.r, color.g, color.b, color.a);
		glVertex2f(c1.GetX() / glutGet(GLUT_WINDOW_WIDTH), c1.GetY() / glutGet(GLUT_WINDOW_HEIGHT));
		glVertex2f(c2.GetX() / glutGet(GLUT_WINDOW_WIDTH), c2.GetY() / glutGet(GLUT_WINDOW_HEIGHT));
		glVertex2f(c3.GetX() / glutGet(GLUT_WINDOW_WIDTH), c3.GetY() / glutGet(GLUT_WINDOW_HEIGHT));
	glEnd();
}

void Drawer::DrawPivot(Coord c1) {

	Color colorX = Color(0, 255, 0, 255);
	Color colorY = Color(0, 0, 255, 255);

	float lineSize = 40 * Camera::zoom;
	float triangleSize = 4 * Camera::zoom;

	Coord c2x = Coord(c1.GetX() + lineSize, c1.GetY());
	Coord c2y = Coord(c1.GetX(), c1.GetY() + lineSize);

	// Draw arrow in X axis
	DrawLine(c1, c2x, colorX);
	DrawTriangle(Coord(c2x.GetX(), c2x.GetY() + triangleSize),
		Coord(c2x.GetX(), c2x.GetY() - triangleSize),
		Coord(c2x.GetX() + triangleSize, c2x.GetY()),
		colorX);

	// Draw arrow in Y axis
	DrawLine(c1, c2y, colorY);
	DrawTriangle(Coord(c2y.GetX() + triangleSize, c2y.GetY()),
		Coord(c2y.GetX() - triangleSize, c2y.GetY()),
		Coord(c2y.GetX(), c2y.GetY() + triangleSize),
		colorY);

}