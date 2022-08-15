#include "../../ModConfig.h"

ObjectUIDiorama *UIDiorama;

void UIDiorama_Update(void) {
    Mod.Super(UIDiorama->classID, SUPER_UPDATE, NULL);    

    RSDK_THIS(UIDiorama);
}

void UIDiorama_Create(void* data)
{
    RSDK_THIS(UIDiorama);

    Mod.Super(UIDiorama->classID, SUPER_CREATE, data);

    self->position.x -= extraWidth << 16;
}
