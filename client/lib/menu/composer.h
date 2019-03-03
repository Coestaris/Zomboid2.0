//
// Created by maxim on 3/3/19.
//

#ifndef ZOMBOID2_CONTROL_COMPOSER_H
#define ZOMBOID2_CONTROL_COMPOSER_H

#include "../gameLogic/gameobject.h"
#include "../resources/texManager.h"

#include "controls/control_label.h"
#include "controls/control_button.h"

#include "menu_container.h"

menu_container_child* composer_messageBox_1btn(gameObject* parent, char* string, char* s1, int btnTex,
                                               void* font, color_t fontColor, int tex, void (*func)(void));

menu_container_child* composer_messageBox_2btn(gameObject* parent, char* text, char* s1, char* s2, int btnTex,
                                               void* font, color_t fontColor, int tex, void (*func1)(void), void (*func2)(void));

menu_container_child* composer_input_double(gameObject* parent, char* sl1, char* sl2, char* s1, char* s2,
                                            char* defStr1, char* defStr2, int btnTex, void* font, color_t fontColor,
                                            int tex, void (*func1)(char*), void (*func2)(char*));

#endif //ZOMBOID2_CONTROL_COMPOSER_H
