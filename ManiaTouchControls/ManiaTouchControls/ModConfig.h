#ifndef MOD_CONFIG_H
#define MOD_CONFIG_H

#include "../GameAPI/C/GameAPI/Game.h"

typedef struct {
    float vDPadSize;
    float vDPadOpacity;
    Vector2 moveDPadPos;
    Vector2 jumpDPadPos;
} ModConfig;

extern ModConfig config;

#endif // !MOD_CONFIG_H