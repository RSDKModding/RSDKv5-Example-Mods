#include "All.h"


void UIDiorama_Create(void* data)
{
    RSDK_THIS(UIDiorama);

    Object *uiDiorama = Mod.FindObject("UIDiorama");
    Mod.Super(uiDiorama->classID, SUPER_CREATE, data);

    self->position.x -= (ScreenInfo->width - 424) / 2;
}
