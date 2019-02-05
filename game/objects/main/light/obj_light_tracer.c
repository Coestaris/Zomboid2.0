//
// Created by maxim on 2/5/19.
//

#include <values.h>
#include "obj_light_tracer.h"

int getIntersection(double rayX1, double rayY1, double rayX2, double rayY2,
                     double segX1, double segY1, double segX2, double segY2,
                     double* rx, double* ry, double* dist)
{
    double r_px = rayX1;
    double r_py = rayY1;
    double r_dx = rayX2 - rayX1;
    double r_dy = rayY2 - rayY1;

    double s_px = segX1;
    double s_py = segY1;
    double s_dx = segX2 - segX1;
    double s_dy = segY2 - segY1;

    double r_mag = sqrt(r_dx*r_dx+r_dy*r_dy);
    double s_mag = sqrt(s_dx*s_dx+s_dy*s_dy);

    if(r_dx/r_mag==s_dx/s_mag && r_dy/r_mag==s_dy/s_mag){
        return 0;
    }

    double T2 = (r_dx*(s_py-r_py) + r_dy*(r_px-s_px))/(s_dx*r_dy - s_dy*r_dx);
    double T1 = (s_px+s_dx*T2-r_px)/r_dx;

    if(T1<0) return 0;
    if(T2<0 || T2>1) return 0;
    // Return the POINT OF INTERSECTION

    *rx = r_px+r_dx*T1;
    *ry = r_py+r_dy*T1;
    *dist = T1;

    return 1;
/*    return {
            x: r_px+r_dx*T1,
            y: r_py+r_dy*T1,
            param: T1
    };*/
}

#define WIN_W 790
#define WIN_H 590

double edges[4][4][2] = {
        { { 10, 10 }, { WIN_W, 10 }, { WIN_W, WIN_H }, { 10, WIN_H } }
        //{ { 100, 100 }, { 200, 100 }, { 200, 200 }, { 100, 200 } },
};

void lightTracer_init(gameObject* this)
{
    evqSubscribeEvent(this, EVT_Update, lightTracer_event_update);
}

double points[100];
int pointsCount;

void ray_to(double x1, double y1, double x2, double y2)
{
    double nearest = MAXDOUBLE;
    double nearestX = x1;
    double nearestY = y1;

    double dist = 0;
    double intX, intY;

    for(int i = 0; i < 4; i++) {

        for(int j = 0; j < 4; j++) {
            int start = j;
            int end = (j + 1) % 4;

            if(getIntersection(x1, y1, x2, y2,
                       edges[i][start][0], edges[i][start][1], edges[i][end][0], edges[i][end][1],
                       &intX, &intY, &dist))
            {
                if(dist < nearest) {
                    nearest = dist;
                    nearestX = intX;
                    nearestY = intY;
                }
            }
        }
    }

    dqnDrawLine(x1, y1, nearestX, nearestY, 1, 1, 1, 1);

    points[pointsCount] = nearestX;
    points[pointsCount + 1] = nearestY;
    pointsCount+=2;
}

void ray_twice_to(double x1, double y1, double x2, double y2, double delta)
{
    double angle = atan2(y2 - y1, x2 - x1);

    ray_to(x1, y1, x1 + cos(angle + delta), y1 + sin(angle + delta));
    ray_to(x1, y1, x1 + cos(angle - delta), y1 + sin(angle - delta));
}

int first = 1;

void lightTracer_event_update(gameObject* this, void* data)
{
    lightTracer_data* ld = (lightTracer_data*)this->data;
    pointsCount = 0;

    if(first) {
        int objCount;
        gameObject **objects = scmGetObjects(&objCount);
        int counter = 1;
        for (int i = 0; i < objCount; i++) {
            if (objects[i]->texID == TEXID_BOX) {

                gameObject *box = objects[i];
                double w = 32 * box->size;
                double h = 32 * box->size;

                edges[counter][0][0] = box->x - w / 2;
                edges[counter][0][1] = box->y - h / 2;
                edges[counter][1][0] = box->x + w / 2;
                edges[counter][1][1] = box->y - h / 2;
                edges[counter][2][0] = box->x + w / 2;
                edges[counter][2][1] = box->y + h / 2;
                edges[counter][3][0] = box->x - w / 2;
                edges[counter][3][1] = box->y + h / 2;

                counter++;
            }
        }
        first = 0;
    }

    int mx, my;
    getMousePos(&mx, &my);

    //dqnDrawLine(ld->lightSource->x, ld->lightSource->y, mx, my, 1, 0, 0.4, 1);

    for(int i = 0; i < 4; i++) {

        for(int j = 0; j < 4; j++) {
            int start = j;
            int end = (j + 1) % 4;
            dqnDrawLine(edges[i][start][0], edges[i][start][1], edges[i][end][0], edges[i][end][1], 1, 0, 0.4, 1);

            ray_twice_to(
                    ld->lightSource->x,
                    ld->lightSource->y,
                    edges[i][start][0],
                    edges[i][start][1],
                    0.001);
        }
    }

    dqnDrawPolygon(points, pointsCount, 1, 1, 1, 0.4);
}

gameObject* createLightTracer(gameObject* light_source)
{
    gameObject* this = object();
    this->onInit = lightTracer_init;

    this->data = malloc(sizeof(lightTracer_data));
    lightTracer_data* ld = (lightTracer_data*)this->data;

    ld->lightSource = light_source;

    return this;
}