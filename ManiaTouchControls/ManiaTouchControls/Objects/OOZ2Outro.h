#ifndef OBJ_OOZ2OUTRO_H
#define OBJ_OOZ2OUTRO_H

#include "GameAPI/Game.h"

#if MANIA_USE_PLUS
// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    uint16 sfxGlug;
    uint16 sfxSubLaunch;
} ObjectOOZ2Outro;

// Mod Object Class
typedef struct {
    uint16 dpadFrames;
    Animator dpadArrowAnimator;
    int32 dpadAlpha;
    Vector2 skipPos;
} ModObjectOOZ2Outro;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    Vector2 size;
    Vector2 moveOffset;
    Vector2 scrollOffset;
    int32 timer;
    Animator animator; // unused
    TileLayer *moveLayer;
    void *prisonPtr;
    Vector2 prisonPos;
} EntityOOZ2Outro;

// Object Struct
extern ObjectOOZ2Outro *OOZ2Outro;
extern ModObjectOOZ2Outro *Mod_OOZ2Outro;

// Standard Entity Events
void OOZ2Outro_StageLoad(void);

// Public Functions
extern StateMachine(OOZ2Outro_State_BoardSub);
extern StateMachine(OOZ2Outro_State_SubActivate);

// State Hooks
bool32 OOZ2Outro_State_Hook(bool32 skipped);

// Extra Entity Functions
void OOZ2Outro_DrawUI(void);

// Mod Callbacks
void OOZ2Outro_ModCB_OnDraw(void *data);
#endif

#endif //! OBJ_OOZ2OUTRO_H
