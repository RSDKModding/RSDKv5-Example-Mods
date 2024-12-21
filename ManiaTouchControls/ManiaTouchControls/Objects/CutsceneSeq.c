#include "CutsceneSeq.h"
#include "HUD.h"
#include "../ModConfig.h"
#include "../Helpers.h"

#if MANIA_USE_PLUS
ObjectCutsceneSeq *CutsceneSeq;
ModObjectCutsceneSeq *Mod_CutsceneSeq;

void CutsceneSeq_Update(void)
{
    RSDK_THIS(CutsceneSeq);

    ControllerInfo->keyStart.press |= CheckTouchPause();

    Mod.Super(CutsceneSeq->classID, SUPER_UPDATE, NULL);
}

void CutsceneSeq_LateUpdate(void)
{
    RSDK_THIS(CutsceneSeq);

    Mod.Super(CutsceneSeq->classID, SUPER_LATEUPDATE, NULL);

    self->visible = true;
}

void CutsceneSeq_Draw(void)
{
    RSDK_THIS(CutsceneSeq);

    if (self->skipType) {
        int32 alphaStore = self->alpha;
        int32 inkStore   = self->inkEffect;

        Mod_CutsceneSeq->skipPos.x = TO_FIXED(ScreenInfo[SceneInfo->currentScreenID].size.x - 25);
        Mod_CutsceneSeq->skipPos.y = TO_FIXED(16);

        if (HUD) {
            foreach_all(HUD, hud)
            {
                if (hud->lifePos.x == TO_FIXED(16))
                    Mod_CutsceneSeq->skipPos.y = TO_FIXED(41);
            }
        }

        self->inkEffect = INK_ALPHA;

        int32 opacity = (int32)(0x100 * config.vDPadOpacity);

        if ((SceneInfo->state & 3) == ENGINESTATE_REGULAR) {
            if (Mod_CutsceneSeq->dpadAlpha < opacity)
                Mod_CutsceneSeq->dpadAlpha += 4;

            if (ControllerInfo->keyStart.down)
                self->alpha = opacity;
            else
                self->alpha = Mod_CutsceneSeq->dpadAlpha;
            Mod_CutsceneSeq->dpadArrowAnimator.frameID = 4;
            RSDK.DrawSprite(&Mod_CutsceneSeq->dpadArrowAnimator, &Mod_CutsceneSeq->skipPos, true);
        }
        else {
            Mod_CutsceneSeq->dpadAlpha = 0;
        }

        self->alpha     = alphaStore;
        self->inkEffect = inkStore;
    }

    Mod.Super(CutsceneSeq->classID, SUPER_DRAW, NULL);
}

void CutsceneSeq_Create(void *data)
{
    RSDK_THIS(CutsceneSeq);

    ControllerInfo->keyStart.press |= CheckTouchPause();

    Mod.Super(CutsceneSeq->classID, SUPER_CREATE, data);

    self->visible = true;
}

void CutsceneSeq_StageLoad(void)
{
    Mod.Super(CutsceneSeq->classID, SUPER_STAGELOAD, NULL);

    Mod_CutsceneSeq->dpadFrames = RSDK.LoadSpriteAnimation("Global/TouchControls.bin", SCOPE_STAGE);

    RSDK.SetSpriteAnimation(Mod_CutsceneSeq->dpadFrames, 2, &Mod_CutsceneSeq->dpadArrowAnimator, true, 0);
}
#endif
