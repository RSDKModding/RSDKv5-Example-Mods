#ifndef OBJ_TITLESETUP_H
#define OBJ_TITLESETUP_H

#include "GameAPI/Game.h"

// Public Functions
extern bool32 (*TitleSetup_VideoSkipCB)(void);

// Mod Callbacks
void TitleSetup_ModCB_VideoSkip(void *data);

#endif //! OBJ_TITLESETUP_H
