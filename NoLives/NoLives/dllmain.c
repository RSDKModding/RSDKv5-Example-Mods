#include "../GameAPI/C/GameAPI/Game.h"

#include "Objects/Player.h"
#include "Objects/HUD.h"

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);
#endif

void InitModAPI(void)
{
    // Register State Hooks
    Mod.RegisterStateHook(Mod.GetPublicFunction(NULL, "Player_State_Die"), Player_State_Die_Hook, false);
    Mod.RegisterStateHook(Mod.GetPublicFunction(NULL, "Player_State_Drown"), Player_State_Drown_Hook, false);

    // Register Modded Objects
    MOD_REGISTER_OBJ_OVERLOAD(HUD, NULL, NULL, NULL, HUD_Draw, NULL, NULL, NULL, NULL, NULL);
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