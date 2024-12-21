#ifndef OBJ_TRYAGAINE_H
#define OBJ_TRYAGAINE_H

#include "GameAPI/Game.h"

#if MANIA_USE_PLUS
// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    uint16 playerFrames;
} ObjectTryAgainE;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 timer;
    int32 unused1;
    int32 unused2;
    Animator mainAnimator;
    Animator handUpAnimator;
    Animator handDownAnimator;
    Animator player1Animator;
    Animator player2Animator;
} EntityTryAgainE;

// Object Struct
extern ObjectTryAgainE *TryAgainE;

// Extra Entity Functions
bool32 TryAgainE_State_Stinger_Hook(bool32 skippedState);
#endif

#endif //! OBJ_TRYAGAINE_H
