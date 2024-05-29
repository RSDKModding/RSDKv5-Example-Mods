#ifndef OBJ_CREDITSSETUP_H
#define OBJ_CREDITSSETUP_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    int32 unused1;
    int32 creditsTrack;
    void *fxFade;
    bool32 started;
    bool32 skipped;
    int32 scrollPos;
    int32 creditsPos;
    int32 creditsSize;
} ObjectCreditsSetup;

// Mod Object Class
typedef struct {
    uint16 dpadFrames;
    Animator dpadArrowAnimator;
    int32 dpadAlpha;
    Vector2 backPos;
} ModObjectCreditsSetup;

// Entity Class
typedef struct {
    RSDK_ENTITY
} EntityCreditsSetup;

// Object Struct
extern ObjectCreditsSetup *CreditsSetup;
extern ModObjectCreditsSetup *Mod_CreditsSetup;

// Standard Entity Events
void CreditsSetup_StaticUpdate(void);
void CreditsSetup_StageLoad(void);

// Extra Entity Functions
void CreditsSetup_DrawUI(void);

// Mod Callbacks
void CreditsSetup_ModCB_OnDraw(void *data);

#endif //! OBJ_CREDITSSETUP_H
