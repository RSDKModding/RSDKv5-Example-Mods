#ifndef OBJ_CUTSCENESEQ_H
#define OBJ_CUTSCENESEQ_H

#include "GameAPI/Game.h"

#define CUTSCENESEQ_POINT_COUNT (8)

#if MANIA_USE_PLUS
typedef enum {
    SKIPTYPE_DISABLED,
    SKIPTYPE_RELOADSCN,
    SKIPTYPE_NEXTSCENE,
    SKIPTYPE_CALLBACK,
} SkipTypes;
#endif

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
#if MANIA_USE_PLUS
    int32 skipType;
    void (*skipCallback)(void);
#endif
} EntityCutsceneSeq;

#if MANIA_USE_PLUS

// Public Functions
extern void (*CutsceneSeq_CheckSkip)(uint8 skipType, EntityCutsceneSeq *seq, void (*skipCallback)(void));

// Standard Entity Events
void CutsceneSeq_Update(void);
void CutsceneSeq_Create(void *data);

// Extra Entity Functions
void CutsceneSeq_CheckSkip_Hook(uint8 skipType, EntityCutsceneSeq *seq, void (*skipCallback)(void));
#endif

#endif //! OBJ_CUTSCENESEQ_H
