cmake_minimum_required(VERSION 3.13)
project(Zomboid2 C)

set(CMAKE_C_STANDARD 11)

FILE(GLOB oilSources ../lib/oil/*.c)
FILE(GLOB oilHeaders ../lib/oil/*.h)
add_executable(Zomboid2 main.c lib/appInit.h lib/appInit.c lib/gameLogic/eventfuncs.h lib/gameLogic/eventfuncs.c lib/resources/tex.h lib/resources/tex.c lib/graphics/drawer.h lib/graphics/drawer.c lib/resources/texManager.h lib/resources/texManager.c lib/gameLogic/eventQueue.h lib/gameLogic/eventQueue.c game/objects/main/player/obj_player.h lib/gameLogic/gameobject.h lib/gameLogic/gameobject.c game/objects/main/player/obj_player.c lib/gameLogic/gameScene.h lib/gameLogic/gameScene.c lib/helpers.h lib/helpers.c game/objects/main/bullet/obj_bullet.h game/objectInclude.h game/objects/main/bullet/obj_bullet.c game/loader.h game/loader.c game/game.h game/game.c game/objects/main/box/obj_box.h game/objects/main/box/obj_box.c game/objects/main/light/obj_light.h game/objects/main/light/obj_light.c game/objects/main/flashlight/obj_flashlight.h game/objects/main/flashlight/obj_flashlight.c lib/graphics/surface.h lib/graphics/surface.c game/objects/main/enemy/obj_enemy.c game/objects/main/enemy/obj_enemy.h lib/rlist/rlist.h lib/rlist/rlist.c lib/rlist/rlist_commands.c lib/rlist/rlist_commands.h lib/rlist/rlist_c.c lib/rlist/rlist_c.h lib/gameLogic/gameHelpers.c lib/gameLogic/gameHelpers.h game/objects/main/light/obj_light_tracer.c game/objects/main/light/obj_light_tracer.h lib/structs.c lib/structs.h game/objects/main/light/obj_rotatable_light.c game/objects/main/light/obj_rotatable_light.h lib/ltracer/ltracer.c lib/ltracer/ltracer.h lib/ltracer/ltracer_structs.h lib/ltracer/ltracer_math.c lib/ltracer/ltracer_math.h lib/menu/controls/control_button.c lib/menu/controls/control_button.h game/objects/menu/object_menu.c game/objects/menu/object_menu.h lib/menu/menu_container.c lib/menu/menu_container.h lib/menu/controls/control_label.c lib/menu/controls/control_label.h lib/menu/composer.c lib/menu/composer.h lib/menu/controls/control_input.c lib/menu/controls/control_input.h lib/shaders/shader.c lib/shaders/shader.h ${oilSources} ${oilHeaders} lib/shaders/shaderManager.c lib/shaders/shaderManager.h lib/graphics/gmath.c lib/graphics/gmath.h)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS})

target_link_libraries(Zomboid2 m)
target_link_libraries(Zomboid2 z)
target_link_libraries(Zomboid2 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

target_compile_options(Zomboid2 PRIVATE "-Wno-implicit-function-declaration")

add_custom_command(
        TARGET Zomboid2
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/lib/shaders/shaders/* ${CMAKE_CURRENT_BINARY_DIR}/shaders
        COMMENT "Copying shaders to output directory")