cmake_minimum_required(VERSION 3.13)
project(Zomboid2 C)

set(CMAKE_C_STANDARD 11)



add_executable(Zomboid2 main.c lib/graphics.h lib/graphics.c lib/eventfuncs.h lib/eventfuncs.c lib/tex.h lib/tex.c lib/drawer.h lib/drawer.c lib/texManager.h lib/texManager.c lib/eventQueue.h lib/eventQueue.c)

find_path(SOIL_INCLUDE_DIR SOIL.h PATH_SUFFIXES include/SOIL include)

set(SOIL_NAMES SOIL Soil soil)
find_library(SOIL_LIBRARY NAMES ${SOIL_NAMES} )

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} ${SOIL_INCLUDE_DIR})

target_link_libraries(Zomboid2 m)
target_link_libraries(Zomboid2 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${SOIL_LIBRARY} )

