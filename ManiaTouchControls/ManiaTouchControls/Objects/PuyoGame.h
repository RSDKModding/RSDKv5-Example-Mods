#ifndef OBJ_PUYOGAME_H
#define OBJ_PUYOGAME_H

#include "GameAPI/Game.h"

typedef enum {
    PUYOGAME_PLAYER1,
    PUYOGAME_PLAYER2,
} PuyoGamePlayerIDs;

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    void *managers[2];
    void *indicators[2];
    void *platforms[2];
    void *score1[2];
    void *score2[2];
    void *levelSel[2];
    void *fxFade;
} ObjectPuyoGame;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 unused1;
    Vector2 startPos;
    int32 timer;
    int32 selectedLevels[2];
    int32 unused2;
    int32 unused3;
    Animator animator;
    bool32 started;
    int32 finishedMatch;
    bool32 determinedLoser;
    uint8 roundWinner;
    uint8 matchWinner;
} EntityPuyoGame;

// Object Struct
extern ObjectPuyoGame *PuyoGame;

// Standard Entity Events
void PuyoGame_Update(void);

// Extra Entity Functions
bool32 PuyoGame_State_ShowRoundResults_Hook(bool32 skippedState);
bool32 PuyoGame_State_ShowMatchResults_Hook(bool32 skippedState);

#endif //! OBJ_PUYOGAME_H
