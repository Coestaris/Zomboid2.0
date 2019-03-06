//
// Created by maxim on 1/22/19.
//

#include "appInit.h"

void initGraphics(int argc, char **argv, int w, int h, const char *title, int isFixedSize, char* mainResFile)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA);
    glutInitWindowSize(w, h);
    glutCreateWindow(title);

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, h, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    if(isFixedSize) {
        setFixedSize(w, h);
    }

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable( GL_ALPHA_TEST );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    printf("Using OpenGL Version: %s\n=========\n", (char*)glGetString(GL_VERSION));

    srfInit(w, h);
    initEventFuncs();
    registerEvents();
    dcInit();
    evqInit();
    texmInit();
    rlist_init();

    if(!fileExists(mainResFile)) {
        printf("\"%s\" doesn't exist", mainResFile);
        exit(1);
    }

    if(!rlist_load(mainResFile, true)) {
        puts("There were errors while processing RList (strict mode is turned on). Exiting...");
        exit(1);
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

    glutIdleFunc(mainEventLoop);
    glutDisplayFunc(mainEventLoop);
}

void runApp(int sceneID)
{
    scmLoadScene(sceneID);
    glutMainLoop();
}
