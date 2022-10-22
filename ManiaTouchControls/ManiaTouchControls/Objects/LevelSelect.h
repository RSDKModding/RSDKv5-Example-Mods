#ifndef OBJ_LEVELSELECT_H
#define OBJ_LEVELSELECT_H

#include "GameAPI/Game.h"

typedef enum {
    LSELECT_PLAYER_NONE,
    LSELECT_PLAYER_SONIC,
    LSELECT_PLAYER_TAILS,
    LSELECT_PLAYER_KNUCKLES,
#if MANIA_USE_PLUS
    LSELECT_PLAYER_MIGHTY,
    LSELECT_PLAYER_RAY,
#endif
} LevelSelectPlayerIDs;

// Object Class
typedef struct {
    RSDK_OBJECT
#if MANIA_USE_PLUS
    STATIC(int32 bgAniDuration, 240);
    TABLE(int32 bgAniDurationTable[4], { 240, 3, 3, 3 });
    TABLE(int32 cheat_RickyMode[9], { 1, 9, 7, 9, 0, 8, 1, 1, 255 });
    TABLE(int32 cheat_AllEmeralds[5], { 4, 1, 2, 6, 255 });
    TABLE(int32 cheat_MaxContinues[9], { 1, 9, 9, 2, 1, 1, 2, 4, 255 });
    TABLE(int32 cheat_SwapGameMode[9], { 2, 0, 1, 8, 0, 6, 2, 3, 255 });
    TABLE(int32 cheat_UnlockAllMedals[9], { 1, 9, 8, 9, 0, 5, 0, 1, 255 });
    TABLE(int32 cheat_SuperDash[9], { 2, 0, 1, 7, 0, 8, 1, 5, 255 });
    TABLE(int32 cheat_MaxControl[5],
          { 9, 0, 0, 1, 255 }); // says there's 9 values here in static obj & IDA but only 5 are loaded so it is what it is ig
    TABLE(int32 cheat_ToggleSuperMusic[9], { 6, 2, 1, 4, 255, 0, 0, 0, 0 });
    int32 bgAniFrame;
    int32 startMusicID;
    int32 soundTestMax;
    uint16 sfxFail;
    uint16 sfxRing;
    uint16 sfxEmerald;
    uint16 sfxContinue;
    uint16 sfxMedalGot;
    int32 *cheatCodePtrs[8];
    int32 cheatCodePos[8];
    void (*checkCheatActivated[8])(void);
#else
    STATIC(int32 bgAniDuration, 240);
    int32 bgAniFrame;
    TABLE(int32 bgAniDurationTable[4], { 240, 3, 3, 3 });
    int32 startMusicID;
    int32 soundTestMax;
    uint16 sfxFail;
#endif
} ObjectLevelSelect;

// Mod Object Class
typedef struct {
    uint8 touchDir;
    uint8 touchConfirm;
    uint8 touchSwap;
    uint8 touchSwapP2;
    uint16 dpadFrames;
    Animator dpadAnimator;
    Animator dpadTouchAnimator;
    Vector2 dpadPos;
    int32 dpadAlpha;
    Vector2 confirmPos;
    int32 confirmAlpha;
    Vector2 swapPos;
    int32 swapAlpha;
    Vector2 swapP2Pos;
    int32 swapP2Alpha;
} ModObjectLevelSelect;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(stateDraw);
    int32 timer;
    int32 labelID;
    int32 soundTestID;
    int32 leaderCharacterID;
    int32 sidekickCharacterID;
    Entity *zoneNameLabels[32];
    Entity *stageIDLabels[32];
    Entity *soundTestLabel;
    Entity *zoneIcon;
    Entity *confirmer1Icon;
    Entity *confirmer2Icon;
#if MANIA_USE_PLUS
    Entity *pinballLabel;
#endif
    int32 labelCount;
#if MANIA_USE_PLUS
    int32 offsetUFO;
    int32 offsetBSS;
    int32 unused1;
    int32 unused2;
    int32 unused3;
    int32 unused4;
#endif
} EntityLevelSelect;

// Object Struct
extern ObjectLevelSelect *LevelSelect;
extern ModObjectLevelSelect *Mod_LevelSelect;

// Standard Entity Events
void LevelSelect_Draw(void);
void LevelSelect_StageLoad(void);

// Extra Entity Functions
bool32 LevelSelect_State_Navigate_Hook(bool32 skippedState);
void LevelSelect_DrawUI(void);

#endif //! OBJ_LEVELSELECT_H
