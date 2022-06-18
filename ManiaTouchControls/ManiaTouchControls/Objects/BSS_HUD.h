#ifndef OBJ_BSS_HUD_H
#define OBJ_BSS_HUD_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    uint8 debugEnabled;
} ObjectBSS_HUD;

// Entity Class
typedef struct {
    RSDK_ENTITY
    Animator sphereAnimator;
    Animator ringAnimator;
    Animator numbersAnimator;
} EntityBSS_HUD;

// Object Struct
extern ObjectBSS_HUD *BSS_HUD;

// Standard Entity Events
void BSS_HUD_Draw(void);

#endif //! OBJ_BSS_HUD_H
