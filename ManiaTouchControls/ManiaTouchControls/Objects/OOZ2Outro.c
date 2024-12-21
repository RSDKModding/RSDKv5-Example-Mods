#include "OOZ2Outro.h"
#include "../Helpers.h"
#include "../ModConfig.h"

#if MANIA_USE_PLUS
ObjectOOZ2Outro *OOZ2Outro;
ModObjectOOZ2Outro *Mod_OOZ2Outro;

StateMachine(OOZ2Outro_State_BoardSub)    = NULL;
StateMachine(OOZ2Outro_State_SubActivate) = NULL;

bool32 OOZ2Outro_State_Hook(bool32 skipped)
{
    ControllerInfo->keyStart.press |= CheckTouchPause();
    return false;
}

void OOZ2Outro_ModCB_OnDraw(void *data)
{
    int32 group = VOID_TO_INT(data);

    if (OOZ2Outro && group == DRAWGROUP_COUNT - 1)
        OOZ2Outro_DrawUI();
}

void OOZ2Outro_DrawUI(void)
{
    RSDK_THIS(OOZ2Outro);

    int32 alphaStore = self->alpha;
    int32 inkStore   = self->inkEffect;

    Mod_OOZ2Outro->skipPos.x = TO_FIXED(ScreenInfo[SceneInfo->currentScreenID].size.x - 25);
    Mod_OOZ2Outro->skipPos.y = TO_FIXED(16);

    self->inkEffect = INK_ALPHA;

    int32 opacity = (int32)(0x100 * config.vDPadOpacity);

    bool32 canSkip = false;
    foreach_active(OOZ2Outro, outro)
    {
        if (outro->state == OOZ2Outro_State_BoardSub || outro->state == OOZ2Outro_State_SubActivate)
            canSkip = true;
    }

    if (canSkip) {
        if ((SceneInfo->state & 3) == ENGINESTATE_REGULAR) {
            if (Mod_OOZ2Outro->dpadAlpha < opacity)
                Mod_OOZ2Outro->dpadAlpha += 4;

            if (ControllerInfo->keyStart.down)
                self->alpha = opacity;
            else
                self->alpha = Mod_OOZ2Outro->dpadAlpha;
            Mod_OOZ2Outro->dpadArrowAnimator.frameID = 4;
            RSDK.DrawSprite(&Mod_OOZ2Outro->dpadArrowAnimator, &Mod_OOZ2Outro->skipPos, true);
        }
        else {
            Mod_OOZ2Outro->dpadAlpha = 0;
        }
    }
    else {
        if (Mod_OOZ2Outro->dpadAlpha > 0)
            Mod_OOZ2Outro->dpadAlpha -= 8;

        self->alpha = Mod_OOZ2Outro->dpadAlpha;
        if (self->alpha > 0) {
            Mod_OOZ2Outro->dpadArrowAnimator.frameID = 4;
            RSDK.DrawSprite(&Mod_OOZ2Outro->dpadArrowAnimator, &Mod_OOZ2Outro->skipPos, true);
        }
    }

    self->alpha     = alphaStore;
    self->inkEffect = inkStore;
}

void OOZ2Outro_StageLoad(void)
{
    Mod.Super(OOZ2Outro->classID, SUPER_STAGELOAD, NULL);

    Mod_OOZ2Outro->dpadFrames = RSDK.LoadSpriteAnimation("Global/TouchControls.bin", SCOPE_STAGE);

    RSDK.SetSpriteAnimation(Mod_OOZ2Outro->dpadFrames, 2, &Mod_OOZ2Outro->dpadArrowAnimator, true, 0);
}
#endif
