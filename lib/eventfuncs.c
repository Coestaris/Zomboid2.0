//
// Created by maxim on 1/22/19.
//

#include "eventfuncs.h"

int counter = 0;
double elapsed = 0;
double fps = 0;
int mousex = -1, mousey = -1;
int fixedW = -1, fixedH = -1;

char keysBuffer[256];
char specKeysBuffer[256];

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
    beginDraw();

    int count = 0;
    gameObject** obj = getObjects(&count);

    if(obj != NULL) {
        for (int i = 0; i < count; i++) {
            if(obj[i]->drawable) {

                if(!obj[i]->cachedTex) {
                    obj[i]->cachedTex = texmGetID(obj[i]->texID);
                    assert(obj[i]->cachedTex != NULL);
                    assert(obj[i]->cachedTex->textureId != 0);
                }

                drawTexture(obj[i]->cachedTex, obj[i]->x, obj[i]->y, obj[i]->angle, obj[i]->size);
            }
        }
    }

    endDraw();
}

void pumpEvents()
{
    event* ev;
    while ((ev = evqNextEvent()))
    {
        freeEvent(ev);
    }
    resetEvents();
}

void eventLoop()
{
    double tickStart = getMillis();
    evqPushEvent(createEvent(EVT_Update, NULL));

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

        printf("FPS: %lf (objects %i, listeners: %i)\n", fps, getObjectsCount(), getListenersCount());
    }
}

void getWinSize(int* w, int* h)
{
    if(fixedH != -1) {
        *w = fixedW;
        *h = fixedH;
    } else {
        *w = glutGet(GLUT_WINDOW_WIDTH);
        *h = glutGet(GLUT_WINDOW_HEIGHT);
    }
}

void getMousePos(int* x, int* y)
{
    *x = mousex;
    *y = mousey;
}

char specKeyPressed(int key)
{
    return specKeysBuffer[key];
}

char keyPressed(unsigned char key)
{
    return keysBuffer[key];
}

void eventKeyDown(int key, int x, int y)
{
    specKeysBuffer[key] = 1;
    evqPushEvent(createEvent(EVT_KeyDown, createKeyboardEvent(key, x, y)));
}

void eventCharKeyDown(unsigned char key, int x, int y)
{
    keysBuffer[tolower(key)] = 1;
    evqPushEvent(createEvent(EVT_CharKeyDown, createKeyboardEvent(key, x, y)));
}

void eventKeyCharUp(unsigned char key, int x, int y)
{
    keysBuffer[tolower(key)] = 0;
    evqPushEvent(createEvent(EVT_CharKeyUp, createKeyboardEvent(key, x, y)));
}

void eventKeyUp(int key, int x, int y)
{
    specKeysBuffer[key] = 0;
    evqPushEvent(createEvent(EVT_KeyUp, createKeyboardEvent(key, x, y)));
}

void eventMouseClick(int button, int state, int x, int y)
{
    evqPushEvent(createEvent(EVT_MouseClick, createMouseEvent(button, state, x, y)));
}

void eventMouseMove(int x, int y)
{
    mousex = x;
    mousey = y;
    evqPushEvent(createEvent(EVT_MouseMove, createMouseEvent(-1, -1, x, y)));
}

void eventMouseEntry(int state)
{
    evqPushEvent(createEvent(EVT_MouseEntry, createMouseEvent(-1, state, -1, -1)));
}

void setFixedSize(int w, int h)
{
    fixedW = w;
    fixedH = h;
}

void eventReshapeFunc(int w, int h)
{
    if(fixedW != -1) {
        glutReshapeWindow(fixedW, fixedH);
    } else {
        glViewport(0, 0, w, h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, w, h, 0, -1, 1);
        glMatrixMode(GL_MODELVIEW);
    }
}