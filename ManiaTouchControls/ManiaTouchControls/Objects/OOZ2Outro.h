#ifndef OBJ_OOZ2OUTRO_H
#define OBJ_OOZ2OUTRO_H

#include "GameAPI/Game.h"

#if MANIA_USE_PLUS
// Extra Entity Functions
extern StateMachine(OOZ2Outro_State_BoardSub);
extern StateMachine(OOZ2Outro_State_SubActivate);

// State Hooks
void OOZ2Outro_State_BoardSub_Hook(void);
void OOZ2Outro_State_SubActivate_Hook(void);
#endif

#endif //! OBJ_OOZ2OUTRO_H
