//
// Created by maxim on 1/22/19.
//

#ifndef ZOMBOID2_EVENTFUNCS_H
#define ZOMBOID2_EVENTFUNCS_H

void eventLoop();
void eventKeyDown(int key, int x, int y);
void eventCharKeyDown(unsigned char key, int x, int y);
void eventKeyCharUp(unsigned char key, int x, int y);
void eventKeyUp(int key, int x, int y);
void eventMouseClick(int button, int state, int x, int y);
void eventMouseMove(int x, int y);
void eventMouseEntry(int state);
void eventReshapeFunc(int _width, int _height);

#endif //ZOMBOID2_EVENTFUNCS_H
