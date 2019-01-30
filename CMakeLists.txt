cmake_minimum_required(VERSION 3.13)
project(Zomboid2 C)

set(CMAKE_C_STANDARD 11)



add_executable(Zomboid2 main.c lib/appInit.h lib/appInit.c lib/eventfuncs.h lib/eventfuncs.c lib/tex.h lib/tex.c lib/drawer.h lib/drawer.c lib/texManager.h lib/texManager.c lib/eventQueue.h lib/eventQueue.c game/objects/main/player/obj_player.h lib/gameobject.h lib/gameobject.c game/objects/main/player/obj_player.c lib/gameScene.h lib/gameScene.c lib/helpers.h lib/helpers.c game/objects/main/bullet/obj_bullet.h game/objectInclude.h game/objects/main/bullet/obj_bullet.c game/loader.h game/loader.c game/game.h game/game.c game/objects/main/box/obj_box.h game/objects/main/box/obj_box.c game/objects/main/light/obj_light.h game/objects/main/light/obj_light.c game/objects/main/flashlight/obj_flashlight.h game/objects/main/flashlight/obj_flashlight.c lib/surface.h lib/surface.c game/objects/main/enemy/obj_enemy.c game/objects/main/enemy/obj_enemy.h)

find_path(SOIL_INCLUDE_DIR SOIL.h PATH_SUFFIXES include/SOIL include)

set(SOIL_NAMES SOIL Soil soil)
find_library(SOIL_LIBRARY NAMES ${SOIL_NAMES} )

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} ${SOIL_INCLUDE_DIR})

target_link_libraries(Zomboid2 m)
target_link_libraries(Zomboid2 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${SOIL_LIBRARY} )

