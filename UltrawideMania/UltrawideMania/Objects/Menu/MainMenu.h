#if MANIA_USE_PLUS
#ifndef MAINMENU_H
#define MAINMENU_H

struct ObjectMainMenu {
    RSDK_OBJECT
    EntityUIControl *menuControl;
    void *confirmPrompt; // EntityUIButtonPrompt
    EntityUIDiorama *diorama;
};

// Entity Class
struct EntityMainMenu {
    RSDK_ENTITY
};

void MainMenu_StaticUpdate(void);

extern ObjectMainMenu *MainMenu;

extern bool32 (*MathHelpers_PointInHitbox)(int32 thisX1, int32 thisY1, int32 otherX1, int32 otherY1, int32 direction, Hitbox *hitbox);
#endif
#endif
