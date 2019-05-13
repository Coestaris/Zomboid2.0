//
// Created by maxim on 5/13/19.
//

#include "score.h"

#define MAX_LEVELS 13
#define MAX_ENEMIES 6
#define COMPLETED 0.9

int levels[MAX_LEVELS * MAX_ENEMIES] = {
    //  tic     body    zombie  slug    ghost   slicer
        10,     0,      0,      0,      0,      0,
        10,     5,      0,      0,      0,      0,
        10,     5,      5,      0,      0,      0,
        10,     5,     10,      0,      0,      0,
        10,     5,     20,      5,      0,      0,
        10,     0,     20,     10,      0,      0,
        10,     0,     30,     10,      5,      0,
        15,     0,     30,     10,     10,      0,
        15,     0,     30,     10,     15,      0,
        15,     0,     30,     10,     20,      0,
        15,     0,     30,     10,     20,      5,
        15,     0,     30,     10,     20,     10,
        15,     5,     30,     30,     30,     20,
};

int mobCount(int level)
{
    int sum = 0;
    for(int i = 0; i < MAX_ENEMIES; i++) {
        sum += levels[level * MAX_ENEMIES + i];
    }
    return sum;
}

void recieveScore(int level, int id)
{

}