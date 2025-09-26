#ifndef OBJ_HUD_H
#define OBJ_HUD_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
#if GAME_VERSION != VER_100
    uint16 superButtonFrames;
#endif
#if MANIA_USE_PLUS
    uint16 sfxClick;
    uint16 sfxStarpost;
    bool32 showTAPrompt;
    bool32 replaySaveEnabled;
    int32 screenBorderType[PLAYER_COUNT];
    int32 swapCooldown;
    int32 stockFlashTimers[PLAYER_COUNT];
#endif
} ObjectHUD;

// Modded Object Class
typedef struct {
    uint16 dpadFrames;
    Animator dpadAnimator;
    Animator dpadTouchAnimator;
    Vector2 dpadPos;
    int32 dpadAlpha[PLAYER_COUNT];
    Vector2 actionPos;
    int32 jumpAlpha[PLAYER_COUNT];
#if GAME_VERSION != VER_100
    Vector2 superPos;
    int32 superAlpha[PLAYER_COUNT];
#endif
    Vector2 swapPos; // Also used for time attack quick restart
    int32 swapAlpha[PLAYER_COUNT]; // Also used for time attack quick restart
    Vector2 pausePos;
    int32 pauseAlpha[PLAYER_COUNT];
} ModObjectHUD;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    Vector2 scorePos;
    Vector2 timePos;
    Vector2 ringsPos;
    Vector2 lifePos;
#if MANIA_USE_PLUS
    int32 lifeFrameIDs[PLAYER_COUNT];
    int32 lives[PLAYER_COUNT];
#endif
    int32 targetPos;
#if GAME_VERSION != VER_100
    int32 actionPromptPos;
#endif
#if MANIA_USE_PLUS
    StateMachine(vsStates[PLAYER_COUNT]);
    Vector2 vsScorePos[PLAYER_COUNT];
    Vector2 vsTimePos[PLAYER_COUNT];
    Vector2 vsRingsPos[PLAYER_COUNT];
    Vector2 vsLifePos[PLAYER_COUNT];
    int32 vsTargetPos[PLAYER_COUNT];
    int32 screenID;
#endif
#if GAME_VERSION != VER_100
    int32 timeFlashFrame;
#endif
    int32 ringFlashFrame;
    bool32 enableTimeFlash;
    bool32 enableRingFlash;
    Animator hudElementsAnimator;
    Animator numbersAnimator;
    Animator hyperNumbersAnimator;
    Animator lifeIconAnimator;
    Animator playerIDAnimator;
#if GAME_VERSION != VER_100
    Animator superIconAnimator;
    Animator superButtonAnimator;
#endif
#if MANIA_USE_PLUS
    Animator thumbsUpIconAnimator;
    Animator thumbsUpButtonAnimator;
    Animator replayClapAnimator;
    Animator saveReplayButtonAnimator;
#endif
} EntityHUD;

// Object Struct
extern ObjectHUD *HUD;
extern ModObjectHUD *Mod_HUD;

// Standard Entity Events
void HUD_Draw(void);
void HUD_StageLoad(void);

// Extra Entity Functions
void HUD_DrawTouchControls(void);
void HUD_DrawMobileHUD(void);

// Entity States
extern void (*HUD_DrawNumbersBase16)(Vector2 *drawPos, int32 value);

#endif //! OBJ_HUD_H
