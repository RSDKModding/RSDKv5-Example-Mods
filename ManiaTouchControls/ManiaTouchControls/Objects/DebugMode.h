#ifndef OBJ_DEBUGMODE_H
#define OBJ_DEBUGMODE_H

#include "GameAPI/Game.h"

#define DEBUGMODE_OBJECT_COUNT (0x100)

// Object Class
typedef struct {
    RSDK_OBJECT
    // Never used, only set, prolly leftover from S1/S2
    int16 classIDs[DEBUGMODE_OBJECT_COUNT];
    StateMachine(draw[DEBUGMODE_OBJECT_COUNT]);
    StateMachine(spawn[DEBUGMODE_OBJECT_COUNT]);
    Animator animator;
    int32 itemID;
    int32 itemCount;
    bool32 debugActive;
    uint8 itemType;
    uint8 itemTypeCount;
    int32 unused1; // no clue, though it could be "exitTimer" assuming this was based on v4's debugMode object?
} ObjectDebugMode;

// Entity Class
typedef struct {
    RSDK_ENTITY
} EntityDebugMode;

// Object Struct
extern ObjectDebugMode *DebugMode;

// Standard Entity Events
void DebugMode_Update(void);

#endif //! OBJ_DEBUGMODE_H
