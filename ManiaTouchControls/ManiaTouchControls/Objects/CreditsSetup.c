#include "CreditsSetup.h"
#include "FXFade.h"

ObjectCreditsSetup *CreditsSetup;

void CreditsSetup_StaticUpdate(void)
{
    Mod.Super(CreditsSetup->classID, SUPER_STATICUPDATE, NULL);

    if (CreditsSetup->started && !CreditsSetup->skipped) {
        if (TouchInfo->count) {
            CreditsSetup->skipped = true;

            EntityFXFade *fade = CreditsSetup->fxFade;

            fade->state    = Mod.GetPublicFunction(NULL, "FXFade_State_FadeIn");
            fade->speedIn  = 8;
            fade->wait     = 64;
            fade->speedOut = 8;
            fade->timer    = 0;
            fade->oneWay   = false;

            void (*Music_FadeOut)(float speed) = Mod.GetPublicFunction(NULL, "Music_FadeOut");
            if (Music_FadeOut)
                Music_FadeOut(0.0125f);
        }
    }
}
