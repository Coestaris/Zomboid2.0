//
// Created by maxim on 1/22/19.
//

#include "drawer.h"

void createPoint(double* x, double* y, double inx, double iny, double vcos, double vsin,
        double hw, double hh, double cx, double cy, int s1, int s2)
{
    inx += hw * s1;
    iny += hh * s2;

    *x = inx * vcos - iny * vsin - cx * (vcos - 1) + cy * vsin;
    *y = inx * vsin + iny * vcos - cy * (vcos - 1) - cx * vsin;
}

void drawBackground(tex2d* tex, int frame, int windowW, int windowH)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex->textureIds[frame]);

    //glPushMatrix();

    double texW = (double)windowW / tex->width;
    double texH = (double)windowH / tex->height;

    glBegin(GL_QUAD_STRIP);
        glTexCoord2f(0,             (GLfloat)texH); glVertex2f((GLfloat)-10,       (GLfloat)      -10);
        glTexCoord2f(0,                         0); glVertex2f((GLfloat)-10,       (GLfloat)windowH + 10);
        glTexCoord2f((GLfloat)texW, (GLfloat)texH); glVertex2f((GLfloat)windowW + 10, (GLfloat)      -10);
        glTexCoord2f((GLfloat)texW,             0); glVertex2f((GLfloat)windowW + 10, (GLfloat)windowH + 10);
    glEnd();

    //glPopMatrix();
}

void drawTexture(tex2d* tex, int frame, double x, double y, double angle, double scaleFactor)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex->textureIds[frame]);

    //glPushMatrix();

    const double hw = tex->width / 2.0;
    const double hh = tex->height / 2.0;

    const double acos = cos(angle) * scaleFactor;
    const double asin = sin(angle) * scaleFactor;

    double x1, x2, x3, x4, y1, y2, y3, y4;

    createPoint(&x1, &y1, x, y, acos, asin, hw, hh, - tex->centerX + x, tex->centerY + y, -1, -1);
    createPoint(&x2, &y2, x, y, acos, asin, hw, hh, - tex->centerX + x, tex->centerY + y, -1,  1);
    createPoint(&x3, &y3, x, y, acos, asin, hw, hh, - tex->centerX + x, tex->centerY + y,  1, -1);
    createPoint(&x4, &y4, x, y, acos, asin, hw, hh, - tex->centerX + x, tex->centerY + y,  1,  1);

    glBegin(GL_QUAD_STRIP);
        glTexCoord2f(0, 1); glVertex3f((GLfloat)x1, (GLfloat)y1, 1);
        glTexCoord2f(0, 0); glVertex3f((GLfloat)x2, (GLfloat)y2, 1);
        glTexCoord2f(1, 1); glVertex3f((GLfloat)x3, (GLfloat)y3, 1);
        glTexCoord2f(1, 0); glVertex3f((GLfloat)x4, (GLfloat)y4, 1);
    glEnd();

    //glPopMatrix();
}

void beginDraw(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void endDraw(void)
{
    glFlush();
}

void rotateScreen(double angle, double sceneW, double sceneH)
{
    glLoadIdentity ();
    glTranslatef((GLfloat)(sceneW / 2.0), (GLfloat)(sceneH / 2.0), 0);
    glRotatef((GLfloat)angle, 0, 0, 1);
    glTranslatef(- (GLfloat)(sceneW / 2.0), - (GLfloat)(sceneH / 2.0), 0);

}