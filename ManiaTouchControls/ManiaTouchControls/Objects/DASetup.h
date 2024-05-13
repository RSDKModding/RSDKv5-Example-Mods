#ifndef OBJ_DASETUP_H
#define OBJ_DASETUP_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    bool32 initialized;
    int32 returnToMenu;
    int32 trackCount;
    int32 trackID;
    int32 activeTrack;
    void *control;
    void *trackSelLabel;
    void *trackTitleLabel;
    void *fxFade;
    void *trackList[64];
    uint16 sfxEmerald;
    uint16 sfxMedal;
    uint16 sfxSSExit;
    uint16 sfxScoreTotal;
} ObjectDASetup;

// Mod Object Class
typedef struct {
    uint8 touchConfirm;
    uint16 dpadFrames;
    Animator dpadAnimator;
    Animator dpadTouchAnimator;
    Animator dpadArrowAnimator;
    int32 dpadAlpha;
    Vector2 dpadPos;
    Vector2 playPos;
    Vector2 backPos;
} ModObjectDASetup;

// Entity Class
typedef struct {
	RSDK_ENTITY
} EntityDASetup;

// Object Struct
extern ObjectDASetup *DASetup;
extern ModObjectDASetup *Mod_DASetup;

// Standard Entity Events
void DASetup_StageLoad(void);

// Extra Entity Functions
bool32 DASetup_State_ManageControl_Hook(bool32 skippedState);
void DASetup_DrawUI(void);

// Mod Callbacks
void DASetup_ModCB_OnDraw(void *data);

#endif //!OBJ_DASETUP_H
