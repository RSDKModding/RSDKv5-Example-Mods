#ifndef OBJ_UFO_HUD_H
#define OBJ_UFO_HUD_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    uint8 debugEnabled;
} ObjectUFO_HUD;

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
} ModObjectUFO_HUD;

// Entity Class
typedef struct {
    RSDK_ENTITY
    Animator sphereAnimator;
    Animator ringAnimator;
    Animator numbersAnimator;
} EntityUFO_HUD;

// Object Struct
extern ObjectUFO_HUD *UFO_HUD;
extern ModObjectUFO_HUD *Mod_UFO_HUD;

// Standard Entity Events
void UFO_HUD_Draw(void);
void UFO_HUD_StageLoad(void);

// Extra Entity Functions
void UFO_HUD_DrawTouchControls(void);

#endif //! OBJ_UFO_HUD_H
