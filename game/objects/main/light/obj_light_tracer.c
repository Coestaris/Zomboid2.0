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

#define WIN_W 800
#define WIN_H 600

_point edges[20][4] = {
        { { 0, 0 }, { WIN_W, 0 }, { WIN_W, WIN_H }, { 0, WIN_H } }
        //{ { 100, 100 }, { 200, 100 }, { 200, 200 }, { 100, 200 } },
};

void lightTracer_init(gameObject* this)
{
    evqSubscribeEvent(this, EVT_Update, lightTracer_event_update);
}

_point points[200];
int pointsCount;
int edgesCount = 1;

void _ray_to(double x1, double y1, double x2, double y2, double angle)
{
    double nearest = MAXDOUBLE;
    double nearestX = x1;
    double nearestY = y1;

    double dist = 0;
    double intX, intY;

    for(int i = 0; i < edgesCount; i++) {

        for(int j = 0; j < 4; j++) {
            int start = j;
            int end = (j + 1) % 4;

            if(getIntersection(x1, y1, x2, y2,
                       edges[i][start].x, edges[i][start].y, edges[i][end].x, edges[i][end].y,
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

    //dqnDrawLine(x1, y1, nearestX, nearestY, 1, 1, 1, 1);

    points[pointsCount].x = nearestX;
    points[pointsCount].y = nearestY;
    points[pointsCount]._angle = angle;

    pointsCount++;
}

void ray_to(double x1, double y1, double x2, double y2)
{
    double angle = atan2(y2 - y1, x2 - x1);
    _ray_to(x1, y1, x2, y2, angle);
}

void ray_twice_to(double x1, double y1, double x2, double y2, double delta)
{
    double angle = atan2(y2 - y1, x2 - x1);
    _ray_to(x1, y1, x1 + cos(angle + delta), y1 + sin(angle + delta), angle + delta);
    _ray_to(x1, y1, x1 + cos(angle - delta), y1 + sin(angle - delta), angle - delta);

}

int first = 1;
double px, py;

int compare(const void* a, const void* b)
{
    _point int_a = * ( (_point*) a );
    _point int_b = * ( (_point*) b );

    if ( int_a._angle == int_b._angle ) return 0;
    else if ( int_a._angle < int_b._angle ) return -1;
    else return 1;
}

void lightTracer_event_update(gameObject* this, void* data)
{
    lightTracer_data* ld = (lightTracer_data*)this->data;
    pointsCount = 0;

    if(first) {
        int objCount;
        gameObject **objects = scmGetObjects(&objCount);
        for (int i = 0; i < objCount; i++) {
            if (objects[i]->texID == TEXID_BOX) {

                gameObject *box = objects[i];
                double w = 32 * box->size;
                double h = 32 * box->size;

                edges[edgesCount][0].x = box->x - w / 2;
                edges[edgesCount][0].y = box->y - h / 2;
                edges[edgesCount][1].x = box->x + w / 2;
                edges[edgesCount][1].y = box->y - h / 2;
                edges[edgesCount][2].x = box->x + w / 2;
                edges[edgesCount][2].y = box->y + h / 2;
                edges[edgesCount][3].x = box->x - w / 2;
                edges[edgesCount][3].y = box->y + h / 2;

                edgesCount++;
            }
        }
        first = 0;
    }

    int mx, my;
    getMousePos(&mx, &my);

    //dqnDrawLine(ld->lightSource->x, ld->lightSource->y, mx, my, 1, 0, 0.4, 1);

    for(int i = 0; i < edgesCount; i++) {
        for(int j = 0; j < 4; j++) {
            int start = j;
            int end = (j + 1) % 4;
             //dqnDrawLine(edges[i][start].x, edges[i][start].y, edges[i][end].x, edges[i][end].y, 1, 0, 0.4, 1);
        }
    }

    for(int i = 0; i < edgesCount; i++) {
        for(int j = 0; j < 4; j++) {
            int start = j;
            int end = (j + 1) % 4;

            if(i == 0) {
                ray_to(
                        ld->lightSource->x,
                        ld->lightSource->y,
                        edges[i][start].x,
                        edges[i][start].y);
                continue;
            }

            ray_twice_to(
                    ld->lightSource->x,
                    ld->lightSource->y,
                    edges[i][start].x,
                    edges[i][start].y,
                    0.00001);
        }
    }

    //sortPoints(ld->lightSource->x, ld->lightSource->y);

    qsort(points, pointsCount, sizeof(_point), compare);
    /*dqnDrawTexPolygon(texmGetID(TEXID_SIMPLE_LIGHT),
            points, pointsCount, ld->lightSource->x, ld->lightSource->y, 0.8, 1, 1, 0.2, 5);*/
    dqnDrawPolygon(points, pointsCount, ld->lightSource->x, ld->lightSource->y, 0.8, 1, 1, 0.2);
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