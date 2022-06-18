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
#endif