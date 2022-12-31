#include "../../ModConfig.h"
ObjectCutsceneSeq *CutsceneSeq;

bool32 (*FBZ1Outro_Cutscene_PrepareFBZ2)(EntityCutsceneSeq *host);

void CutsceneSeq_LateUpdate(void)
{
    RSDK_THIS(CutsceneSeq);

    // Prevent a softlock during the FBZ1 Outro
    if (self->currentState == FBZ1Outro_Cutscene_PrepareFBZ2 && Zone->cameraBoundsL[0] == 13568) {
        Zone->cameraBoundsL[0] = ScreenInfo->position.x;
        Zone->cameraBoundsL[1] = ScreenInfo->position.x;
    }

    Mod.Super(CutsceneSeq->classID, SUPER_LATEUPDATE, NULL);
}