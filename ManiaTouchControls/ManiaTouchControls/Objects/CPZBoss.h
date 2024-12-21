#ifndef OBJ_CPZBOSS_H
#define OBJ_CPZBOSS_H

#include "GameAPI/Game.h"

typedef enum {
    CPZBOSS_PLAYER,
    CPZBOSS_EGGMAN,
} CPZBossTypes;

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxPlayerTrigger;
    void *managers[2];
    uint16 hudSlotID;
    uint16 aniFrames;
    uint16 playerFrames;
    uint16 sfxExplosion;
} ObjectCPZBoss;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint8 type;
    int32 timer;
    Vector2 startPos;
    Vector2 explosionPos;
    Animator panelAnimator;
    Animator enterAnimator;
    Animator characterAnimator;
} EntityCPZBoss;

// Object Struct
extern ObjectCPZBoss *CPZBoss;

// Extra Entity Functions
bool32 CPZBoss_State_HandleMatch_Player_Hook(bool32 skippedState);

#endif //! OBJ_CPZBOSS_H
