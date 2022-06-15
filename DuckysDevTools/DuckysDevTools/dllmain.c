#include "../GameAPI/C/GameAPI/Game.h"

#include "Objects/Player.h"
#include "Objects/HUD.h"
#include "Objects/BSS_HUD.h"

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);
#endif

void InitModAPI(void)
{
    // Register State Hooks
    Mod.RegisterStateHook(Mod.GetPublicFunction(NULL, "Player_Input_P1"), Player_Input_P1_Hook, true);

    // Register Modded Objects
    Mod.RegisterObject((Object **)&BSS_HUD, "BSS_HUD", sizeof(EntityBSS_HUD), sizeof(ObjectBSS_HUD), NULL, NULL, BSS_HUD_StaticUpdate, BSS_HUD_Draw,
                       NULL, NULL, NULL, NULL, NULL, "BSS_HUD");
    Mod.RegisterObject((Object **)&Player, "Player", sizeof(EntityPlayer), sizeof(ObjectPlayer), NULL, NULL, NULL, NULL, NULL, Player_StageLoad, NULL,
                       NULL, NULL, "Player");
    Mod.RegisterObject((Object **)&HUD, "HUD", sizeof(EntityHUD), sizeof(ObjectHUD), NULL, NULL, NULL, HUD_Draw, NULL, NULL, NULL, NULL, NULL, "HUD");
}

#if RETRO_USE_MOD_LOADER
#define ADD_PUBLIC_FUNC(func) Mod.AddPublicFunction(#func, (void *)(func))

void InitModAPI(void);

bool32 LinkModLogic(EngineInfo *info, const char *id)
{
#if MANIA_USE_PLUS
    LinkGameLogicDLL(info);
#else
    LinkGameLogicDLL(*info);
#endif

    globals = Mod.GetGlobals();

    modID = id;

    InitModAPI();

    return true;
}
#endif