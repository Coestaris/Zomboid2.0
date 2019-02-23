//
// Created by maxim on 1/23/19.
//

#ifndef ZOMBOID2_TEXMANAGER_H
#define ZOMBOID2_TEXMANAGER_H

#include "tex.h"

typedef struct _texNode{
    struct _texNode* next;
    tex2d* value;

} texmNode;

void texmFreeNode(texmNode *node);
texmNode* temCreateNode(tex2d *tex);
texmNode* texmRemoveNode(int uid, int free);
void texmPrintNode(texmNode *node);
void texmPrintNodes();
void texmRemoveNodes(int scope, int free);


void texmInit(void);
void texmPush(tex2d* tex);
void texmLoadID(int uid);
void texmLoadScope(int scope);
tex2d* texmGetID(int uid);
void texmUnloadID(int uid);
void texmUnloadScope(int scope);
void texmFreeID(int uid);
void texmFreeScope(int scope);


#endif //ZOMBOID2_TEXMANAGER_H
