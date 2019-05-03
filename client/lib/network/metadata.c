//
// Created by h0tw4t3r on 4/28/19.
//


// WARNING: DON'T USE IT!!!!!!! BUGGGGGGGGGGGGGGGGS!!!!!

#include "metadata.h"
#include "../../../lib/zdtp.h"
#include <inttypes.h>

void serialize(uint8_t *data, player_meta_t meta) {
    union {
        uint64_t d;
        double_t lf;
    } holder;
    int64_t offset = 0x00000000000000FF;
    int8_t cursor = 0;

    holder.lf = meta.pos.x;
    for (int8_t i = 0; cursor < 8; cursor++, i++) {
        data[cursor] = (uint8_t) ((holder.d & offset) >> i * 8);
        offset <<= cursor * 8;
    }

    holder.lf = meta.pos.y;
    for (int8_t i = 0; cursor < 16; cursor++, i++) {
        data[cursor] = (uint8_t) ((holder.d & offset) >> i * 8);
        offset <<= cursor * 8;
    }

    holder.lf = meta.angle;
    for (int8_t i = 0; cursor < 24; cursor++, i++) {
        data[cursor] = (uint8_t) ((holder.d & offset) >> i * 8);
        offset <<= cursor * 8;
    }
}

void deserialize(player_meta_t *meta, uint8_t *data) {
    union {
        uint64_t d;
        double_t lf;
    } holder;
    int8_t cursor = 0;

    holder.d = 0;
    for (int8_t i = 0; cursor < 8; cursor++, i++) {
        holder.d |= data[cursor] << i * 8;
    }
    meta->pos.x = holder.lf;

    holder.d = 0;
    for (int8_t i = 0; cursor < 16; cursor++, i++) {
        holder.d |= data[cursor] << i * 8;
    }
    meta->pos.x = holder.lf;

    holder.d = 0;
    for (int8_t i = 0; cursor < 24; cursor++, i++) {
        holder.d |= data[cursor] << i * 8;
    }
    meta->angle = holder.lf;
}

