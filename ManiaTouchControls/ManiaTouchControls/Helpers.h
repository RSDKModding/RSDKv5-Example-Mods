#ifndef HELPERS_H
#define HELPERS_H

#include "GameAPI/Game.h"

int32 CheckTouchRect(int32 x1, int32 y1, int32 x2, int32 y2, int32 *fx, int32 *fy);


#if MANIA_USE_PLUS
#define API_GetConfirmButtonFlip() API.GetConfirmButtonFlip()
#else
#define API_GetConfirmButtonFlip() false // too lazy lol
#endif

#endif // !HELPERS_H