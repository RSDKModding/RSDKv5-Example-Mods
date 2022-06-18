#ifndef UIDIORAMA_H
#define UIDIORAMA_H

// Object Class
struct ObjectUIDiorama {
    RSDK_OBJECT
    uint16 aniFrames;
    uint16 capsuleFrames;
    uint16 sonicFrames;
    uint16 tailsFrames;
    uint16 knuxFramesAIZ;
    uint16 knuxFramesHCZ;
    uint16 mightyFrames;
    uint16 rayFrames;
    uint16 ringFrames;
    uint16 speedGateFrames;
    uint16 bssSonicFrames;
    uint16 bssFrames;
    uint8 dioramaAlt;
};

// Entity Class
struct EntityUIDiorama {
    RSDK_ENTITY
    int32 dioramaID;
    int32 lastDioramaID;
    int32 timer;
    uint8 parentActivity;
    bool32 needsSetup;
    StateMachine(state);
    StateMachine(stateDraw);
    void *parent; // UIControl
    int32 maskColor;
    Vector2 dioramaPos;
    Vector2 dioramaSize;
    Animator maskAnimator;
    Animator staticAnimator;
    int32 values[16];
    Vector2 vectors[16];
    Animator animators[16];
    String texts[16];
};

// Object Struct
extern ObjectUIDiorama *UIDiorama;

void UIDiorama_Update(void);
void UIDiorama_Create(void* data);

#endif
