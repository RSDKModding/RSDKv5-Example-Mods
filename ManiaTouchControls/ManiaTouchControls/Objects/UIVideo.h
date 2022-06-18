#ifndef OBJ_UIVIDEO_H
#define OBJ_UIVIDEO_H

#include "GameAPI/Game.h"

// Public Functions
extern bool32 (*UIVideo_SkipCB)(void);

// Mod Callbacks
void UIVideo_ModCB_VideoSkip(void *data);

#endif //! OBJ_UIVIDEO_H
