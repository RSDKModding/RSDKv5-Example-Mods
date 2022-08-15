#ifndef MOD_CONFIG_H
#define MOD_CONFIG_H

#include "GameAPI/Game.h"
#include "Objects/All.h"

typedef struct {
    uint8 temp;
} ModConfig;

extern ModConfig config;

extern bool32 (*MathHelpers_PointInHitbox)(int32 thisX1, int32 thisY1, int32 otherX1, int32 otherY1, int32 direction, Hitbox *hitbox);
extern int32 extraWidth;

#endif // !MOD_CONFIG_H