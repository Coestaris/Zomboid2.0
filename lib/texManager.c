//
// Created by maxim on 1/23/19.
//

#include "texManager.h"

texNode* list;

void freeNode(texNode* node)
{
    if(node->value)
    {
        freeOGlTex(node->value);
        freeTex(node->value);
    }
    free(node);
}


texNode* createNode(tex2d* tex)
{
    texNode* node = malloc(sizeof(texNode));
    node->value = tex;
    node->next = NULL;

    return node;
}

texNode* removeNode(int uid, int free)
{
    texNode* prev = NULL;
    texNode* node = list;
    while(1)
    {
        if(node->value && node->value->id == uid)
        {
            if(prev)
            {
                prev->next = node->next;
            }
            if(free) freeNode(node);
            return node;
            //return node;
        }
        if(!node->next) break;

        prev = node;
        node = node->next;
    }

    return NULL;
}

void printNode(texNode* node)
{
    if(node == NULL)
    {
        puts("Texture[NULL]");
    }
    else
    {
        if (node->value)
        {
            if(node->value->textureIds[0])
            {
                if(node->value->framesCount == 1)
                {
                    printf("Texture[UID: %i, Scope %i, FN: \"%s\", Loaded: true, W: %i, H: %i, OGLId: %i]\n",
                           node->value->id, node->value->scope,
                           node->value->fns[0], node->value->width, node->value->height, node->value->textureIds[0]);
                }
                else
                {
                    printf("Animation[UID: %i, Scope %i, Loaded: true, W: %i, H: %i, OGLIds: [",
                            node->value->id, node->value->scope, node->value->width, node->value->height);
                    for(int i = 0; i < node->value->framesCount; i++) {
                        printf("%i%c", node->value->textureIds[i], (i == node->value->framesCount - 1) ? ']' : ',');
                    }
                    putchar('\n');
                }
            }
            else
            {
                if(node->value->framesCount == 1)
                {
                    printf("Texture[UID: %i, FN: \"%s\", Scope %i, Loaded: false]\n", node->value->id, node->value->fns[0], node->value->scope);
                }
                else
                {
                    printf("Animation[UID: %i, Scope %i, Loaded: false]\n", node->value->id, node->value->scope);
                }
            }
        }
        else
        {
            puts("Texture[empty]");
        }
    }
}

void printNodes()
{
    texNode* node = list;
    while(1)
    {
        printNode(node);
        if(node->next == NULL) break;
        node = node->next;
    }
}

void removeNodes(int scope, int free)
{
    texNode* prev = NULL;
    texNode* node = list;
    int removed = 0;

    while(1)
    {
        if(node->value && node->value->scope == scope)
        {
            if(prev) prev->next = node->next;
            removed = 1;
        }
        if(!node->next) break;

        if(!removed)
        {
            prev = node;
            node = node->next;
        }
        else
        {
            removed = 0;
            if (free)
            {
                texNode *next = node->next;
                freeNode(node);

                node = next;
            }
            else
            {
                node = node->next;
            }
        }
    }
}

void texmInit(void)
{
    list = createNode(NULL);
}

void texmPush(tex2d* tex)
{
    texNode* lastNode = list;
    while(lastNode->next) lastNode = lastNode->next;

    texNode* node = createNode(tex);
    lastNode->next = node;

    printNode(node);
}

void texmLoadID(int uid)
{
    texNode* node = list;
    while(1)
    {
        if(node->value && node->value->id == uid)
        {
            loadTex(node->value);
        }
        if(node->next == NULL) break;
        node = node->next;
    }
}

void texmLoadScope(int scope)
{
    texNode* node = list;
    while(1)
    {
        if(node->value && node->value->scope == scope)
        {
            loadTex(node->value);
        }
        if(node->next == NULL) break;
        node = node->next;
    }
}

tex2d* texmGetID(int uid)
{
    texNode* node = list;
    while(1)
    {
        if(node->value && node->value->id == uid)
        {
            return node->value;
        }
        if(node->next == NULL) break;
        node = node->next;
    }

    return NULL;
}

void texmUnloadID(int uid)
{
    texNode* node = list;
    while(1)
    {
        if(node->value && node->value->id == uid)
        {
            freeOGlTex(node->value);
        }
        if(node->next == NULL) break;
        node = node->next;
    }
}

void texmUnloadScope(int scope)
{
    texNode* node = list;
    while(1)
    {
        if(node->value && node->value->scope == scope)
        {
            freeOGlTex(node->value);
        }
        if(node->next == NULL) break;
        node = node->next;
    }
}

void texmFreeID(int uid)
{
    removeNode(uid, 1);
}

void texmFreeScope(int scope)
{
    removeNodes(scope, 1);
}
