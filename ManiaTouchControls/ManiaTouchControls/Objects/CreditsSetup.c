#include "CreditsSetup.h"
#include "../ModConfig.h"
#include "../Helpers.h"

ObjectCreditsSetup *CreditsSetup;
ModObjectCreditsSetup *Mod_CreditsSetup;

void CreditsSetup_StaticUpdate(void)
{
    RSDK_THIS(CreditsSetup);

    if (!CreditsSetup->skipped) {
        if (CheckTouchPause())
            ControllerInfo->keyStart.press |= true;
        else
            ControllerInfo->keyA.down |= TouchInfo->count;
    }

    Mod.Super(CreditsSetup->classID, SUPER_STATICUPDATE, NULL);
}

void CreditsSetup_ModCB_OnDraw(void *data)
{
    int32 group = VOID_TO_INT(data);

    if (CreditsSetup && group == DRAWGROUP_COUNT - 4) // Draw under the FXFade
        CreditsSetup_DrawUI();
}

void CreditsSetup_DrawUI(void)
{
    RSDK_THIS(CreditsSetup);

    int32 alphaStore   = self->alpha;
    int32 inkStore     = self->inkEffect;

    Mod_CreditsSetup->skipPos.x = TO_FIXED(ScreenInfo[SceneInfo->currentScreenID].size.x - 25);
    Mod_CreditsSetup->skipPos.y = TO_FIXED(16);

    self->inkEffect = INK_ALPHA;

    int32 opacity = (int32)(0x100 * config.vDPadOpacity);

    if (Mod_CreditsSetup->dpadAlpha < opacity)
        Mod_CreditsSetup->dpadAlpha += 4;

    if ((SceneInfo->state & 3) == ENGINESTATE_REGULAR) {
        if (ControllerInfo->keyStart.down)
            self->alpha = opacity;
        else
            self->alpha = Mod_CreditsSetup->dpadAlpha;
        Mod_CreditsSetup->dpadArrowAnimator.frameID = 4;
        RSDK.DrawSprite(&Mod_CreditsSetup->dpadArrowAnimator, &Mod_CreditsSetup->skipPos, true);
    }
    else {
        Mod_CreditsSetup->dpadAlpha = 0;
    }

    self->alpha     = alphaStore;
    self->inkEffect = inkStore;
}

void CreditsSetup_StageLoad(void)
{
    Mod.Super(CreditsSetup->classID, SUPER_STAGELOAD, NULL);

    Mod_CreditsSetup->dpadFrames = RSDK.LoadSpriteAnimation("Global/TouchControls.bin", SCOPE_STAGE);
    Mod_CreditsSetup->dpadAlpha  = 0;

    RSDK.SetSpriteAnimation(Mod_CreditsSetup->dpadFrames, 2, &Mod_CreditsSetup->dpadArrowAnimator, true, 0);
}
