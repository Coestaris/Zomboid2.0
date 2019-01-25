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

void drawTexture(tex2d* tex, int frame, double x, double y, double angle, double scaleFactor)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex->textureIds[frame]);

    glPushMatrix();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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
        glTexCoord2f(0, 1); glVertex2f((GLfloat)x1, (GLfloat)y1);
        glTexCoord2f(0, 0); glVertex2f((GLfloat)x2, (GLfloat)y2);
        glTexCoord2f(1, 1); glVertex2f((GLfloat)x3, (GLfloat)y3);
        glTexCoord2f(1, 0); glVertex2f((GLfloat)x4, (GLfloat)y4);
    glEnd();

    glPopMatrix();
}

void beginDraw(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void endDraw(void)
{
    glFlush();
}
