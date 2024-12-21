#ifndef OBJ_PBL_CRANE_H
#define OBJ_PBL_CRANE_H

#include "GameAPI/Game.h"

#if MANIA_USE_PLUS

typedef enum {
    PBL_CRANE_MANAGER,
    PBL_CRANE_CRANE,
    PBL_CRANE_PRIZEDISPLAY,
    PBL_CRANE_PRIZE,
} PBL_CraneTypes;

// Object Class
typedef struct {
    RSDK_OBJECT
    int32 prizeID;
    uint16 aniFrames;
    uint16 sfxBackGlass;
    uint16 sfxCraneMove;
    uint16 sfxCraneDrop;
    uint16 sfxCraneGrab;
    uint16 sfxCraneRise;
    uint16 sfxPrizeGood;
    uint16 sfxPrizeBad;
} ObjectPBL_Crane;

// Object Class
typedef struct {
    bool32 active;
    uint8 touchDir;
    int32 touchDown;
} ModObjectPBL_Crane;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(stateDraw);
    int32 type;
    int32 unused1;
    int32 timer;
    int32 unused2;
    int32 unused3;
    void *parent;
    Entity *cameraTarget;
    Animator displayAnimator;
    Animator bgAnimator;
    Animator craneBackAnimator;
    Animator craneFrontAnimator;
    Animator machineAnimator;
} EntityPBL_Crane;

// Object Struct
extern ObjectPBL_Crane *PBL_Crane;
extern ModObjectPBL_Crane *Mod_PBL_Crane;

// Standard Entity Events
void PBL_Crane_Update(void);
#endif

#endif //! OBJ_PBL_CRANE_H
