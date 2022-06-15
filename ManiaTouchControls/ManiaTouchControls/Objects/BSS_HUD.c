#include "BSS_HUD.h"

ObjectBSS_HUD *BSS_HUD;

void BSS_HUD_Draw(void)
{
    RSDK_THIS(BSS_HUD);

    Mod.Super(BSS_HUD->classID, SUPER_DRAW, NULL);
}
