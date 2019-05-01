//
// Created by maxim on 1/23/19.
//

#include "texManager.h"

texmNode* list;

void texmFreeNode(texmNode *node)
{
    if(node->value)
    {
        freeOGlTex(node->value);
        freeTex(node->value);
    }
    free(node);
}


texmNode* temCreateNode(tex2d *tex)
{
    texmNode* node = malloc(sizeof(texmNode));
    node->value = tex;
    node->next = NULL;

    return node;
}

texmNode* texmRemoveNode(int uid, int free)
{
    texmNode* prev = NULL;
    texmNode* node = list;
    while(1)
    {
        if(node->value && node->value->id == uid)
        {
            if(prev)
            {
                prev->next = node->next;
            }
            if(free) texmFreeNode(node);
            return node;
            //return node;
        }
        if(!node->next) break;

        prev = node;
        node = node->next;
    }

    return NULL;
}

int texCounter = 0;
void texmPrintNode(texmNode *node)
{
    if(node == NULL)
    {
        printf("[texm.c]: %2i. Texture[NULL]\n", ++texCounter);
    }
    else
    {
        if (node->value)
        {
            if(node->value->textureIds[0])
            {
                if(node->value->framesCount == 1)
                {
                    printf("[texm.c]: %2i. Texture[UID: %i, Scope %i, FN: \"%s\", Loaded: true, W: %i, H: %i, OGLId: %i]\n",
                           ++texCounter,
                           node->value->id, node->value->scope,
                           node->value->fns[0], node->value->width, node->value->height, node->value->textureIds[0]);
                }
                else
                {
                    printf("[texm.c]: %2i. Animation[UID: %i, Scope %i, Loaded: true, W: %i, H: %i, OGLIds: [",
                            ++texCounter,
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
                    printf("[texm.c]: %2i. Texture[UID: %i, FN: \"%s\", Scope %i, Loaded: false]\n",
                            ++texCounter,
                            node->value->id, node->value->fns[0], node->value->scope);
                }
                else
                {
                    printf("[texm.c]: %2i. Animation[UID: %i, Scope %i, Loaded: false]\n",
                            ++texCounter,
                            node->value->id, node->value->scope);
                }
            }
        }
        else
        {
            printf("[texm.c]: %2i. Texture[NULL]\n", ++texCounter);
        }
    }
}

void texmPrintNodes()
{
    texmNode* node = list;
    texCounter = 0;
    puts("[texm.c]: Here`s list of all registered texures: ");
    while(1)
    {
        texmPrintNode(node);
        if(node->next == NULL) break;
        node = node->next;
    }
}

void texmRemoveNodes(int scope, int free)
{
    texmNode* prev = NULL;
    texmNode* node = list;
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
                texmNode *next = node->next;
                texmFreeNode(node);

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
    list = temCreateNode(NULL);
}

void texmPush(tex2d* tex)
{
    texmNode* lastNode = list;
    while(lastNode->next) lastNode = lastNode->next;

    texmNode* node = temCreateNode(tex);
    lastNode->next = node;

    //texmPrintNode(node);
}

void texmLoadID(int uid)
{
    texmNode* node = list;
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
    texmNode* node = list;
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
    texmNode* node = list;
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
    texmNode* node = list;
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
    texmNode* node = list;
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
    texmRemoveNode(uid, 1);
}

void texmFreeScope(int scope)
{
    texmRemoveNodes(scope, 1);
}
