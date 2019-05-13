//
// Created by maxim on 1/31/19.
//

#ifndef ZOMBOID2_RLIST_H
#define ZOMBOID2_RLIST_H

#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>

#include "rlist_c.h"
#include "rlist_commands.h"

#include "../helpers.h"

void rlistInit(void);
int rlistLoad(char* filename, int strict);

#endif //ZOMBOID2_RLIST_H
