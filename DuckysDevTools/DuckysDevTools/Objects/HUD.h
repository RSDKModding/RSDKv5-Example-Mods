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

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    Vector2 scoreOffset;
    Vector2 timeOffset;
    Vector2 ringsOffset;
    Vector2 lifeOffset;
#if MANIA_USE_PLUS
    int32 lifeFrameIDs[PLAYER_COUNT];
    int32 lives[PLAYER_COUNT];
#endif
    int32 maxOffset;
#if GAME_VERSION != VER_100
    int32 superButtonPos;
#endif
#if MANIA_USE_PLUS
    StateMachine(vsStates[PLAYER_COUNT]);
    Vector2 vsScoreOffsets[PLAYER_COUNT];
    Vector2 vsTimeOffsets[PLAYER_COUNT];
    Vector2 vsRingsOffsets[PLAYER_COUNT];
    Vector2 vsLifeOffsets[PLAYER_COUNT];
    int32 vsMaxOffsets[PLAYER_COUNT];
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

// Public Functions
extern void (*HUD_DrawNumbersBase16)(Vector2 *drawPos, int32 value);

// Standard Entity Events
void HUD_Draw(void);

#endif //! OBJ_HUD_H
