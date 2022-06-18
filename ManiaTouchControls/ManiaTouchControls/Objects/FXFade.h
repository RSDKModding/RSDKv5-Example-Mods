#ifndef OBJ_FXFADE_H
#define OBJ_FXFADE_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
} ObjectFXFade;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 timer;
    int32 speedIn;
    int32 wait;
    int32 speedOut;
    uint32 color;
    bool32 oneWay;
    bool32 eventOnly;
    bool32 overHUD;
    bool32 fadeOutBlack;
#if MANIA_USE_PLUS
    bool32 transitionScene;
#endif
} EntityFXFade;

#endif //! OBJ_FXFADE_H
