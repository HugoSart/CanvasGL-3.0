# CMakeList.txt: projeto de CMake para CanvasGL_v3, incluir fonte e definir
# lógica específica a um projeto aqui.
#
cmake_minimum_required (VERSION 3.8)

include_directories(Headers)

set(SOURCES
	Source/Main.cpp
	Source/Global.cpp
	Source/Canvas/Camera.cpp
	Source/Canvas/Canvas.cpp
	Source/Canvas/Color.cpp
	Source/Canvas/Drawer.cpp
	Source/Canvas/Util.cpp
	Source/Drawables/CCircle.cpp
	Source/Drawables/CCircle.cpp
	Source/Drawables/CDot.cpp
	Source/Drawables/CLine.cpp
	Source/Drawables/CObject.cpp
	Source/Drawables/CRectangle.cpp
	Source/Drawables/CTriangle.cpp
	Headers/CanvasGL.h
	Headers/Canvas/Camera.h
	Headers/Canvas/Canvas.h
	Headers/Canvas/Color.h
	Headers/Canvas/Drawer.h
	Headers/Canvas/Util.h
	Headers/Drawables/CCircle.h
	Headers/Drawables/CCircle.h
	Headers/Drawables/CDot.h
	Headers/Drawables/CLine.h
	Headers/Drawables/CObject.h
	Headers/Drawables/CRectangle.h
	Headers/Drawables/CTriangle.h)

# Adicione a fonte ao executável deste projeto.
add_executable (CanvasGLv3 ${SOURCES})

# TODO: Adicione testes e instale destinos, se necessário.
