#include "CutsceneSeq.h"

#if MANIA_USE_PLUS

void (*CutsceneSeq_CheckSkip)(uint8 skipType, EntityCutsceneSeq *seq, void (*skipCallback)(void)) = NULL;

void CutsceneSeq_Update(void)
{
    RSDK_THIS(CutsceneSeq);

    CutsceneSeq_CheckSkip_Hook(self->skipType, self, self->skipCallback);
}

void CutsceneSeq_Create(void *data)
{
    RSDK_THIS(CutsceneSeq);

    Object *cutSeq = Mod.FindObject("CutsceneSeq");

    Mod.Super(cutSeq->classID, SUPER_CREATE, data);

    CutsceneSeq_CheckSkip_Hook(self->skipType, self, self->skipCallback);
}

void CutsceneSeq_CheckSkip_Hook(uint8 skipType, EntityCutsceneSeq *seq, void (*skipCallback)(void))
{
    ControllerInfo->keyStart.press |= TouchInfo->count;

    if (CutsceneSeq_CheckSkip)
        CutsceneSeq_CheckSkip(skipType, seq, skipCallback);
}
#endif