#ifndef OBJ_ANNOUNCER_H
#define OBJ_ANNOUNCER_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    uint16 sfxThree;
    uint16 sfxTwo;
    uint16 sfxOne;
    uint16 sfxGo;
    uint16 sfxGoal;
    uint16 sfxSonicWins;
    uint16 sfxTailsWins;
    uint16 sfxKnuxWins;
#if MANIA_USE_PLUS
    uint16 sfxMightyWins;
    uint16 sfxRayWins;
#endif
    uint16 sfxNewRecordTop;
    uint16 sfxNewRecordMid;
    uint16 sfxSonic;
    uint16 sfxTails;
    uint16 sfxKnuckles;
#if MANIA_USE_PLUS
    uint16 sfxMighty;
    uint16 sfxRay;
#endif
    uint16 sfxTheWinnerIs;
    uint16 sfxPlayer1;
    uint16 sfxPlayer2;
#if MANIA_USE_PLUS
    uint16 sfxPlayer3;
    uint16 sfxPlayer4;
#endif
    uint16 sfxDrawRound;
    uint16 sfxDrawSet;
    bool32 finishedCountdown;
} ObjectAnnouncer;

#endif //!OBJ_ANNOUNCER_H
