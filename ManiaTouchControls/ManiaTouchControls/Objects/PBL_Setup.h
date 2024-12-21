#ifndef OBJ_PBL_SETUP_H
#define OBJ_PBL_SETUP_H

#include "GameAPI/Game.h"

#if MANIA_USE_PLUS
// Object Class
typedef struct {
    RSDK_OBJECT
    int32 unused1;
    int32 timer;
    int32 score;
    int32 score1UP;
    int32 rings;
    int32 ringFrame;
    int32 ringPan;
    int32 sectorID;
    int32 sectorCount;
    int32 scanlineTimer;
    uint8 tableLow;
    uint8 tableHigh;
    uint16 sfxContinue;
} ObjectPBL_Setup;

// Entity Class
typedef struct {
    int32 touchPause;
} ModObjectPBL_Setup;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 timer;
    int32 color;
    Matrix unusedMatrix1;
} EntityPBL_Setup;

// Object Struct
extern ObjectPBL_Setup *PBL_Setup;
extern ModObjectPBL_Setup *Mod_PBL_Setup;

// Standard Entity Events
void PBL_Setup_StaticUpdate(void);
#endif

#endif //! OBJ_PBL_SETUP_H
