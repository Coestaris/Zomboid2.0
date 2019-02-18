//
// Created by maxim on 1/25/19.
//

#include "obj_box.h"

gameObject* createBox(int x, int y)
{
    gameObject* go = object();
    go->drawable = true;
    go->size = 1.5;
    go->pos = vec(x, y);
    go->texID = TEXID_BOX;

    const double w = 32;
    const double h = 32;

    ltracer_pushEdge(
            vec_add(go->pos, vec_mult(vec(-w, -h), go->size / 2.0 )),
            vec_add(go->pos, vec_mult(vec( w, -h), go->size / 2.0 )),
            vec_add(go->pos, vec_mult(vec(-w,  h), go->size / 2.0 )),
            vec_add(go->pos, vec_mult(vec( w,  h), go->size / 2.0 )));

    return go;
}