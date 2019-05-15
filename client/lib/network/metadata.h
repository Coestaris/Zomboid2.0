//
// Created by h0tw4t3r on 4/26/19.
//

#ifndef ZOMBOID2_METADATA_H
#define ZOMBOID2_METADATA_H

#include "../structs.h"
#include <inttypes.h>

#define METADATA_LENGTH 24

typedef struct  {
    vec_t pos;
    double angle;
} player_meta_t;

void serialize(uint8_t *data, player_meta_t meta);
void deserialize(player_meta_t *meta, uint8_t *data);

#endif //ZOMBOID2_METADATA_H
