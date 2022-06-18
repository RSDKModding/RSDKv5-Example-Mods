#ifndef OBJ_SUMMARY_H
#define OBJ_SUMMARY_H

#include "GameAPI/Game.h"

#if MANIA_USE_PLUS
// Object Class
typedef struct {
    RSDK_OBJECT
    STATIC(int32 bgAniDuration, 240);
    int32 bgAniFrame;
    TABLE(int32 bgAniDurationTable[4], { 240, 3, 3, 3 });
} ObjectSummary;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(stateDraw);
    int32 timer;
    int32 unused1;
    int32 unused2;
    int32 leaderCharacterID;
    int32 sidekickCharacterID;
    void *gameModeLabel;
    void *saveFileLabel;
    void *totalTime;
    void *zoneLabels[32];
    void *player2Icon;
    void *player1Icon;
    void *unusedPtr;
} EntitySummary;

// Object Struct
extern ObjectSummary *Summary;

// Standard Entity Events

// Extra Entity Functions
bool32 Summary_State_Wait_Hook(bool32 skippedState);

#endif

#endif //! OBJ_SUMMARY_H
