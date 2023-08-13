#ifndef OBJ_OOZ2OUTRO_H
#define OBJ_OOZ2OUTRO_H

#include "GameAPI/Game.h"

#if MANIA_USE_PLUS
// Extra Entity Functions
extern StateMachine(OOZ2Outro_State_BoardSub);
extern StateMachine(OOZ2Outro_State_SubActivate);

// State Hooks
bool32 OOZ2Outro_State_BoardSub_Hook(bool32 skipped);
bool32 OOZ2Outro_State_SubActivate_Hook(bool32 skipped);
#endif

#endif //! OBJ_OOZ2OUTRO_H
