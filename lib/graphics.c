//
// Created by maxim on 1/22/19.
//

#include "graphics.h"

void initGraphics(int argc, char **argv, int w, int h, const char *title, int isFixedSize)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(w, h);
    glutInitWindowPosition(80, 80);
    glutCreateWindow(title);

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, h, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    if(isFixedSize) {
        setFixedSize(w, h);
    }
}

void registerEvents()
{
    glutIgnoreKeyRepeat(1);
    glutSpecialUpFunc(eventKeyUp);
    glutSpecialFunc(eventKeyDown);
    glutMotionFunc(eventMouseMove);
    glutPassiveMotionFunc(eventMouseMove);
    glutMouseFunc(eventMouseClick);
    glutReshapeFunc(eventReshapeFunc);

    glutEntryFunc(eventMouseEntry);
    glutKeyboardFunc(eventCharKeyDown);
    glutKeyboardUpFunc(eventKeyCharUp);

    glutIdleFunc(eventLoop);
    glutDisplayFunc(eventLoop);
}

void run(int sceneID)
{
    loadScene(sceneID, 1, 1, 1);
    glutMainLoop();
}
