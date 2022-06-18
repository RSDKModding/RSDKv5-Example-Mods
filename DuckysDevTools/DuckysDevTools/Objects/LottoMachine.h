#ifndef OBJ_LOTTOMACHINE_H
#define OBJ_LOTTOMACHINE_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBottom;
    Hitbox hitboxMotor;
    uint8 activePlayers;
    uint16 sfxPimPom;
    uint16 sfxFail;
    Animator shineAnimator;
    uint16 aniFrames;
} ObjectLottoMachine;

#endif //! OBJ_LOTTOMACHINE_H
