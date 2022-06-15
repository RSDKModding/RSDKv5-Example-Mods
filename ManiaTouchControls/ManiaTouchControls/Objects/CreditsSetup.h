#ifndef OBJ_CREDITSSETUP_H
#define OBJ_CREDITSSETUP_H

#include "../../GameAPI/C/GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    int32 unused1;
    int32 creditsTrack;
    void *fxFade;
    bool32 started;
    bool32 skipped;
    int32 scrollPos;
    int32 creditsPos;
    int32 creditsSize;
} ObjectCreditsSetup;

// Entity Class
typedef struct {
    RSDK_ENTITY
} EntityCreditsSetup;

// Object Struct
extern ObjectCreditsSetup *CreditsSetup;

// Standard Entity Events
void CreditsSetup_StaticUpdate(void);

#endif //! OBJ_CREDITSSETUP_H
