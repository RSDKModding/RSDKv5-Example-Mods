#include "../GameAPI/C/GameAPI/Game.h"

#include "Objects/Player.h"
#include "Objects/HUD.h"
#include "Objects/BSS_HUD.h"
#include "Objects/COverlay.h"

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);
#endif

void InitModAPI(void)
{
    // Register State Hooks
    Mod.RegisterStateHook(Mod.GetPublicFunction(NULL, "Player_Input_P1"), Player_Input_P1_Hook, true);

    // Register Modded Objects
    MOD_REGISTER_OBJ_OVERLOAD(BSS_HUD, NULL, NULL, BSS_HUD_StaticUpdate, BSS_HUD_Draw, NULL, NULL, NULL, NULL, NULL);
    MOD_REGISTER_OBJ_OVERLOAD(HUD, NULL, NULL, NULL, HUD_Draw, NULL, NULL, NULL, NULL, NULL);
    MOD_REGISTER_OBJ_OVERLOAD(Player, NULL, NULL, NULL, NULL, NULL, Player_StageLoad, NULL, NULL, NULL);
    MOD_REGISTER_OBJ_OVERLOAD(COverlay, NULL, NULL, NULL, COverlay_Draw, NULL, NULL, NULL, NULL, NULL);

    // Get Public Funcs
    Player_ChangeCharacter = Mod.GetPublicFunction(NULL, "Player_ChangeCharacter");

    HUD_DrawNumbersBase16 = Mod.GetPublicFunction(NULL, "HUD_DrawNumbersBase16");
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