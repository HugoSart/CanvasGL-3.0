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
	Source/Canvas/Coord.cpp
	Source/Canvas/Drawer.cpp
	Source/Canvas/Util.cpp
	Source/Drawables/CCircle.cpp
	Source/Drawables/CCircle.cpp
	Source/Drawables/CDot.cpp
	Source/Drawables/CLine.cpp
	Source/Drawables/CObject.cpp
	Source/Drawables/CRectangle.cpp
	Source/Drawables/CTriangle.cpp
)

# Includes
include_directories("./Libraries/freeglut-MSVC-3.0.0-2.mp/freeglut/include")
include_directories("./Libraries/glew-2.2.0/include")
include_directories("./Libraries/glm-1.0.1-light")

# Links
link_directories("./Libraries/freeglut-MSVC-3.0.0-2.mp/freeglut/lib/x64")
link_directories("./Libraries/glew-2.2.0/lib/Release/x64")

# Adicione a fonte ao executável deste projeto.
add_executable (CanvasGLv3 ${SOURCES})
target_link_libraries(CanvasGLv3 freeglut glew32 opengl32)

add_custom_command(TARGET CanvasGLv3 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/Libraries/glew-2.2.0/bin/Release/x64/glew32.dll"
        $<TARGET_FILE_DIR:CanvasGLv3>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/Libraries/freeglut-MSVC-3.0.0-2.mp/freeglut/bin/x64/freeglut.dll"
        $<TARGET_FILE_DIR:CanvasGLv3>
)
