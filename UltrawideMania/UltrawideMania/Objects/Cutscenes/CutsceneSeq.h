#ifndef CUTSCENESEQ_H
#define CUTSCENESEQ_H

#define CUTSCENESEQ_POINT_COUNT (8)

struct ObjectCutsceneSeq {
    RSDK_OBJECT
};

// Entity Class
struct EntityCutsceneSeq {
    RSDK_ENTITY
    bool32 (*currentState)(EntityCutsceneSeq *host);
    uint8 stateID;
    int32 timer;
    int32 storedValue; // never reset, unlike timer & the 8 values
    int32 storedTimer;
    int32 values[8];
    Entity *activeEntity;  // the entity that called StartSequence
    Entity *managerEntity; // the host entity of the sequence
    bool32 (*cutsceneStates[0x40])(EntityCutsceneSeq *host);
    Vector2 points[CUTSCENESEQ_POINT_COUNT];
    int32 fadeWhite;
    int32 fadeBlack;
#if MANIA_USE_PLUS
    int32 skipType;
    void (*skipCallback)(void);
#endif
};

// Object Struct
extern ObjectCutsceneSeq *CutsceneSeq;

// Standard Entity Events
void CutsceneSeq_LateUpdate(void);

// Cutscene State Functions
extern bool32 (*FBZ1Outro_Cutscene_PrepareFBZ2)(EntityCutsceneSeq *host);
#endif
