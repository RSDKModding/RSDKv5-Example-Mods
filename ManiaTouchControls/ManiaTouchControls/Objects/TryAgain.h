#ifndef OBJ_TRYAGAIN_H
#define OBJ_TRYAGAIN_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
} ObjectTryAgain;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 timer;
    int32 unused1;
    int32 unused2;
    Vector2 eggmanPos;
    int32 unused3;
    int32 eggmanVelocityY;
    Vector2 rubyPos;
    Vector2 rubyVelocity;
    Animator debrisAnimator;
    Animator eggmanAnimator;
    Animator rubyAnimator;
} EntityTryAgain;

// Object Struct
extern ObjectTryAgain *TryAgain;

// Standard Entity Events

// Extra Entity Functions
bool32 TryAgain_State_Stinger_Hook(bool32 skippedState);

#endif //! OBJ_TRYAGAIN_H
