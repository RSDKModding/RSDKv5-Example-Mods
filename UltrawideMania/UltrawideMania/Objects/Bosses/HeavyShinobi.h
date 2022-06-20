#ifndef HEAVYSHINOBI_H
#define HEAVYSHINOBI_H

struct ObjectHeavyShinobi {
    RSDK_OBJECT
    int8 health;
    uint8 invincibilityTimer;
    Animator fxTrailAnimator[4];
    uint8 storedIDs[4];
    uint8 storedAnimIDs[4];
    Vector2 storePos[16];
    Animator unusedAnimator;
    uint8 activeShurikens;
    uint16 aniFrames;
    Hitbox hitboxShinobi;
    Hitbox hitboxSlashRange;
    Hitbox hitboxUnused;
    Hitbox hitboxSlash;
    Hitbox hitboxAsteron;
    Hitbox hitboxBounds;
    Hitbox hitboxAsteronSpike;
    uint16 sfxHit;
    uint16 sfxExplosion;
    uint16 sfxDefeat;
    uint16 sfxDropIn;
    uint16 sfxExplode;
    uint16 sfxGlitch;
    uint16 sfxJump;
    uint16 sfxParry;
    uint16 sfxSlash;
    uint16 sfxStick;
    uint16 sfxThrow;
};

// Entity Class
struct EntityHeavyShinobi {
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(stateDraw);
    int32 type;
    int32 timer;
    int32 glitchTimer;
    EntityPlayer *playerPtr;
    Vector2 playerDistance;
    Animator mainAnimator;
    Animator fxAnimator;
};

extern ObjectHeavyShinobi *HeavyShinobi;

extern StateMachine(HeavyShinobi_State_Setup);

bool32 HeavyShinobi_State_Setup_Hook(bool32);

#endif