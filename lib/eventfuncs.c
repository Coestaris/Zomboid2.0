//
// Created by maxim on 1/22/19.
//

#include "eventfuncs.h"

int counter = 0;
double elapsed = 0;
double fps = 0;
int mousex = -1, mousey = -1;
int fixedW = -1, fixedH = -1;
long long frames;

char keysBuffer[KEY_BUFFER_SIZE];
char specKeysBuffer[SPEC_KEY_BUFFER_SIZE];
int mouseBuffer[MOUSE_BUFFER_SIZE];

long long getFrame()
{
    return frames;
}

void initEventFuncs(void)
{
    memset(mouseBuffer, MS_RELEASED, sizeof(int) * MOUSE_BUFFER_SIZE);
}

double getFPS(void)
{
    return fps;
}

int getMouseState(int button)
{
    assert(button < MOUSE_BUFFER_SIZE);
    return mouseBuffer[button];
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
    gameScene* scene = activeScene();

    if(scene->backgroundTexId)
    {
        if(!scene->cachedBack)
        {
            scene->cachedBack = texmGetID(scene->backgroundTexId);
            assert(scene->cachedBack != NULL);
            assert(scene->cachedBack->textureIds[0] != 0);
        }

        drawBackground(scene->cachedBack, 0, fixedW, fixedH);
    }

    if(obj != NULL)
    {
        for (int i = 0; i < count; i++)
        {
            if(obj[i]->drawable)
            {
                if(!obj[i]->cachedTex)
                {
                    obj[i]->cachedTex = texmGetID(obj[i]->texID);
                    assert(obj[i]->cachedTex != NULL);

                    for(int j = 0; j < obj[i]->cachedTex->framesCount; j++)
                        assert(obj[i]->cachedTex->textureIds[j] != 0);
                }

                if(obj[i]->animationSpeed != 0)
                {
                    obj[i]->animationCounter++;
                    if(obj[i]->animationCounter == obj[i]->animationSpeed)
                    {
                        obj[i]->frame += 1;
                        obj[i]->animationCounter = 0;
                        if(obj[i]->frame >= obj[i]->cachedTex->framesCount)
                        {
                            obj[i]->frame = 0;
                        }
                    }
                }

                drawTexture(obj[i]->cachedTex, obj[i]->frame, obj[i]->x, obj[i]->y, obj[i]->angle, obj[i]->size);
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
    frames++;

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
    mouseBuffer[button] = state;
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