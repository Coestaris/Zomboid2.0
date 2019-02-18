//
// Created by maxim on 2/17/19.
//

#include "ltracer_math.h"

int _edgesCount = 0;
ltracer_edge** _edges;

int ltracer_getIntersection(double rayX1, double rayY1, double rayX2, double rayY2, vec_t seg1, vec_t seg2,
        double* rx, double* ry, double* dist)
{
    double r_px = rayX1;
    double r_py = rayY1;
    double r_dx = rayX2 - rayX1;
    double r_dy = rayY2 - rayY1;

    double s_px = seg1.x;
    double s_py = seg1.y;
    double s_dx = seg2.y - seg1.x;
    double s_dy = seg2.y - seg1.y;

    double r_mag = sqrt(r_dx * r_dx + r_dy * r_dy);
    double s_mag = sqrt(s_dx *s_dx + s_dy * s_dy);

    if(r_dx / r_mag == s_dx / s_mag && r_dy / r_mag==s_dy / s_mag)
    {
        return false;
    }

    double T2 = (r_dx * (s_py - r_py) + r_dy * (r_px - s_px)) / (s_dx * r_dy - s_dy * r_dx);
    double T1 = (s_px + s_dx * T2 - r_px) / r_dx;

    if(T1 < 0) return false;
    if(T2 < 0 || T2 > 1) return false;

    *rx = r_px + r_dx * T1;
    *ry = r_py + r_dy * T1;
    *dist = T1;

    return true;
}

#ifdef LTRACER_DRAW_EDGES
#define trace(p1, p2) \
    if(ltracer_getIntersection(x1, y1, x2, y2, p1, p2, &intX, &intY, &dist)) { \
        if(dist < nearest) {\
            nearest = dist;\
            nearestX = intX;\
            nearestY = intY;\
        }\
        dqnDrawLine(vec(x1, y1), vec(intX, intY), color(1, 1, 1, 1));\
    }
#else
#define trace(p1, p2) \
    if(ltracer_getIntersection(x1, y1, x2, y2, p1, p2, &intX, &intY, &dist)) { \
        if(dist < nearest) {\
            nearest = dist;\
            nearestX = intX;\
            nearestY = intY;\
        }\
    }
#endif

void ltracer_ray_to(ltracer_data* ld, double x1, double y1, double x2, double y2, double angle)
{
    double nearest = MAXDOUBLE;
    double nearestX = x1;
    double nearestY = y1;

    double dist = 0;
    double intX, intY;


    for(int i = 0; i < _edgesCount; i++) {

        trace(_edges[i]->a, _edges[i]->b);
        trace(_edges[i]->b, _edges[i]->c);
        trace(_edges[i]->c, _edges[i]->d);
        trace(_edges[i]->d, _edges[i]->a);

    }

#ifdef LTRACER_DRAW_RAYS
    dqnDrawLine(vec(x1, y1), vec(nearestX, nearestY), ld->color);
#endif

    ld->points[ld->pointsCount].point = vec(nearestX, nearestY);
    ld->points[ld->pointsCount].angle = angle;
    ld->points[ld->pointsCount].distance = dist;

    ld->pointsCount++;
}


void ltracer_ray_single_to(ltracer_data* ld, vec_t p1, vec_t p2, double mDist)
{
    if(distance(p1, p2) > mDist) return;

    double angle = atan2(p2.y - p1.y, p2.x - p1.x);
    ltracer_ray_to(ld, p1.x, p1.y, p2.x, p2.y, angle);
}

void ltracer_ray_twice_to(ltracer_data* ld, vec_t p1, vec_t p2, double mDist, double delta)
{
    if(distance(p1, p2) > mDist) return;

    double angle = atan2(p2.y - p1.y, p2.x - p1.x);

    if(ld->angleRange != 0) {
        //TODO!
    }

    ltracer_ray_to(ld, p1.x, p1.y, p1.x + cos(angle + delta), p1.y + sin(angle + delta), angle + delta);
    ltracer_ray_to(ld, p1.x, p1.y, p1.x + cos(angle - delta), p1.y + sin(angle - delta), angle - delta);

}

int ltracer_compare(const void* a, const void* b)
{
    relPoint_t int_a = * ( (relPoint_t*) a );
    relPoint_t int_b = * ( (relPoint_t*) b );

    if ( int_a.angle == int_b.angle ) return 0;
    else if ( int_a.angle < int_b.angle ) return -1;
    else return 1;
}

void ltracer_sortPoints(ltracer_data* ld)
{
    qsort(ld->points, (size_t)ld->pointsCount, sizeof(relPoint_t), ltracer_compare);
}

void ltracer_updateEdges(ltracer_edge** edges, int count)
{
    _edges = edges;
    _edgesCount = count;
}