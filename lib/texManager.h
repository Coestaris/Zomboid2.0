//
// Created by maxim on 1/23/19.
//

#ifndef ZOMBOID2_TEXMANAGER_H
#define ZOMBOID2_TEXMANAGER_H

#include "tex.h"

typedef struct _texNode{
    struct _texNode* next;
    tex2d* value;

} texNode;

void freeNode(texNode* node);
texNode* createNode(tex2d* tex);
texNode* removeNode(int uid, int free);
void printNode(texNode* node);
void printNodes();
void removeNodes(int scope, int free);


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
