//
// Created by h0tw4t3r on 4/26/19.
//

#ifndef ZOMBOID2_METADATA_H
#define ZOMBOID2_METADATA_H

#include "../structs.h"

#define METADATA_LENGTH 24

typedef struct  {
    vec_t pos;
    double angle;
} player_meta_t;

void serialize(unsigned char *data, player_meta_t meta);
void deserialize(player_meta_t *meta, unsigned char *data);

#endif //ZOMBOID2_METADATA_H
