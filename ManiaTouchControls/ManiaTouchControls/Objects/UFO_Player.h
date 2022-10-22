#ifndef OBJ_UFO_PLAYER_H
#define OBJ_UFO_PLAYER_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    int32 maxSpeed;
    uint16 aniFrames; // unused
    uint16 sfxJump;
    uint16 sfxCharge;
    uint16 sfxRelease;
    uint16 sfxLoseRings;
    uint16 sfxDrop;
    uint16 sfxBumper;
    uint16 sfxSpring;
    uint16 sfxSkid;
    uint16 sfxGrittyGround;
    uint16 jogModel;
    uint16 dashModel;
    uint16 jumpModel;
    uint16 ballModel;
    uint16 tumbleModel;
    uint16 sceneIndex;
} ObjectUFO_Player;

// Modded Object Class
typedef struct {
    uint8 touchJump;
    uint8 touchPause;
} ModObjectUFO_Player;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 machQuota1;
    int32 machQuota2;
    int32 machQuota3;
    int32 startingRings;
    int32 timer;
    int32 courseOutTimer;
    int32 angleX;
    int32 height;
    int32 gravityStrength;
    int32 angleZ;
    int32 velDivisor;
    int32 bumperTimer;
    int32 angleVel;
    int32 skidTimer;
    void *camera;
    void *circuitPtr;
    Matrix matRotate;
    Matrix matTransform;
    Matrix matWorld;
    Matrix matNormal;
    StateMachine(stateInput);
    int32 controllerID;
    bool32 up;
    bool32 down;
    bool32 left;
    bool32 right;
    bool32 jumpPress;
    bool32 jumpHold;
    Animator animator;
} EntityUFO_Player;

// Object Struct
extern ObjectUFO_Player *UFO_Player;
extern ModObjectUFO_Player *Mod_UFO_Player;

// Public Functions
extern StateMachine(UFO_Player_Input_P1);

// Extra Entity Functions
bool32 UFO_Player_Input_P1_Hook(bool32 skippedState);

#endif //! OBJ_UFO_PLAYER_H
