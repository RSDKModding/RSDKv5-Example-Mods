#include "ReplayRecorder.h"
#include "../Helpers.h"

#if MANIA_USE_PLUS
ObjectReplayRecorder *ReplayRecorder;
ModObjectReplayRecorder *Mod_ReplayRecorder;

void ReplayRecorder_StaticUpdate(void)
{
    RSDK_THIS(ReplayRecorder);

    if (globals->gameMode == MODE_TIMEATTACK && RSDK.FindObject("Zone")) {
        EntityReplayRecorder *playbackManager = ReplayRecorder->playbackManager;
        if (!playbackManager->isGhostPlayback) {
            bool32 touchedPause = false;
            if (CheckTouchPause()) {
                ControllerInfo->keyStart.down |= true;
                touchedPause = true;
            }

            if (!Mod_ReplayRecorder->touchPause && touchedPause)
                ControllerInfo->keyStart.press |= ControllerInfo->keyStart.down;
            Mod_ReplayRecorder->touchPause = ControllerInfo->keyStart.down;
        }
    }

    Mod.Super(ReplayRecorder->classID, SUPER_STATICUPDATE, NULL);
}
#endif
