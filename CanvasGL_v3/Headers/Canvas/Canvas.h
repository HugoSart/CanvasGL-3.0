#pragma once

#include <vector>
#include "Coord.h"
#include "../Drawables/CObject.h"

#define NONE -1
#define SELECT 0
#define DOT 1
#define LINE 2
#define TRIANGLE 3
#define RECTANGLE 4
#define CIRCLE 5

class Canvas {
public:
	std::vector<CObject*> objects;
	std::vector<CObject*> ghostObjects;

	Canvas();
	~Canvas();

	// Life Cyle
	void Start(int argc, char *argv[]);
	virtual void OnStart();
	virtual void OnUpdate();

	// Bindings
	virtual void OnMouseButtonPressed(int button, int state, int x, int y);
	virtual void OnKeyboardKeyPressed(unsigned char key, int x, int y);
	virtual void OnSpecialKeyPressed(int key, int x, int y);

	// Actions
	void PlaceObject(CObject*);
	void SelectObject(CObject*);
	void RemoveObject(CObject*);
	void EnframeObject(CObject*);

private:
	CObject *selectedObject = nullptr;
	CObject *buildingObject = nullptr;
	int buildingObjectType = SELECT;
	bool isBuilding = false;
	Coord mousePos = {};
	int numberOfActions = 0;

	// Life Cycle
	void Update();
	void Render();

	// Actions
	void StartObjectBuilding(CObject *object);
	void FinishObjectBuilding(bool success);

	// Binding
	friend void HandleMouseInput(int button, int state, int x, int y);
	friend void HandleKeyboardInput(unsigned char key, int x, int y);
	friend void HandleSpecialInput(int key, int x, int y);
	friend void HandlePassiveMouseInput(int x, int y);
	friend void _Render();
	friend void StartConsole();

};

