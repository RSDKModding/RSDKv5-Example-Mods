#ifndef OBJ_COVERLAY_H
#define OBJ_COVERLAY_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
} ObjectCOverlay;

// Entity Class
typedef struct {
    RSDK_ENTITY
} EntityCOverlay;

// Object Struct
extern ObjectCOverlay *COverlay;

// Standard Entity Events
void COverlay_Draw(void);

#endif //! OBJ_COVERLAY_H
