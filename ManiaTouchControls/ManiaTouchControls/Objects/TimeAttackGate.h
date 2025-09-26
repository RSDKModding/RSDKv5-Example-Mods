#ifndef OBJ_TIMEATTACKGATE_H
#define OBJ_TIMEATTACKGATE_H

#include "GameAPI/Game.h"
#include "Player.h"

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(stateDraw);
    bool32 finishLine;
    int32 extendTop;
    int32 extendBottom;
    Vector2 boundsSize;
    Vector2 boundsOffset;
    bool32 topBoundary;
    int32 timer;
    bool32 hasFinished;
    int32 baseRotation;
    int32 spinSpeed;
    int32 spinTimer;
    int32 radius;
    int32 restartTimer;
    int32 fadeTimer;
    Vector2 playerPos;
    Animator baseAnimator;
    Animator topAnimator;
    Animator finAnimator;
} EntityTimeAttackGate;

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxGate;
    uint16 aniFrames;
    EntityTimeAttackGate *restartManager;
    EntityPlayer *triggerPlayer;
    bool32 started;
    int32 isFinished;
    int32 unused1;
    bool32 suppressedTitlecard;
    bool32 disableRecords;
    uint16 sfxSignpost;
    uint16 sfxTeleport;
    int32 teleportChannel;
    StateMachine(startCB);
    StateMachine(endCB);
} ObjectTimeAttackGate;

// Modded Object Class
typedef struct {
    uint8 touchRestart;
} ModObjectTimeAttackGate;

// Object Struct
extern ObjectTimeAttackGate *TimeAttackGate;
extern ModObjectTimeAttackGate *Mod_TimeAttackGate;

bool32 TimeAttackGate_State_Restarter_Hook(bool32 skippedState);

#endif //! OBJ_TIMEATTACKGATE_H
