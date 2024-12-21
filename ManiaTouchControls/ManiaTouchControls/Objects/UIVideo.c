#include "UIVideo.h"

bool32 (*UIVideo_SkipCB)(void) = NULL;

void UIVideo_ModCB_VideoSkip(void *data)
{
    if (data == UIVideo_SkipCB && TouchInfo->count) {
        if (!ControllerInfo->keyStart.down)
            ControllerInfo->keyStart.press = true;
    }
}
