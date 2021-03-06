//
// Created by maxim on 1/22/19.
//

#ifndef ZOMBOID2_EVENTFUNCS_H
#define ZOMBOID2_EVENTFUNCS_H

#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <ctype.h>

#include "GL/freeglut.h"
#include "GL/gl.h"

#include "../ltracer/ltracer.h"
#include "../graphics/drawer.h"
#include "../resources/texManager.h"
#include "eventQueue.h"
#include "gameScene.h"

#define FPSToLock 60.0
#define FPSDelay 1000.0 / FPSToLock
#define FPSAvCounter 1000.0

#define MOUSE_BUFFER_SIZE 15
#define KEY_BUFFER_SIZE 256
#define SPEC_KEY_BUFFER_SIZE 256

#define PRINT_FRAME_LOG

void initEventFuncs(void);

double getMillis(void);
double getFPS(void);

long long getFrame();
void getWinSize(int* w, int* h);
vec_t getMousePos();
char keyPressed(unsigned char key);
int getMouseState(int button);
char specKeyPressed(int key);

void rotateScene(double angle);

void dfDrawBackground(void);
void dfDrawObjects(void);
void mainDF(void);
void pumpEvents(void);

void mainEventLoop(void);
void eventKeyDown(int key, int x, int y);
void eventCharKeyDown(unsigned char key, int x, int y);
void eventKeyCharUp(unsigned char key, int x, int y);
void eventKeyUp(int key, int x, int y);
void eventMouseClick(int button, int state, int x, int y);
void eventMouseMove(int x, int y);
void eventMouseEntry(int state);
void eventReshapeFunc(int _width, int _height);

void setFixedSize(int w, int h);

#endif //ZOMBOID2_EVENTFUNCS_H
