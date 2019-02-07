//
// Created by maxim on 2/5/19.
//

#include "obj_light_tracer.h"

relPoint_t edges[20][4];
int edgesCount = 1;

void updateEdges(int texID)
{
    edgesCount = 1;
    int objCount;
    gameObject **objects = scmGetObjects(&objCount);
    for (int i = 0; i < objCount; i++) {
        if (objects[i]->texID == texID) {

            gameObject *box = objects[i];
            double w = 32 * box->size;
            double h = 32 * box->size;

            edges[edgesCount][0].point = vec(
                    box->pos.x - w / 2,
                    box->pos.y - h / 2);

            edges[edgesCount][1].point = vec(
                    box->pos.x + w / 2,
                    box->pos.y - h / 2);

            edges[edgesCount][2].point = vec(
                    box->pos.x + w / 2,
                    box->pos.y + h / 2);

            edges[edgesCount][3].point = vec(
                    box->pos.x - w / 2,
                    box->pos.y + h / 2);

            edgesCount++;
        }
    }
}

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
        return false;
    }

    double T2 = (r_dx*(s_py-r_py) + r_dy*(r_px-s_px))/(s_dx*r_dy - s_dy*r_dx);
    double T1 = (s_px+s_dx*T2-r_px)/r_dx;

    if(T1<0) return false;
    if(T2<0 || T2>1) return false;

    *rx = r_px+r_dx*T1;
    *ry = r_py+r_dy*T1;
    *dist = T1;

    return true;
}

void lightTracer_init(gameObject* this)
{
    evqSubscribeEvent(this, EVT_Update, lightTracer_event_update);
}

void _ray_to(lightTracer_data* ld, double x1, double y1, double x2, double y2, double angle)
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
                       edges[i][start].point.x, edges[i][start].point.y,
                       edges[i][end].point.x, edges[i][end].point.y,
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

    dqnDrawLine(vec(x1, y1), vec(nearestX, nearestY), ld->color);
    ld->points[ld->pointsCount].point = vec(nearestX, nearestY);
    ld->points[ld->pointsCount].angle = angle;
    ld->points[ld->pointsCount].distance = dist;

    ld->pointsCount++;
}

void ray_to(lightTracer_data* ld, double x1, double y1, double x2, double y2, double mDist)
{
    if(distance(vec(x1, y1), vec(x2, y2)) > mDist) return;

    double angle = atan2(y2 - y1, x2 - x1);
    _ray_to(ld, x1, y1, x2, y2, angle);
}

void ray_twice_to(lightTracer_data* ld, double x1, double y1, double x2, double y2, double mDist, double delta)
{
    if(distance(vec(x1, y1), vec(x2, y2)) > mDist) return;

    double angle = atan2(y2 - y1, x2 - x1);
    _ray_to(ld, x1, y1, x1 + cos(angle + delta), y1 + sin(angle + delta), angle + delta);
    _ray_to(ld, x1, y1, x1 + cos(angle - delta), y1 + sin(angle - delta), angle - delta);

}

int compare(const void* a, const void* b)
{
    relPoint_t int_a = * ( (relPoint_t*) a );
    relPoint_t int_b = * ( (relPoint_t*) b );

    if ( int_a.angle == int_b.angle ) return 0;
    else if ( int_a.angle < int_b.angle ) return -1;
    else return 1;
}

void lightTracer_event_update(gameObject* this, void* data)
{
    lightTracer_data* ld = (lightTracer_data*)this->data;
    ld->pointsCount = 0;

    if(ld->type == LT_AREA) {

        edges[0][0].point = vec(this->pos.x - ld->range / 2, this->pos.y - ld->range / 2);
        edges[0][1].point = vec(this->pos.x + ld->range / 2, this->pos.y - ld->range / 2);
        edges[0][2].point = vec(this->pos.x + ld->range / 2, this->pos.y + ld->range / 2);
        edges[0][3].point = vec(this->pos.x - ld->range / 2, this->pos.y + ld->range / 2);

        for (int i = 0; i < edgesCount; i++) {
            for (int j = 0; j < 4; j++) {
                int start = j;
                int end = (j + 1) % 4;
/*

                dqnDrawLine(
                        edges[i][start].point,
                        edges[i][end].point,
                        ld->color);
*/

                if (i == 0) {
                    ray_to(
                            ld,
                            this->pos.x,
                            this->pos.y,
                            edges[i][start].point.x,
                            edges[i][start].point.y,
                            ld->range / 2 * M_SQRT2 + 0.001);
                    continue;
                }

                ray_twice_to(
                        ld,
                        this->pos.x,
                        this->pos.y,
                        edges[i][start].point.x,
                        edges[i][start].point.y,
                        ld->range / 2 * M_SQRT2 + 0.001,
                        0.00001);
            }
        }
    }

    qsort(ld->points, (size_t)ld->pointsCount, sizeof(relPoint_t), compare);

    if(ld->textured) {
        dqnDrawTexPolygon(ld->tex, ld->frame, ld->points, ld->pointsCount, this->pos, ld->color, ld->range);
    } else {
        dqnDrawPolygon(ld->points, ld->pointsCount, this->pos, ld->color);
    }
}

gameObject* createAreaLT(vec_t pos, double range, color_t color)
{
    gameObject* this = object();
    this->onInit = lightTracer_init;
    this->pos = pos;

    this->data = malloc(sizeof(lightTracer_data));
    lightTracer_data* ld = (lightTracer_data*)this->data;

    ld->points = malloc(sizeof(relPoint_t) * 100);
    ld->pointsCount = 0;

    ld->textured = false;
    ld->type = LT_AREA;
    ld->range = range;
    ld->color = color;

    return this;
}

gameObject* createTexturedAreaLT(vec_t pos, double range, color_t color, tex2d* tex, int frame)
{
    gameObject* this = object();
    this->onInit = lightTracer_init;
    this->pos = pos;

    this->data = malloc(sizeof(lightTracer_data));
    lightTracer_data* ld = (lightTracer_data*)this->data;

    ld->points = malloc(sizeof(relPoint_t) * 100);
    ld->pointsCount = 0;

    ld->textured = true;
    ld->tex = tex;
    ld->type = LT_AREA;
    ld->frame = frame;
    ld->range = range;
    ld->color = color;

    return this;
}