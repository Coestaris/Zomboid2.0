//
// Created by maxim on 1/23/19.
//

#include "texManager.h"

texmNode_t* list;

void texmFreeNode(texmNode_t* node)
{
    if (node->value)
    {
        freeOGlTex(node->value);
        freeTex(node->value);
    }
    free(node);
}


texmNode_t* temCreateNode(tex_t* tex)
{
    texmNode_t* node = malloc(sizeof(texmNode_t));
    node->value = tex;
    node->next = NULL;

    return node;
}

texmNode_t* texmRemoveNode(int uid, int free)
{
    texmNode_t* prev = NULL;
    texmNode_t* node = list;
    while (1)
    {
        if (node->value && node->value->id == uid)
        {
            if (prev)
            {
                prev->next = node->next;
            }
            if (free) texmFreeNode(node);
            return node;
            //return node;
        }
        if (!node->next) break;

        prev = node;
        node = node->next;
    }

    return NULL;
}

int texCounter = 0;

void texmPrintNode(texmNode_t* node)
{
    if (node == NULL)
    {
        printf("[texm.c]: %2i. Texture[NULL]\n", ++texCounter);
    }
    else
    {
        if (node->value)
        {
            if (node->value->textureIds[0])
            {
                if (node->value->framesCount == 1)
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
                    for (int i = 0; i < node->value->framesCount; i++)
                    {
                        printf("%i%c", node->value->textureIds[i], (i == node->value->framesCount - 1) ? ']' : ',');
                    }
                    putchar('\n');
                }
            }
            else
            {
                if (node->value->framesCount == 1)
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
    texmNode_t* node = list;
    texCounter = 0;
    puts("[texm.c]: Here`s list of all registered texures: ");
    while (1)
    {
        texmPrintNode(node);
        if (node->next == NULL) break;
        node = node->next;
    }
}

void texmRemoveNodes(int scope, int free)
{
    texmNode_t* prev = NULL;
    texmNode_t* node = list;
    int removed = 0;

    while (1)
    {
        if (node->value && node->value->scope == scope)
        {
            if (prev) prev->next = node->next;
            removed = 1;
        }
        if (!node->next) break;

        if (!removed)
        {
            prev = node;
            node = node->next;
        }
        else
        {
            removed = 0;
            if (free)
            {
                texmNode_t* next = node->next;
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

void texmPush(tex_t* tex)
{
    tex_t* oldTex;
    if ((oldTex = texmGetID(tex->id)))
    {
        printf("[texm.c][ERROR]: Texture with ID %i already exists. New path: \"%s\", old path \"%s\"", tex->id,
               tex->fns[0], oldTex->fns[0]);
        exit(1);
    }

    texmNode_t* lastNode = list;
    while (lastNode->next) lastNode = lastNode->next;

    texmNode_t* node = temCreateNode(tex);
    lastNode->next = node;

    //texmPrintNode(node);
}

void texmLoadID(int uid)
{
    texmNode_t* node = list;
    while (1)
    {
        if (node->value && node->value->id == uid)
        {
            loadTex(node->value);
        }
        if (node->next == NULL) break;
        node = node->next;
    }
}

void texmLoadScope(int scope)
{
    texmNode_t* node = list;
    while (1)
    {
        if (node->value && node->value->scope == scope)
        {
            loadTex(node->value);
        }
        if (node->next == NULL) break;
        node = node->next;
    }
}

tex_t* texmGetID(int uid)
{
    texmNode_t* node = list;
    while (1)
    {
        if (node->value && node->value->id == uid)
        {
            return node->value;
        }
        if (node->next == NULL) break;
        node = node->next;
    }

    return NULL;
}

void texmUnloadID(int uid)
{
    texmNode_t* node = list;
    while (1)
    {
        if (node->value && node->value->id == uid)
        {
            freeOGlTex(node->value);
        }
        if (node->next == NULL) break;
        node = node->next;
    }
}

void texmUnloadScope(int scope)
{
    texmNode_t* node = list;
    while (1)
    {
        if (node->value && node->value->scope == scope)
        {
            freeOGlTex(node->value);
        }
        if (node->next == NULL) break;
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
