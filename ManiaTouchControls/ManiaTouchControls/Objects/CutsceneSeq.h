#ifndef OBJ_CUTSCENESEQ_H
#define OBJ_CUTSCENESEQ_H

#include "GameAPI/Game.h"

#if MANIA_USE_PLUS
#define CUTSCENESEQ_POINT_COUNT (8)

typedef enum {
    SKIPTYPE_DISABLED,
    SKIPTYPE_RELOADSCN,
    SKIPTYPE_NEXTSCENE,
    SKIPTYPE_CALLBACK,
} SkipTypes;

// Object Class
typedef struct {
    RSDK_OBJECT
} ObjectCutsceneSeq;

// Mod Object Class
typedef struct {
    uint16 dpadFrames;
    Animator dpadArrowAnimator;
    int32 dpadAlpha;
    Vector2 skipPos;
} ModObjectCutsceneSeq;

// Entity Class
typedef struct {
    RSDK_ENTITY
    bool32 (*currentState)(void *host);
    uint8 stateID;
    int32 timer;
    int32 storedValue; // never reset, unlike timer & the 8 values
    int32 storedTimer;
    int32 values[8];
    Entity *activeEntity;  // the entity that called StartSequence
    Entity *managerEntity; // the host entity of the sequence
    bool32 (*cutsceneStates[0x40])(void *host);
    Vector2 points[CUTSCENESEQ_POINT_COUNT];
    int32 fadeWhite;
    int32 fadeBlack;
    int32 skipType;
    void (*skipCallback)(void);
} EntityCutsceneSeq;

extern ObjectCutsceneSeq *CutsceneSeq;
extern ModObjectCutsceneSeq *Mod_CutsceneSeq;

// Standard Entity Events
void CutsceneSeq_Update(void);
void CutsceneSeq_LateUpdate(void);
void CutsceneSeq_Draw(void);
void CutsceneSeq_Create(void *data);
void CutsceneSeq_StageLoad(void);
#endif

#endif //! OBJ_CUTSCENESEQ_H
