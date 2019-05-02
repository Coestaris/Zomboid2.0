//
// Created by maxim on 1/23/19.
//

#ifndef ZOMBOID2_TEXMANAGER_H
#define ZOMBOID2_TEXMANAGER_H

#include "tex.h"

typedef struct _texNode{
    struct _texNode* next;
    tex_t* value;

} texmNode_t;

void texmFreeNode(texmNode_t *node);
texmNode_t* temCreateNode(tex_t *tex);
texmNode_t* texmRemoveNode(int uid, int free);
void texmPrintNode(texmNode_t *node);
void texmPrintNodes();
void texmRemoveNodes(int scope, int free);


void texmInit(void);
void texmPush(tex_t* tex);
void texmLoadID(int uid);
void texmLoadScope(int scope);
tex_t* texmGetID(int uid);
void texmUnloadID(int uid);
void texmUnloadScope(int scope);
void texmFreeID(int uid);
void texmFreeScope(int scope);


#endif //ZOMBOID2_TEXMANAGER_H
