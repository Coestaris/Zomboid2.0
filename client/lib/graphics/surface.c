//
// Created by maxim on 1/26/19.
//

#include "surface.h"

GLuint surfTexID;
GLuint surfFBO;

#define glSrfCheck(s) glCheck("surface.c", s)
int srfFree()
{
    GLenum glerror = glGetError(); //reset gl error flag

    glBindFramebuffer( GL_FRAMEBUFFER, 0 );
    glSrfCheck("Unable to unbind framebuffer");

    glDeleteFramebuffers( 1, &surfFBO );
    glSrfCheck("Unable to delete framebuffer");

    glDeleteTextures(1, &surfTexID);
    glSrfCheck("Unable to delete texture");

    return 1;
}

void srfBind()
{
    //glBlendFunc(GL_ONE, GL_ONE);
    glColor4f(1, 1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, surfTexID);
}

int winW, winH;
int srfInit()
{
    GLenum glerror = glGetError(); //reset gl error flag

    glGenTextures(1, &surfTexID);
    glSrfCheck("Unable to generate textures");

    glBindTexture(GL_TEXTURE_2D, surfTexID);
    glSrfCheck("Unable to bind texture");

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glSrfCheck("Unable to set tex parameter: mag filter");

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glSrfCheck("Unable to set tex parameter: min_filter");

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glSrfCheck("Unable to set tex parameter: wrap_s");

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glSrfCheck("Unable to set tex parameter: wrap_t");

    uint8_t* data = malloc(winW * winH * 4);
    memset(data, 0, winW * winH * 4);
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA, winW, winH, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glSrfCheck("Unable to set tex parameters");

    free(data);

    glGenFramebuffers(1, &surfFBO);
    glSrfCheck("Unable to generate FBO");

    glBindFramebuffer( GL_FRAMEBUFFER, surfFBO );
    glSrfCheck("Unable to bind FBO");

    glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, surfTexID, 0 );
    glSrfCheck("Unable to attach FBO");

    glBindFramebuffer( GL_FRAMEBUFFER, 0 );
    glSrfCheck("Unable to unbind FBO");

    return true;
}

int srfClear()
{
    GLenum glerror = glGetError(); //reset gl error flag

    uint8_t* data = malloc(winW * winH * 4);
    memset(data, 0, winW * winH * 4);
    glBindTexture(GL_TEXTURE_2D, surfTexID);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, winW, winH, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glSrfCheck("Unable to set tex parameters");

    free(data);

    return true;
}

void srfDrawTexture(tex_t* tex, int frame, color_t color, vec_t pos, double angle, double scaleFactor)
{
    glBindFramebuffer(GL_FRAMEBUFFER, surfFBO);
    glViewport(0, 0, winW, winH);

    pos.y = winH - pos.y;

    glBindTexture(GL_TEXTURE_2D, tex->textureIds[frame]);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glBlendFunc(GL_ONE, GL_ONE);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    //glBlendEquation(GL_MAX);

    glColor4d(color.r, color.g, color.b, color.a);

    const double hw = tex->width / 2.0;
    const double hh = tex->height / 2.0;

    const double acos = cos(angle) * scaleFactor;
    const double asin = sin(angle) * scaleFactor;

    vec_t p1, p2, p3, p4;

    createRotatedPoint(&p1, pos, acos, asin, hw, hh, vec(-tex->center.x + pos.x, tex->center.y + pos.y), -1, -1);
    createRotatedPoint(&p2, pos, acos, asin, hw, hh, vec(-tex->center.x + pos.x, tex->center.y + pos.y), -1, 1);
    createRotatedPoint(&p3, pos, acos, asin, hw, hh, vec(-tex->center.x + pos.x, tex->center.y + pos.y), 1, -1);
    createRotatedPoint(&p4, pos, acos, asin, hw, hh, vec(-tex->center.x + pos.x, tex->center.y + pos.y), 1, 1);

    glBegin(GL_QUAD_STRIP);
        glTexCoord2i(0, 1); glVertex2f(p1.x, p1.y);
        glTexCoord2i(0, 0); glVertex2f(p2.x, p2.y);
        glTexCoord2i(1, 1); glVertex2f(p3.x, p3.y);
        glTexCoord2i(1, 0); glVertex2f(p4.x, p4.y);
    glEnd();

    //glBlendEquation(GL_FUNC_ADD);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}