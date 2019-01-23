//
// Created by maxim on 1/22/19.
//

#ifndef ZOMBOID2_EVENTFUNCS_H
#define ZOMBOID2_EVENTFUNCS_H

#include <unistd.h>

#include "GL/freeglut.h"
#include "GL/gl.h"
#include <time.h>
#include <sys/time.h>

#include "drawer.h"
#include "texManager.h"
#include "eventQueue.h"

#define FPSToLock 60.0
#define FPSDelay 1000.0 / FPSToLock
#define FPSAvCounter 1000.0

inline double getMillis(void);
double getFPS(void);

void drawFunc(void);
void pumpEvents(void);

void eventLoop(void);
void eventKeyDown(int key, int x, int y);
void eventCharKeyDown(unsigned char key, int x, int y);
void eventKeyCharUp(unsigned char key, int x, int y);
void eventKeyUp(int key, int x, int y);
void eventMouseClick(int button, int state, int x, int y);
void eventMouseMove(int x, int y);
void eventMouseEntry(int state);
void eventReshapeFunc(int _width, int _height);

#endif //ZOMBOID2_EVENTFUNCS_H
