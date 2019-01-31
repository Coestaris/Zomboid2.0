//
// Created by maxim on 1/31/19.
//

#include <ctype.h>
#include "rlist.h"

#define MAX_TOKENS 200
char** lines;
char** tokens;
int linesCount;
int tokenCount;

void rlist_init()
{
    tokens = malloc(sizeof(char*) * MAX_TOKENS);
    lines = malloc(sizeof(char*) * MAX_TOKENS);

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


void trim(char * s) {
    char * p = s;
    int l = strlen(p);

    while(isspace(p[l - 1])) p[--l] = 0;
    while(* p && isspace(* p)) ++p, --l;

    memmove(s, p, l + 1);
}

void proceed_line(char* input, int start, int end)
{
    size_t len = (size_t)end - start + 2;
    char* line = malloc(len);
    memcpy(line, input + start, len - 1);
    line[len - 1] = '\0';
    lines[linesCount++] = line;
    trim(line);
}

void get_lines(char* str)
{
    int a = 0;
    int startIndex = 0;
    int endIndex = 0;

    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == '\n' && str[i - 1] != '\n') {
            endIndex = i;
            proceed_line(str, startIndex, endIndex);
            startIndex = endIndex + 1;
        }
    }
    if(str[strlen(str)] != '\n') {
        proceed_line(str, startIndex, strlen(str) - 1);
    }
}

int rlist_load(char* filename, int strict)
{
    clearTokens();

    FILE* f = fopen(filename, "r");
    if(!f) return false;


    fseek(f, 0, SEEK_END);

    size_t size = (size_t)ftell(f);
    fseek(f, 0, SEEK_SET);

    char* rawInput = malloc(size + 1);
    memset(rawInput, 0, size + 1);
    fread(rawInput, size, size, f);

    fclose(f);

    int commandsCount = 0;
    rlist_c** commands = rlist_getcommands(&commandsCount);
    int lineCounter = 0;

    get_lines(rawInput);

    char** myLines = malloc(sizeof(char*) * linesCount);
    int myLinesCount = linesCount;

    memcpy(myLines, lines, sizeof(char*) * linesCount);
    linesCount = 0;

    for(int i = 0; i < myLinesCount; i++)
    {
        char* line = myLines[i];
        //puts(line);

        if(!getTokens(line)) {
            printf("Rlist error: Invalid syntax at line %i in \"%s\"\n", lineCounter, filename);
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
                        printf("Rlist error: Wrong argument count. Expected %i, but got %i, at line %i in \"%s\"\n", commands[i]->argumentCount, tokenCount - 1, lineCounter, filename);
                        if(strict) return false;
                        else goto end;
                    }

                    //skipping one token - command
                    rlist_cdata* data = malloc(sizeof(rlist_cdata));
                    data->args = &tokens[1];
                    data->filename = filename;
                    data->lineIndex = lineCounter;
                    data->command = commands[i];
                    data->strict = strict;
                    data->fnToAddLines = NULL;

                    if(!commands[i]->runFunc(data)) {
                        free(data);
                        return false;
                    }

                    if(data->fnToAddLines) {

                        if(!rlist_load(data->fnToAddLines, strict)) {
                            if(strict) goto end;
                            else return false;
                        }

                        clearTokens();

                        free(data->fnToAddLines);
                    }

                    free(data);
                }
            }

            if(!found) {
                printf("Rlist error: Unknown command \"%s\" at line %i in \"%s\"\n", tokens[0], lineCounter, filename);
                if(strict) return false;
                else goto end;
            }
        }

        end:
        clearTokens();
        lineCounter++;
        free(line);
    }

    free(myLines);
    free(rawInput);
}
