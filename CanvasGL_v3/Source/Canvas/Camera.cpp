#include "Canvas/Camera.h"

#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>

float Camera::zoom = 1.0f;
float Camera::xOffset = 0.0f;
float Camera::yOffset = 0.0f;
float Camera::r = 0.0f;
float Camera::g = 0.0f;
float Camera::b = 0.0f;
float Camera::a = 1.0f;

Camera::Camera() {}
Camera::~Camera() {}

void Camera::Translate(float x, float y) {
	xOffset += x / glutGet(GLUT_WINDOW_WIDTH);
	yOffset += y / glutGet(GLUT_WINDOW_HEIGHT);
	Refresh();
}

void Camera::Goto(Coord c) {
	xOffset = c.GetX() / ((float)glutGet(GLUT_WINDOW_WIDTH));
	yOffset = c.GetY() / ((float)glutGet(GLUT_WINDOW_HEIGHT));
	Refresh();
}

void Camera::Zoom(float value) {
	Camera::zoom -= value;
	Refresh();
}

void Camera::Initialize(float r, float g, float b, float a) {
	Camera::r = r;
	Camera::g = g;
	Camera::b = b;
	Camera::a = a;
	glClearColor(r, g, b, a);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(xOffset, zoom + xOffset, yOffset, zoom + yOffset);
	glMatrixMode(GL_MODELVIEW);
}

void Camera::Refresh() {
	glClearColor(r, g, b, a);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(xOffset, zoom + xOffset, yOffset, zoom + yOffset);
	glMatrixMode(GL_MODELVIEW);
}

Coord Camera::ScreenToWorld(Coord c) {
	
	float zoom = Camera::zoom;
	float xOffset = Camera::xOffset, yOffset = Camera::yOffset;

	float wx = (c.GetX() + xOffset * glutGet(GLUT_WINDOW_WIDTH));
	float wy = ((glutGet(GLUT_WINDOW_HEIGHT) - c.GetY()) + yOffset * glutGet(GLUT_WINDOW_HEIGHT));
	wx += c.GetX() * (zoom - 1);
	wy += (glutGet(GLUT_WINDOW_HEIGHT) - c.GetY()) * (zoom - 1);
	return Coord(wx, wy);
}

Coord Camera::GetWorldLocation() {
	return ScreenToWorld(Coord(0, glutGet(GLUT_WINDOW_HEIGHT)));
}
