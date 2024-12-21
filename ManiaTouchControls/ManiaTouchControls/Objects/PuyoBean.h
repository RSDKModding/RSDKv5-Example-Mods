#ifndef OBJ_PUYOBEAN_H
#define OBJ_PUYOBEAN_H

#include "GameAPI/Game.h"

#define PUYO_PLAYFIELD_W (6)
#define PUYO_PLAYFIELD_H (14)

typedef enum {
    PUYOBEAN_BLUE   = 0,
    PUYOBEAN_GREEN  = 6,
    PUYOBEAN_PURPLE = 12,
    PUYOBEAN_RED    = 18,
    PUYOBEAN_YELLOW = 24,
    PUYOBEAN_JUNK   = 30,
} PuyoBeanTypes;

typedef enum {
    PUYOBEAN_ANI_FLASH,
    PUYOBEAN_ANI_IDLE,
    PUYOBEAN_ANI_BOUNCE,
    PUYOBEAN_ANI_CONNECT,
    PUYOBEAN_ANI_POP,
    PUYOBEAN_ANI_DEBRIS,
} PuyoBeanAniIDs;

// Object Class
typedef struct {
    RSDK_OBJECT
    TABLE(int32 fallDelays[5], { 16, 12, 8, 4, 2 });
    Hitbox hitboxBean;
    int32 comboChainCount[2];
    int32 disableBeanLink[2];
    void *playfield[256];
    int32 beanLinkCount;
    Vector2 beanLinkPositions[256];
    bool32 beanLinkTable[84]; // PUYO_PLAYFIELD_W * PUYO_PLAYFIELD_H
    int32 shinkDelay;
    Animator junkBeanAnimator;
    uint16 aniFrames;
    uint16 sfxLand;
    uint16 sfxRotate;
    uint16 chainFrames[6];
    uint16 sfxJunk;
    uint16 sfxFall;
} ObjectPuyoBean;

// Modded Object Class
typedef struct {
    int32 touchRight;
    int32 touchLeft;
} ModObjectPuyoBean;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 playerID;
    int32 type;
    int32 linkSides;
    int32 linkCount;
    void *linkBeans[4];
    int32 timer;
    int32 popTimer;
    int32 moveTimer;
    int32 fallTimer;
    int32 fallDelay;
    int32 rotateSpeed;
    int32 unused1;
    int32 rotationDir;
    int32 idleTimer;
    int32 connectTimer;
    int32 selectedLevel;
    Vector2 stillPos;
    Vector2 unused2;
    Vector2 origin;
    int32 targetAngle;
    bool32 forceRotationActive;
    bool32 isJunk;
    void *partner;
    StateMachine(stateInput);
    int32 controllerID;
    bool32 down;
    bool32 left;
    bool32 right;
    bool32 rotateRight;
    bool32 rotateLeft;
    bool32 forceRotateLeft;
    bool32 forceRotateRight;
    Animator beanAnimator;
} EntityPuyoBean;

// Object Struct
extern ObjectPuyoBean *PuyoBean;
extern ModObjectPuyoBean *Mod_PuyoBean;

// Extra Entity Functions
bool32 PuyoBean_Input_Player_Hook(bool32 skippedState);

#endif //! OBJ_PUYOBEAN_H
