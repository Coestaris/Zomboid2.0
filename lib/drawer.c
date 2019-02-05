//
// Created by maxim on 1/22/19.
//

#include "drawer.h"

void dcCreatePoint(double *x, double *y, double inx, double iny, double vcos, double vsin,
                   double hw, double hh, double cx, double cy, int s1, int s2)
{
    inx += hw * s1;
    iny += hh * s2;

    *x = inx * vcos - iny * vsin - cx * (vcos - 1) + cy * vsin;
    *y = inx * vsin + iny * vcos - cy * (vcos - 1) - cx * vsin;
}


void dcDrawText(double x, double y, double r, double g, double b, double a, void *font, const char *string)
{
    glBindTexture(GL_TEXTURE_2D, 0);

    int j = (int)strlen( string );
    glColor4d(r, g, b, a);

    glRasterPos2f(x, y);

    for( int i = 0; i < j; i++ ) {
        glutBitmapCharacter(font, string[i]);
        //glutStrokeCharacter(font, string[i]);
    }
}

void dcDrawSurface(int winW, int winH)
{
    srfBind();

    glBegin( GL_QUADS );
        glTexCoord2f(0.0, 0.0);	glVertex2f(0.0,	  0.0);
        glTexCoord2f(1.0, 0.0); glVertex2f(winW,  0.0);
        glTexCoord2f(1.0, 1.0); glVertex2f(winW, winH);
        glTexCoord2f(0.0, 1.0); glVertex2f(0.0,  winH);
    glEnd();
}

void dcDrawBackground(tex2d *tex, int frame, int windowW, int windowH)
{
    glBindTexture(GL_TEXTURE_2D, tex->textureIds[frame]);

    glPushMatrix();

    double texW = (double)windowW / tex->width;
    double texH = (double)windowH / tex->height;
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    glBegin(GL_QUAD_STRIP);
        glTexCoord2f(0,             (GLfloat)texH);
        glVertex2f((GLfloat) - BACKGROUND_OFFSET,        (GLfloat)        - BACKGROUND_OFFSET);

        glTexCoord2f(0,                         0);
        glVertex2f((GLfloat) - BACKGROUND_OFFSET,        (GLfloat)windowH + BACKGROUND_OFFSET);

        glTexCoord2f((GLfloat)texW, (GLfloat)texH);
        glVertex2f((GLfloat)windowW + BACKGROUND_OFFSET, (GLfloat)        - BACKGROUND_OFFSET);

        glTexCoord2f((GLfloat)texW,             0);
        glVertex2f((GLfloat)windowW + BACKGROUND_OFFSET, (GLfloat)windowH + BACKGROUND_OFFSET);
    glEnd();

    glPopMatrix();
}

void dcDrawLine(double x1, double y1, double x2, double y2, double r, double g, double b, double a)
{
    glBindTexture(GL_TEXTURE_2D, 0);

    glBegin(GL_LINES);
        glVertex3d(x1, y1, 0);
        glVertex3d(x2, y2, 0);
    glEnd();
}

void dcDrawPolygon(double* points, int count, double r, double g, double b, double a)
{
    glBindTexture(GL_TEXTURE_2D, 0);
    glPushMatrix();

    glColor4d(r, g, b, a);

    glBegin(GL_POLYGON);
        for(int i = 0; i < count; i += 2){
            glVertex2d(points[i], points[i + 1]);
        }
    glEnd();
    /*glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(count, GL_DOUBLE, 0, points);
    glDrawArrays(GL_TRIANGLE_FAN, 0, count);

    glDisableClientState(GL_VERTEX_ARRAY);
*/
    glPopMatrix();
}

void dcDrawTexture(tex2d *tex, double alpha, int frame, double x, double y, double angle, double scaleFactor)
{
    glBindTexture(GL_TEXTURE_2D, tex->textureIds[frame]);

    glPushMatrix();

    const double hw = tex->width / 2.0;
    const double hh = tex->height / 2.0;

    const double acos = cos(angle) * scaleFactor;
    const double asin = sin(angle) * scaleFactor;

    double x1, x2, x3, x4, y1, y2, y3, y4;

    dcCreatePoint(&x1, &y1, x, y, acos, asin, hw, hh, -tex->centerX + x, tex->centerY + y, -1, -1);
    dcCreatePoint(&x2, &y2, x, y, acos, asin, hw, hh, -tex->centerX + x, tex->centerY + y, -1, 1);
    dcCreatePoint(&x3, &y3, x, y, acos, asin, hw, hh, -tex->centerX + x, tex->centerY + y, 1, -1);
    dcCreatePoint(&x4, &y4, x, y, acos, asin, hw, hh, -tex->centerX + x, tex->centerY + y, 1, 1);

    if(tex->mode == TEXMODE_OVERLAY)
    {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        glBlendEquation(GL_ADD);
    }
    else
    {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    glColor4f(1.0f, 1.0f, 1.0f, (GLfloat)alpha);

    glBegin(GL_QUAD_STRIP);
        glTexCoord2f(0, 1); glVertex3f((GLfloat)x1, (GLfloat)y1, 1);
        glTexCoord2f(0, 0); glVertex3f((GLfloat)x2, (GLfloat)y2, 1);
        glTexCoord2f(1, 1); glVertex3f((GLfloat)x3, (GLfloat)y3, 1);
        glTexCoord2f(1, 0); glVertex3f((GLfloat)x4, (GLfloat)y4, 1);
    glEnd();

    glPopMatrix();
}

void dcBeginDraw(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void dcEndDraw(void)
{
    glutSwapBuffers();
}

void dcRotateScreen(double angle, double sceneW, double sceneH)
{
    glLoadIdentity ();
    glTranslatef((GLfloat)(sceneW / 2.0), (GLfloat)(sceneH / 2.0), 0);
    glRotatef((GLfloat)angle, 0, 0, 1);
    glTranslatef(- (GLfloat)(sceneW / 2.0), - (GLfloat)(sceneH / 2.0), 0);

}

#define MAXDP_START 256
#define SIZE_INCREASE 1.2

size_t MAXDP = MAXDP_START;
size_t dpCount = 0;

drawingPrimitive** dpList;

void checkDPSize()
{
    if(dpCount == MAXDP - 1) {
        size_t newSize = (size_t)(MAXDP * SIZE_INCREASE);
        dpList = realloc(dpList, newSize);
        for(size_t i = dpCount; i < newSize; i++) {
            dpList[i] = malloc(sizeof(drawingPrimitive));
        }
    }
}

void dqnDrawText(double x, double y, double r, double g, double b, double a, void *font, char *string)
{
    checkDPSize();
    drawingPrimitive* dp = dpList[dpCount++];
    dp->type = DPTYPE_TEXT;

    dp->x1 = x; dp->y1 = y;
    dp->r = r; dp->g = g; dp->b = b; dp->a = a;
    dp->font = font;
    dp->string = string;
}

void dqnDrawSprite(tex2d *tex, double alpha, int frame, double x, double y, double angle, double scaleFactor)
{
    checkDPSize();
    drawingPrimitive* dp = dpList[dpCount++];
    dp->type = DPTYPE_SPRITE;

    dp->tex =tex;
    dp->a = alpha;
    dp->frame = frame;
    dp->x1 = x; dp->y1 = y;
    dp->angle = angle;
    dp->scale = scaleFactor;
};

void dqnDrawPolygon(double* points, int count, double r, double g, double b, double a)
{
    checkDPSize();
    drawingPrimitive* dp = dpList[dpCount++];
    dp->type = DPTYPE_POLY;

    dp->points = points;
    dp->scale = count;
    dp->r = r; dp->g = g; dp->b = b; dp->a = a;
}

void dqnDrawLine(double x1, double y1, double x2, double y2, double r, double g, double b, double a)
{
    checkDPSize();
    drawingPrimitive* dp = dpList[dpCount++];
    dp->type = DPTYPE_LINE;

    dp->x1 = x1; dp->y1 = y1; dp->x2 = x2; dp->y2 = y2;
    dp->r = r; dp->g = g; dp->b = b; dp->a = a;
}

void dcDrawPrimitives()
{
    for(size_t i = 0; i < dpCount; i++) {
        drawingPrimitive* dp = dpList[i];
        switch(dp->type) {
            case DPTYPE_TEXT:
                dcDrawText(
                    dp->x1, dp->y1,
                    dp->r, dp->g, dp->b, dp->a,
                    dp->font, dp->string);
                break;

            case DPTYPE_SPRITE:
                dcDrawTexture(
                    dp->tex, dp->a,
                    dp->frame,
                    dp->x1, dp->y1,
                    dp->angle, dp->scale);
                break;
            case DPTYPE_LINE:
                dcDrawLine(
                    dp->x1, dp->y1,
                    dp->x2, dp->y2,
                    dp->r, dp->g, dp->b, dp->a);
                break;
            case DPTYPE_POLY:
                dcDrawPolygon(
                        dp->points, (int)dp->scale,
                        dp->r, dp->g, dp->b, dp->a);

            default:
                break;
        }
    }
    dpCount = 0;
}

void dcInit()
{
    dpList = malloc(sizeof(drawingPrimitive*) * MAXDP);
    for(int i = 0; i < MAXDP; i++) {
        dpList[i] = malloc(sizeof(drawingPrimitive));
    }
}
