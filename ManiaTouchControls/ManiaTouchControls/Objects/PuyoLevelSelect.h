#ifndef OBJ_PUYOLEVELSELECT_H
#define OBJ_PUYOLEVELSELECT_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    uint16 sfxMenuBleep;
    uint16 sfxMenuAccept;
} ObjectPuyoLevelSelect;

// Modded Object Class
typedef struct {
    int32 touchFlags;
} ModObjectPuyoLevelSelect;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 playerID;
    bool32 canSelectLevels;
    bool32 ready;
    int32 optionID;
    Animator frameAnimator;
    Animator labelAnimator;
    bool32 up;
    bool32 down;
    bool32 confirmPress;
    bool32 backPress;

} EntityPuyoLevelSelect;

// Object Struct
extern ObjectPuyoLevelSelect *PuyoLevelSelect;
extern ModObjectPuyoLevelSelect *Mod_PuyoLevelSelect;

// Standard Entity Events
void PuyoLevelSelect_Update(void);

#endif //! OBJ_PUYOLEVELSELECT_H
