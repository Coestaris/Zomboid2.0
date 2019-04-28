//
// Created by h0tw4t3r on 4/28/19.
//

#include "metadata.h"
#include <inttypes.h>

#define pack754_32(f) (pack754((f), 32, 8))
#define pack754_64(f) (pack754((f), 64, 11))
#define unpack754_32(i) (unpack754((i), 32, 8))
#define unpack754_64(i) (unpack754((i), 64, 11))

uint64_t pack754(long double f, unsigned bits, unsigned expbits) {
    long double fnorm;
    int shift;
    long long sign, exp, significand;
    unsigned significandbits = bits - expbits - 1; // -1 for sign bit

    if (f == 0.0) return 0; // get this special case out of the way

    // check sign and begin normalization
    if (f < 0) {
        sign = 1;
        fnorm = -f;
    }
    else {
        sign = 0;
        fnorm = f;
    }

    // get the normalized form of f and track the exponent
    shift = 0;
    while (fnorm >= 2.0) {
        fnorm /= 2.0;
        shift++;
    }
    while (fnorm < 1.0) {
        fnorm *= 2.0;
        shift--;
    }
    fnorm = fnorm - 1.0;

    // calculate the binary form (non-float) of the significand data
    significand = fnorm * ((1LL << significandbits) + 0.5f);

    // get the biased exponent
    exp = shift + ((1 << (expbits - 1)) - 1); // shift + bias

    // return the final answer
    return (sign << (bits - 1)) | (exp << (bits - expbits - 1)) | significand;
}

double unpack754(uint64_t i, unsigned bits, unsigned expbits) {
    double result;
    long long shift;
    unsigned bias;
    unsigned significandbits = bits - expbits - 1; // -1 for sign bit

    if (i == 0) return 0.0;

    // pull the significand
    result = (i & ((1LL << significandbits) - 1)); // mask
    result /= (1LL << significandbits); // convert back to float
    result += 1.0f; // add the one back on

    // deal with the exponent
    bias = (1 << (expbits - 1)) - 1;
    shift = ((i >> significandbits) & ((1LL << expbits) - 1)) - bias;
    while (shift > 0) {
        result *= 2.0;
        shift--;
    }
    while (shift < 0) {
        result /= 2.0;
        shift++;
    }

    // sign it
    result *= (i >> (bits - 1)) & 1 ? -1.0 : 1.0;

    return result;
}

void serialize(unsigned char *data, player_meta_t meta) {
    uint64_t d, offset = 0x00000000000000FF;
    int cursor = 0;

    d = pack754_64(meta.pos.x);
    for (short i = 0; cursor < 8; cursor++, i++) {
        data[cursor] = (unsigned char) ((d & offset) >> i * 8);
        offset <<= cursor * 8;
    }

    d = pack754_64(meta.pos.y);
    for (short i = 0; cursor < 16; cursor++, i++) {
        data[cursor] = (unsigned char) ((d & offset) >> i * 8);
        offset <<= cursor * 8;
    }

    d = pack754_64(meta.angle);
    for (short i = 0; cursor < 24; cursor++, i++) {
        data[cursor] = (unsigned char) ((d & offset) >> i * 8);
        offset <<= cursor * 8;
    }
}

void deserialize(player_meta_t *meta, unsigned char *data) {
    uint64_t d = 0;
    int cursor = 0;

    for(short i = 0; cursor < 8; cursor++, i++) {
        d |= data[cursor] << i * 8;
    }
    meta->pos.x = unpack754_64(d);

    for(short i = 0; cursor < 16; cursor++, i++) {
        d |= data[cursor] << i * 8;
    }
    meta->pos.x = unpack754_64(d);

    for(short i = 0; cursor < 24; cursor++, i++) {
        d |= data[cursor] << i * 8;
    }
    meta->angle = unpack754_64(d);
}
