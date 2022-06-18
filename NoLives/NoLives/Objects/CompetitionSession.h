#ifndef OBJ_COMPETITIONSESSION_H
#define OBJ_COMPETITIONSESSION_H

#include "GameAPI/Game.h"

#if !MANIA_USE_PLUS
// preplus was always 2P
#define COMPETITION_PLAYER_COUNT (2)
#endif

#define COMPETITION_STAGE_COUNT (12)

typedef enum {
    FINISHTYPE_NOTFINISHED,
    FINISHTYPE_GAMEOVER,
    FINISHTYPE_PASSEDSIGNPOST,
} vsFinishFlags;

typedef enum {
    VS_BORDER_NONE,
    VS_BORDER_BOTTOMRIGHT,
    VS_BORDER_BOTTOM,
    VS_BORDER_BOTTOMLEFT,
    VS_BORDER_TOPRIGHT,
    VS_BORDER_TOP,
    VS_BORDER_TOPLEFT,
} vsScreenBorderTypes;

// created so I can easily set up times in an array
typedef struct {
    int32 minutes;
    int32 seconds;
    int32 milliseconds;
} vsTime;

// Object Class
typedef struct {
    RSDK_OBJECT
} ObjectCompetitionSession;

// Entity Class
typedef struct {
    RSDK_ENTITY
    bool32 inMatch;
    int32 playerCount;
    int32 stageIndex;
    int32 zoneID;
    int32 actID;
    int32 matchID;
    int32 matchCount;
    int32 itemMode;
#if MANIA_USE_PLUS
    int32 swapType;
#endif
    bool32 completedStages[COMPETITION_STAGE_COUNT];
    uint8 playerID[PLAYER_COUNT];
    uint8 matchWinner[COMPETITION_STAGE_COUNT];
    int32 rings[PLAYER_COUNT];
    int32 score[PLAYER_COUNT];
    int32 items[PLAYER_COUNT];
    vsTime time[PLAYER_COUNT];
    uint8 finishState[PLAYER_COUNT];
    int32 totalRings[PLAYER_COUNT];
    int32 wins[PLAYER_COUNT];
    int32 lives[PLAYER_COUNT];
#if MANIA_USE_PLUS
    int32 screenBorderType[SCREEN_COUNT];
    int32 displayMode;
    int32 controllerIDs[PLAYER_COUNT];
    int32 prevMatchID;
#endif
} EntityCompetitionSession;

#endif //! OBJ_COMPETITIONSESSION_H
