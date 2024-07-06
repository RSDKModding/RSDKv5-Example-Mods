#include "../All.h"
#if MANIA_USE_PLUS
ObjectMainMenu *MainMenu;

bool32 (*MathHelpers_PointInHitbox)(int32 thisX1, int32 thisY1, int32 otherX1, int32 otherY1, int32 direction, Hitbox *hitbox);

void MainMenu_StaticUpdate(void)
{
    if (MainMenu->menuControl) {
        foreach_all(UIDiorama, diorama)
        {
            int32 x = MainMenu->menuControl->startPos.x - MainMenu->menuControl->cameraOffset.x;
            int32 y = MainMenu->menuControl->startPos.y - MainMenu->menuControl->cameraOffset.y;

            Hitbox hitbox;
            hitbox.right  = (((MainMenu->menuControl->size.x) >> 17) + extraWidth);
            hitbox.left   = -(((MainMenu->menuControl->size.x) >> 17) + extraWidth);
            hitbox.bottom = (MainMenu->menuControl->size.y >> 17);
            hitbox.top    = -(MainMenu->menuControl->size.y >> 17);

            if (MathHelpers_PointInHitbox(x, y, diorama->position.x, diorama->position.y, FLIP_NONE, &hitbox)) {
                MainMenu->diorama = diorama;
                diorama->parent   = MainMenu->menuControl;
            }
        }
    }

    Mod.Super(MainMenu->classID, SUPER_STATICUPDATE, NULL);
}
#endif
