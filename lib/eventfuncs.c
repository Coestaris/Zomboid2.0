//
// Created by maxim on 1/22/19.
//

#include "eventfuncs.h"

#include "GL/freeglut.h"
#include "GL/gl.h"
#include "drawer.h"

void eventLoop()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Drawing is done by specifying a sequence of vertices.  The way these
    // vertices are connected (or not connected) depends on the argument to
    // glBegin.  GL_POLYGON constructs a filled polygon.
    glBegin(GL_POLYGON);
    glColor3f(1, 0, 0); glVertex3f(0, 0, 0);
    glColor3f(0, 1, 0); glVertex3f(400, 0, 0);
    glColor3f(0, 0, 1); glVertex3f(200, 500, 0);
    glEnd();


    // Flush drawing command buffer to make drawing happen as soon as possible.
    glFlush();
}

void eventKeyDown(int key, int x, int y)
{

}

void eventCharKeyDown(unsigned char key, int x, int y)
{

}

void eventKeyCharUp(unsigned char key, int x, int y)
{

}

void eventKeyUp(int key, int x, int y)
{

}

void eventMouseClick(int button, int state, int x, int y)
{

}

void eventMouseMove(int x, int y)
{

}

void eventMouseEntry(int state)
{

}

void eventReshapeFunc(int _width, int _height)
{

}