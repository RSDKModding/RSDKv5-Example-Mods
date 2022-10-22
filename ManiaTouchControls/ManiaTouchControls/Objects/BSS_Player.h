#ifndef OBJ_BSS_PLAYER_H
#define OBJ_BSS_PLAYER_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 jumpPressState;
    uint16 unused1;
    uint16 sonicFrames;
    uint16 tailsFrames;
    uint16 knuxFrames;
    uint16 mightyFrames;
    uint16 rayFrames;
    uint16 sfxJump;
} ObjectBSS_Player;

// Modded Object Class
typedef struct {
    uint8 touchJump;
    uint8 touchPause;
} ModObjectBSS_Player;

// Entity Class
typedef struct {
    RSDK_ENTITY
    int32 gravityStrength;
    bool32 sidekick;
    StateMachine(stateInput);
    int32 controllerID;
    bool32 up;
    bool32 down;
    bool32 left;
    bool32 right;
    bool32 jumpPress;
    Animator animator;
    Animator tailAnimator;
    uint16 aniFrames;
} EntityBSS_Player;

// Object Struct
extern ObjectBSS_Player *BSS_Player;
extern ModObjectBSS_Player *Mod_BSS_Player;

// Public Functions
extern StateMachine(BSS_Player_Input_P1);

// Extra Entity Functions
bool32 BSS_Player_Input_P1_Hook(bool32 skippedState);

#endif //! OBJ_BSS_PLAYER_H
