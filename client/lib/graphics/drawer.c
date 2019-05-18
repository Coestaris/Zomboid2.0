//
// Created by maxim on 1/22/19.
//

#include "drawer.h"
#include "../resources/font.h"

size_t MAXDP = MAXDP_START;
size_t DPLEVELS = MAX_DP_LEVELS;

size_t* dpCounts;
drawingPrimitive_t*** dpList;
shader_t* textShader;

int winW, winH;

void dcDrawText(vec_t pos, color_t col, font_t* font, const char* string, double scale)
{
    if (!string) return;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
/*
    glUseProgram(textShader->progID);
    GLint loc = glGetUniformLocation(textShader->progID, "text");
    glUniform1i(loc, 0);

    loc = glGetUniformLocation(textShader->progID, "texcolor");
    glUniform3f(loc, col.r, col.g, col.b);

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(font->VAO);

    for (int c = 0; c < strlen(string); c++)
    {
        font_character_t ch = font->chars[string[c] - font->startIndex];

        GLfloat xpos = pos.x + ch.bearing.x * scale;
        GLfloat ypos = pos.y - (ch.size.y - ch.bearing.y) * scale;

        GLfloat w = ch.size.x * scale;
        GLfloat h = ch.size.y * scale;

        GLfloat vertices[6][4] = {
                { xpos       / winW - 1, (ypos + h) / winH - 1, 0.0, 0.0 },
                { xpos       / winW - 1, ypos 		/ winH - 1, 0.0, 1.0 },
                { (xpos + w) / winW - 1, ypos       / winH - 1, 1.0, 1.0 },

                { xpos       / winW - 1, (ypos + h) / winH - 1, 0.0, 0.0 },
                { (xpos + w) / winW - 1, ypos       / winH - 1, 1.0, 1.0 },
                { (xpos + w) / winW - 1, (ypos + h) / winH - 1, 1.0, 0.0 }
        };

        glBindTexture(GL_TEXTURE_2D, ch.textureID);

        glBindBuffer(GL_ARRAY_BUFFER, font->VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        pos.x += (ch.advance >> 6) * scale;
    }

    glUseProgram(0);

    //glColor3d(0, 1, 0);
*/

    for (int i = 0; i < strlen(string); i++)
    {
        font_character_t ch = font->chars[string[i] - font->startIndex];
        /*for(int j = 0; j < 129; j++) {
            if(font[j].c == s[i]) {
                ch = font[j].info;
                break;
            }
        }
*/
        GLfloat xpos = pos.x + ch.bearing.x * scale;
        GLfloat ypos = pos.y - (ch.size.y + ch.bearing.y) * scale;

        GLfloat w = ch.size.x * scale;
        GLfloat h = ch.size.y * scale;

        glBindTexture(GL_TEXTURE_2D, ch.textureID);
        glColor4f(col.r, col.g, col.b, col.a);

        glBegin(GL_TRIANGLE_STRIP);
            glTexCoord2i(0, 1); glVertex2f(xpos, ypos + h);
            glTexCoord2i(0, 0); glVertex2f(xpos, ypos);
            glTexCoord2i(1, 1); glVertex2f(xpos + w, ypos + h);
            glTexCoord2i(1, 0); glVertex2f(xpos + w, ypos);
        glEnd();


        pos.x += (ch.advance >> 6) * scale;
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    //glUseProgram(0);
}

void dcDrawSurface()
{
    srfBind();

    glBegin(GL_QUADS);
        glTexCoord2i(0, 0); glVertex2f(0.0, 0.0);
        glTexCoord2i(1, 0); glVertex2f(winW, 0.0);
        glTexCoord2i(1, 1); glVertex2f(winW, winH);
        glTexCoord2i(0, 1); glVertex2f(0.0, winH);
    glEnd();
}

void dcDrawStretchedTexture(tex_t* tex, vec_t pos, int frame, color_t col, double w, double h)
{
    bindTex(tex, frame);

    glColor4d(col.r, col.g, col.b, col.a);

    glBegin(GL_QUAD_STRIP);
        glTexCoord2i(0, 1); glVertex2f(pos.x, pos.y + tex->height * h);
        glTexCoord2i(0, 0); glVertex2f(pos.x, pos.y);
        glTexCoord2i(1, 1); glVertex2f(pos.x + tex->width * w, pos.y + tex->height * h);
        glTexCoord2i(1, 0); glVertex2f(pos.x + tex->width * w, pos.y);
    glEnd();
}

void dcDrawBackground(tex_t* tex, int frame, int windowW, int windowH)
{
    bindTex(tex, frame);

    double texW = (double) windowW / tex->width;
    double texH = (double) windowH / tex->height;
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    glBegin(GL_QUAD_STRIP);
        glTexCoord2f(0, (GLfloat) texH);
        glVertex2f((GLfloat) -BACKGROUND_OFFSET, (GLfloat) -BACKGROUND_OFFSET);

        glTexCoord2f(0, 0);
        glVertex2f((GLfloat) -BACKGROUND_OFFSET, (GLfloat) windowH + BACKGROUND_OFFSET);

        glTexCoord2f((GLfloat) texW, (GLfloat) texH);
        glVertex2f((GLfloat) windowW + BACKGROUND_OFFSET, (GLfloat) -BACKGROUND_OFFSET);

        glTexCoord2f((GLfloat) texW, 0);
        glVertex2f((GLfloat) windowW + BACKGROUND_OFFSET, (GLfloat) windowH + BACKGROUND_OFFSET);
    glEnd();
}

void dcDrawLine(vec_t p1, vec_t p2, color_t col)
{
    bindTex(NULL, 0);

    glColor4d(col.r, col.g, col.b, col.a);
    glBegin(GL_LINES);
        glVertex2f(p1.x, p1.y);
        glVertex2f(p2.x, p2.y);
    glEnd();
}

void dcDrawPolygon(relPoint_t* points, int count, vec_t center, color_t col)
{
    bindTex(NULL, 0);

    glPushMatrix();

    glColor4d(col.r, col.g, col.b, col.a);
    glBegin(GL_TRIANGLES);

    for (int i = 0; i < count; i++)
    {
        int c = (i + 1) % count;

        glVertex2f(center.x, center.y);
        glVertex2f(points[i].point.x, points[i].point.y);
        glVertex2f(points[c].point.x, points[c].point.y);
    }
    glEnd();

    glPopMatrix();
}

vec_t rotate_point(double cx, double cy, double angle, vec_t p)
{
    double s = sin(angle);
    double c = cos(angle);

    // translate point back to origin:
    p.x -= cx;
    p.y -= cy;

    // rotate point
    double xnew = p.x * c - p.y * s;
    double ynew = p.x * s + p.y * c;

    // translate point back:
    p.x = xnew + cx;
    p.y = ynew + cy;
    return p;
}

void
dcDrawRotatedTexPolygon(tex_t* tex, int frame, relPoint_t* points, int count, vec_t center, color_t col, double angle,
                        double scale, vec_t texOffset, vec_t texScaleFactor)
{
    bindTex(tex, frame);
    glPushMatrix();

    double x = center.x;
    double y = center.y;

    glColor4f(col.r, col.g, col.b, col.a);
    glBegin(GL_TRIANGLES);

    double zeroX = (tex->width - tex->center.x - texOffset.x) / (2.0 * tex->width);
    double zeroY = (tex->height - tex->center.y - texOffset.y) / (2.0 * tex->height);

    for (int i = 0; i < count; i++)
    {
        int c = (i + 1) % count;

        double x1 = points[i].point.x;
        double x2 = points[c].point.x;
        double y1 = points[i].point.y;
        double y2 = points[c].point.y;

        glTexCoord2f(zeroX, zeroY);
        glVertex2f(x, y);

        vec_t coordP1 = vec(
                (x1 - x) / scale + zeroX,
                (y1 - y) / scale + zeroY);

        coordP1 = rotate_point(zeroX, zeroY, -angle, coordP1);
        glTexCoord2f(
                (coordP1.x - zeroX) / texScaleFactor.x + zeroX,
                (coordP1.y - zeroY) / texScaleFactor.y + zeroY);
        glVertex2f(x1, y1);

        vec_t coordP2 = vec(
                (x2 - x) / scale + zeroX,
                (y2 - y) / scale + zeroY);

        coordP2 = rotate_point(zeroX, zeroY, -angle, coordP2);
        glTexCoord2f(
                (coordP2.x - zeroX) / texScaleFactor.x + zeroX,
                (coordP2.y - zeroY) / texScaleFactor.y + zeroY);
        glVertex2f(x2, y2);
    }
    glEnd();

    glPopMatrix();
}

void dcDrawTexPolygon(tex_t* tex, int frame, relPoint_t* points, int count, vec_t center, color_t col, double scale)
{
    bindTex(tex, frame);
    glPushMatrix();

    glColor4f(col.r, col.g, col.b, col.a);
    glBegin(GL_TRIANGLES);

    double x = center.x;
    double y = center.y;

    for (int i = 0; i < count; i++)
    {
        int c = (i + 1) % count;

        double x1 = points[i].point.x;
        double x2 = points[c].point.x;
        double y1 = points[i].point.y;
        double y2 = points[c].point.y;

        glTexCoord2f(0.5, 0.5);
        glVertex2f(x, y);

        glTexCoord2f((x1 - x) / scale + 0.5, (y1 - y) / scale + 0.5);
        glVertex2f(x1, y1);

        glTexCoord2f((x2 - x) / scale + 0.5, (y2 - y) / scale + 0.5);
        glVertex2f(x2, y2);

    }
    glEnd();

    glPopMatrix();
}

void dcDrawTexture(tex_t* tex, color_t col, int frame, vec_t pos, double angle, double scaleFactor)
{
    bindTex(tex, frame);

    const double hw = tex->width / 2.0;
    const double hh = tex->height / 2.0;

    const double acos = cos(angle) * scaleFactor;
    const double asin = sin(angle) * scaleFactor;

    vec_t p1, p2, p3, p4;

    createRotatedPoint(&p1, pos, acos, asin, hw, hh, vec(-tex->center.x + pos.x, tex->center.y + pos.y), -1, -1);
    createRotatedPoint(&p2, pos, acos, asin, hw, hh, vec(-tex->center.x + pos.x, tex->center.y + pos.y), -1, 1);
    createRotatedPoint(&p3, pos, acos, asin, hw, hh, vec(-tex->center.x + pos.x, tex->center.y + pos.y), 1, -1);
    createRotatedPoint(&p4, pos, acos, asin, hw, hh, vec(-tex->center.x + pos.x, tex->center.y + pos.y), 1, 1);

    glColor4f(col.r, col.g, col.b, col.a);

    glBegin(GL_QUAD_STRIP);
        glTexCoord2i(0, 1); glVertex2f(p1.x, p1.y);
        glTexCoord2i(0, 0); glVertex2f(p2.x, p2.y);
        glTexCoord2i(1, 1); glVertex2f(p3.x, p3.y);
        glTexCoord2i(1, 0); glVertex2f(p4.x, p4.y);
    glEnd();
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
    glLoadIdentity();
    glTranslatef((GLfloat) (sceneW / 2.0), (GLfloat) (sceneH / 2.0), 0);
    glRotatef((GLfloat) angle, 0, 0, 1);
    glTranslatef(-(GLfloat) (sceneW / 2.0), -(GLfloat) (sceneH / 2.0), 0);

}

void checkDPSize(int depth)
{
    assert(depth >= 0 && depth < DPLEVELS);
    assert(dpCounts[depth] < MAXDP);
}

void dqnDrawText(vec_t pos, color_t col, font_t* font, char* string, double size, int depth)
{
    assert(font);
    checkDPSize(depth);

    drawingPrimitive_t* dp = dpList[depth][dpCounts[depth]++];
    dp->type = DPTYPE_TEXT;

    dp->p1 = pos;
    dp->col = col;
    dp->font = font;
    dp->string = string;
    dp->scale = size;
}

void dqnDrawStretchedTexture(tex_t* tex, vec_t pos, int frame, color_t col, double w, double h, int depth)
{
    assert(tex);
    checkDPSize(depth);

    drawingPrimitive_t* dp = dpList[depth][dpCounts[depth]++];
    dp->type = DPTYPE_STR_SPRITE;

    dp->col = col;
    dp->p1 = pos;
    dp->tex = tex;
    dp->frame = frame;

    dp->p2 = vec(w, h);
}

void dqnDrawSprite(tex_t* tex, color_t color, int frame, vec_t pos, double angle, double scaleFactor, int depth)
{
    assert(tex);
    checkDPSize(depth);

    drawingPrimitive_t* dp = dpList[depth][dpCounts[depth]++];
    dp->type = DPTYPE_SPRITE;

    dp->col = color;
    dp->p1 = pos;
    dp->tex = tex;
    dp->frame = frame;
    dp->angle = angle;
    dp->scale = scaleFactor;
};

void dqnDrawPolygon(relPoint_t* points, int count, vec_t center, color_t col, int depth)
{
    checkDPSize(depth);

    drawingPrimitive_t* dp = dpList[depth][dpCounts[depth]++];
    dp->type = DPTYPE_POLY;

    dp->points = points;
    dp->p1 = center;
    dp->count = count;
    dp->col = col;
}

void dqnDrawRotatedTexPolygon(tex_t* tex, int frame, relPoint_t* points, int count, vec_t center, color_t col, double angle,
                         double scale, vec_t texOffset, vec_t texScaleFactor, int depth)
{
    assert(tex);
    checkDPSize(depth);

    drawingPrimitive_t* dp = dpList[depth][dpCounts[depth]++];
    dp->type = DPTYPE_POLY_ROTATEDTEX;

    dp->texOffset = texOffset;
    dp->texScaleFactor = texScaleFactor;

    dp->angle = angle;
    dp->tex = tex;
    dp->frame = frame;
    dp->points = points;
    dp->count = count;
    dp->p1 = center;
    dp->col = col;
    dp->scale = scale;
}

void dqnDrawTexPolygon(tex_t* tex, int frame, relPoint_t* points, int count, vec_t center, color_t col, double scale,
                       int depth)
{
    assert(tex);
    checkDPSize(depth);

    drawingPrimitive_t* dp = dpList[depth][dpCounts[depth]++];
    dp->type = DPTYPE_POLY_TEX;

    dp->tex = tex;
    dp->frame = frame;
    dp->points = points;
    dp->count = count;
    dp->p1 = center;
    dp->col = col;
    dp->scale = scale;
}

void dqnDrawLine(vec_t p1, vec_t p2, color_t col, int depth)
{
    checkDPSize(depth);

    drawingPrimitive_t* dp = dpList[depth][dpCounts[depth]++];
    dp->type = DPTYPE_LINE;

    dp->p1 = p1;
    dp->p2 = p2;
    dp->col = col;
}

int dqnCount(void)
{
    int i = 0;
    for (ssize_t level = 0; level < DPLEVELS; level++)
    {
        i += dpCounts[level];
    }
    return i;
}

void dcDrawPrimitives()
{
    for (ssize_t level = 0; level < DPLEVELS; level++)
    {
        for (size_t i = 0; i < dpCounts[level]; i++)
        {
            drawingPrimitive_t* dp = dpList[level][i];
            switch (dp->type)
            {
                case DPTYPE_TEXT:
                    dcDrawText(dp->p1, dp->col, dp->font, dp->string, dp->scale);
                    break;

                case DPTYPE_SPRITE:
                    dcDrawTexture(
                            dp->tex, dp->col, dp->frame, dp->p1,
                            dp->angle, dp->scale);
                    break;

                case DPTYPE_LINE:
                    dcDrawLine(dp->p1, dp->p2, dp->col);
                    break;

                case DPTYPE_POLY:
                    dcDrawPolygon(dp->points, dp->count, dp->p1, dp->col);
                    break;

                case DPTYPE_POLY_TEX:
                    dcDrawTexPolygon(
                            dp->tex, dp->frame,
                            dp->points, dp->count,
                            dp->p1, dp->col,
                            dp->scale);
                    break;

                case DPTYPE_POLY_ROTATEDTEX:
                    dcDrawRotatedTexPolygon(
                            dp->tex, dp->frame,
                            dp->points, dp->count,
                            dp->p1, dp->col, dp->angle,
                            dp->scale, dp->texOffset, dp->texScaleFactor);
                    break;
                case DPTYPE_STR_SPRITE:
                    dcDrawStretchedTexture(
                            dp->tex, dp->p1, dp->frame,
                            dp->col, dp->p2.x, dp->p2.y);
                    break;

                default:
                    break;
            }
        }
    }
    dqnClearQueue();
}

void dqnClearQueue(void)
{
    for (int i = 0; i < DPLEVELS; i++)
    {
        dpCounts[i] = 0;
    }
}

void dcInit()
{
    textShader = shmGetShader(SHADER_TEXT);
    int loc = glGetUniformLocation(textShader->progID, "text");
    if (loc == -1 || loc == 0)
    {
        puts("[drawer.c][ERROR]: Unable to get font shader uniform location");
        //exit(1);
    }
    else
    {
        glUniform1i(loc, 0);
    }

    dpList = malloc(sizeof(drawingPrimitive_t**) * DPLEVELS);
    dpCounts = malloc(sizeof(size_t) * DPLEVELS);

    for (size_t level = 0; level < DPLEVELS; level++)
    {
        dpList[level] = malloc(sizeof(drawingPrimitive_t*) * MAXDP);
        for (int i = 0; i < MAXDP; i++)
        {
            dpList[level][i] = malloc(sizeof(drawingPrimitive_t));
        }
    }
}