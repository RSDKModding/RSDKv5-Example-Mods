#include "TitleSetup.h"

bool32 (*TitleSetup_VideoSkipCB)(void) = NULL;

void TitleSetup_ModCB_VideoSkip(void *data)
{
    if (data == TitleSetup_VideoSkipCB && TouchInfo->count) {
        if (!ControllerInfo->keyStart.down)
            ControllerInfo->keyStart.press = true;
    }
}