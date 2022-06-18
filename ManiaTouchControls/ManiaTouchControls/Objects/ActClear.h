#ifndef OBJ_ACTCLEAR_H
#define OBJ_ACTCLEAR_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    uint16 sfxScoreAdd;
    uint16 sfxScoreTotal;
#if MANIA_USE_PLUS
    uint16 sfxEvent;
#endif
    bool32 bufferMoveEnabled;
    bool32 isSavingGame;
#if MANIA_USE_PLUS
    bool32 disableResultsInput;
#endif
    int32 displayedActID;
    bool32 finished;
#if MANIA_USE_PLUS
    bool32 forceNoSave;
    StateMachine(bufferMove_CB);
    StateMachine(saveReplay_CB);
    bool32 hasSavedReplay;
    bool32 disableTimeBonus;
    bool32 actClearActive;
#endif
} ObjectActClear;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 timer;
    int32 stageFinishTimer;
    int32 timeBonus;
    int32 ringBonus;
    int32 coolBonus;
    int32 totalScore;
    int32 time;
    int32 newRecordTimer;
    bool32 achievedRank;
    bool32 isNewRecord;
    bool32 showCoolBonus;
    Vector2 playerNamePos;
    Vector2 gotThroughPos;
    Vector2 timeBonusPos;
    Vector2 ringBonusPos;
    Vector2 coolBonusPos;
    Vector2 totalScorePos;
    void *targetPlayer;
    Animator hudElementsAnimator;
    Animator numbersAnimator;
    Animator playerNameAnimator;
    Animator gotThroughAnimator;
    Animator actNumAnimator;
#if MANIA_USE_PLUS
    Animator timeElementsAnimator;
#endif
} EntityActClear;

// Object Struct
extern ObjectActClear *ActClear;

// Standard Entity Events

// Extra Entity Functions
bool32 ActClear_State_TallyScore_Hook(bool32 skippedState);
#if MANIA_USE_PLUS
bool32 ActClear_State_ShowResultsTA_Hook(bool32 skippedState);
#endif

#endif //! OBJ_ACTCLEAR_H
