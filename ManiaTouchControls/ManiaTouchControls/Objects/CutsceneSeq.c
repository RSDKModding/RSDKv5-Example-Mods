#include "CutsceneSeq.h"

#if MANIA_USE_PLUS
ObjectCutsceneSeq *CutsceneSeq;

void CutsceneSeq_Update(void)
{
    RSDK_THIS(CutsceneSeq);

    ControllerInfo->keyStart.press |= TouchInfo->count;

    Mod.Super(CutsceneSeq->classID, SUPER_UPDATE, NULL);
}

void CutsceneSeq_Create(void *data)
{
    RSDK_THIS(CutsceneSeq);

    ControllerInfo->keyStart.press |= TouchInfo->count;

    Mod.Super(CutsceneSeq->classID, SUPER_CREATE, data);
}
#endif