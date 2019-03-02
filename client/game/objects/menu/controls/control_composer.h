//
// Created by maxim on 3/3/19.
//

#ifndef ZOMBOID2_CONTROL_COMPOSER_H
#define ZOMBOID2_CONTROL_COMPOSER_H

#include "../../../objectInclude.h"

#include "object_control_label.h"
#include "object_control_button.h"

menu_container_child* composer_messageBox_1btn(gameObject* parent, char* string,
        void* font, color_t fontColor, int tex);
menu_container_child* composer_messageBox_2btn(gameObject* parent, char* string,
        void* font, color_t fontColor, int tex, void (*func1)(void), void (*func2)(void));

#endif //ZOMBOID2_CONTROL_COMPOSER_H
