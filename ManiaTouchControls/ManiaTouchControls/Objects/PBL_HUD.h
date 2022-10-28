#ifndef OBJ_PBL_HUD_H
#define OBJ_PBL_HUD_H

#include "GameAPI/Game.h"

#if MANIA_USE_PLUS
// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    uint8 debugEnabled;
} ObjectPBL_HUD;

// Modded Object Class
typedef struct {
    uint16 dpadFrames;
    Animator dpadAnimator;
    Animator dpadTouchAnimator;
    Vector2 dpadPos;
    int32 dpadAlpha;
    Vector2 actionPos;
    Vector2 pausePos;
    int32 pauseAlpha;
} ModObjectPBL_HUD;

// Entity Class
typedef struct {
    RSDK_ENTITY
    Animator sphereAnimator;
    Animator ringAnimator;
    Animator numbersAnimator;
} EntityPBL_HUD;

// Object Struct
extern ObjectPBL_HUD *PBL_HUD;
extern ModObjectPBL_HUD *Mod_PBL_HUD;

// Standard Entity Events
void PBL_HUD_Draw(void);
void PBL_HUD_StageLoad(void);

// Extra Entity Functions
void PBL_HUD_DrawTouchControls(void);

#endif

#endif //! OBJ_PBL_HUD_H
