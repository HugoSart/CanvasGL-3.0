#include "Canvas/Canvas.h"
#include <iostream>
#include <regex>
#include <string>
#include <thread>
#include <GL/glut.h>
#include "Canvas/Color.h"
#include "Canvas/Camera.h"
#include "Canvas/Drawer.h"
#include "Drawables/CLine.h"
#include "Drawables/CTriangle.h"
#include "Drawables/CRectangle.h"
#include "Drawables/CCircle.h"
#include "Global.h"

void StartConsole();

Canvas Global::canvas = {};

Canvas::Canvas() : objects({}), ghostObjects({}) {}
Canvas::~Canvas() {}

void Canvas::Start(int argc, char *argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("OpenGL Canvas");

	Camera::Initialize(0, 0, 0, 0);
	Camera::Translate(-300, -300);
	Camera::Zoom(-0.75);

	glutDisplayFunc(_Render);
	glutMouseFunc(HandleMouseInput);
	glutKeyboardFunc(HandleKeyboardInput);
	glutSpecialFunc(HandleSpecialInput);
	glutPassiveMotionFunc(HandlePassiveMouseInput);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	OnStart();

	std::thread console(StartConsole);
	glutMainLoop();

}

void Canvas::Update() {
	OnUpdate();
	for (auto &obj : objects)
		obj->OnUpdate();
}

void Canvas::Render() {
	Drawer::DrawGrid(100, Color(255, 255, 255, 15));
	for (auto &obj : objects) {
		obj->OnRender();
		obj->Draw();
		if (selectedObject == obj && obj->GetPivot() != nullptr) Drawer::DrawPivot(*obj->GetPivot());
	}
	for (auto &obj : ghostObjects) {
		obj->OnRender();
		obj->Draw();
	}
}

void Canvas::PlaceObject(CObject *object) {
	objects.emplace_back(object);
	object->OnStart();
}

void Canvas::SelectObject(CObject *object) {
	this->selectedObject = object;
}

void Canvas::EnframeObject(CObject* obj) {

	float wWidth = glutGet(GLUT_WINDOW_WIDTH), wHeight = glutGet(GLUT_WINDOW_HEIGHT);
	Coord pc = *obj->GetPivot(), cc = Camera::GetWorldLocation();
	float zoom = Camera::zoom;

	float lowerPX = std::numeric_limits<float>::max(), lowerPY = std::numeric_limits<float>::max(), higherPX = std::numeric_limits<float>::min(), higherPY = std::numeric_limits<float>::min();
	for (auto &c : obj->coords) {
		lowerPX = c->GetX() < lowerPX ? c->GetX() : lowerPX;
		lowerPY = c->GetY() < lowerPY ? c->GetY() : lowerPY;
		higherPX = c->GetX() > higherPX ? c->GetX() : higherPX;
		higherPY = c->GetY() > higherPY ? c->GetY() : higherPY;
	}

	float mX = (lowerPX + higherPX) / 2.0, mY = (lowerPY + higherPY) / 2.0;
	float offsetX = Camera::ScreenToWorld(Coord(wWidth / 2.0, wHeight / 2.0)).GetX() - Camera::GetWorldLocation().GetX();
	float offsetY = Camera::ScreenToWorld(Coord(wWidth / 2.0, wHeight / 2.0)).GetY() - Camera::GetWorldLocation().GetY();

	Camera::Goto(Coord(mX - offsetX, mY - offsetY));

}

void HandleMouseInput(int button, int state, int x, int y) {

	// Scroll Event
	if ((button == 3) || (button == 4)) {
		if (button == 3) {
			Camera::Zoom(0.1f);
		} else {
			Camera::Zoom(-0.1f);
		}
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

		if (!Global::canvas.isBuilding) {

			CObject *obj = nullptr;
			if (Global::canvas.buildingObjectType == SELECT) {
				for (auto &obj : Global::canvas.objects) {
					if (obj->Belongs(Global::canvas.mousePos)) {
						Global::canvas.SelectObject(obj);
						break;
					}
				}
			} else if (Global::canvas.buildingObjectType == LINE)
				obj = new CLine(Global::canvas.mousePos, Global::canvas.mousePos);
			else if (Global::canvas.buildingObjectType == TRIANGLE)
				obj = new CTriangle(Global::canvas.mousePos, Global::canvas.mousePos, Global::canvas.mousePos);
			else if (Global::canvas.buildingObjectType == RECTANGLE)
				obj = new CRectangle(Global::canvas.mousePos, Global::canvas.mousePos);
			else if (Global::canvas.buildingObjectType == CIRCLE)
				obj = new CCircle(Global::canvas.mousePos, 0);

			if (obj != nullptr) Global::canvas.StartObjectBuilding(obj);

		} else {

			if (dynamic_cast<CLine*>(Global::canvas.buildingObject) != nullptr) {
				if (Global::canvas.numberOfActions == 0)
					Global::canvas.FinishObjectBuilding(true);
				else Global::canvas.numberOfActions++;
			} else if (dynamic_cast<CTriangle*>(Global::canvas.buildingObject) != nullptr) {
				if (Global::canvas.numberOfActions == 1)
					Global::canvas.FinishObjectBuilding(true);
				else Global::canvas.numberOfActions++;
			} else if (dynamic_cast<CRectangle*>(Global::canvas.buildingObject) != nullptr) {
				if (Global::canvas.numberOfActions == 0)
					Global::canvas.FinishObjectBuilding(true);
				else Global::canvas.numberOfActions++;
			} else if (dynamic_cast<CCircle*>(Global::canvas.buildingObject) != nullptr) {
				if (Global::canvas.numberOfActions == 0)
					Global::canvas.FinishObjectBuilding(true);
				else Global::canvas.numberOfActions++;
			}
		}
	}

	if (button == GLUT_RIGHT_BUTTON) {
		if (Global::canvas.isBuilding) {
			Global::canvas.FinishObjectBuilding(false);
		}
	}

	Global::canvas.OnMouseButtonPressed(button, state, x, y);

}

void HandleKeyboardInput(unsigned char key, int x, int y) {

	// Change object type to be constructed
	if (key == '0') {
		Global::canvas.buildingObjectType = SELECT;
		//std::cout << "Mouse click now SELECTS an OBJECT;" << std::endl;
	}

	if (key == '1') {
		Global::canvas.buildingObjectType = DOT;
		//std::cout << "Mouse click now BUILDS a DOT;" << std::endl;
	}

	if (key == '2') {
		Global::canvas.buildingObjectType = LINE;
		//std::cout << "Mouse click now BUILDS a LINE;" << std::endl;
	}

	if (key == '3') {
		Global::canvas.buildingObjectType = TRIANGLE;
		//std::cout << "Mouse click now BUILDS a TRIANGLE;" << std::endl;
	}

	if (key == '4') {
		Global::canvas.buildingObjectType = RECTANGLE;
		//std::cout << "Mouse click now BUILDS a RECTANGLE;" << std::endl;
	}

	if (key == '5') {
		Global::canvas.buildingObjectType = CIRCLE;
		//std::cout << "Mouse click now BUILDS a CIRCLE;" << std::endl;
	}

	if (key == 'f') {
		if (Global::canvas.selectedObject != nullptr) {
			Global::canvas.EnframeObject(Global::canvas.selectedObject);
		}
	}

	CObject *selected = Global::canvas.selectedObject;
	if (selected != nullptr) {

		float moveSpeed = 10;
		if (key == 'w') {
			selected->Move(0, moveSpeed);
		}

		if (key == 's') {
			selected->Move(0, -moveSpeed);
		}

		if (key == 'd') {
			selected->Move(moveSpeed, 0);
		}


		if (key == 'a') {
			selected->Move(-moveSpeed, 0);
		}

		if (key == 'r') {
			selected->Rotate(1);
		}

		if (key == '[') {
			selected->Scale(1.1, 1.1);
		}

		if (key == ']') {
			selected->Scale(0.9, 0.9);
		}

		if (key == 'p') {
			
			CObject *obj = Global::canvas.selectedObject;

			for (int i = 0; i < obj->coords.size(); i++) {
				if (obj->coords.at(i) == obj->GetPivot()) {
					obj->SetPivot(obj->coords.at((i + 1) % obj->coords.size()));
					break;
				}
			}
			
		}

		if (key == 127) { // DEL
			Global::canvas.RemoveObject(selected);
			Global::canvas.selectedObject = nullptr;
		}

	}

	if (key == 27) { // ESC
		Global::canvas.selectedObject = nullptr;
		if (Global::canvas.isBuilding) Global::canvas.FinishObjectBuilding(false);
	}

	if (key == 9) { // TAB
		Canvas &canvas = Global::canvas;

		if (canvas.selectedObject == nullptr && !canvas.objects.empty())
			canvas.SelectObject(canvas.objects.at(0));

		for (int i = 0; i < canvas.objects.size(); i++)
			if (canvas.objects.at(i) == canvas.selectedObject) {
				if (i != canvas.objects.size() - 1) canvas.SelectObject(canvas.objects.at(i + 1));
				else canvas.SelectObject(canvas.objects.at(0));
				break;
			}
	}

	Global::canvas.OnKeyboardKeyPressed(key, x, y);
}

float speed = 10;
void HandleSpecialInput(int key, int x, int y) {

	if (key == GLUT_KEY_RIGHT) {
		Camera::Translate(speed * Camera::zoom, 0);
	}

	if (key == GLUT_KEY_LEFT) {
		Camera::Translate(-speed * Camera::zoom, 0);
	}

	if (key == GLUT_KEY_UP) {
		Camera::Translate(0, speed * Camera::zoom);
	}

	if (key == GLUT_KEY_DOWN) {
		Camera::Translate(0, -speed * Camera::zoom);
	}

	if (key == GLUT_KEY_F12) {
		Global::canvas.objects.clear();
	}

	Global::canvas.OnSpecialKeyPressed(key, x, y);

}

void HandlePassiveMouseInput(int x, int y) {

	Coord wc = Camera::ScreenToWorld(Coord(x, y));
	Global::canvas.mousePos.Set(wc.GetX(), wc.GetY());

	if (Global::canvas.isBuilding) {
		CObject *obj = Global::canvas.buildingObject;
		if (dynamic_cast<CCircle*>(obj) == nullptr) {
			if (dynamic_cast<CRectangle*>(obj) != nullptr) {
				obj->coords[2]->Set(wc.GetX(), wc.GetY());
				obj->coords[1]->Set(obj->coords[2]->GetX(), obj->coords[0]->GetY());
				obj->coords[3]->Set(obj->coords[0]->GetX(), obj->coords[2]->GetY());
			} else {
				obj->coords[Global::canvas.numberOfActions + 1]->Set(wc.GetX(), wc.GetY());
			}
		} else {
			CCircle *circle = dynamic_cast<CCircle*>(obj);
			circle->SetRadius(circle->coords[0]->Distance(wc));
		}
	}

	for (auto &obj : Global::canvas.objects) {
		if (obj->Belongs(wc) && Global::canvas.buildingObject == nullptr) {
			obj->color = Color(255, 255, 0);
			break;
		} else obj->color = Color(255, 255, 255);
	}

}

void Canvas::StartObjectBuilding(CObject *obj) {
	isBuilding = true;
	buildingObject = obj;
	ghostObjects.emplace_back(obj);
}

void Canvas::FinishObjectBuilding(bool success) {
	isBuilding = false;

	if (success) {
		for (int i = 0; i < ghostObjects.size(); i++) {
			if (ghostObjects.at(i) == buildingObject) {
				PlaceObject(buildingObject);
				SelectObject(buildingObject);
				ghostObjects.erase(ghostObjects.begin() + i);
				break;
			}
		}
	} else {
		for (int i = 0; i < ghostObjects.size(); i++) {
			if (ghostObjects.at(i) == buildingObject) {
				ghostObjects.erase(ghostObjects.begin() + i);
				break;
			}
		}
		//buldingObject->Destroy();
	}

	buildingObject = nullptr;
	buildingObjectType = SELECT;
	numberOfActions = 0;

}

void _Render() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);

	Global::canvas.Update();
	Global::canvas.Render();

	glutPostRedisplay();
	glFlush();
}

void Canvas::OnStart() {}
void Canvas::OnUpdate() {}
void Canvas::OnMouseButtonPressed(int button, int state, int x, int y) {}
void Canvas::OnKeyboardKeyPressed(unsigned char key, int x, int y) {}
void Canvas::OnSpecialKeyPressed(int key, int x, int y) {}

void Canvas::RemoveObject(CObject *obj) {
	for (int i = 0; i < objects.size(); i++)
		if (objects.at(i) == obj) {
			objects.erase(objects.begin() + i);
			break;
		}
}

void StartConsole() {

	Canvas *canvas = &Global::canvas;

	while (true) {

		char input[100];
		std::cout << "Command > ";
		std::cin.getline(input, sizeof(input));

		std::string command = input;
		std::regex ws_re("\\s+");
		std::vector<std::string> vet{std::sregex_token_iterator(command.begin(), command.end(), ws_re, -1),{}};

		try {

			if (vet.at(0) == "create") {
				CObject *obj;
				if (vet.at(1) == "line") {
					Coord c1 = Coord(std::stof(vet.at(2)), std::stof(vet.at(3))), c2 = Coord(std::stof(vet.at(4)), std::stof(vet.at(5)));
					obj = new CLine(c1, c2);
				} else if (vet.at(1) == "triangle") {
					Coord c1 = Coord(std::stof(vet.at(2)), std::stof(vet.at(3))),
						c2 = Coord(std::stof(vet.at(4)), std::stof(vet.at(5))),
						c3 = Coord(std::stof(vet.at(6)), std::stof(vet.at(7)));
					obj = new CTriangle(c1, c2, c3);
				} else if (vet.at(1) == "rectangle") {
					Coord c1 = Coord(std::stof(vet.at(2)), std::stof(vet.at(3))),
						c2 = Coord(std::stof(vet.at(4)), std::stof(vet.at(5)));
					obj = new CRectangle(c1, c2);
				} else if (vet.at(1) == "circle") {
					Coord center = Coord(std::stof(vet.at(2)), std::stof(vet.at(3)));
					float radius = std::stof(vet.at(4));
					obj = new CCircle(center, radius);
				} else {
					throw std::runtime_error("Unknow geometry.");
				}
				canvas->PlaceObject(obj);
				canvas->SelectObject(obj);
			} else if (vet.at(0) == "clear") {
				canvas->objects.clear();
			} else if (vet.at(0) == "help") {
			
				std::cout << "Avaliable commands: " << std::endl
					<< "  " << "translate X Y       -> translate the selected object;" << std::endl
					<< "  " << "move-to X Y         -> move the selected object;" << std::endl
					<< "  " << "rotate ANGLE        -> rotate the selected object;" << std::endl
					<< "  " << "scale X Y           -> scale the selected object;" << std::endl
					<< "  " << "enframe             -> enframe the selected object (zoom extend);" << std::endl
					<< "  " << "delete              -> delete the selected object;" << std::endl
					<< "  " << "select [prev|next]  -> select the next or the previous object;" << std::endl
					<< "  " << "clear               -> clear the canvas;" << std::endl
					<< "  " << "zoom OFFSET         -> zoom the camera;" << std::endl
					<< "  " << "create TYPE         -> substitue TYPE for one of the following types:" << std::endl
					<< "  " << "							line X1 Y1 X2 Y2;" << std::endl
					<< "  " << "							triangle X1 Y1 X2 Y2 X3 Y3;" << std::endl
					<< "  " << "							rectangle X1 Y1 X2 Y2;" << std::endl
					<< "  " << "							circle X Y RADIUS;" << std::endl;
			
			} else if (vet.at(0) == "zoom") {
				Camera::Zoom(std::stof(vet.at(1)) / 10.0);
			} else if (vet.at(0) == "select") {
				if (vet.at(1) == "next") {
					if (canvas->selectedObject == nullptr && !canvas->objects.empty())
						canvas->SelectObject(canvas->objects.at(0));

					for (int i = 0; i < canvas->objects.size(); i++)
						if (canvas->objects.at(i) == canvas->selectedObject) {
							if (i != canvas->objects.size() - 1) canvas->SelectObject(canvas->objects.at(i + 1));
							else canvas->SelectObject(canvas->objects.at(0));
							break;
						}
				} else if (vet.at(1) == "prev") {
					if (canvas->selectedObject == nullptr && !canvas->objects.empty())
						canvas->SelectObject(canvas->objects.at(0));

					for (int i = 0; i < canvas->objects.size(); i++)
						if (canvas->objects.at(i) == canvas->selectedObject) {
							if (i != 0) canvas->SelectObject(canvas->objects.at(i - 1));
							else canvas->SelectObject(canvas->objects.at(canvas->objects.size() - 1));
							break;
						}
				}

			} else {

				if (canvas->selectedObject == nullptr) throw std::runtime_error("Need to select an object first!");

				if (vet.at(0) == "translate") {
					float x = std::stof(vet.at(1)), y = std::stof(vet.at(2));
					canvas->selectedObject->Move(x, y);
				} else if (vet.at(0) == "rotate") {
					float angle = std::stof(vet.at(1));
					canvas->selectedObject->Rotate(angle);
				} else if (vet.at(0) == "scale") {
					try {
						float x = std::stof(vet.at(1)), y = std::stof(vet.at(2));
						canvas->selectedObject->Scale(x, y);
					} catch (const std::out_of_range &e) {
						float x = std::stof(vet.at(1));
						canvas->selectedObject->Scale(x, x);
					}
				} else if (vet.at(0) == "move-to") {
					float x = std::stof(vet.at(1)), y = std::stof(vet.at(2));
					canvas->selectedObject->Translate(Coord(x, y));
				} else if (vet.at(0) == "delete") {
					canvas->RemoveObject(canvas->selectedObject);
					canvas->selectedObject = nullptr;
				} else if (vet.at(0) == "enframe") {
					canvas->EnframeObject(canvas->selectedObject);
				} else {
					throw std::runtime_error("Unknow command.");
				}
			}

		} catch (const std::runtime_error &e) {
			std::cerr << "Error   > " << e.what() << std::endl;
		} catch (const std::out_of_range &e) {
			std::cerr << "Error   > Wrong parameters." << std::endl;
		}

	}
}