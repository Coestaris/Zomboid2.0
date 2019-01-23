//
// Created by maxim on 1/22/19.
//

#include "eventfuncs.h"

int counter = 0;
double elapsed = 0;
double fps = 0;

double getFPS(void)
{
    return fps;
}

double getMillis(void)
{
    struct timeval  tv;
    gettimeofday(&tv, NULL);

    return (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000.0 ;
}

tex2d* tex = NULL;

void drawFunc()
{
    if(tex == NULL) tex = texmGetID(2);

    glClear(GL_COLOR_BUFFER_BIT);

    drawTexture(tex, 200, 200, 0, 1);

    glFlush();
}

void pumpEvents()
{
    event* ev;
    while (ev = evqNextEvent())
    {
        freeEvent(ev);
    }
    resetEvents();
}

void eventLoop()
{
    double tickStart = getMillis();

    pumpEvents();
    drawFunc();

    double diff = getMillis() - tickStart;
    counter++;

    if(diff < FPSDelay) {
        usleep((unsigned int) (FPSDelay - diff) * 1000);
    }

    elapsed += getMillis() - tickStart;


    if(elapsed > FPSAvCounter)
    {
        fps = 1000 * counter / elapsed;
        counter = 0;
        elapsed = 0;
    }
}

void eventKeyDown(int key, int x, int y)
{
    //evqPushEvent(createEvent(EVT_KeyDown, createKeyboardEvent(key, x, y)));
}

void eventCharKeyDown(unsigned char key, int x, int y)
{
    //evqPushEvent(createEvent(EVT_CharKeyDown, createKeyboardEvent(key, x, y)));
}

void eventKeyCharUp(unsigned char key, int x, int y)
{
    //evqPushEvent(createEvent(EVT_CharKeyUp, createKeyboardEvent(key, x, y)));
}

void eventKeyUp(int key, int x, int y)
{
    //evqPushEvent(createEvent(EVT_KeyUp, createKeyboardEvent(key, x, y)));
}

void eventMouseClick(int button, int state, int x, int y)
{
    evqPushEvent(createEvent(EVT_MouseClick, createMouseEvent(button, state, x, y)));
}

void eventMouseMove(int x, int y)
{
    //evqPushEvent(createEvent(EVT_MouseMove, createMouseEvent(-1, -1, x, y)));
}

void eventMouseEntry(int state)
{
    //evqPushEvent(createEvent(EVT_MouseEntry, createMouseEvent(-1, state, -1, -1)));
}

void eventReshapeFunc(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, h, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}