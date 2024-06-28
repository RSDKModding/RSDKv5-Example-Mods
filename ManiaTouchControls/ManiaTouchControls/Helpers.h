#ifndef HELPERS_H
#define HELPERS_H

#include "GameAPI/Game.h"

int32 CheckTouchRect(int32 x1, int32 y1, int32 x2, int32 y2, int32 *fx, int32 *fy);

void HandleDPad_4Dir(RSDKControllerState *controller);
void HandleDPad_8Dir(RSDKControllerState *controller);

#if MANIA_USE_PLUS
#define API_GetConfirmButtonFlip() API.GetConfirmButtonFlip()
#else
#define API_GetConfirmButtonFlip() false // too lazy lol
#endif

#define CheckTouchPause() (CheckTouchRect(ScreenInfo->size.x - 0x80, 0, ScreenInfo->size.x, 0x40, NULL, NULL) >= 0)

#endif // !HELPERS_H