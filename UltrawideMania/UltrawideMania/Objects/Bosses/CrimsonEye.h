#ifndef CRIMSONEYE_H
#define CRIMSONEYE_H

struct ObjectCrimsonEye {
    RSDK_OBJECT
    TABLE(int32 debrisInfo[97],
          { 24,       0,  0, -0x28000, -0x28000, 1,  0, -0x14000, -0x28000, 2,  0, 0x14000,  -0x26000, 3,  0, 0x28000,  -0x26000, 4,  0, -0x26000,
            -0x24000, 5,  0, 0x26000,  -0x24000, 6,  0, -0x26000, -0x22000, 7,  0, 0x26000,  -0x22000, 8,  0, -0x24000, -0x20000, 9,  0, -0x12000,
            -0x20000, 10, 0, 0x12000,  -0x20000, 11, 0, 0x24000,  -0x20000, 12, 0, -0x22000, -0x1E000, 13, 0, -0x11000, -0x1E000, 14, 0, 0x11000,
            -0x1E000, 15, 0, 0x22000,  -0x1E000, 16, 0, -0x20000, -0x1C000, 17, 0, -0x10000, -0x1C000, 18, 0, 0x10000,  -0x1C000, 19, 0, 0x20000,
            -0x1C000, 20, 0, -0x1A000, -0x1A000, 21, 0, -0xD000,  -0x1A000, 22, 0, 0xD000,   -0x1A000, 23, 0, 0x1A000,  -0x1A000 });
    uint8 health;
    uint8 invincibilityTimer;
    uint8 ballSpinAngleX;
    uint8 ballSpinAngleY;
    int32 ballSpinRadius;
    int32 ballOffsetY;
    Vector2 containerPos;
    Vector2 eyePositions[3];
    TABLE(int32 ballDestroyOrder[8], { 1, 5, 2, 6, 3, 7, 4, 8 });
    int32 destroyedBallCount;
    int32 elevatorSpeed;
    int32 targetElevatorSpeed;
    int32 nextTargetElevatorSpeed;
    int32 elevatorGravity; // probably not this, but I really didn't have much to work with here, sorry!
    int32 shotTimer;
    uint8 shotsRemaining;
    int32 unused;
    uint16 aniFrames;
    Hitbox hitboxEye;
    Hitbox hitboxBall;
    Hitbox hitboxOrb;
    Hitbox hitboxBlock;
    Hitbox hitboxElecOrb;
    Hitbox hitboxUnused1;
    Hitbox hitboxUnused2;
    uint16 sfxHit;
    uint16 sfxExplosion;
    uint16 sfxHover;
    uint16 sfxHover2;
    uint16 sfxElevator;
    uint16 sfxShot;
    uint16 sfxBeep;
    uint16 sfxHullClose;
    uint16 sfxButton;
    uint16 sfxImpact;
    TileLayer *liftBackground;
    TileLayer *bg2Layer;
};

struct EntityCrimsonEye {
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(stateEye);
    StateMachine(stateDraw);
    int32 type;
    int32 timer;
    int32 ballTimer;
    int32 ballRadiusTimer;
    Vector2 originPos;
    Animator animator;
};

extern StateMachine(CrimsonEye_StateContainer_SetupArena);
extern StateMachine(CrimsonEye_StateContainer_AwaitPlayer);
extern ObjectCrimsonEye *CrimsonEye;

bool32 CrimsonEye_StateContainer_SetupArena_Hook(bool32);
bool32 CrimsonEye_StateContainer_AwaitPlayer_Hook(bool32);
#endif