//
// Created by maxim on 1/22/19.
//

#include "drawer.h"

GLfloat imageVertices[] = {
     0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f, -0.5f,  0.0f,  1.0f,  1.0f,
    -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,
    -0.5f,  0.5f,  0.0f,  0.0f,  0.0f
};

GLint indices[] = {
    0, 1, 3,
    1, 2, 3
};

size_t winW, winH;

GLint ImageVAO;

shader* imageShader;
shader* backgroundShader;

//Image Rotate matrix
mat4 rm;
//Image Transform matrix
mat4 tm;
//Image Scale matrix
mat4 sm;
//Result image matrix
mat4 m;

size_t MAXDP = MAXDP_START;
size_t DPLEVELS = MAX_DP_LEVELS;

size_t* dpCounts;
drawingPrimitive*** dpList;

void dcCreatePoint(vec_t* p, vec_t inp, double vcos, double vsin, double hw, double hh, vec_t cp, int s1, int s2)
{
    inp.x += hw * s1;
    inp.y += hh * s2;

    p->x = inp.x * vcos - inp.y * vsin - cp.x * (vcos - 1) + cp.y * vsin;
    p->y = inp.x * vsin + inp.y * vcos - cp.y * (vcos - 1) - cp.x * vsin;
}


void dcDrawText(vec_t pos, color_t col, void *font, const char *string)
{
   /* if(!string)
        return;

    bindTex(NULL, 0);

    int j = (int)strlen( string );
    glColor4d(col.r, col.g, col.b, col.a);

    glRasterPos2d(pos.x, pos.y);

    for( int i = 0; i < j; i++ ) {
        glutBitmapCharacter(font, string[i]);
        //glutStrokeCharacter(font, string[i]);
    }*/
}

void dcDrawSurface(int winW, int winH)
{
    /*
    srfBind();

    glBegin( GL_QUADS );
        glTexCoord2f(0.0, 0.0);	glVertex2f(0.0,	  0.0);
        glTexCoord2f(1.0, 0.0); glVertex2f(winW,  0.0);
        glTexCoord2f(1.0, 1.0); glVertex2f(winW, winH);
        glTexCoord2f(0.0, 1.0); glVertex2f(0.0,  winH);
    glEnd();*/
}

void dcDrawBackground(tex2d *tex, int frame)
{
    bindTex(tex, frame);
    glUseProgram(backgroundShader->progID);
    glBindVertexArray(tex->VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void dcDrawLine(vec_t p1, vec_t p2, color_t col)
{
    /*
    bindTex(NULL, 0);

    glColor4d(col.r, col.g, col.b, col.a);
    glBegin(GL_LINES);
        glVertex3d(p1.x, p1.y, 0);
        glVertex3d(p2.x, p2.y, 0);
    glEnd();
     */
}

#include "../helpers.h"

void dcDrawPolygon(relPoint_t* points, int count, vec_t center, color_t col)
{
    /*
    bindTex(NULL, 0);

    glPushMatrix();

    glColor4d(col.r, col.g, col.b, col.a);
    glBegin(GL_TRIANGLES);

        for(int i = 0; i < count; i++) {
            int c = (i + 1) % count;

            glVertex2d(center.x, center.y);

            glVertex2d(points[i].point.x, points[i].point.y);
            glVertex2d(points[c].point.x, points[c].point.y);
        }
    glEnd();

    glPopMatrix();
     */
}

vec_t rotate_point(double cx, double cy,double angle, vec_t p)
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

void dcDrawRotatedTexPolygon(tex2d* tex, int frame, relPoint_t *points, int count, vec_t center, color_t col, double angle,
        double scale, vec_t texOffset, vec_t texScaleFactor)
{
    /*
    bindTex(tex, frame);
    glPushMatrix();

    double x = center.x;
    double y = center.y;

    glColor4d(col.r, col.g, col.b, col.a);
    glBegin(GL_TRIANGLES);

    double zeroX = (tex->width - tex->center.x  - texOffset.x) / (2.0 * tex->width);
    double zeroY = (tex->height - tex->center.y - texOffset.y) / (2.0 * tex->height);

    for(int i = 0; i < count; i++) {
        int c = (i + 1) % count;

        double x1 = points[i].point.x;
        double x2 = points[c].point.x;
        double y1 = points[i].point.y;
        double y2 = points[c].point.y;

        glTexCoord2d(zeroX, zeroY);
        glVertex2d(x, y);

        vec_t coordP1 = vec(
                (x1 - x) / scale + zeroX,
                (y1 - y) / scale + zeroY);

        coordP1 = rotate_point(zeroX, zeroY, - angle, coordP1);
        glTexCoord2d(
                (coordP1.x - zeroX) / texScaleFactor.x + zeroX,
                (coordP1.y - zeroY) / texScaleFactor.y + zeroY);
        glVertex2d(x1, y1);

        vec_t coordP2 = vec(
                (x2 - x) / scale + zeroX,
                (y2 - y) / scale + zeroY);

        coordP2 = rotate_point(zeroX, zeroY, - angle, coordP2);
        glTexCoord2d(
                (coordP2.x - zeroX) / texScaleFactor.x + zeroX,
                (coordP2.y - zeroY) / texScaleFactor.y + zeroY);
        glVertex2d(x2, y2);


    }
    glEnd();

    glPopMatrix();
     */
}

void dcDrawTexPolygon(tex2d* tex, int frame, relPoint_t *points, int count, vec_t center, color_t col, double scale)
{
    /*
    bindTex(tex, frame);
    glPushMatrix();

    glColor4d(col.r, col.g, col.b, col.a);
    glBegin(GL_TRIANGLES);

    double x = center.x;
    double y = center.y;

    for(int i = 0; i < count; i++) {
        int c = (i + 1) % count;

        double x1 = points[i].point.x;
        double x2 = points[c].point.x;
        double y1 = points[i].point.y;
        double y2 = points[c].point.y;

        glTexCoord2d(0.5, 0.5);
        glVertex2d(x, y);

        glTexCoord2d((x1 - x) / scale + 0.5, (y1 - y) / scale + 0.5);
        glVertex2d(x1, y1);

        glTexCoord2d((x2 - x) / scale + 0.5, (y2 - y) / scale + 0.5);
        glVertex2d(x2, y2);

    }
    glEnd();

    glPopMatrix();
     */
}

void dcDrawTexture(tex2d *tex, color_t col, int frame, vec_t pos, double angle, double scaleFactor)
{
    bindTex(tex, frame);

    identityMat(m);

    float k = (float)winW / winH;

    identityMat(rm);
    rotateMat4Z(rm, -angle);

    identityMat(sm);
    scaleMat(sm, tex->width / (float)winW * (scaleFactor + 1), tex->height / (float)winH * (scaleFactor + 1) / k, 1);

    identityMat(tm);
    translateMat(tm, pos.x / (float)(winW / 2.0) - 1.0f, (winH - pos.y) / (float)(winH / 2.0) - 1.0f, 0);

    mat4_mulm(m, tm);
    mat4_mulm(m, rm);
    mat4_mulm(m, sm);

    identityMat(tm);
    translateMat(tm, tex->center.x / tex->width, tex->center.y / tex->width, 0);
    mat4_mulm(m, tm);

    glUseProgram(imageShader->progID);

    GLint transformLoc = glGetUniformLocation(imageShader->progID, "transform");
    GLint colorLoc = glGetUniformLocation(imageShader->progID, "color");

    glUniformMatrix4fv(transformLoc, 1, GL_TRUE, m);
    glUniform4f(colorLoc, col.r, col.g, col.b, col.a);

    glBindVertexArray(ImageVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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
    /*
    glLoadIdentity ();
    glTranslatef((GLfloat)(sceneW / 2.0), (GLfloat)(sceneH / 2.0), 0);
    glRotatef((GLfloat)angle, 0, 0, 1);
    glTranslatef(- (GLfloat)(sceneW / 2.0), - (GLfloat)(sceneH / 2.0), 0);
     */

}

void checkDPSize(int depth)
{
    assert(depth >= 0 && depth < DPLEVELS);
    assert(dpCounts[depth] < MAXDP);
}

void dqnDrawText(vec_t pos, color_t col, void *font, char *string, int depth)
{
    checkDPSize(depth);

    drawingPrimitive* dp = dpList[depth][dpCounts[depth]++];
    dp->type = DPTYPE_TEXT;

    dp->p1 =  pos;
    dp->col = col;
    dp->font = font;
    dp->string = string;
}

void dqnDrawSprite(tex2d *tex, color_t color, int frame, vec_t pos, double angle, double scaleFactor, int depth)
{
    checkDPSize(depth);

    drawingPrimitive* dp = dpList[depth][dpCounts[depth]++];
    dp->type = DPTYPE_SPRITE;

    dp->col = color;
    dp->p1 = pos;
    dp->tex =tex;
    dp->frame = frame;
    dp->angle = angle;
    dp->scale = scaleFactor;
};

void dqnDrawPolygon(relPoint_t* points, int count, vec_t center, color_t col, int depth)
{
    checkDPSize(depth);

    drawingPrimitive* dp = dpList[depth][dpCounts[depth]++];
    dp->type = DPTYPE_POLY;

    dp->points = points;
    dp->p1 = center;
    dp->count = count;
    dp->col = col;
}

void dqnDrawRotatedTexPolygon(tex2d* tex, int frame, relPoint_t *points, int count, vec_t center, color_t col, double angle,
                              double scale, vec_t texOffset, vec_t texScaleFactor, int depth)
{
    checkDPSize(depth);

    drawingPrimitive* dp = dpList[depth][dpCounts[depth]++];
    dp->type = DPTYPE_POLY_ROTATEDTEX;

    dp->texOffset = texOffset;
    dp->texScaleFactor = texScaleFactor;

    dp->angle = angle;
    dp->tex = tex;
    dp->frame = frame;
    dp->points = points;
    dp->count= count;
    dp->p1 = center;
    dp->col = col;
    dp->scale = scale;
}

void dqnDrawTexPolygon(tex2d* tex, int frame, relPoint_t *points, int count, vec_t center, color_t col, double scale, int depth)
{
    checkDPSize(depth);

    drawingPrimitive* dp = dpList[depth][dpCounts[depth]++];
    dp->type = DPTYPE_POLY_TEX;

    dp->tex = tex;
    dp->frame = frame;
    dp->points = points;
    dp->count= count;
    dp->p1 = center;
    dp->col = col;
    dp->scale = scale;
}

void dqnDrawLine(vec_t p1, vec_t p2, color_t col, int depth)
{
    checkDPSize(depth);

    drawingPrimitive* dp = dpList[depth][dpCounts[depth]++];
    dp->type = DPTYPE_LINE;

    dp->p1 = p1;
    dp->p2 = p2;
    dp->col = col;
}

void dcDrawPrimitives()
{
    for(ssize_t level = 0; level < DPLEVELS; level++) {
        for (size_t i = 0; i < dpCounts[level]; i++) {
            drawingPrimitive *dp = dpList[level][i];
            switch (dp->type) {
                case DPTYPE_TEXT:
                    dcDrawText(dp->p1, dp->col, dp->font, dp->string);
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


                default:
                    break;
            }
        }
    }
    dqnClearQueue();
}

void dqnClearQueue(void)
{
    for(int i = 0; i < DPLEVELS; i++) {
        dpCounts[i] = 0;
    }
}

void dcInit()
{
    rm = cmat4();
    tm = cmat4();
    sm = cmat4();

    m = cmat4();

    imageShader = shmGetShader(SHADER_IMAGE);
    backgroundShader = shmGetShader(SHADER_BACKGROUND);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GLint VBO, EBO;

    glGenVertexArrays(1, &ImageVAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(ImageVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(imageVertices), imageVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glUseProgram(imageShader->progID);
    shaderSetInt(imageShader, "texture1", 0);

    glUseProgram(backgroundShader->progID);
    shaderSetInt(backgroundShader, "texture1", 0);

    dpList = malloc(sizeof(drawingPrimitive**) * DPLEVELS);
    dpCounts = malloc(sizeof(size_t) * DPLEVELS);

    for(size_t level = 0; level < DPLEVELS; level++) {
        dpList[level] = malloc(sizeof(drawingPrimitive *) * MAXDP);
        for (int i = 0; i < MAXDP; i++) {
            dpList[level][i] = malloc(sizeof(drawingPrimitive));
        }
    }
}