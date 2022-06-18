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

typedef struct {
    uint8 touchDir;
    uint8 touchConfirm;
    uint8 touchBack;
} ModObjectDASetup;

// Entity Class
typedef struct {
	RSDK_ENTITY
} EntityDASetup;

// Object Struct
extern ObjectDASetup *DASetup;
extern ModObjectDASetup *Mod_DASetup;

// Standard Entity Events
void DASetup_Update(void);
void DASetup_LateUpdate(void);
void DASetup_StaticUpdate(void);
void DASetup_Draw(void);
void DASetup_Create(void* data);
void DASetup_StageLoad(void);
#if RETRO_INCLUDE_EDITOR
void DASetup_EditorDraw(void);
void DASetup_EditorLoad(void);
#endif
void DASetup_Serialize(void);

// Extra Entity Functions
bool32 DASetup_State_ManageControl_Hook(bool32 skippedState);

#endif //!OBJ_DASETUP_H
