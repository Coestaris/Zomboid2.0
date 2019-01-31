//
// Created by maxim on 1/31/19.
//

#include "rlist.h"

#define MAX_TOKENS 200
char** tokens;
int tokenCount;

void rlist_init()
{
    tokens = malloc(sizeof(char*) * MAX_TOKENS);
    initCommands();
}


void proceedLine(char* token, int start, int end)
{
    size_t len = (size_t)end - start + 2;
    char* newToken = malloc(len);
    memcpy(newToken, token + start, len - 1);
    newToken[len - 1] = '\0';
    tokens[tokenCount++] = newToken;

    for(long i = strlen(newToken) - 1; i >= 0; i--) {
        if(newToken[i] == '\\') {
            memmove(&newToken[i], &newToken[i + 1], strlen(newToken) - i);
        }
    }
}

int getTokens(char *str)
{
    int startIndex = 0;
    int endIndex = 0;

    int i = 0;
    while(str[i] != '\0' && str[i] != '\n')
    {
        if((str[i - 1] == '\\' || str[i] != ' ') && str[i] != '\0' && str[i] != '\n')
        {
            startIndex = i;

            if(str[i] == '"')
            {
                startIndex++;
                i++;
                while(str[i] != '"') {
                    if(str[i] == '\0') return false;
                    i++;
                }

                endIndex = i - 1;
                proceedLine(str, startIndex, endIndex);
                i++;

            } else {
                while ((str[i - 1] == '\\' || str[i] != ' ') && str[i] != '\0' && str[i] != '\n') {
                    i++;
                }

                endIndex = i - 1;
                proceedLine(str, startIndex, endIndex);
            }
        }
        else
        {
            i++;
        }
    }
    return true;
}

void clearTokens()
{
    for(int i = 0; i < tokenCount; i++) {
        free(tokens[i]);
        tokens[i] = NULL;
    }
    tokenCount = 0;
}

int rlist_load(char* filename, int strict)
{
    FILE* f = fopen(filename, "r");
    if(!f) return false;


    fseek(f, 0, SEEK_END);

    size_t size = (size_t)ftell(f);
    fseek(f, 0, SEEK_SET);

    char* rawInput = malloc(sizeof(char) * size);
    fread(rawInput, 1, size, f);
    fclose(f);

    int commandsCount = 0;
    rlist_c** commands = rlist_getcommands(&commandsCount);
    int lineCounter = 0;

    char* line = strtok(rawInput, "\n");
    while(line)
    {
        if(!getTokens(line)) {
            printf("Rlist: Invalid syntax at line %i", lineCounter);
            if(strict) return false;
            else goto end;
        }

        if(tokenCount != 0 && tokens[0][0] != ';')
        {
            int found = false;
            //current line is not comment
            for(int i = 0; i < commandsCount; i++) {
                if(!strcmp(commands[i]->name, tokens[0])) {
                    //found command
                    found = true;

                    assert(commands[i]->runFunc);


                    if(commands[i]->argumentCount != ARGC_VARIADIC && tokenCount - 1 != commands[i]->argumentCount) {
                        printf("Rlist: Wrong argument count. Expected %i, but got %i, at line %i", commands[i]->argumentCount, tokenCount - 1, lineCounter);
                        if(strict) return false;
                        else goto end;
                    }

                    //skipping one token - command
                    rlist_cdata* data = malloc(sizeof(rlist_cdata));
                    data->args = &tokens[1];
                    data->command = commands[i];

                    commands[i]->runFunc(data);

                    free(data);

                }
            }

            if(!found) {
                printf("Rlist: Unknown command \"%s\" at line %i", tokens[0], lineCounter);
                if(strict) return false;
                else goto end;
            }
        }

        end:
        clearTokens();
        line = strtok(NULL, "\n");
        lineCounter++;
    }

    free(rawInput);
}
