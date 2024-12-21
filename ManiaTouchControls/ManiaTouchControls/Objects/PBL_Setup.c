#include "PBL_Setup.h"
#include "../Helpers.h"

#if MANIA_USE_PLUS
ObjectPBL_Setup *PBL_Setup;
ModObjectPBL_Setup *Mod_PBL_Setup;

void PBL_Setup_StaticUpdate(void)
{
    bool32 touchedPause = false;
    if (CheckTouchPause()) {
        ControllerInfo->keyStart.down |= true;
        touchedPause = true;
    }

    if (!Mod_PBL_Setup->touchPause && touchedPause) {
        ControllerInfo->keyStart.press |= ControllerInfo->keyStart.down;
    }
    Mod_PBL_Setup->touchPause = ControllerInfo->keyStart.down;

    Mod.Super(PBL_Setup->classID, SUPER_STATICUPDATE, NULL);
}
#endif
