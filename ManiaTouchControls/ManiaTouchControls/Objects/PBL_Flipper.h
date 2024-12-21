#ifndef OBJ_PBL_FLIPPER_H
#define OBJ_PBL_FLIPPER_H

#include "GameAPI/Game.h"

#if MANIA_USE_PLUS
// Object Class
typedef struct {
    RSDK_OBJECT
    Animator unusedAnimator1;
    Hitbox hitbox;
    Hitbox hitboxUnused;
    int32 drawType;
    uint16 aniFrames;
    uint16 modelFrames;
    uint16 sceneIndex;
    uint16 sfxFlipper;
    uint16 sfxFlipperStage;
} ObjectPBL_Flipper;

// Modded Object Class
typedef struct {
    int32 touchL;
    int32 touchR;
    int32 touchB;
} ModObjectPBL_Flipper;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint8 minCraneID;
    int32 height;
    bool32 retractable;
    Matrix unusedMatrix1;
    Matrix matTransform;
    Matrix matWorld;
    Matrix matNormal;
    bool32 buttonPress;
    bool32 buttonDown;
    bool32 flipperActive;
    Animator animator;
} EntityPBL_Flipper;

// Object Struct
extern ObjectPBL_Flipper *PBL_Flipper;
extern ModObjectPBL_Flipper *Mod_PBL_Flipper;

// Standard Entity Events
void PBL_Flipper_StaticUpdate(void);
#endif

#endif //! OBJ_PBL_FLIPPER_H
